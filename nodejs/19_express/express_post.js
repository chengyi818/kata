/*
 * File Name: express_post.js
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Fri 03 May 2019 08:47:57 PM CST
 */

var express = require('express');
var app = express();
var bodyParser = require('body-parser');

// 创建 application/x-www-form-urlencoded 编码解析
var urlencodedParser = bodyParser.urlencoded({
    extended: false
});

app.use('/public', express.static('public'));

app.get('/index.htm', function(req, res) {
    res.sendFile(__dirname + "/" + "index.htm");
});

app.post('/process_post', urlencodedParser, function(req, res) {

    // 输出 JSON 格式
    var response = {
        "first_name": req.body.first_name,
        "last_name": req.body.last_name
    };
    console.log(response);
    res.end(JSON.stringify(response));
});

var server = app.listen(8081, function() {
    var host = server.address().address;
    var port = server.address().port;

    console.log("应用实例，访问地址为 http://%s:%s", host, port);

});
