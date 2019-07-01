/*
 * File Name: main.go
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Wed 12 Jun 2019 02:26:35 PM CST
 */
package main

import (
	"time"
	"fmt"
	"github.com/BurntSushi/toml"
)

type Config struct {
	tmp string
	Age int
	Cats []string
	Pi float64
	Perfection []int
	DOB time.Time // requires `import time`
}

func main() {
	var conf Config
	if _, err := toml.DecodeFile("./basic.toml", &conf); err != nil {
		// handle error
		fmt.Println(err)
	}

	fmt.Println(conf.Age)
	fmt.Println(conf.Cats)
	fmt.Println(conf.DOB)

}
