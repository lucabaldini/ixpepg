EVENT_SOURCES := $(shell find $(IXPESWROOT)/Event/$(SRCDIR) -type f -name \*.$(SRCEXT))
SOURCES += $(EVENT_SOURCES)
INCLUDE_FLAGS += -I $(IXPESWROOT)/Event/$(INCDIR)
