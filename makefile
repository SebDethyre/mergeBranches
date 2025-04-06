CC = gcc
CFLAGS = -Wall -g
GTK_CFLAGS = `pkg-config --cflags gtk+-3.0`
GTK_LIBS = `pkg-config --libs gtk+-3.0`
GTK_INCLUDE = -I/usr/include/gtk-3.0
GTK_LIBDIR = -L/usr/lib/x86_64-linux-gnu
GTK_LIBRARIES = -lgtk-3 -lX11 -lXtst -lm 

SRC = c.c
TARGET = ~/sandbox/merge_boisson/merge_boisson

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(GTK_CFLAGS) $(GTK_INCLUDE) $(GTK_LIBDIR) $(GTK_LIBRARIES) $(GTK_LIBS)

clean:
	rm -f $(TARGET)

debug: $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(GTK_CFLAGS) $(GTK_INCLUDE) $(GTK_LIBDIR) $(GTK_LIBRARIES) $(GTK_LIBS)
	gdb $(TARGET)

