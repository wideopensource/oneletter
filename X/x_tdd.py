from ctdd import Tester


class BootstrapTests(Tester):
    def test_sut_compiles(self):
        self.assertIsNotNone(self.sut)


class StrcmpCommonTests(Tester):
    def test_X_strcmp_empty_equal(self):
        self.assertZero(self.sut.X_strcmp(b'', b''))

    def test_X_strcmpi_empty_equal(self):
        self.assertZero(self.sut.X_strcmpi(b'', b''))

    def test_X_strcmp_first_shorter_not_equal(self):
        self.assertNotZero(self.sut.X_strcmp(b'', b'a'))

    def test_X_strcmpi_first_shorter_not_equal(self):
        self.assertNotZero(self.sut.X_strcmpi(b'', b'a'))

    def test_X_strcmp_second_shorter_not_equal(self):
        self.assertNotZero(self.sut.X_strcmp(b'a', b''))

    def test_X_strcmpi_second_shorter_not_equal(self):
        self.assertNotZero(self.sut.X_strcmpi(b'a', b''))

    def test_X_strcmp_not_equal(self):
        self.assertNotZero(self.sut.X_strcmp(b'a', b'b'))

    def test_X_strcmpi_not_equal(self):
        self.assertNotZero(self.sut.X_strcmpi(b'a', b'b'))

    def test_X_strcmp_equal(self):
        self.assertZero(self.sut.X_strcmp(b'a', b'a'))

    def test_X_strcmpi_equal(self):
        self.assertZero(self.sut.X_strcmpi(b'a', b'a'))

    def test_X_strcmp_underscore_equal(self):
        self.assertZero(self.sut.X_strcmp(b'_', b'-'))

    def test_X_strcmpi_underscore_equal(self):
        self.assertZero(self.sut.X_strcmpi(b'_', b'-'))

    def test_X_strcmp_long_not_equal(self):
        self.assertNotZero(self.sut.X_strcmp(b'aa', b'ba'))

    def test_X_strcmpi_long_not_equal(self):
        self.assertNotZero(self.sut.X_strcmpi(b'aa', b'ba'))

    def test_X_strcmp_long_equal(self):
        self.assertZero(self.sut.X_strcmp(b'aa', b'aa'))

    def test_X_strcmpi_long_equal(self):
        self.assertZero(self.sut.X_strcmpi(b'aa', b'aa'))


class StrcmpTests(Tester):
    def test_X_strcmp_case_not_equal(self):
        self.assertNotZero(self.sut.X_strcmp(b'a', b'A'))


class StrcmpiTests(Tester):
    def test_X_strcmp_case_equal(self):
        self.assertZero(self.sut.X_strcmpi(b'a', b'A'))


Tester.go()
