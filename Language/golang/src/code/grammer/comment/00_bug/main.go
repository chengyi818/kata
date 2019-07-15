/*
 * File Name: main.go
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Tue 02 Jul 2019 02:15:16 PM CST
 */

// Package main.
package main

import "fmt"

func main() {
	// BUG(astaxie):This divides by zero.
	var i int = 1 / 0
	fmt.Println(i)
}
