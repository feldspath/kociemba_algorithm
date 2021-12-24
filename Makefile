CPPFLAGS = -g -std=c++14 -Wall
CXX = g++

ODIR := build
SDIR := src

_TARGETS := main
TARGETS := $(patsubst %, $(ODIR)/%,$(_TARGETS))
TARGETS_SRC := $(patsubst %, $(SDIR)/%.cpp, $(_TARGETS))
TARGETS_OBJ := $(addsuffix .o, $(TARGETS));

CPP_FILES := $(filter-out $(TARGETS_SRC),$(wildcard $(SDIR)/*.cpp))
OBJ_FILES := $(patsubst $(SDIR)/%.cpp, $(ODIR)/%.o,$(CPP_FILES)) 

#-------
# RULES 
#-------

all : $(TARGETS)
	@echo "\e[32m\e[1mDone!\e[0m"

clean: 
	@rm -rf $(ODIR)/*

$(ODIR)/% : $(OBJ_FILES) $(TARGETS_OBJ)
	@echo "\e[32mLinking $@...\e[0m"
	@$(CXX) -g -o $@ $@.o $(OBJ_FILES) $(CPPFLAGS)

$(ODIR)/%.o : $(SDIR)/%.cpp
	@echo "\e[32mCompiling $<...\e[0m"
	@$(CXX) -g -o $@ -c $< $(CPPFLAGS)

.PHONY: all clean

# Comment this line to remove .o files after compilation
.SECONDARY: $(OBJ_FILES) $(TARGETS_OBJ)