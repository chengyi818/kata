/*
 * File Name: exercise_errors.go
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Mon 08 Apr 2019 09:37:35 AM CST
 */

package main

import (
	"fmt"
)

type ErrNegativeSqrt float64

func (e ErrNegativeSqrt) Error() string {
	return fmt.Sprintf("cannot Sqrt negative number: %v", float64(e))
	// return fmt.Sprintf("cannot Sqrt negative number: %v", e)
}

func Sqrt(x float64) (float64, error) {
	if(x < 0) {
		return 0, ErrNegativeSqrt(x)
	}

	z := 1.0
	for i:=0; i<10; i++ {
		z -= (z*z - x) / (2*z)
		// fmt.Println(z);
	}

	return z, nil
}

func main() {
	fmt.Println(Sqrt(2))
	fmt.Println(Sqrt(-2))
}
