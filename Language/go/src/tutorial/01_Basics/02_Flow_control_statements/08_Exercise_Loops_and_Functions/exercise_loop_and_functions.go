/*
 * File Name: exercise_loop_and_functions.go
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Wed 03 Apr 2019 04:40:42 PM CST
 */

package main

import (
	"fmt"
)

func Sqrt(x float64) float64 {
	z := 1.0
	for i:=0; i<10; i++ {
		z -= (z*z - x) / (2*z)
		fmt.Println(z);
	}
	return z
}

func main() {
	fmt.Println(Sqrt(2))
}
