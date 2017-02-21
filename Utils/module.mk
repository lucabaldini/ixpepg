UTILS_SOURCES := $(shell find Utils/$(SRCDIR) -type f -name \*.$(SRCEXT))
SOURCES += $(UTILS_SOURCES)
INCLUDE_FLAGS += -I Utils/$(INCDIR)
