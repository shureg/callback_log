-include lib.config.mk

DY_LIB_NAME = lib$(LIB_NAME_STEM).so
ST_LIB_NAME = lib$(LIB_NAME_STEM).a

LIB_OBJECTS = $(patsubst %$(LIB_SRC_SUFFIX), %$(LIB_OBJ_SUFFIX), $(shell find . -name "*$(LIB_SRC_SUFFIX)" ! -name "*.swig_wrap$(LIB_SRC_SUFFIX)" -type f))

LIB_DEP_FILES = $(patsubst %$(LIB_OBJ_SUFFIX), %$(LIB_SRC_DEP_SUFFIX), $(LIB_OBJECTS))

LIB_DEP_FLAGS = $(foreach l,$(LIB_EXT_DEPS),-l$l)

LIB_DEP_PATH_FLAGS = $(foreach L,$(LIB_EXT_DEP_PATHS),-L$L)

ifndef PROJECT_INCLUDE_PATH
   $(error Value for PROJECT_INCLUDE_PATH must be set before libraries can be compiled)
endif

LIB_INCLUDE_PATHS += $(PROJECT_INCLUDE_PATH)

ifeq "$(PROJECT_CONFIGURATION_TYPE)" "debug_strict"
   LIB_WARNINGS += error
endif

LIB_WARNING_FLAGS = $(foreach W,$(LIB_WARNINGS),-W$W)

LIB_DEFINES += $(PROJECT_DEFINES)

LIB_DEFINE_FLAGS =$(foreach D,$(LIB_DEFINES),-D$D=$($D))

ifeq "$(MAKECMDGOALS)" "install"
   ifndef INSTALL_PREFIX
      $(error INSTALL_PREFIX value must be set for installation to proceed)
   endif
endif

lib: $(DY_LIB_NAME) $(ST_LIB_NAME)

$(DY_LIB_NAME): $(LIB_OBJECTS)
	g++ -shared -Wl,-soname,$@ -o $@ $(LIB_DEP_FLAGS) $(LIB_DEP_PATH_FLAGS) $^

$(ST_LIB_NAME): $(LIB_OBJECTS)
	ar -rv $@ $^

clean: swigclean
	@rm -rfv $(DY_LIB_NAME)
	@rm -rfv $(ST_LIB_NAME)
	@find -name "*$(LIB_OBJ_SUFFIX)" -type f -exec rm -rfv '{}' \;  

.PHONY: install
install: lib swiginstall
	install -Dv $(DY_LIB_NAME) $(INSTALL_PREFIX)/lib/$(DY_LIB_NAME)
	install -Dv $(ST_LIB_NAME) $(INSTALL_PREFIX)/lib/$(ST_LIB_NAME)

-include $(LIB_DEP_FILES)

%$(LIB_OBJ_SUFFIX): %$(LIB_SRC_SUFFIX)

include swig_wrap.mk 

LIB_INCLUDE_FLAGS = $(call flags,$(LIB_INCLUDE_PATHS),I)

%$(LIB_OBJ_SUFFIX): %$(LIB_SRC_SUFFIX)
	$(call make_depend,$<,$@,$*$(LIB_SRC_DEP_SUFFIX),$(LIB_INCLUDE_FLAGS))
	g++ -c -g -fPIC $(LIB_WARNING_FLAGS) $(LIB_INCLUDE_FLAGS) $(LIB_DEFINE_FLAGS) -o $@ $<

#A script to generate dependency files for c/c++ sources
#usage $(call make_depend,src_file,obj_file,dep_file,flags)
define make_depend
   g++ -MM -MF $3 -MP -MT $2 $4 $1
endef

#usage $(call flags,list,flag)
define flags
$(foreach f,$1,-$2$f)
endef
