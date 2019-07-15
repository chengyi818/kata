/*
 * File Name: basic_types.go
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Wed 03 Apr 2019 03:46:58 PM CST
 */

/**
1. Go基本类型
bool

string

int  int8  int16  int32  int64
uint uint8 uint16 uint32 uint64
uintptr

byte // alias for uint8

rune // alias for int32
     // represents a Unicode code point

float32 float64

complex64 complex128

2. int,uint,uintptr在32位系统32bits长度,在64位系统64bits长度
3. 整数通常使用int类型
*/

package main

import (
	"fmt"
	"math/cmplx"
)

var (
	ToBe   bool       = false
	MaxInt uint64     = 1<<64 - 1
	z      complex128 = cmplx.Sqrt(-5 + 12i)
)

func main() {
	fmt.Printf("Type: %T Value: %v\n", ToBe, ToBe)
	fmt.Printf("Type: %T Value: %v\n", MaxInt, MaxInt)
	fmt.Printf("Type: %T Value: %v\n", z, z)
}
