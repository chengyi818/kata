# README
https://segment.com/blog/5-advanced-testing-techniques-in-go/

## Use test suites
针对接口写测试用例,从而方便复用测试用例

conntest.go
conntest_test.go

[golang.org/x/net/nettest](/home/chengyi/code/github/kata/Language/go/src/golang.org/x/net/nettest/conntest.go)

## Avoid interface pollution
[errors package](https://godoc.org/github.com/pkg/errors)
[errors_test](https://github.com/pkg/errors/blob/master/errors_test.go)
