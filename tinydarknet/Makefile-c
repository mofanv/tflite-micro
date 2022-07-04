VPATH=./src/:./examples
EXEC=tinydarknet
OBJDIR=./obj/

CC=gcc
#OPTS=-Ofast
OPTS=-O0 -g
LDFLAGS= -lm -pthread
COMMON= -Iinclude/ -Isrc/
CFLAGS=-Wall -Wno-unused-result -Wno-unknown-pragmas -Wfatal-errors -fPIC

CFLAGS+=$(OPTS)


OBJ=gemm.o utils.o list.o blas.o parser.o option_list.o network.o dropout_layer.o softmax_layer.o connected_layer.o cost_layer.o activation_layer.o

EXECOBJA=classifier.o darknet.o


EXECOBJ = $(addprefix $(OBJDIR), $(EXECOBJA))
OBJS = $(addprefix $(OBJDIR), $(OBJ))
DEPS = $(wildcard src/*.h) Makefile include/darknet.h

all: obj $(EXEC)

$(EXEC): $(EXECOBJ) $(OBJS)
	$(CC) $(COMMON) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(OBJDIR)%.o: %.c $(DEPS)
	$(CC) $(COMMON) $(CFLAGS) -c $< -o $@

obj:
	mkdir -p obj

.PHONY: clean

clean:
	rm -rf $(OBJS) $(EXEC) $(EXECOBJ) $(OBJDIR)/*