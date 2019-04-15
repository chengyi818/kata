// Copyright 2015 The Gorilla WebSocket Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

// +build ignore

package main

import (
	"flag"
	"log"
	"net/url"
	"os"
	"os/signal"
	"fmt"

	"github.com/gorilla/websocket"
)

var addr = flag.String("addr", "localhost:8080", "http service address")

func readSo(path string) []byte {
	file,err := os.Open(path)
	if err != nil {
		log.Fatal(err)
	}

	defer file.Close()

	fileinfo,err := file.Stat()
	if err != nil {
		log.Fatal(err)
	}

	fileSize := fileinfo.Size()
	buffer := make([]byte,fileSize)

	bytesread,err := file.Read(buffer)
	if err != nil {
		log.Fatal(err)
	}

	log.Println("bytes read:", bytesread)
	log.Println("bytestream to string:", string(buffer))

	return buffer
}

func main() {
	flag.Parse()
	log.SetFlags(0)

	soContent := readSo(
		"./lib/test_so.so")

	interrupt := make(chan os.Signal, 1)
	signal.Notify(interrupt, os.Interrupt)

	u := url.URL{Scheme: "ws", Host: *addr, Path: "/echo"}
	log.Printf("connecting to %s", u.String())

	c, _, err := websocket.DefaultDialer.Dial(u.String(), nil)
	if err != nil {
		log.Fatal("dial:", err)
	}
	defer c.Close()


	err := c.WriteMessage(websocket.BinaryMessage, soContent)

	// done := make(chan struct{})

	// go func() {
	// 	defer close(done)
	// 	for {
	// 		_, message, err := c.ReadMessage()
	// 		if err != nil {
	// 			log.Println("read:", err)
	// 			return
	// 		}
	// 		log.Printf("recv: %s", message)
	// 	}
	// }()

	// ticker := time.NewTicker(time.Second)
	// defer ticker.Stop()

	// for {
	// 	select {
	// 	// case <-done:
	// 	// 	return
	// 	case t := <-ticker.C:
	// 		err := c.WriteMessage(websocket.TextMessage, []byte(t.String()))
	// 		if err != nil {
	// 			log.Println("write:", err)
	// 			return
	// 		}
	// 	case <-interrupt:
	// 		log.Println("interrupt")

	// 		// Cleanly close the connection by sending a close message and then
	// 		// waiting (with timeout) for the server to close the connection.
	// 		err := c.WriteMessage(websocket.CloseMessage, websocket.FormatCloseMessage(websocket.CloseNormalClosure, ""))
	// 		if err != nil {
	// 			log.Println("write close:", err)
	// 			return
	// 		}
	// 		select {
	// 		case <-done:
	// 		case <-time.After(time.Second):
	// 		}
	// 		return
	// 	}
	// }
}
