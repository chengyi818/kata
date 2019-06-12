/*
 * File Name: main.go
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Wed 12 Jun 2019 02:43:32 PM CST
 */

package main

import (
	"time"
	"fmt"
	"log"
	"github.com/BurntSushi/toml"
)

type song struct {
	Name     string
	Duration duration
}
type songs struct {
	Song []song
}

type duration struct {
	time.Duration
}

func (d *duration) UnmarshalText(text []byte) error {
	var err error
	d.Duration, err = time.ParseDuration(string(text))
	return err
}

func main() {
	var favorites songs
	if _, err := toml.DecodeFile("./config.toml", &favorites); err != nil {
		log.Fatal(err)
	}

	for _, s := range favorites.Song {
		fmt.Printf("%s (%s)\n", s.Name, s.Duration)
	}

}
