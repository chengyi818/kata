/*
 * File Name: nil_interface_values.go
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Thu 04 Apr 2019 04:25:53 PM CST
 */

package main

import "fmt"

type I interface {
	M()
}

func main() {
	var i I
	describe(i)
	// Error: (接口, 实现)不存在,不能直接调用
	// i.M()
}

func describe(i I) {
	fmt.Printf("(%v, %T)\n", i, i)
}
