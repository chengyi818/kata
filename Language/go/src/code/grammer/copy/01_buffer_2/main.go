/*
 * File Name: main.go
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Tue 02 Jul 2019 05:14:50 PM CST
 */

// https://stackoverflow.com/questions/51419111/golang-bytes-buffer-passby-value-issue
package main

import (
	"bytes"
	"fmt"
)

func main() {
	var b bytes.Buffer
	//Commenting the below line will fix the problem
	b.WriteString("aas-aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa")
	fmt.Printf("Before Calling - \"%s\"\n", b.String())
	b = makeMeMad(b)
	fmt.Printf("FinalValue - \"%s\"\n", b.String())
}

func makeMeMad(b bytes.Buffer) bytes.Buffer {
	b.WriteString("xcxxcx asdasdas dasdsd asdasdasdasd")
	fmt.Printf("Write More - \"%s\"\n", b.String())

	/*
	   //This will fix the problem
	   var newBuffer bytes.Buffer
	   newBuffer.WriteString(b.String())
	   return newBuffer
	*/
	return b
}
