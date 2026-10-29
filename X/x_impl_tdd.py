from ctdd import Tester


class BootstrapTests(Tester):
    def test_sut_compiles(self):
        self.assertIsNotNone(self.sut)


class ImplementationAfter_X_IMPL_Tests(Tester):
    def test_an_X_function_is_implemented(self):
        self.assertZero(self.sut.X_strcmp(b'a', b'a'))

    def test_an_X_enum_function_is_implemented(self):
        self.assertEqual(self.sut.EUT_ITEM2, self.sut.eut_parse(b'ITEM2'))

    def test_X_IMPL_is_not_defined(self):
        self.assertZero(self.sut.X_IMPL_is_defined())


Tester.go()
