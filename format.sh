#!/bin/bash

find . -regex '.*\.\(cpp\|h\|hpp\|cc\|cxx\)' -exec clang-format -style=WebKit -i {} \;
