/*
 * File Name: main.go
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Tue 02 Jul 2019 01:51:40 PM CST
 */

package main

import "fmt"

type MyInt int

//BUG:死循环
// func (m MyInt) String() string {
// 	return fmt.Sprint(m)
// }

//这是安全的,因为我们内部进行了类型转换
func (m MyInt) String() string {
	return fmt.Sprint(int(m))
}

func main() {
	var a MyInt = 2
	fmt.Println(a)
}
