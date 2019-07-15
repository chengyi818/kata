/*
 * File Name: variables_with_initializers.go
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Wed 03 Apr 2019 03:41:42 PM CST
 */

/**
1. 声明并初始化变量
2. 变量类型可省略
*/

package main

import "fmt"

var i, j int = 1, 2
var x, y = 1, 2

func main() {
	var c, python, java = true, false, "no!"
	fmt.Println(i, j, x, y, c, python, java)
}
