CC = g++
CFLAGS = -Ofast
TARGET = Mag_calc
SRCS = main.cpp
SRCS += PBC.cpp
SRCS += spin.cpp
SRCS += system.cpp
OBJS = $(SRCS:.cpp=.o)

INCDIR = 
LIBDIR = 
LIBS = 
INSTDIR = /usr/local/bin/

$(TARGET): $(OBJS)
	$(CC) -o $@ $^

$(OBJS) : $(SRCS)
	$(CC) $(CFLAGS) $(INCDIR) -c $(SRCS)

clean:
	-rm -f $(OBJS) $(TARGET) *.d

rmo:
	-rm -f $(OBJS) *.d

rmdat:
	-rm -f *.dat

install: $(TARGET)
	install -s $(TARGET) $(INSTDIR)