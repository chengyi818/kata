/*
 * File Name: main.go
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Fri 14 Jun 2019 05:51:00 PM CST
 */
package main

import "github.com/tidwall/gjson"

const json = `{
  "name":
    {
      "first":"Janet",
      "last":"Prichard"
    },
    "age":47
}`

func main() {
	value := gjson.Get(json, "name.last")
	println(value.String())
}
