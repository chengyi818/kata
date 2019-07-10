/*
 * File Name: factorsof.go
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Wed 10 Jul 2019 10:48:06 AM CST
 */
package factor

func factorsOf(n int) []int {
	var factors []int
	for divisor := 2; n > 1; divisor++ {
		for n%divisor == 0 {
			factors = append(factors, divisor)
			n /= divisor
		}
	}
	return factors
}
