/*
 * File Name: main.go
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Wed 12 Jun 2019 02:26:35 PM CST
 */
package main

import (
	"fmt"
	"github.com/BurntSushi/toml"
)

type Config struct {
	ObscureKey string `toml:"some_key_NAME"`
}

func main() {
	var conf Config
	if _, err := toml.DecodeFile("./tags.toml", &conf); err != nil {
		// handle error
		fmt.Println(err)
	}

	fmt.Println(conf.ObscureKey)
}
