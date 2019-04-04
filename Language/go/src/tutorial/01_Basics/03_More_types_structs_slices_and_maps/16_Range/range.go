/*
 * File Name: range.go
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Thu 04 Apr 2019 10:58:40 AM CST
 */

// 1. range类似于python的enumerate
package main

import "fmt"

var pow = []int{1, 2, 4, 8, 16, 32, 64, 128}

func main() {
	for i, v := range pow {
		fmt.Printf("2**%d = %d\n", i, v)
	}
}
