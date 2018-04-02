CC ?= gcc
CFLAGS ?= 

OUT := particledector

IN := src/main.c \


$(OUT): $(IN)
	$(CC) $(CFLAGS) -o $@ $<

clean:
	-@rm $(OUT)
