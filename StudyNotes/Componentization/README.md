#### Local Lib

```
$ git init
$ git add .
$ git commit -m"add"
$ pod spec create BaseComponent
```

```
$ pod init
pod 'BaseComponent', :path => './LocalPrivateLib/BaseComponent'
$ pod install
```

#### Remote Lib

```
$ pod repo add ComponentSpecs git@git.dev.tencent.com:dtid_ada36270f1f70012/ComponentSpecs.git
~/.cocoapods/repos/
$ pod repo remove ComponentSpecs
```

```
$ pod lib create BaseComponent
$ pod lib lint  --allow-warnings
```

```
$ git remote add origin git@git.dev.tencent.com:dtid_ada36270f1f70012/BaseComponent.git
$ git remote rm origin
$ git remote
$ git push origin master
```

```
$ git tag '0.1.0'
$ git tag
$ git push --tags
$ git tag -d 0.1.0
$ git push origin: 0.1.0
$ pod spec lint  --allow-warnings
$ pod cache clean BaseComponent
$ pod repo push coderzsq BaseComponent.podspec  --allow-warnings

```

#### Fastlane

```
$ fastlane new_action
$ fastlane action remove_tag
$ fastlane ManagerLib tag:0.1.2 target:RemotePlayerComponent
```

#### Package

```
$ gem install cocoapods-packager
$ pod package BaseComponent.podspec
```