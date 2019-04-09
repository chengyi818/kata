/*
 * File Name: methods_continued.go
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Thu 04 Apr 2019 03:19:34 PM CST
 */

// 1. 方法的定义,reciver不一定要是type struct
// 2. 通过type可以增加普通类型的方法
// 3. 增加普通类型的方法,必须通过在本文件中使用type
// 4. 扩充普通类型的方法

package main

import (
	"fmt"
	"math"
)

type MyFloat float64

func (f MyFloat) Abs() float64 {
	if f < 0 {
		return float64(-f)
	}
	return float64(f)
}

func main() {
	f := MyFloat(-math.Sqrt2)
	fmt.Println(f.Abs())
}
