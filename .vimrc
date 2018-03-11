color desert
set hlsearch
set number

edit build_test.sh
vsplit makefile

tabe src/impl/matrix.c
vsplit test/matrix.c
split src/header/matrix.h

tabe src/impl/stats.c
vsplit test/stats.c
split src/header/stats.h

tabe src/impl/neural_network.c
" vsplit test/neural_network.c
vsplit src/header/neural_network.h

" tabe src/impl/graph.c
" vsplit test/graph.c
" split src/header/graph.h

tabe src/impl/nnopti.c
vsplit test/neural_network.c
split src/header/nnopti.h

tabe src/impl/nnactiv.c
vsplit src/header/nnactiv.h

