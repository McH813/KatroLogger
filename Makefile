BIN=/usr/bin/
EXEC=katrologger

all:
	gcc src/event.c src/main.c src/usage.c src/curl_smtp.c src/status.c -o $(EXEC) -lX11 -w

make install:
	mv $(EXEC) $(BIN)

uninstall:
	rm -f $(BIN)$(EXEC)
