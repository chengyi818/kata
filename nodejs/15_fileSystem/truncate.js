/*
 * File Name: truncate.js
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Wed 01 May 2019 09:35:15 PM CST
 */

var fs = require("fs");
var buf = new Buffer.alloc(1024);

console.log("准备打开文件！");
fs.open('input.txt', 'r+', function(err, fd) {
    if (err) {
        return console.error(err);
    }
    console.log("文件打开成功！");
    console.log("截取10字节内的文件内容，超出部分将被去除。");

    // 截取文件
    fs.ftruncate(fd, 10, function(err){
        if (err){
            console.log(err);
        }
        console.log("文件截取成功。");
        console.log("读取相同的文件");
        fs.read(fd, buf, 0, buf.length, 0, function(err, bytes){
            if (err){
                console.log(err);
            }

            // 仅输出读取的字节
            if(bytes > 0){
                console.log(buf.slice(0, bytes).toString());
            }

            // 关闭文件
            fs.close(fd, function(err){
                if (err){
                    console.log(err);
                }
                console.log("文件关闭成功！");
            });
        });
    });
});
