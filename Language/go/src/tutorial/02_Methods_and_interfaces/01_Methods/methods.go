/*
 * File Name: methods.go
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Thu 04 Apr 2019 02:59:16 PM CST
 */

package main

import (
	"fmt"
	"math"
)

type Vertex struct {
	X, Y float64
}

func (v Vertex) Abs() float64 {
	return math.Sqrt(v.X*v.X + v.Y*v.Y)
}

func main() {
	v := Vertex{3, 4}
	fmt.Println(v.Abs())
}
