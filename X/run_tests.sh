#!/bin/bash

# python3 -m venv .venv
# . .venv/bin/activate
# pip3 install ctdd
# pip3 install setuptools           # until ctdd is fixed
# sudo apt install python3-dev

set -e

# until ctdd gets `Tester.addMacro('ONELETTER_TEST').go()` you need to define the macro:
CFLAGS=-DONELETTER_TEST python3 x_tdd.py
CFLAGS=-DONELETTER_TEST python3 x_enum_tdd.py
CFLAGS=-DONELETTER_TEST python3 x_impl_tdd.py
