/*
 * File Name: type_conversions.go
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Wed 03 Apr 2019 03:54:16 PM CST
 */
/**
1. Go类型转换
2. Go语言必须显式进行类型转换
*/

package main

import (
	"fmt"
	"math"
)

func main() {
	var x, y int = 3, 4
	var f float64 = math.Sqrt(float64(x*x + y*y))
	var z uint = uint(f)
	// var z uint = f          // error
	fmt.Println(x, y, z, f)
}
