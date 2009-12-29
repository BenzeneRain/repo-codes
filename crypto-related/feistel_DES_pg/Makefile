CPPFLAGS = -I./include 
#CFLAGS   = -O1
CFLAGS   = -ggdb3
LDFLAGS  = -lm -lssl

OBJS =feistel_pg_lib.o test.o

.PHONY: all
all: $(OBJS)
	$(CC) $(OBJS) -o test $(CPPFLAGS) $(CFLAGS) $(LDFLAGS)

$(OBJS): %.o:%.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean: 
	rm -f *.o
	rm -f test
