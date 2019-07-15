/*
 * File Name: 01_inherit_01.go
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Tue 09 Apr 2019 03:23:56 PM CST
 */

package main

import (
	"fmt"
)

type Person interface {
	getName() string
	getAge() int
}

type Father struct {
	name string
	age int
}

func (f *Father) getName() string {
	return f.name
}

func (f *Father) getAge() int {
	return f.age
}

type Son struct {
	Person
	weight float64
}

func (s Son) getWeight() float64 {
	return s.weight
}


func main() {
	var f Person = &Father{"father", 55}

	fmt.Println(f.getName())
	fmt.Println(f.getAge())

	s := Son{&Father{"son", 31}, 63.5}

	fmt.Println(s.getName())
	fmt.Println(s.getAge())
	fmt.Println(s.getWeight())
}
