/*
 * File Name: main.go
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Fri 12 Apr 2019 11:48:35 AM CST
 */

package main

import "fmt"

/*
#cgo CFLAGS: -I./
#cgo LDFLAGS: -L./ -lhi
#include "hi.h" //非标准c头文件，所以用引号
*/
import "C"

func main() {
    C.hi()
    fmt.Println("Hi, vim-go")
}
