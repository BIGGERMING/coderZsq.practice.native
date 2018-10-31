//
//  ViewController.m
//  Business
//
//  Created by 朱双泉 on 2018/10/30.
//  Copyright © 2018 Castie!. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()
@property (nonatomic, copy) NSArray * dataSource;
@end

@implementation ViewController

- (NSArray *)dataSource {
    
    if (!_dataSource) {
        _dataSource = @[@{@"classes" : @[],
                          @"titleheader" : @"practical-tech",
                          @"titlefooter" : @"Some examples of practical-tech learning."}];
    }
    return _dataSource;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return self.dataSource.count;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return [self.dataSource[section][@"classes"] count];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell * cell = [tableView dequeueReusableCellWithIdentifier:@"identifier"];
    if (!cell) {
        cell = [[UITableViewCell alloc]initWithStyle:(UITableViewCellStyleDefault) reuseIdentifier:@"identifier"];
        cell.imageView.image = [UIImage imageNamed:@"Mark"];
    }
    cell.textLabel.text = NSStringFromClass(self.dataSource[indexPath.section][@"classes"][indexPath.row]);
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    [self.navigationController pushViewController:[[UIStoryboard storyboardWithName:NSStringFromClass(self.dataSource[indexPath.section][@"classes"][indexPath.row]) bundle:nil]instantiateInitialViewController] animated:YES];
}

- (NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section {
    return self.dataSource[section][@"titleheader"];
}

- (NSString *)tableView:(UITableView *)tableView titleForFooterInSection:(NSInteger)section {
    return self.dataSource[section][@"titlefooter"];
}


@end
