/*
 * File Name: exercise_rot_reader.go
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Mon 08 Apr 2019 04:45:31 PM CST
 */

package main

import (
	"fmt"
	"io"
	"os"
	"strings"
)

type rot13Reader struct {
	r io.Reader
}

func (rot rot13Reader) Read(b []byte) (int, error) {
	n, err := rot.r.Read(b)
	// rot13
	for i:=0; i<n; i++ {
		target := int(b[i])
		if 97 <= target && target <= 109 {
			b[i] += 13
		} else if 110 <= target && target <= 122{
			b[i] -= 13
		}
	}

	return n, err
}

func main() {
	s := strings.NewReader("Lbh penpxrq gur pbqr!")
	r := rot13Reader{s}
	_, err := io.Copy(os.Stdout, &r)

	if(err != nil) {
		fmt.Println(err)
	}
}
