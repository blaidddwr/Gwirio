.RECIPEPREFIX := +
MAKEFLAGS := $(MAKEFLAGS) --no-print-directory
CXX := g++
NAME := unit
FILES := Gwirio.ut.files



build := ../build/unit/
run := ../run/

acxxflags := $(CXXFLAGS) -g -std=c++11 -I../include
aldflags := $(LDFLAGS) -L../lib
aldlibs := $(LDLIBS) -lgwirio

progf := $(run)$(NAME)

raw := $(shell cat $(FILES))
srcs := $(filter %.cpp,$(raw))

dpds := $(addprefix $(build),$(srcs:%.cpp=%.d))
objs := $(addprefix $(build),$(srcs:%.cpp=%.o))



.PHONY: clean depclean all unit check base

all: unit
unit: $(progf)

ifndef DEPIGNORE
include $(dpds)
endif

$(progf): $(objs) $(dpds)
+@echo "Building unit test."
+@$(CXX) $(objs) $(aldflags) $(aldlibs) -o $@

depend: $(dpds)
+@echo Done.

$(build)%.o : %.cpp
+@echo "Building object $(*F)."
+@$(CXX) $(acxxflags) -c $< -o $@

$(build)%.d: %.cpp
+@echo "Building depend $(*F)."
+@echo -n "$@ $(build)" > $@
+@$(CXX) $(acxxflags) -MM $< >> $@

base:
+@echo "Building base code..."
+@cd ../src && $(MAKE)

check:
+@echo "Running unit tests..."
+@cd $(run) && ./$(NAME)

clean:
+@echo "Cleaning all objects."
+@rm -f $(build)*.o

depclean:
+@echo "Cleaning all dependency files."
+@rm -f $(build)*.d
