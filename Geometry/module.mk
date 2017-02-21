GEOMETRY_SOURCES := $(shell find Geometry/$(SRCDIR) -type f -name \*.$(SRCEXT))
SOURCES += $(GEOMETRY_SOURCES)
INCLUDE_FLAGS += -I Geometry/$(INCDIR)
