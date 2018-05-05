SOURCES :=	$(wildcard *.cc)
OBJS :=		$(patsubst %.cc, %.o, $(SOURCES))
TARGET :=	beacon-scanner
CXX :=		clang++

# CXXFLAGS :=	-Wall -Wextra -pedantic -Wshadow -Wpointer-arith 	\
# 		-Wcast-align -Wwrite-strings -Wmissing-declarations	\
# 		-Wno-long-long -Werror -Wunused-variable -std=c++17	\
# 		-D_XOPEN_SOURCE -O0 -g -I. -fno-elide-constructors	\
# 		-fPIC
CXXFLAGS :=	-Wall $(shell pkg-config --cflags dbus-1 dbus-c++-1)

LDLIBS :=	-lble++

ADAPTER :=	hci0

.PHONY: beacon-scanner
all: tags $(TARGET)
	@echo "-----"
	@sudo ./$(TARGET)

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
