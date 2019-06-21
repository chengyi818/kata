/*
 * File Name: main.go
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Fri 21 Jun 2019 03:37:44 PM CST
 */
package main

import (
	"flag"
	"fmt"
)

var ip = flag.Int("flagname1", 1234, "help message for flagname")

var flagvar int

func init() {
	flag.IntVar(&flagvar, "flagname2", 1234, "help message for flagname")
}

func main() {
	flag.Parse()
	fmt.Println("ip has value ", *ip)
	fmt.Println("flagvar has value ", flagvar)
}
