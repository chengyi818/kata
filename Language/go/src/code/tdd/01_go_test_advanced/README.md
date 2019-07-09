# README
https://tutorialedge.net/golang/advanced-go-testing-tutorial/

## 构造一组输入输出
[strings_test.go](/usr/share/go-1.11/src/strings/strings_test.go)

var lastIndexTests
func TestLastIndex

---

## 文件形式的输入输出
[reader_test.go](/usr/share/go-1.11/src/archive/tar/reader_test.go)

func TestReader
testdata

---

## Mock Http
httptest

## Separate Packages
[strings_test.go](/usr/share/go-1.11/src/strings/strings_test.go)
[strings.go](/usr/share/go-1.11/src/strings/strings.go)

avoid cyclic imports

## Differentiate your Unit and Integration Tests
区分单元测试和集成测试
// +build integration
go test -tags=integration
