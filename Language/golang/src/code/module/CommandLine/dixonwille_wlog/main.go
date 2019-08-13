/*
 * File Name: main.go
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Tue 13 Aug 2019 04:27:52 PM CST
 */
package main

import (
	"os"
	"strings"

	"github.com/dixonwille/wlog"
)

func main() {
	var ui wlog.UI
	reader := strings.NewReader("User Input\r\n") //Simulate user typing "User Input" then pressing [enter] when reading from os.Stdin
	ui = wlog.New(reader, os.Stdout, os.Stdout)
	ui = wlog.AddPrefix("?", wlog.Cross, " ", "", "", "~", wlog.Check, "!", ui)
	ui = wlog.AddConcurrent(ui)

	ui.Ask("Ask question", "")
	ui.Error("Error message")
	ui.Info("Info message")
	ui.Output("Output message")
	ui.Running("Running message")
	ui.Success("Success message")
	ui.Warn("Warning message")
}
