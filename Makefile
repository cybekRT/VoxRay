PROJECT=VoxRay
LIBS=SDL2

CFLAGS=-O2 -ggdb -Wall -Wextra $(shell pkg-config $(LIBS) --cflags)
CXXFLAGS=$(CFLAGS)

SRC+=$(wildcard src/*.c src/*.cpp)
OBJS=$(addsuffix .o,$(basename $(SRC)))

LDFLAGS+=$(shell pkg-config $(LIBS) --libs) $(addprefix -l,$(LIBS))

all: $(PROJECT)

clean:
	rm $(OBJS) $(PROJECT) $(PROJECT).exe 2>/dev/null || true

$(PROJECT): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)
	
.PHONY: all clean
