/*
 * File Name: mutating_maps.go
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Thu 04 Apr 2019 11:57:22 AM CST
 */

package main

import "fmt"

func main() {
	// 1. 字典初始化
	m := make(map[string]int)

	// 2. 字典插入
	m["Answer"] = 42
	fmt.Println("The value:", m["Answer"])

	// 3. 字典修改
	m["Answer"] = 48
	fmt.Println("The value:", m["Answer"])

	// 4. 删除元素
	delete(m, "Answer")
	fmt.Println("The value:", m["Answer"])

	// 5. 判断元素是否存在
	v, ok := m["Answer"]
	fmt.Println("The value:", v, "Present?", ok)
}
