/*
 * File Name: Formatting.go
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Tue 09 Apr 2019 05:25:23 PM CST
 */
package main

import (
	"fmt"
)

// type T struct {
// 	name  string // name of the object
// 	value int    // its value
// }

func main() {
	x := 1
	y := 1
	c := x<<8 + y<<16
	fmt.Println(c)

	i := 5
	if i < 10 {
		fmt.Println(i)
	}
}
