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

type Father struct {
	name string
	age int
}

func (f Father) getName() string {
	return f.name
}

func (f Father) getAge() int {
	return f.age
}

type Son struct {
	weight float64
	*Father
}

func (s Son) getWeight() float64 {
	return s.weight
}

type Daughter struct {
	height float64
	Father
}


func main() {
	f := Father{"father", 55}

	fmt.Println(f.getName())
	fmt.Println(f.getAge())

	s := Son{63.5, &Father{"son", 31}}

	fmt.Println(s.getName())
	fmt.Println(s.name)
	fmt.Println(s.getAge())
	fmt.Println(s.getWeight())

	d := Daughter{155, Father{"daughter", 24}}
	fmt.Println(d.getName())
	fmt.Println(d.getAge())
	fmt.Println(d.name)
}
