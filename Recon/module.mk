RECON_SOURCES := $(shell find $(IXPESWROOT)/Recon/$(SRCDIR) -type f -name \*.$(SRCEXT))
SOURCES += $(RECON_SOURCES)
INCLUDE_FLAGS += -I $(IXPESWROOT)/Recon/$(INCDIR)
