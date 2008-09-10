# RAPTOR_CPPFLAGS := $(shell raptor-config --cflags)
# RAPTOR_LDFLAGS := $(shell raptor-config --libs)
RAPTOR_CPPFLAGS := $(shell /Users/dajobe/dev/redland/raptor/raptor-src-config --cflags)
RAPTOR_LDFLAGS := $(shell /Users/dajobe/dev/redland/raptor/raptor-src-config --libs)

CPPFLAGS= -I. $(RAPTOR_CPPFLAGS)
CXXFLAGS=-g
LDFLAGS=-g $(RAPTOR_LDFLAGS)

all: rapper

RAPTORPP_SRCS=RaptorException.cc \
RaptorParser.cc \
RaptorParserDescriptor.cc \
RaptorTriple.cc \
RaptorUri.cc \
RaptorWorld.cc

RAPTORPP_OBJS=$(RAPTORPP_SRCS:.cc=.o)

libraptorpp.a:  $(RAPTORPP_OBJS)
	$(RM) $@
	$(AR) $(ARFLAGS) $@ $(RAPTORPP_OBJS) && ranlib $@

rapper: rapper.o libraptorpp.a
	$(LINK.cc) $^ $(LOADLIBES) $(LDLIBS) -o $@
