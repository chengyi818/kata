/*
 * File Name: interface_values_with_nil.go
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Thu 04 Apr 2019 04:14:18 PM CST
 */

// 1. 接口和实现的关系类似于 (接口, 实现) 的元组
// 2. 在接口上调用方法,会执行实现的方法
// 3. 实现为nil,并不代表接口为nil

package main

import "fmt"

type I interface {
	M()
}

type T struct {
	S string
}

func (t *T) M() {
	// 处理对象为nil的情况,在go中比较常见
	if t == nil {
		fmt.Println("<nil>")
		return
	}
	fmt.Println(t.S)
}

func main() {
	var i I

	// 空指针
	var t *T
	i = t
	describe(i)
	i.M()

	// i != nil
	fmt.Println(i == nil)
	// t = nil
	fmt.Println(t == nil)

	i = &T{"hello"}
	describe(i)
	i.M()
}

func describe(i I) {
	fmt.Printf("(%v, %T)\n", i, i)
}
