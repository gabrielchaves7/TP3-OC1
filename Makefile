CC=g++
CFLAGS=-Wall -Wextra
EXEC=./tp03

$(EXEC): main.cpp
	$(CC) $(CFLAGS) main.cpp -o $(EXEC)

test: $(EXEC)
	@bash extensao.sh $(EXEC)
	
clean:
	rm -rf tp04