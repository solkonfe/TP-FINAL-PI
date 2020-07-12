OBJS = backend.o lectura.o query.o
BUE = mainBUE.o
VAN = mainVAN.o
BINARYBUE = arbolesADTBUE
BINARYVAN = arbolesADTVAN
CFLAGS = -pedantic -std=c99 -Wall -fsanitize=address -g
QUERY = query1.csv query2.csv query3.csv

programaBUE: $(OBJS) $(BUE)
	gcc $(CFLAGS) -o $(BINARYBUE) $(BUE) $(OBJS)
  
programaVAN: $(OBJS) $(VAN)
	gcc $(CFLAGS) -o $(BINARYVAN) $(VAN) $(OBJS)

mainBUE.o: mainBUE.c query.h
	gcc $(CFLAGS) -c mainBUE.c

mainVAN.o: mainVAN.c query.h
	gcc $(CFLAGS) -c mainVAN.c

backend.o: backend.c backend.h
	gcc $(CFLAGS) -c backend.c

query.o: query.c query.h
	gcc $(CFLAGS) -c query.c

lectura.o: lectura.c lectura.h
	gcc $(CFLAGS) -c lectura.c

clean:
	rm -f $(OBJS) $(BUE) $(VAN)

delexecutables: 
	rm -f $(BINARYBUE) $(BINARYVAN)

delquery:
	rm -f $(QUERY)
