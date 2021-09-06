CC=g++
CFLAGS=-Wall -Wextra
EXEC=./tp03

$(EXEC): main.cpp
	$(CC) $(CFLAGS) main.cpp -o $(EXEC)

test: $(EXEC)
	@bash extensao.sh $(EXEC)
	
clean:
	rm -rf tp03
	rm -rf result.01
	rm -rf result.02
	rm -rf result.03
	rm -rf result.04
	rm -rf result.05