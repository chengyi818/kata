/*
 * File Name: main.go
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Tue 11 Jun 2019 05:28:37 PM CST
 */

package main

import (
	"time"
)

import l4g "github.com/alecthomas/log4go"

func main() {
	log := l4g.Global
	defer log.Close()
	log.AddFilter("stdout", l4g.DEBUG, l4g.NewConsoleLogWriter())
	log.Info("The time is now: %s", time.Now().Format("15:04:05 MST 2006/01/02"))
}
