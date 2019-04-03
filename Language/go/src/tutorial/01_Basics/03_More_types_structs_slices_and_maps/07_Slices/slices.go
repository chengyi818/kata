/*
 * File Name: slices.go
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Wed 03 Apr 2019 06:24:21 PM CST
 */

package main

import "fmt"

func main() {
	primes := [6]int{2, 3, 5, 7, 11, 13}

	var s []int = primes[1:4]
	fmt.Println(s)
	fmt.Printf("Type: %T Value: %v\n", s, s)
}
