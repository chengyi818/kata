/*
 * File Name: range_and_close.go
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Mon 08 Apr 2019 06:08:54 PM CST
 */

package main

import (
	"fmt"
)

func fibonacci(n int, c chan int) {
	x, y := 0, 1
	for i := 0; i < n; i++ {
		c <- x
		x, y = y, x+y
	}

	fmt.Println("close c")
	// 通知range,内容结束
	close(c)
}

func main() {
	c := make(chan int, 10)
	go fibonacci(cap(c), c)

	for i := range c {
		fmt.Println(i)
	}
}
