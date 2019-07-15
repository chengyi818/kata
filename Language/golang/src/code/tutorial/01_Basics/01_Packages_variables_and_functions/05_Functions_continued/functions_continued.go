/*
 * File Name: functions_continued.go
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Wed 03 Apr 2019 03:09:49 PM CST
 */

/**
 同类型变量统一声明,不需要每个单独声明
 int a;
 int b;
可以换成:
 int a,b;
*/

package main

import "fmt"

func add(x, y int) int {
	return x + y
}

func main() {
	fmt.Println(add(42, 13))
}
