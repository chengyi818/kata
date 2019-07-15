/*
 * File Name: errors.go
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Thu 04 Apr 2019 05:01:56 PM CST
 */

package main

import (
	"fmt"
	"strconv"
	"time"
)

type MyError struct {
	When time.Time
	What string
}

// go error built-in
func (e *MyError) Error() string {
	// return fmt.Sprint(e)
	return fmt.Sprintf("at %v, %s",
		e.When, e.What)
}

func run() error {
	return &MyError{
		time.Now(),
		"it didn't work",
	}
}

func main() {
	// 会调用built-in Error()
	if err := run(); err != nil {
		fmt.Println(err)
	}

	// 常见用法
	i, err := strconv.Atoi("42a")
	if err != nil {
		fmt.Printf("couldn't convert number: %v\n", err)
		return
	}
	fmt.Println("Converted integer:", i)
}
