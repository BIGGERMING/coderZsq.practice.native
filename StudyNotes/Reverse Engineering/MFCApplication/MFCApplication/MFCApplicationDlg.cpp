
// MFCApplicationDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApplication.h"
#include "MFCApplicationDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static CMFCApplicationDlg * g_dlg = NULL;

static HANDLE g_game = NULL;

static HANDLE g_monitorThread = NULL;

void WriteMemory(void * value, DWORD valueSize, ...) {
	if (value == NULL || valueSize == 0 || g_game == NULL) return;
	DWORD tempValue = 0;
	va_list addresses;
	va_start(addresses, valueSize);
	DWORD offset = 0;
	DWORD lastAddress = 0;
	while ((offset = va_arg(addresses, DWORD)) != -1) {
		lastAddress = tempValue + offset;
		ReadProcessMemory(g_game, (LPCVOID)lastAddress, &tempValue, sizeof(DWORD), NULL);
	}
	va_end(addresses);
	WriteProcessMemory(g_game, (LPVOID)lastAddress, value, valueSize, NULL);
}

void WriteMemory(void * value, DWORD valueSize, DWORD address) {
	WriteMemory(value, valueSize, address, -1);
}

DWORD WINAPI monitorThreadFunc(LPVOID lpThread) {
	while (true) {
		HWND window = FindWindow(CString("MainWindow"), CString("植物大战僵尸中文版"));
		if (!window) {
			g_dlg->m_kill.EnableWindow(false);
			g_dlg->m_sun.EnableWindow(false);
			g_dlg->m_kill.SetCheck(false);
			g_dlg->m_sun.SetCheck(false);
		}
		else if (!g_game) {
			DWORD pid = NULL;
			GetWindowThreadProcessId(window, &pid);
			g_game = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
			g_dlg->m_kill.EnableWindow(true);
			g_dlg->m_sun.EnableWindow(true);
		}
		if (g_dlg->m_sun.GetCheck()) {
			DWORD value = 9990;
			WriteMemory(&value, sizeof(value), 0x6A9EC0, 0x320, 0x8, 0x0, 0x8, 0x144, 0x2c, 0x5560, -1);
		}
		Sleep(1000);
	}
	return 0;
}

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplicationDlg dialog



CMFCApplicationDlg::CMFCApplicationDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplicationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SUN, m_sun);
	DDX_Control(pDX, IDC_KILL, m_kill);
}

BEGIN_MESSAGE_MAP(CMFCApplicationDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_GITHUB, CMFCApplicationDlg::OnBnClickedGitHub)
	ON_BN_CLICKED(IDC_SUN, &CMFCApplicationDlg::OnBnClickedSun)
	ON_BN_CLICKED(IDC_KILL, &CMFCApplicationDlg::OnBnClickedKill)
END_MESSAGE_MAP()


// CMFCApplicationDlg message handlers

BOOL CMFCApplicationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	g_dlg = this;
	g_monitorThread = CreateThread(NULL, 0, monitorThreadFunc, NULL, 0, NULL);
	// TerminateThread(g_monitorThread, 0);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCApplicationDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCApplicationDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCApplicationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMFCApplicationDlg::OnBnClickedGitHub() {
	ShellExecute(
		NULL,
		CString("open"),
		CString("https://github.com/coderZsq"),
		NULL, NULL, SW_SHOWNORMAL
	);
}


void CMFCApplicationDlg::OnBnClickedSun()
{
	if (m_sun.GetCheck()) {
	
	}
	else {
	
	}
	m_sun.SetCheck(true);
}


void CMFCApplicationDlg::OnBnClickedKill()
{
	DWORD address = 0x531310;
	if (this->m_kill.GetCheck()) {
		BYTE value = 0xFF;
		WriteMemory(&value, sizeof(value), address);
	}
	else {
		BYTE value = 0x7C;
		WriteMemory(&value, sizeof(value), address);
	}
}
