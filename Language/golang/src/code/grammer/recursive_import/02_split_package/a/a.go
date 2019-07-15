/*
 * File Name: a.go
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Wed 03 Jul 2019 04:00:50 PM CST
 */

package a

import (
	"code/grammer/recursive_import/02_split_package/b"
	"code/grammer/recursive_import/02_split_package/c"
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
