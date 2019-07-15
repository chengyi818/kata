/*
 * File Name: main.go
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Fri 12 Apr 2019 02:04:14 PM CST
 */

package main
/*
#include "load_so.h"
#cgo LDFLAGS: -ldl
*/
import "C"
import "fmt"

func main() {
    fmt.Println("20*30=", C.do_test_so_func(20, 30))
}
