/*
 * File Name: for_is_gos_while.go
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Wed 03 Apr 2019 04:28:02 PM CST
 */

/**
1. go语言中的for可以充当c语言中的while使用
*/

package main

import "fmt"

func main() {
	sum := 1
	for sum < 1000 {
		sum += sum
	}
	fmt.Println(sum)
}
