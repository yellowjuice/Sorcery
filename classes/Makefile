CXX = clang++ -std=c++20
CXXFLAGS = -Wall -g -fsanitize=address # use -MMD to generate dependencies
SOURCES = ${wildcard *.cc} ${wildcard *_impl/*.cc} ${wildcard asciiart/*.cc}  # list of all .cc files in the current directory
OBJECTS = ${SOURCES:.cc=.o}  # .o files depend upon .cc files with same names
DEPENDS = ${OBJECTS:.o=.d}   # .d file is list of dependencies for corresponding .cc file
EXEC=sorcery

# First target in the makefile is the default target.
$(EXEC): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(EXEC)  $(LIBFLAGS) -lX11


-include ${DEPENDS}

.PHONY: clean tests
clean:
	rm  -f $(OBJECTS) $(DEPENDS) $(EXEC)
