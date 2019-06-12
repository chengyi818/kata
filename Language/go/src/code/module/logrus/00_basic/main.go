/*
 * File Name: main.go
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Wed 12 Jun 2019 11:18:36 AM CST
 */

package main

import (
	log "github.com/sirupsen/logrus"
)

func main() {
	log.WithFields(log.Fields{
		"animal": "walrus",
	}).Info("A walrus appears")
	log.Info("cy test")
}
