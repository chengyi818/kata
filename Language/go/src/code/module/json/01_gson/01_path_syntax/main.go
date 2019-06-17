/*
 * File Name: main.go
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Mon 17 Jun 2019 10:39:27 AM CST
 */

package main

import (
	"fmt"
	"github.com/tidwall/gjson"
)

const json = `
{
  "name": {"first": "Tom", "last": "Anderson"},
  "age":37,
  "children": ["Sara","Alex","Jack"],
  "fav.movie": "Deer Hunter",
  "friends": [
    {"first": "Dale", "last": "Murphy", "age": 44},
    {"first": "Roger", "last": "Craig", "age": 68},
    {"first": "Jane", "last": "Murphy", "age": 47}
  ]
}
`

func main() {
	showKey("name.last") // "Anderson"
	showKey("age") // 37
	showKey("children") // ["Sara","Alex","Jack"]

	// To get the number of elements in an array or to access a child path,
	// use the '#' character.
	showKey("children.#") // 3
	showKey("children.1") // "Alex"
	showKey("child*.2") // "Jack"
	showKey("c?ildren.0") // "Sara"
	showKey("fav\\.movie") // "Deer Hunter"
	showKey("friends.#.first") // ["Dale","Roger","Jane"]
	showKey("friends.1.last") // "Craig"

	showKey("friends.#[last==\"Murphy\"].first") // "Dale"
	showKey("friends.#[last==\"Murphy\"]#.first") // ["Dale","Jane"]
	showKey("friends.#[age>45]#.last") // ["Craig","Murphy"]
	showKey("friends.#[first%\"D*\"].last") // "Murphy"
	showKey("friends.#[first!%\"D*\"].last") // "Craig"

	// -----------------
	showArray("friends")
}

func showKey(key string) {
	value := gjson.Get(json, key)
	fmt.Println(value.String())
}

func showArray(key string) {
	result := gjson.Get(json, key)
	result.ForEach(func(key, value gjson.Result) bool {
		m := value.Map()
		fmt.Println(m["first"], m["age"])
		return true // keep iterating
	})
}
