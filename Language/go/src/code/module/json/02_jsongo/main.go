/*
 * File Name: main.go
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Fri 14 Jun 2019 06:16:27 PM CST
 */

// https://github.com/ricardolonga/jsongo
package main

import (
	"log"
    j "github.com/ricardolonga/jsongo"
	sj "encoding/json"
)

/*
{
    "name":"Ricardo Longa",
    "idade":28,
    "owner":true,
    "skills":[
        "Golang",
        "Android"
    ]
}
*/

type Person struct {
    Name string `json:"name"`
    Idade  int `json:"idade"`
	Owner bool `json:"owner"`
	Skills []string `json:"skills"`
}

func main() {
	json := j.Object().Put("name", "Ricardo Longa").
		Put("idade", 28).
		Put("owner", true).
		Put("skills",
		j.Array().Put("Golang").Put("Android"))

	log.Println(json.Indent())
	log.Println(json.String())

    // bytes, err := sj.Marshal(in)
    // if err != nil {
    //     panic(err)
    // }
	// log.Printf("%T", bytes)

    var p Person
	in := json.String()
    err := sj.Unmarshal([]byte(in), &p)
    if err != nil {
        panic(err)
    }

    log.Printf("%+v", p)
}
