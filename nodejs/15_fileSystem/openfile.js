/*
 * File Name: openfile.js
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Wed 01 May 2019 09:28:25 PM CST
 */

var fs = require("fs");

// 异步打开文件
console.log("准备打开文件！");
fs.open('input.txt', 'r+', function(err, fd) {
    if (err) {
        return console.error(err);
    }
    console.log("文件打开成功！");

    fs.stat('input.txt', function (err, stats) {
        if (err) {
            return console.error(err);
        }
        console.log(stats);
        console.log("读取文件信息成功！");

        // 检测文件类型
        console.log("是否为文件(isFile) ? " + stats.isFile());
        console.log("是否为目录(isDirectory) ? " + stats.isDirectory());
    });
});
