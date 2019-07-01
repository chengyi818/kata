/*
 * File Name: main.go
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Wed 12 Jun 2019 05:35:45 PM CST
 */

//https://blog.csdn.net/wangshubo1989/article/details/78066344

package main

import (
	"net"
	"fmt"
	"errors"
)

func main() {
	fmt.Println(ExternalIP())

}

func ExternalIP() (string, string, error) {
	ifaces, err := net.Interfaces()
	if err != nil {
		return "", "", err
	}
	for _, iface := range ifaces {
		fmt.Println(iface.Name)

		// interface down
		if iface.Flags&net.FlagUp == 0 {
			continue
		}

		// loopback interface
		if iface.Flags&net.FlagLoopback != 0 {
			continue
		}

		addrs, err := iface.Addrs()
		if err != nil {
			return "", "", err
		}
		for _, addr := range addrs {
			var ip net.IP
			switch v := addr.(type) {
			case *net.IPNet:
				ip = v.IP
				ipnet := v
				fmt.Println(ipnet)
			case *net.IPAddr:
				fmt.Println("IPAddr")
				ip = v.IP
			}
			if ip == nil || ip.IsLoopback() {
				continue
			}
			ip = ip.To4()
			if ip == nil {
				continue // not an ipv4 address
			}
			return ip.String(), iface.HardwareAddr.String(), nil
		}
	}
	return "", "", errors.New("are you connected to the network?")
}
