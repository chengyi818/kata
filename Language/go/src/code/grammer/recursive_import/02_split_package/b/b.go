/*
 * File Name: b.go
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Wed 03 Jul 2019 04:00:45 PM CST
 */

package b

import (
	"code/grammer/recursive_import/02_split_package/c"
)

type B struct {
	Pa a
}

type a interface {
	GetC() *c.C
}

func New(a a) *B {
	return &B{
		Pa: a,
	}
}

func (b *B) DisplayC() {
	b.Pa.GetC().Show()
}
