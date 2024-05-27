###########################################################
#
# Example GNUmakefile to build an Application 
#
###########################################################


#----------------------------------------------------------------------------
#        user variables
#----------------------------------------------------------------------------

# name of the program
PROGNAME = lhe2root

# source files for the binary
# leave this commented out if your Application does not produce binary files
BINSRCS = $(PROGNAME).C 

USERINCLUDES = `root-config --cflags`
USERLIBS += `root-config --glibs` 

#----------------------------------------------------------------------------
#        do not modify anything below in order to use top level makefile
#----------------------------------------------------------------------------

# binary files with path
BIN = $(patsubst %.C,%,$(BINSRCS))

# object files for the binaries without path
BINOBJS = $(patsubst %.C,%.o,$(BINSRCS))

# object files for the binaries with path
BINOBJ = $(patsubst %,%,$(BINOBJS))

# source files without path
SRCS = $(filter-out $(BINSRCS),$(wildcard *.C))

# object files without path
OBJS = $(patsubst %.C,%.o,$(SRCS))

# object files with path
OBJ = $(patsubst %,$(OBJDIR)/%,$(OBJS))


# c++ compiler
ifdef MY_CXX
  CXX = $(MY_CXX)
else
  CXX = g++
endif

# compiler flags
ifdef MARLINDEBUG
 CXXFLAGS = -g -Wall -ansi
else
 CXXFLAGS = -O3 -Wall -ansi
endif 

# pre-processor flags
CPPFLAGS += $(USERINCLUDES)

LIBS += $(USERLIBS)


# linker
LD = $(CXX)

# linker flags
#LDFLAGS = -Wl,--demangle -m32

# archiever
#AR = ar cru



.PHONY: all clean distclean

all: bin

ifdef BINSRCS
.PHONY: bin
bin: $(BINOBJ) $(BIN)
	rm -f $(BINOBJ)
endif

clean:
	rm -f $(OBJ) $(BINOBJ) $(BIN) $(LIB)

# tell make to include dependencies
-include $(DEP)

# binary rule
$(BIN) : $(OBJ) $(BINOBJ)
	$(LD) $@.o $(LDFLAGS) $(LIBS) -o $@

# objects rule
%.o: %.cc
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@


# end
