/*
 * File Name: a.go
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Wed 03 Jul 2019 04:00:50 PM CST
 */

package a

import (
	"fmt"

	"code/grammer/recursive_import/01_add_interface/b"
	"code/grammer/recursive_import/01_add_interface/c"
)

type A struct {
	Pb *b.B
	Pc *c.C
}

func New(ic int) *A {
	a := &A{
		Pc: c.New(ic),
	}

	a.Pb = b.New(a)

	return a
}

func (a *A) GetC() *c.C {
	return a.Pc
}

func Printf(v int) {
	fmt.Printf("%v", v)
}
