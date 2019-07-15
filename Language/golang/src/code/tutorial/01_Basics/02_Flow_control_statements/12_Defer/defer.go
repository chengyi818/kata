/*
 * File Name: defer.go
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Wed 03 Apr 2019 05:47:46 PM CST
 */

/**
1. defer关键字 用于推迟函数的执行
2. 在函数return前,执行?
3. 参数会立刻展开,但执行会推迟
*/
package main

import "fmt"

func main() {
	defer fmt.Println("world")

	fmt.Println("hello")

	b()
}

func trace(s string) string {
    fmt.Println("entering:", s)
    return s
}

func un(s string) {
    fmt.Println("leaving:", s)
}

func a() {
    defer un(trace("a"))
    fmt.Println("in a")
}

func b() {
    defer un(trace("b"))
    fmt.Println("in b")
    a()
}
