/*
 * File Name: exercise_maps.go
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Thu 04 Apr 2019 12:00:38 PM CST
 */

package main

import (
	// "fmt"
	"golang.org/x/tour/wc"
	"strings"
)

func WordCount(s string) map[string]int {
	ret := make(map[string]int)

	for _, i := range strings.Fields(s) {
		// fmt.Printf("Type: %T Value: %v\n", i, i)
		ret[i] += 1
	}

	// fmt.Println(ret)
	return ret
}

func main() {
	wc.Test(WordCount)
}
