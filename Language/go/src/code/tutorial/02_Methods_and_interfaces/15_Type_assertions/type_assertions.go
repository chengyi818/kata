/*
 * File Name: type_assertions.go
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Thu 04 Apr 2019 04:32:44 PM CST
 */

// 1. 检查接口对应的实现的类型,类似python isinstance

package main

import "fmt"

func main() {
	var i interface{} = "hello"

	// 获取接口i对应的实现
	s := i.(string)
	fmt.Println(s)
	describe(s)

	s, ok := i.(string)
	fmt.Println(s, ok)

	f, ok := i.(float64)
	fmt.Println(f, ok)

	// panic
	// f = i.(float64)
	// fmt.Println(f)
}


func describe(i interface{}) {
	fmt.Printf("(%v, %T)\n", i, i)
}
