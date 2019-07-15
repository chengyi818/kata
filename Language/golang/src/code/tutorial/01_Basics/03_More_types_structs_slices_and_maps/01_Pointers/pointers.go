/*
 * File Name: pointers.go
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Wed 03 Apr 2019 06:03:06 PM CST
 */

/**
1. go不支持指针运算,即没有p++之类的
*/
package main

import "fmt"

func main() {
	var p *int
	i, j := 42, 2701

	// p := &i         // point to i
	p = &i
	fmt.Println(*p) // read i through the pointer
	*p = 21         // set i through the pointer
	fmt.Println(i)  // see the new value of i

	p = &j         // point to j
	*p = *p / 37   // divide j through the pointer
	fmt.Println(j) // see the new value of j
}
