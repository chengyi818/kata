/*
 * File Name: interfaces_are_satisfied_implicitly.go
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Thu 04 Apr 2019 03:49:43 PM CST
 */

// 1. 隐式实现接口,只要对象拥有接口声明的方法即可

package main

import "fmt"

type I interface {
	M()
	// P()
}

type T struct {
	S string
}

// This method means type T implements the interface I,
// but we don't need to explicitly declare that it does so.
func (t *T) M() {
	fmt.Println(t.S)
}

func main() {
	var i I = &T{"hello"}
	i.M()
}
