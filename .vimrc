set hlsearch
color desert
set number

edit build_test.sh
vsplit makefile

tabe src/impl/matrix.c
vsplit test/matrix.c
split src/header/matrix.h

tabe src/impl/stats.c
vsplit test/stats.c
split src/header/stats.h

