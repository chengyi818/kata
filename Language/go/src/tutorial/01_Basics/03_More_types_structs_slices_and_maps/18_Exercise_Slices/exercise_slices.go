/*
 * File Name: exercise_slices.go
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Thu 04 Apr 2019 11:16:57 AM CST
 */

package main

import (
	"fmt"
	"golang.org/x/tour/pic"
)

func Pic(dx, dy int) [][]uint8 {
	// fmt.Println(dx, dy)

	ret := make([][]uint8, dy)

	for i := 0; i < dy; i++ {
		ret[i] = make([]uint8, dx)

		for j := 0; j < dx; j++ {
			ret[i][j] = uint8(i*j)
		}
	}

	// fmt.Println(ret)
	return ret
}

func main() {
	pic.Show(Pic)
	// Pic(3, 3)
}
