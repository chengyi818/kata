/*
 * File Name: main.go
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Fri 12 Apr 2019 02:23:45 PM CST
 */
package main

// #cgo LDFLAGS: -ldl
// #include <dlfcn.h>
import "C"

import "fmt"

func foo() {
	handle := C.dlopen(C.CString("../02_dlopen_self/lib/test_so.so"), C.RTLD_LAZY)
	bar := C.dlsym(handle, C.CString("test_so_func"))
	fmt.Printf("bar is at %p\n", bar)
}

func main() {
	foo()
}
