/*
 * File Name: images.go
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Mon 08 Apr 2019 05:22:58 PM CST
 */

package main

import (
	"fmt"
	"image"
)

func main() {
	m := image.NewRGBA(image.Rect(0, 0, 100, 100))
	fmt.Println(m.Bounds())
	fmt.Println(m.At(0, 0).RGBA())
}
