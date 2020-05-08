# Compiler Specific:
COMP=g++
CFLAG=-c
WFLAG=-Wall
OFLAG=-o

# Program Specific:
SOURCES=	main.cpp

OBJECTS=$(SOURCES:.cpp=.o)
HEADERS=$(SOURCES:.cpp=.h)
EXECUTABLE=DBPBE


# Start of Make:
Start: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(COMP) $(OBJECTS) $(OFLAG) $@ $(WFLAG)

.cpp.o:
	$(COMP) $(CFLAG) $< $(OFLAG) $@ $(WFLAG)

# Cleanup Routines:
clean:
	rm $(OBJECTS) $(EXECUTABLE) $(EXECUTABLE).tar

clean-o:
	rm $(OBJECTS)

clean-b:
	rm $(EXECUTABLE)

clean-tar:
	rm $(EXECUTABLE).tar

show-tar:
	tar -tvf $(EXECUTABLE).tar

tar:
	tar -cf $(EXECUTABLE).tar *.cpp *.h