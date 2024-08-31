CC ?= gcc
CFLAGS = -g

# ================= BUILD =================
all: test

# Build test
test: test.o map.o
	$(CC) -o $@ $^

# ================ COMPILE ================
# Compile test
test.o: test.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compile c-map
map.o: src/map.c
	$(CC) $(CFLAGS) -c $< -o $@

# ================= CLEAN =================
clean:
	rm -rf *.o
	rm -rf test
