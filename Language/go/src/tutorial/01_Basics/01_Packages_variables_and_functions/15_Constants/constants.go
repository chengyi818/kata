/*
 * File Name: constants.go
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Wed 03 Apr 2019 04:00:38 PM CST
 */
/**
1. 常量使用const定义
2. 常量不能使用 := 定义
*/
package main

import "fmt"

const Pi = 3.14

func main() {
	const World = "世界"
	fmt.Println("Hello", World)
	fmt.Println("Happy", Pi, "Day")

	const Truth = true
	fmt.Println("Go rules?", Truth)
	// Truth = false        // error
}
