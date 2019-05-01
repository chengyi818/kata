/*
 * File Name: hello_who.go
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Wed 24 Apr 2019 01:57:30 PM CST
 */

// os_args.go
package main

import (
    "fmt"
    "os"
    "strings"
)

func main() {
    who := ""
    if len(os.Args) > 1 {
        who += strings.Join(os.Args[1:], " ")
    }
    fmt.Println("Hello", who)
}
