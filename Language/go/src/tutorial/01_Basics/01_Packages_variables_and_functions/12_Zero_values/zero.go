/*
 * File Name: zero.go
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Wed 03 Apr 2019 03:52:09 PM CST
 */

/**
1. 未初始化的变量会被赋予默认值0
2. 数值类型为0
3. 布尔类型为false
4. 字符串为""
*/

package main

import "fmt"

func main() {
	var i int
	var f float64
	var b bool
	var s string
	fmt.Printf("%v %v %v %q\n", i, f, b, s)
}
