/*
 * File Name: main.go
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Wed 12 Jun 2019 05:55:32 PM CST
 */

package main

import (
    "fmt"
    tnet "github.com/toolkits/net"
    "net"
    "regexp"
    "strings"
)

func getipaddr() {
    fmt.Println("program init...")
    ifaces, _ := net.Interfaces()
    for _, i := range ifaces {

        addrs, _ := i.Addrs()
        for _, addr := range addrs {
            match, _ := regexp.MatchString(`^[0-9]+\.[0-9]+\.[0-9]+\.[0-9]+/[0-9]+$`, addr.String())
            if !match {
                continue
            }
            slit := strings.Split(addr.String(), "/")
            fmt.Println(i.Name, i.Flags, slit)
        }
    }
}

func main() {
    fmt.Println("Hello, 世界")
    getipaddr()
    ips, err := tnet.IntranetIP()
    fmt.Println("IntranetIP:", ips, err)
}
