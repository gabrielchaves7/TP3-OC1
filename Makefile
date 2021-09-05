CC=g++
CFLAGS=-Wall -Wextra
EXEC=./tp03
TMPOUT=tp03.testresult

$(EXEC): main.cpp
	$(CC) $(CFLAGS) main.cpp -o $(EXEC)

test: $(EXEC)
	@bash run_tests.sh $(EXEC) $(TMPOUT)

clean:
	rm -rf tp04