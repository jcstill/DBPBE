# Compiler Specific:
COMP=g++
CFLAG=-c
WFLAG=-Wall
OFLAG=-o
testnum=0

# Program Specific:
SOURCES=	main.cpp		\
			coordinate.cpp

OBJECTS=$(SOURCES:.cpp=.o)
HEADERS=$(SOURCES:.cpp=.h)
EXECUTABLE=DBPBE

# Start of Make:
Start: clean $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(COMP) $(OBJECTS) $(OFLAG) $@ $(WFLAG)

.cpp.o:
	$(COMP) -D mode=$(testnum) $(CFLAG) $< $(OFLAG) $@ $(WFLAG)

# Cleanup Routines:
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

clean-o:
	rm -f $(OBJECTS)

clean-b:
	rm -f $(EXECUTABLE)

clean-tar:
	rm -f $(EXECUTABLE).tar

show-tar:
	tar -tvf $(EXECUTABLE).tar

tar:
	tar -cf $(EXECUTABLE).tar *.cpp *.h