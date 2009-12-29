OBJS = encrypt decrypt

.PHONY: all
all: $(OBJS)

$(OBJS): %:%.cpp
	g++ -lcrypto++ $< -ggdb3 -o $@
