/*
 * File Name: demo.js
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Wed 01 May 2019 10:59:25 PM CST
 */

//express_demo.js 文件
var express = require('express');
var app = express();

app.get('/', function(req, res) {
    console.log("req.route: %s", req.route);
    res.send('Hello World');
});

var server = app.listen(8081, function() {

    var host = server.address().address;
    var port = server.address().port;

    console.log("应用实例，访问地址为 http://%s:%s", host, port);
});
