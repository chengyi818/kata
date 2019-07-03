/*
 * File Name: main.go
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Wed 03 Jul 2019 04:01:43 PM CST
 */

package main

import "code/grammer/recursive_import/02_split_package/a"

func main() {
	a := a.New(3)
	a.Pb.DisplayC()
}
