/*
 * File Name: main.go
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Tue 02 Jul 2019 02:07:11 PM CST
 */

package main

import (
	"fmt"
	"sync"
)

// https://golang.org/doc/articles/race_detector.html#Race_on_loop_counter

func main() {
	var wg sync.WaitGroup
	wg.Add(5)
	for i := 0; i < 5; i++ {
		go func() {
			fmt.Println(i) // Not the 'i' you are looking for.
			wg.Done()
		}()
	}
	wg.Wait()
}

// func main() {
// 	var wg sync.WaitGroup
// 	wg.Add(5)
// 	for i := 0; i < 5; i++ {
// 		go func(j int) {
// 			fmt.Println(j) // Good. Read local copy of the loop counter.
// 			wg.Done()
// 		}(i)
// 	}
// 	wg.Wait()
// }
