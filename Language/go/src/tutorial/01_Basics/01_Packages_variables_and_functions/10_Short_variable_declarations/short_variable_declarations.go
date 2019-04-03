/*
 * File Name: short_variable_declarations.go
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Wed 03 Apr 2019 03:44:02 PM CST
 */

/**
1. 函数内可以使用 := 来声明并初始化变量
*/

package main

import "fmt"

func main() {
	var i, j int = 1, 2
	k := 3
	c, python, java := true, false, "no!"

	fmt.Println(i, j, k, c, python, java)
}
