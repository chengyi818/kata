/*
 * File Name: slice_bounds.go
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Thu 04 Apr 2019 10:19:42 AM CST
 */

// 1. 默认起始边界0
// 2. 默认结束边界为数组长度
package main

import "fmt"

func main() {
	s := []int{2, 3, 5, 7, 11, 13}

	s = s[1:4]
	printSlice(s)

	s = s[:2]
	printSlice(s)

	s = s[1:]
	printSlice(s)
}

func printSlice(s []int) {
	fmt.Printf("len=%d cap=%d %v\n", len(s), cap(s), s)
}
