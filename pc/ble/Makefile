SOURCES :=	$(wildcard *.cc)
OBJS :=		$(patsubst %.cc, %.o, $(SOURCES))
TARGET :=	beacon-scanner

CXXFLAGS :=	-Wall -Wextra -pedantic -Wshadow -Wpointer-arith 	\
		-Wcast-align -Wwrite-strings -Wmissing-declarations	\
		-Wno-long-long -Werror -Wunused-variable -std=c++17	\
		-D_XOPEN_SOURCE -O0 -g -I. -fno-elide-constructors	\
		-fPIC -Weffc++

LDLIBS :=	-lble++

ADAPTER :=	hci0

.PHONY: beacon-scanner
all: tags $(TARGET)
	@echo "-----"
	@sudo ./$(TARGET)
	@if [ -e core ]; then sudo chown kyle:kyle core ; fi

$(TARGET): $(OBJS)
	$(CXX) -o $@ $(LDFLAGS) $(OBJS) $(LDLIBS)

clean:
	rm -f $(TARGET) $(OBJS) tags

tags: $(SOURCES)
	ctags -R $(SOURCES)

.PHONY: reset-adapter
reset-adapter:
	sudo hciconfig $(ADAPTER) down
	sudo hciconfig $(ADAPTER) up
