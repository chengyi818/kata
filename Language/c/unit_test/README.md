# 简介
主要学习使用check工具来进行c的单元测试

## main page
https://libcheck.github.io/check/doc/check_html/index.html#Top


## tutorial
https://libcheck.github.io/check/doc/check_html/check_3.html


## Install
```
$git clone git@github.com:libcheck/check.git
$autoreconf --install
$./configure --prefix=/usr/local/stow/check
$make
$make check
$sudo make install
$cd /usr/local/stow
$sudo stow check
$sudo ldconfig
```

## Error
```
 * existing target is neither a link nor a directory: share/info/dir
```

```
$sudo vi /usr/local/stow/.stowrc
input --ignore=share/info/dir
```
