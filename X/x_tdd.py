from ctdd import Tester


class BootstrapTests(Tester):
    def test_sut_compiles(self):
        self.assertIsNotNone(self.sut)


class ArrayLengthTests(Tester):
    def test_X_ARRAY_LENGTH(self):
        self.assertEqual(5, self.sut.x_tdd_array_length_is_5())

    def test_X_ARRAY_LENGTH_of_cast(self):
        self.assertEqual(4, self.sut.x_tdd_array_length_of_cast_is_4())


class ToUpperTests(Tester):
    def test_X_to_upper_from_lower_case(self):
        self.assertEqual(ord('A'), self.sut.x_tdd_to_upper(ord('a')))
        self.assertEqual(ord('Z'), self.sut.x_tdd_to_upper(ord('z')))

    def test_X_to_upper_from_upper_case(self):
        self.assertEqual(ord('A'), self.sut.x_tdd_to_upper(ord('A')))
        self.assertEqual(ord('Z'), self.sut.x_tdd_to_upper(ord('Z')))

    def test_X_to_upper_from_junk(self):
        for c in '09_-@[`{':
            self.assertEqual(ord(c), self.sut.x_tdd_to_upper(ord(c)))


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

    def test_X_strcmp_first_prefix_not_equal(self):
        self.assertNotZero(self.sut.X_strcmp(b'a', b'ab'))

    def test_X_strcmpi_first_prefix_not_equal(self):
        self.assertNotZero(self.sut.X_strcmpi(b'a', b'ab'))

    def test_X_strcmp_second_prefix_not_equal(self):
        self.assertNotZero(self.sut.X_strcmp(b'ab', b'a'))

    def test_X_strcmpi_second_prefix_not_equal(self):
        self.assertNotZero(self.sut.X_strcmpi(b'ab', b'a'))

    def test_X_strcmp_long_prefix_not_equal(self):
        self.assertNotZero(self.sut.X_strcmp(b'item1', b'item10'))

    def test_X_strcmpi_long_prefix_not_equal(self):
        self.assertNotZero(self.sut.X_strcmpi(b'item1', b'item10'))

    def test_X_strcmp_null_equal(self):
        null = self.factory.null_pointer
        self.assertZero(self.sut.X_strcmp(null, null))

    def test_X_strcmpi_null_equal(self):
        null = self.factory.null_pointer
        self.assertZero(self.sut.X_strcmpi(null, null))

    def test_X_strcmp_first_null_not_equal(self):
        null = self.factory.null_pointer
        self.assertNotZero(self.sut.X_strcmp(null, b'a'))

    def test_X_strcmpi_first_null_not_equal(self):
        null = self.factory.null_pointer
        self.assertNotZero(self.sut.X_strcmpi(null, b'a'))

    def test_X_strcmp_second_null_not_equal(self):
        null = self.factory.null_pointer
        self.assertNotZero(self.sut.X_strcmp(b'a', null))

    def test_X_strcmpi_second_null_not_equal(self):
        null = self.factory.null_pointer
        self.assertNotZero(self.sut.X_strcmpi(b'a', null))


class StrcmpTests(Tester):
    def test_X_strcmp_case_not_equal(self):
        self.assertNotZero(self.sut.X_strcmp(b'a', b'A'))


class StrcmpiTests(Tester):
    def test_X_strcmp_case_equal(self):
        self.assertZero(self.sut.X_strcmpi(b'a', b'A'))

    def test_X_strcmpi_case_prefix_not_equal(self):
        self.assertNotZero(self.sut.X_strcmpi(b'A', b'ab'))


Tester.go()
