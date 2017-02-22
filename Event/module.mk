EVENT_SOURCES := $(shell find Event/$(SRCDIR) -type f -name \*.$(SRCEXT))
SOURCES += $(EVENT_SOURCES)
INCLUDE_FLAGS += -I Event/$(INCDIR)
