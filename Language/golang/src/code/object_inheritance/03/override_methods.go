/*
 * File Name: override_methods.go
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Tue 09 Apr 2019 04:05:09 PM CST
 */
package main

import (
    "fmt"
)

type Pet struct {
    name string
}

type Dog struct {
    Pet
    Breed string
}

func (p *Pet) Play() {
    fmt.Println(p.Speak())
}

func (p *Pet) Speak() string {
    return fmt.Sprintf("my name is %v", p.name)
}

func (p *Pet) Name() string {
    return p.name
}

func (d *Dog) Speak() string {
    return fmt.Sprintf("%v and I am a %v", d.Pet.Speak(), d.Breed)
}

func main() {
    d := Dog{
		Pet: Pet{name: "spot"},
		Breed: "pointer"}
    fmt.Println(d.Name())
    fmt.Println(d.Speak())
    d.Play()
}
