/*
 * File Name: named_results.go
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Wed 03 Apr 2019 03:21:30 PM CST
 */

/**
仅适用于短函数
*/
package main

import "fmt"

func split(sum int) (x, y int) {
	x = sum * 4 / 9
	y = sum - x
	return
}

func split_2(sum int) (int, int) {
	var x,y int
	x = sum * 4 / 9
	y = sum - x
	return x, y
}

func main() {
	fmt.Println(split(17))
	fmt.Println(split_2(17))
}
