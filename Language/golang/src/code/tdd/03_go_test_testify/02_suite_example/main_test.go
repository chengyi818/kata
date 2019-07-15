/*
 * File Name: main_test.go
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Tue 09 Jul 2019 06:33:07 PM CST
 */

// Basic imports
package main_test

import (
	"fmt"
	"testing"

	"github.com/stretchr/testify/suite"
)

// Define the suite, and absorb the built-in basic suite
// functionality from testify - including assertion methods.
type ExampleTestSuite struct {
	suite.Suite
	VariableThatShouldStartAtFive int
}

// Make sure that VariableThatShouldStartAtFive is set to five
// before each test
func (suite *ExampleTestSuite) SetupTest() {
	suite.VariableThatShouldStartAtFive = 5
}

// Make sure that VariableThatShouldStartAtFive is set to zero
// after each test
func (suite *ExampleTestSuite) TearDownTest() {
	suite.VariableThatShouldStartAtFive = 0
}

// All methods that begin with "Test" are run as tests within a
// suite.
func (suite *ExampleTestSuite) TestExample() {
	fmt.Println("TestExample start")
	suite.Equal(suite.VariableThatShouldStartAtFive, 5)
}

// In order for 'go test' to run this suite, we need to create
// a normal test function and pass our suite to suite.Run
func TestExampleTestSuite(t *testing.T) {
	fmt.Println("TestExampleTestSuite start")
	suite.Run(t, new(ExampleTestSuite))
}
