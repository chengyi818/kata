// Copyright 2015 The Gorilla WebSocket Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

// +build ignore

package main

// #include <string.h>
// #include <stdlib.h>
//
// int
// my_test_so_func(void *f, int a, int b)
// {
//   int (*test_so_func)(int, int);
//
//   test_so_func = (int (*)(int, int))f;
//   return test_so_func(a, b);
// }
import "C"

import (
	"flag"
	"io/ioutil"
	"log"
	"net/http"
	"fmt"
	"path/filepath"
	"os"
	"strings"

	"github.com/gorilla/websocket"
	"github.com/coreos/pkg/dlopen"
)

var addr = flag.String("addr", "localhost:8080", "http service address")

var upgrader = websocket.Upgrader{} // use default options

func GetCurrentDirectory() string {
	dir, err := filepath.Abs(filepath.Dir(os.Args[0]))  //返回绝对路径  filepath.Dir(os.Args[0])去除最后一个元素的路径
	if err != nil {
		log.Fatal(err)
	}
	return strings.Replace(dir, "\\", "/", -1) //将\替换成/
}

func echo(w http.ResponseWriter, r *http.Request) {
	c, err := upgrader.Upgrade(w, r, nil)
	if err != nil {
		log.Print("upgrade:", err)
		return
	}
	defer c.Close()
	for {
		mt, message, err := c.ReadMessage()
		if err != nil {
			log.Println("read:", err)
			break
		}

		switch mt {
		case websocket.BinaryMessage:
			{
				// save file
				err := ioutil.WriteFile("tmp", message, 0755)
				if err != nil {
					log.Println("recv binary:", err)
					break
				}

				currentPath := GetCurrentDirectory()
				log.Println(currentPath)

				// get handle
				h, err := dlopen.GetHandle([]string{currentPath+"/tmp"})
				if err != nil {
					fmt.Println(`couldn't get a handle to the library: `, err)
					return
				}
				defer h.Close()

				f := "test_so_func"
				// cs := c.cstring(s)
				// defer c.free(unsafe.pointer(cs))

				test_so_func, err := h.GetSymbolPointer(f)
				if err != nil {
					fmt.Println(`couldn't get symbol %q: %v`, f, err)
					return
				}

				ret := int(C.my_test_so_func(test_so_func, 2, 3))
				log.Println("my_test_so_func: ", ret)

				var result []byte = []byte(string(ret))
				log.Println("result: ", result)

				err = c.WriteMessage(websocket.TextMessage, result)
				if err != nil {
					log.Println("write:", err)
					break
				}
			}
		}

	}
}

func main() {
	flag.Parse()
	log.SetFlags(0)
	http.HandleFunc("/echo", echo)
	log.Fatal(http.ListenAndServe(*addr, nil))
}
