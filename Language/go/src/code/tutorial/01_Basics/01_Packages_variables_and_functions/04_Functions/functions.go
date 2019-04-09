/*
 * File Name: functions.go
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Wed 03 Apr 2019 03:07:46 PM CST
 */
/**
 * 注意go类型声明的位置
 * https://blog.golang.org/gos-declaration-syntax
*/

package main

import "fmt"

func add(x int, y int) int {
	return x + y
}

func main() {
	fmt.Println(add(42, 13))
}
