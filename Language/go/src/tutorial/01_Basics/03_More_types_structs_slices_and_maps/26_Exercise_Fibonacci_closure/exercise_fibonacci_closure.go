/*
 * File Name: exercise_fibonacci_closure.go
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Thu 04 Apr 2019 02:54:34 PM CST
 */

package main

import "fmt"

// fibonacci is a function that returns
// a function that returns an int.
func fibonacci() func() int {
	a := 0
	b := 1
	c := 0

	return func() int {
		c = a+b
		a = b
		b = c

		return c
	}

}

func main() {
	f := fibonacci()
	for i := 0; i < 10; i++ {
		fmt.Println(f())
	}
}
