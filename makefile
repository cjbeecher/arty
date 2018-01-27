CC=gcc
INCLUDE=-Isrc/header/
COMPILEO=-fPIC -g -O -c

SO=-shared -o
MATRIX=src/impl/matrix.c
MATRIXO=build/libmatrix.o
MATRIXSO=build/libmatrix.so
STATS=src/impl/stats.c
STATSO=build/libstats.o
STATSSO=build/libstats.so

stats :
	$(CC) $(INCLUDE) $(COMPILEO) $(STATS) -o $(STATSO)
	$(CC) $(STATSO) $(SO) $(STATSSO)
	rm $(STATSO)

matrix : stats
	$(CC) $(INCLUDE) $(COMPILEO) $(MATRIX) -o $(MATRIXO)
	$(CC) $(MATRIXO) $(SO) $(MATRIXSO)
	rm $(MATRIXO)

MATRIXTESTC=test/matrix.c
MATRIXTEST=-o build/matrix_test
STATSTESTC=test/stats.c
STATSTEST=-o build/stats_test

matrix_test : matrix
	$(CC) $(INCLUDE) -fPIC -g $(MATRIXTESTC) $(MATRIXTEST) $(MATRIXSO) -lm

stats_test : stats
	$(CC) $(INCLUDE) -fPIC -g $(STATSTESTC) $(STATSTEST) $(STATSSO) -lm

clean :
	rm build/*

