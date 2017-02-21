#The executable we want to create
TARGET := testGeometry

#Executable output directory
TARGETDIR := bin

#Package dependencies
MODULES := Utils Geometry XPOL

#Directories with .cpp and .h.
#This structure is assumed for all the modules involved
SRCDIR := src
INCDIR := include

#We will have only one global build dir and one global dependency dir
BUILDDIR := build
DEPDIR   := dep

#The relevant files extension
SRCEXT := cpp
DEPEXT := d
OBJEXT := o

# Compiler
CC := g++

#Compiler flags
CPPFLAGS := -g -Wall -O2 --std=gnu++14

#We are using gcc to auto generate dependency for us (i.e. find include directives in the .cpp and .h files).
#See http://make.mad-scientist.net/papers/advanced-auto-dependency-generation/ for more info
#These are the special GCC-specific flags which convince the compiler to generate the dependency file. Full descriptions can be found in the GCC manual section Options Controlling the Preprocessor:
# -MT : set the name of the target in the generated dependency file.
# -MMD : generate dependency information as a side-effect of compilation, not instead of compilation. This version omits system headers from the generated dependencies; if you prefer to preserve system headers as prerequisites, use -MD.
# -MP : adds a target for each prerequisite in the list, to avoid errors when deleting files.
# -MF : write the generated dependency file to a temporary location $(DEPDIR)/$*.Td.
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td

#Rename the generated temporary dependency file to the real dependency file. We do this in a separate step so that failures during the compilation won’t leave a corrupted dependency file.
POSTCOMPILE = mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d

#List of all required source files: each module will add to this list
SOURCES := testMain.cpp

#Include path list (each module will add to this list too)
INCLUDE_FLAGS :=

#Load source files and include path from the .mk files in the submodules
include $(patsubst %,%/module.mk,$(MODULES))

#Register all the source directories in vpath, so that make will find the .cpp
#files without need for the full path in the rules
vpath %.cpp $(sort $(dir $(SOURCES)))

#FIXME: the same trick should work for the .h too, but for some reason it
#doesn't. I have switched to the -I option instead

#The rule that will be used to compile
COMPILE = $(CC) $(DEPFLAGS) $(CPPFLAGS) -c $(INCLUDE_FLAGS)


###### DO NOT CHANGE ANYTHING BELOW THIS LINE ######


#Create the list of .o files by changing the extension of the source files
#and redirecting the path to point to the build directory
#NOTE: 'notdir' remove everything from the path up to the last /, leaving basically the filename+extension
OBJECTS := $(addprefix $(BUILDDIR)/,$(notdir $(SOURCES:.$(SRCEXT)=.$(OBJEXT))))

#Default Make
all: $(TARGETDIR)/$(TARGET)

#Remake
remake: cleaner all

#Clean only Objects
clean:
	@$(RM) -rf $(BUILDDIR)

#Full Clean, Objects and Binaries 
cleaner: clean
	@$(RM) -rf $(TARGETDIR)

#Link (the dependency after the pipeline are order dependency)
$(TARGETDIR)/$(TARGET): $(OBJECTS) | $(TARGETDIR)
	$(CC) $(DEPFLAGS) $(CPPFLAGS) $^ -o $(TARGETDIR)/$(TARGET)

#Rule for building object files from .cpp files
$(BUILDDIR)/%.o: %.$(SRCEXT) $(DEPDIR)/%.$(DEPEXT) | $(BUILDDIR) $(DEPDIR)
	$(COMPILE) -o $@ $<
	$(POSTCOMPILE)

#Make the directories if they do not exist
$(TARGETDIR):
	@mkdir -p $(TARGETDIR)

$(BUILDDIR):
	@mkdir -p $(BUILDDIR)

$(DEPDIR):
	@mkdir -p $(DEPDIR)

#Create a pattern rule with an empty recipe, so that make won’t fail if the dependency file doesn’t exist
$(DEPDIR)/%.$(DEPEXT): ;

# Mark the dependency files precious to make, so they won’t be automatically deleted as intermediate files.
.PRECIOUS: $(DEPDIR)/%.$(DEPEXT)

#Include the dependency files that exist: translate each file listed in SOURCES into its dependency file. Use wildcard to avoid failing on non-existent files.
include $(wildcard $(patsubst %,$(DEPDIR)/%.$(DEPEXT),$(notdir $(basename $(SOURCES)))))

#Non-File Targets
.PHONY: all remake clean cleaner
