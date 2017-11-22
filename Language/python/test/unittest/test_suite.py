import unittest

from test_mathfunc import TestMathFunc

if __name__ == '__main__':
    suite = unittest.TestSuite()

    # tests = [TestMathFunc("test_add"),
    #          TestMathFunc("test_minus"),
    #          TestMathFunc("test_divide")]
    # suite.addTests(tests)

    suite.addTests(unittest.TestLoader().loadTestsFromTestCase(
        TestMathFunc))

    runner = unittest.TextTestRunner(verbosity=2)
    runner.run(suite)
