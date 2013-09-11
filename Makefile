CXX		= g++
CXXFLAGS	= -Wall -O2
COMMON		= classgen.o Generator.o ParseCmdLine.o Date.o Time.o
TARGET		= classgen
INSTALL_DIR	= /usr/local/bin

all: $(TARGET)

$(TARGET): $(COMMON)
	$(CXX) -o $(TARGET) $(COMMON)
	strip $(TARGET)

install: $(TARGET)
	cp $(TARGET) $(INSTALL_DIR)

clean:
	@rm -vf *.o *~ core DEADJOE $(COMMON)
	@rm -vf $(TARGET)

dist:
	make clean && cd .. && tar -czvf $(TARGET).tar.gz $(TARGET)

