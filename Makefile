CC = g++ -Wall -I include

OBJS = test.o

test: $(OBJS)
	$(CC) -o $@ $(OBJS)

%.o: src/%.cpp
	$(CC) -o $@ -c $<

.phony clean:
	rm -f test $(OBJS)
