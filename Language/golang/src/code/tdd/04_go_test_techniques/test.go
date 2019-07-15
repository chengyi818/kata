import "testing"

type Thinger interface {
	DoThing(input string) (Result, error)
}

// Suite tests all the functionality that Thingers should implement
func Suite(t *testing.T, impl Thinger) {
	res, _ := impl.DoThing("thing")
	if res != expected {
		t.Fail("unexpected result")
	}
}

// TestOne tests the first implementation of Thinger
func TestOne(t *testing.T) {
	one := one.NewOne()
	Suite(t, one)
}

// TestOne tests another implementation of Thinger
func TestTwo(t *testing.T) {
	two := two.NewTwo()
	Suite(t, two)
}
