/*
 * File Name: c.go
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Wed 03 Jul 2019 04:01:07 PM CST
 */

package c

import (
	"code/grammer/recursive_import/00_intro/a"
)

type C struct {
	Vc int
}

func New(i int) *C {
	return &C{
		Vc: i,
	}
}

func (c *C) Show() {
	a.Printf(c.Vc)
}
