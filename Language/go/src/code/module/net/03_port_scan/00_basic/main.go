/*
 * File Name: main.go
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Fri 14 Jun 2019 02:29:48 PM CST
 */

package main

import (
    "fmt"
	"time"
	"github.com/anvie/port-scanner"
)

func main(){
	// scan localhost with a 2 second timeout per port in 5 concurrent threads
	ps := portscanner.NewPortScanner("192.168.130.173", 2*time.Second, 5)

	// get opened port
	fmt.Printf("scanning port %d-%d...\n", 20, 30000)

	openedPorts := ps.GetOpenedPort(20, 30000)

	for i := 0; i < len(openedPorts); i++ {
     	port := openedPorts[i]
     	fmt.Print(" ", port, " [open]")
     	fmt.Println("  -->  ", ps.DescribePort(port))
	}
}
