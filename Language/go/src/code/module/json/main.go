/*
 * File Name: main.go
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Wed 24 Apr 2019 11:37:29 AM CST
 */

// json.go
// http://wiki.jikexueyuan.com/project/the-way-to-go/12.9.html
package main

import (
	"encoding/json"
	"fmt"
	"log"
	"os"
)

type Address struct {
	Type    string
	City    string
	Country string
}

type VCard struct {
	FirstName string
	LastName  string
	Addresses []*Address
	Remark    string
}

func main() {
	pa := &Address{"private", "Aartselaar", "Belgium"}
	wa := &Address{"work", "Boom", "Belgium"}
	vc := VCard{"Jan", "Kersschot", []*Address{pa, wa}, "none"}
	fmt.Printf("%v: \n", vc) // {Jan Kersschot [0x126d2b80 0x126d2be0] none}:

	// JSON format:
	js, _ := json.Marshal(vc)
	fmt.Printf("JSON format: %s\n", js)

	// JSON Parse 1
	var vc1 VCard
	err := json.Unmarshal(js, &vc1)
	if err != nil {
		log.Println("Error in unmarshal json")
	}
	fmt.Println(vc1)

	// JSON Parse 2
	var f interface{}
	err = json.Unmarshal(js, &f)
	if err != nil {
		log.Println("Error in unmarshal json")
	}
	fmt.Println(f)

	m := f.(map[string]interface{})
	for k, v := range m {
		switch vv := v.(type) {
		case string:
			fmt.Println(k, "is string", vv)
		case int:
			fmt.Println(k, "is int", vv)

		case []interface{}:
			fmt.Println(k, "is an array:")
			for i, u := range vv {
				fmt.Println(i, u)
			}
		default:
			fmt.Println(k, "is of a type I don’t know how to handle")
		}
	}

	// using an encoder:
	file, _ := os.OpenFile("vcard.json", os.O_CREATE|os.O_RDWR, 0666)
	defer file.Close()
	enc := json.NewEncoder(file)
	err = enc.Encode(vc)
	if err != nil {
		log.Println("Error in encoding json")
	}

	// using an decoder
	var vc2 VCard
	_, err = file.Seek(0, 0)
	if err != nil {
		log.Println("seek file: ", err)
	}

	dec := json.NewDecoder(file)
	err = dec.Decode(&vc2)
	if err != nil {
		log.Println("Error in decode json: ", err)
	}
	fmt.Println("vc2: ", vc2)

}
