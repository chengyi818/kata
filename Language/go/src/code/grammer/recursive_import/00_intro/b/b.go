/*
 * File Name: b.go
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Wed 03 Jul 2019 04:00:45 PM CST
 */

package b

import (
	"code/grammer/recursive_import/00_intro/a"
)

type B struct {
	Pa *a.A
}

func New(a *a.A) *B {
	return &B{
		Pa: a,
	}
}

func (b *B) DisplayC() {
	b.Pa.Pc.Show()
}
