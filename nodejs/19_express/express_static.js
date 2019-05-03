/*
 * File Name: express_static.js
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Fri 03 May 2019 08:40:01 PM CST
 */

var express = require('express');
var app = express();

app.use('/public', express.static('public'));

app.get('/', function(req, res) {
    res.send('Hello World');
});

var server = app.listen(8081, function() {

    var host = server.address().address;
    var port = server.address().port;

    console.log("应用实例，访问地址为 http://%s:%s", host, port);

});
