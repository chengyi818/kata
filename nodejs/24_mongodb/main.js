/*
 * File Name: main.js
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Fri 03 May 2019 09:59:17 PM CST
 */

var MongoClient = require('mongodb').MongoClient;
var url = 'mongodb://localhost:27017/runoob';

MongoClient.connect(url, {
    useNewUrlParser: true
}, function(err, db) {
    if (err) throw err;
    console.log('数据库已创建');

    var dbase = db.db("runoob");
    dbase.createCollection('site', function(err, res) {
        if (err) throw err;
        console.log("创建集合!");
        db.close();
    });
});
