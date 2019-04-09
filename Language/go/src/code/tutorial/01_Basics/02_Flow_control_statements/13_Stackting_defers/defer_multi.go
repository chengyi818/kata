/*
 * File Name: defer_multi.go
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Wed 03 Apr 2019 05:49:10 PM CST
 */

/**
1. defer语句会逐个压栈
2. 在return执行时,会后进先出
*/
package main

import "fmt"

func main() {
	fmt.Println("counting")

	for i := 0; i < 10; i++ {
		defer fmt.Println(i)
	}

	fmt.Println("done")
}
