/*
 * File Name: makeing_slices.go
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Thu 04 Apr 2019 10:38:43 AM CST
 */

// 1. 通过内置函数make创建动态大小的数组
package main

import "fmt"

func main() {
	// 长度为5
	a := make([]int, 5)
	printSlice("a", a)

	// 长度为0, 容量为5
	b := make([]int, 0, 5)
	printSlice("b", b)

	c := b[:2]
	printSlice("c", c)

	d := c[2:5]
	printSlice("d", d)
}

func printSlice(s string, x []int) {
	fmt.Printf("%s len=%d cap=%d %v\n",
		s, len(x), cap(x), x)
}
