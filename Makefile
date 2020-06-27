PROGRAMS=test_receiver test_sender

all: $(PROGRAMS)

CFLAGS=-g -Og -W -Wall -Wno-unused-result -Wno-unused-parameter -Werror

test_receiver: test_receiver.c
	gcc $(CFLAGS) -o $@ $^

test_sender: test_sender.c
	gcc $(CFLAGS) -o $@ $^

clean:
	rm -f $(PROGRAMS) *~

.PHONY: clean all
