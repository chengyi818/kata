/*
 * File Name: main.js
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Wed 01 May 2019 07:03:47 PM CST
 */

var hello = require('./hello');
hello.world();

var hello2 = require('./hello2');
hello = new hello2();
hello.setName('BYVoid');
hello.sayHello();
