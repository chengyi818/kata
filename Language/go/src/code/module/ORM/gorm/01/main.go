/*
 * File Name: main.go
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Wed 17 Apr 2019 05:10:48 PM CST
 */

package main

import (
	"github.com/jinzhu/gorm"
	_ "github.com/jinzhu/gorm/dialects/sqlite"
)


// 声明数据库表的形式

type Product struct {
	gorm.Model
	Code string
	Price uint
}

func main() {
	// 建立连接
	db, err := gorm.Open("sqlite3", "test.db")
	if err != nil {
		panic("failed to connect database")
	}
	defer db.Close()

	// 生成数据库表
	db.AutoMigrate(&Product{})

	// 新增一条记录：将Product 对象转换成数据库内一条记录
	db.Create(&Product{Code: "L1212", Price: 1000})

	// 获取对象：将数据库内一条记录转换成 product 对象
	var product Product
	db.First(&product, 1) // find product with id 1
	db.First(&product, "code = ?", "L1212") // find product with code l1212

	// 更新记录
	db.Model(&product).Update("Price", 2000)

	// 删除记录
	db.Delete(&product)
}
