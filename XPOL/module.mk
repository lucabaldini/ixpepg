XPOL_SOURCES := $(shell find XPOL/$(SRCDIR) -type f -name \*.$(SRCEXT))
SOURCES += $(XPOL_SOURCES)
INCLUDE_FLAGS += -I XPOL/$(INCDIR)
