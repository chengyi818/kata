/*
 * File Name: indirection.go
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Thu 04 Apr 2019 03:34:29 PM CST
 */

// 1. 函数定义入参必须类型严格一致
// 2. 方法调用,使用指针或者类型都可以

package main

import "fmt"

type Vertex struct {
	X, Y float64
}

func (v *Vertex) Scale(f float64) {
	v.X = v.X * f
	v.Y = v.Y * f
}

// error: method redeclared
// func (v Vertex) Scale(f float64) {
// 	v.X = v.X * f * 2
// 	v.Y = v.Y * f * 2
// }

func ScaleFunc(v *Vertex, f float64) {
	v.X = v.X * f
	v.Y = v.Y * f
}

func main() {
	v := Vertex{3, 4}
	v.Scale(2)
	ScaleFunc(&v, 10)

	p := &Vertex{4, 3}
	p.Scale(3)
	ScaleFunc(p, 8)

	fmt.Println(v, p)
}
