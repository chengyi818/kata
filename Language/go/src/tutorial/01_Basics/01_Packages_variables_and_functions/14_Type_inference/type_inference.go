/*
 * File Name: type_inference.go
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Wed 03 Apr 2019 03:57:44 PM CST
 */

/**
1. 变量类型自动推导,依赖于等号右边的变量类型
*/

package main

import "fmt"

func main() {
	i := 42           // int
	f := 3.142        // float64
	g := 0.867 + 0.5i // complex128
	fmt.Printf("i is of type %T\n", i)
	fmt.Printf("f is of type %T\n", f)
	fmt.Printf("g is of type %T\n", g)
}
