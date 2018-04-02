CC ?= smlrcc
CFLAGS ?= 

OUT := particledetector

IN := src/main.c \


$(OUT): $(IN)
	$(CC) $(CFLAGS) -o $@ $<

clean:
	-@rm $(OUT)
