/*
 * File Name: stringer.go
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Thu 04 Apr 2019 04:45:31 PM CST
 */

// 1. Stringer接口的String()是最常用的接口
// 2. 类似python的repr,自己描述如何打印自己

package main

import "fmt"

type Person struct {
	Name string
	Age  int
}

func (p Person) String() string {
	return fmt.Sprintf("%v (%v years)\n", p.Name, p.Age)
}

func main() {
	x := Person{"Arthur Dent", 42}
	y := Person{"Zaphod Beeblebrox", 9001}
	fmt.Println(x, y)
}
