/*
 * File Name: range_continued.go
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Thu 04 Apr 2019 11:13:46 AM CST
 */

// 1. range的其他使用方式,忽略符号_

package main

import "fmt"

func main() {
	pow := make([]int, 10)
	for i := range pow {
		pow[i] = 1 << uint(i) // == 2**i
	}
	for _, value := range pow {
		fmt.Printf("%d\n", value)
	}
}
