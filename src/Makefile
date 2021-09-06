CC=g++
CFLAGS=-Wall -Wextra
EXEC=./tp03

$(EXEC): main.cpp
	$(CC) $(CFLAGS) main.cpp -o $(EXEC)

test: $(EXEC)
	@bash extensao.sh $(EXEC)
	
clean:
	rm -rf results/result.01
	rm -rf results/result.02
	rm -rf results/result.03
	rm -rf results/result.04
	rm -rf results/result.05
	rm -rf tp03