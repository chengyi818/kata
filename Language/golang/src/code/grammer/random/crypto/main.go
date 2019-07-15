/*
 * File Name: main.go
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Tue 02 Jul 2019 05:37:31 PM CST
 */
package main

import (
	"crypto/rand"
	// "encoding/base64"
	// "encoding/hex"
	"fmt"
)

func Key() string {
	buf := make([]byte, 16)
	_, err := rand.Read(buf)
	if err != nil {
		panic(err) // out of randomness, should never happen
	}
	return fmt.Sprintf("%x", buf)
	// or hex.EncodeToString(buf)
	// or base64.StdEncoding.EncodeToString(buf)
}

func main() {
	fmt.Println(Key())
}
