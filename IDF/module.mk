IDF_SOURCES := $(shell find IDF/$(SRCDIR) -type f -name \*.$(SRCEXT))
SOURCES += $(IDF_SOURCES)
INCLUDE_FLAGS += -I IDF/$(INCDIR)
