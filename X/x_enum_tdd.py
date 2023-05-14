from ctdd import Tester


class BootstrapTests(Tester):
    def test_sut_compiles(self):
        self.assertIsNotNone(self.sut)

    def test_print_all_does_not_raise(self):
        context = self.factory.null_pointer

        with self.assertDoesNotRaise():
            self.sut.eut_print_all(context)


class Tests(Tester):
    def test_invalid_value(self):
        self.assertEqual(0, self.sut.EUT_INVALID)

    def test_item_values(self):
        self.assertEqual(1, self.sut.EUT_ITEM1)
        self.assertEqual(3, self.sut.EUT_ITEM2)
        self.assertEqual(4, self.sut.EUT_ITEM3)

    def test_number_of_items(self):
        self.assertEqual(3, self.sut.EUT_NUMBER_OF_ITEMS)

    def test_next(self):
        self.assertEqual(5, self.sut._EUT_NEXT)

    def test_count(self):
        self.assertEqual(self.sut.EUT_NUMBER_OF_ITEMS, self.sut.eut_count())

    def test_is_valid(self):
        self.assertTrue(self.sut.eut_is_valid(self.sut.EUT_ITEM1))
        self.assertTrue(self.sut.eut_is_valid(self.sut.EUT_ITEM1))
        self.assertTrue(self.sut.eut_is_valid(self.sut.EUT_ITEM1))

    def test_is_not_valid(self):
        self.assertFalse(self.sut.eut_is_valid(self.sut.EUT_ITEM1 - 1))
        self.assertFalse(self.sut.eut_is_valid(self.sut.EUT_ITEM1 + 1))
        self.assertFalse(self.sut.eut_is_valid(self.sut.EUT_ITEM3 + 1))

    def test_clamp(self):
        self.assertEqual(self.sut.EUT_ITEM1,
                         self.sut.eut_clamp(self.sut.EUT_ITEM1 - 1))
        self.assertEqual(self.sut.EUT_ITEM1,
                         self.sut.eut_clamp(self.sut.EUT_ITEM1 + 1))
        self.assertEqual(self.sut.EUT_ITEM3,
                         self.sut.eut_clamp(self.sut.EUT_ITEM3 + 1))

    def test_index(self):
        self.assertEqual(0, self.sut.EUT_INDEX_ITEM1)
        self.assertEqual(1, self.sut.EUT_INDEX_ITEM2)
        self.assertEqual(2, self.sut.EUT_INDEX_ITEM3)

    def test_index_of_invalid(self):
        self.assertEqual(self.sut.EUT_INDEX_INVALID,
                         self.sut.eut_index_of(self.sut.EUT_INVALID))

    def test_index_of(self):
        self.assertEqual(self.sut.EUT_INDEX_ITEM1,
                         self.sut.eut_index_of(self.sut.EUT_ITEM1))
        self.assertEqual(self.sut.EUT_INDEX_ITEM2,
                         self.sut.eut_index_of(self.sut.EUT_ITEM2))
        self.assertEqual(self.sut.EUT_INDEX_ITEM3,
                         self.sut.eut_index_of(self.sut.EUT_ITEM3))

    def test_flag(self):
        self.assertEqual(0x0001, self.sut.EUT_FLAG_ITEM1)
        self.assertEqual(0x0002, self.sut.EUT_FLAG_ITEM2)
        self.assertEqual(0x0004, self.sut.EUT_FLAG_ITEM3)

    def test_flag_of_invalid(self):
        self.assertEqual(0, self.sut.eut_flag_of(self.sut.EUT_INVALID))

    def test_flag_of(self):
        self.assertEqual(self.sut.EUT_FLAG_ITEM1,
                         self.sut.eut_flag_of(self.sut.EUT_ITEM1))
        self.assertEqual(self.sut.EUT_FLAG_ITEM2,
                         self.sut.eut_flag_of(self.sut.EUT_ITEM2))
        self.assertEqual(self.sut.EUT_FLAG_ITEM3,
                         self.sut.eut_flag_of(self.sut.EUT_ITEM3))

    def test_at_invalid(self):
        self.assertEqual(self.sut.EUT_INVALID, self.sut.eut_at(-1))
        self.assertEqual(self.sut.EUT_INVALID, self.sut.eut_at(
            self.sut.EUT_NUMBER_OF_ITEMS))

    def test_at(self):
        self.assertEqual(self.sut.EUT_ITEM1,
                         self.sut.eut_at(self.sut.EUT_INDEX_ITEM1))
        self.assertEqual(self.sut.EUT_ITEM2,
                         self.sut.eut_at(self.sut.EUT_INDEX_ITEM2))
        self.assertEqual(self.sut.EUT_ITEM3,
                         self.sut.eut_at(self.sut.EUT_INDEX_ITEM3))

    def test_invalid_to_string(self):
        self.assertStrEqual(
            'EUT_INVALID', self.sut.eut_to_string(self.sut.EUT_INVALID))

    def test_to_string(self):
        self.assertStrEqual(
            'ITEM1', self.sut.eut_to_string(self.sut.EUT_ITEM1))
        self.assertStrEqual(
            'ITEM2', self.sut.eut_to_string(self.sut.EUT_ITEM2))
        self.assertStrEqual(
            'ITEM3', self.sut.eut_to_string(self.sut.EUT_ITEM3))

    def test_parse_invalid(self):
        self.assertEqual(self.sut.EUT_INVALID, self.sut.eut_parse(b'ITEM0'))
        self.assertEqual(self.sut.EUT_INVALID, self.sut.eut_parse(b'ITEm2'))

    def test_parse(self):
        self.assertEqual(self.sut.EUT_ITEM1, self.sut.eut_parse(b'ITEM1'))
        self.assertEqual(self.sut.EUT_ITEM2, self.sut.eut_parse(b'ITEM2'))
        self.assertEqual(self.sut.EUT_ITEM3, self.sut.eut_parse(b'ITEM3'))

    def test_parsei_invalid(self):
        self.assertEqual(self.sut.EUT_INVALID, self.sut.eut_parsei(b'ITEm0'))

    def test_parsei(self):
        self.assertEqual(self.sut.EUT_ITEM1, self.sut.eut_parsei(b'ITEm1'))
        self.assertEqual(self.sut.EUT_ITEM2, self.sut.eut_parsei(b'ITEm2'))
        self.assertEqual(self.sut.EUT_ITEM3, self.sut.eut_parsei(b'ITEm3'))

    def test_test_invalid_flag(self):
        self.assertZero(self.sut.eut_test_flag(0xffff, self.sut.EUT_INVALID))

    def test_test_flag_is_set(self):
        self.assertNotZero(self.sut.eut_test_flag(0x0001, self.sut.EUT_ITEM1))
        self.assertNotZero(self.sut.eut_test_flag(0x0002, self.sut.EUT_ITEM2))
        self.assertNotZero(self.sut.eut_test_flag(0x0004, self.sut.EUT_ITEM3))

    def test_test_flag_is_not_set(self):
        self.assertZero(self.sut.eut_test_flag(0xfffe, self.sut.EUT_ITEM1))
        self.assertZero(self.sut.eut_test_flag(0xfffd, self.sut.EUT_ITEM2))
        self.assertZero(self.sut.eut_test_flag(0xfffb, self.sut.EUT_ITEM3))

    def test_set_flag(self):
        self.assertEqual(0x0001, self.sut.eut_set_flag(
            0x0000, self.sut.EUT_ITEM1))
        self.assertEqual(0x0002, self.sut.eut_set_flag(
            0x0000, self.sut.EUT_ITEM2))
        self.assertEqual(0x0004, self.sut.eut_set_flag(
            0x0000, self.sut.EUT_ITEM3))

    def test_clear_flag(self):
        self.assertEqual(0xfffe, self.sut.eut_clear_flag(
            0xffff, self.sut.EUT_ITEM1))
        self.assertEqual(0xfffd, self.sut.eut_clear_flag(
            0xffff, self.sut.EUT_ITEM2))
        self.assertEqual(0xfffb, self.sut.eut_clear_flag(
            0xffff, self.sut.EUT_ITEM3))


Tester.go()
