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
NN=src/impl/neural_network.c
NNO=build/libnn.o
NNSO=build/libnn.so

stats :
	$(CC) $(INCLUDE) $(COMPILEO) $(STATS) -o $(STATSO)
	$(CC) $(STATSO) $(SO) $(STATSSO)
	rm $(STATSO)

matrix : stats
	$(CC) $(INCLUDE) $(COMPILEO) $(MATRIX) -o $(MATRIXO)
	$(CC) $(MATRIXO) $(SO) $(MATRIXSO)
	rm $(MATRIXO)

neural : matrix
	$(CC) $(INCLUDE) $(COMPILEO) $(NN) -o $(NNO)
	$(CC) $(NNO) $(SO) $(NNSO)
	rm $(NNO)

MATRIXTESTC=test/matrix.c
MATRIXTEST=-o build/matrix_test
NNTESTC=test/neural_network.c
NNTEST=-o build/nn_test

matrix_test : matrix
	$(CC) $(INCLUDE) -fPIC -g $(MATRIXTESTC) $(MATRIXTEST) $(MATRIXSO) $(STATSSO) -lm

stats_test : stats
	$(CC) $(INCLUDE) -fPIC -g $(STATSTESTC) $(STATSTEST) $(STATSSO) -lm

nn_test : neural
	$(CC) $(INCLUDE) -fPIC -g $(NNTESTC) $(NNTEST) $(NNSO) -lm

clean :
	rm build/*

