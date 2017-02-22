RECON_SOURCES := $(shell find Recon/$(SRCDIR) -type f -name \*.$(SRCEXT))
SOURCES += $(RECON_SOURCES)
INCLUDE_FLAGS += -I Recon/$(INCDIR)
