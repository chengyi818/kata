/*
 * File Name: get.js
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Wed 01 May 2019 09:41:08 PM CST
 */

var http = require('http');
var url = require('url');
var util = require('util');

http.createServer(function(req, res){
    res.writeHead(200, {'Content-Type': 'text/plain'});

    res.end(util.inspect(url.parse(req.url, true)));
    // 解析 url 参数
    // var params = url.parse(req.url, true).query;
    // res.write("网站名：" + params.name);
    // res.write("\n");
    // res.write("网站 URL：" + params.url);
    // res.end();

}).listen(3000);
