/*
 * File Name: fork.js
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Fri 03 May 2019 09:37:24 PM CST
 */

const fs = require('fs');
const child_process = require('child_process');

for (var i = 0; i < 3; i++) {
    var worker_process = child_process.fork("support.js", [i]);

    worker_process.on('close', function(code) {
        console.log('子进程已退出，退出码 ' + code);
    });
}
