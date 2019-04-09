/*
 * File Name: nil_slice.go
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Thu 04 Apr 2019 10:36:59 AM CST
 */

// 1. 空的切片 length和capacity 均为0
package main

import "fmt"

func main() {
	var s []int
	fmt.Println(s, len(s), cap(s))

	if s == nil {
		fmt.Println("nil!")
	}
}
