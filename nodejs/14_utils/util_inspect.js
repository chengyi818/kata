/*
 * File Name: util_inspect.js
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Wed 01 May 2019 09:12:21 PM CST
 */

var util = require('util');
function Person() {
    this.name = 'byvoid';
    this.toString = function() {
        return this.name;
    };
}
var obj = new Person();
console.log(util.inspect(obj));
console.log(util.inspect(obj, true));
