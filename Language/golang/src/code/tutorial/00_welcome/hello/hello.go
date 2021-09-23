/*
 * File Name: hello.go
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Wed 03 Apr 2019 11:22:19 AM CST
 */

//package main

//import "fmt"

//func main() {
//fmt.Printf("hello, world\n")
//}

package main

import (
	"fmt"
	"sync/atomic"
	"time"
)

func main() {
	var x int32
	var y int32

	go func() {
		for {
			x = atomic.AddInt32(&x, 1)
			y = atomic.AddInt32(&y, 1)
		}
	}()

	time.Sleep(time.Second)
	fmt.Println("x=", x)
	fmt.Println("y=", y)
}
