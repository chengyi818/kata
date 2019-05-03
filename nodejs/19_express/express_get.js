/*
 * File Name: server.js
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Fri 03 May 2019 08:44:06 PM CST
 */

var express = require('express');
var app = express();

app.use('/public', express.static('public'));

app.get('/index.htm', function(req, res) {
    res.sendFile(__dirname + "/" + "get_index.htm");
});

app.get('/process_get', function(req, res) {

    // 输出 JSON 格式
    var response = {
        "first_name": req.query.first_name,
        "last_name": req.query.last_name
    };
    console.log(response);
    res.end(JSON.stringify(response));
});

var server = app.listen(8081, function() {

    var host = server.address().address;
    var port = server.address().port;

    console.log("应用实例，访问地址为 http://%s:%s", host, port);

});
