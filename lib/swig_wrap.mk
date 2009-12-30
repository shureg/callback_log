space :=
space +=
$(space) :=
$(space) +=
, := ,

PYTHON_PREFIX := $(shell env python -c "import sys; print sys.prefix")
PYTHON_VERSION_XY := $(shell env python -c "import sys; print sys.version" | head -n1 | cut -d' ' -f1 | cut -d'.' -f1-2)

MODULE_PATH_python := $(PYTHON_PREFIX)/lib/python$(PYTHON_VERSION_XY)/site-packages

SUFFIX_python = py

SWIG_INCLUDE_python = $(PYTHON_PREFIX)/include/python$(PYTHON_VERSION_XY)
SWIG_INCLUDE_r = /usr/share/R/include

MODULE := $(PROJECT_NAME)

TARGET_LANGS := python

RUNTIME_SUFFIXES = pyc py R

INTERFACE_SOURCES = $(foreach l,$(TARGET_LANGS),$(MODULE).$l.swig_wrap.cc)
INTERFACE_DEPS = $(patsubst %.cc,%.d,$(INTERFACE_SOURCES))

.PHONY: swigclean wrap swiginstall

.INTERMEDIATE: $(INTERFACE_SOURCES)

.DELETE_ON_ERROR: $(INTERFACE_SOURCES)

wrap: $(foreach l,$(TARGET_LANGS),$(MODULE).$l.swig_wrap.so)

swigclean:
	@rm -rfv *$(MODULE)*swig_wrap.so
	@rm -rfv $(MODULE).*.swig_wrap.cc
	@find . -regextype posix-extended -type f -regex ".*\.($(subst $( ),,$(foreach s,$(RUNTIME_SUFFIXES),|$s)))" -exec rm -rfv '{}' \;

vimclean:
	@find . -regextype posix-extended -regex ".*(~|.swp)" -exec rm -rfv '{}' \;

swiginstall: $(foreach l,$(TARGET_LANGS),$l_install)

%_install: INSTALLABLE_SCRIPT = $(if $(SUFFIX_$*),$(shell find . -maxdepth 1 -type f -regex ".*$(MODULE)_$*_swig_wrap\.$(SUFFIX_$*)"))
%_install: INSTALLABLE_LIB = $(shell find . -maxdepth 1 -type f -regex ".*$(MODULE)\.$*\.swig_wrap\.so")

%_install:
	install -Dv --backup=numbered $(INSTALLABLE_SCRIPT) $(MODULE_PATH_$*)/$(notdir $(INSTALLABLE_SCRIPT))
	install -Dv --backup=numbered $(INSTALLABLE_LIB) $(MODULE_PATH_$*)/$(notdir $(INSTALLABLE_LIB))
	$(call make_link,$(MODULE_PATH_$*)/$(notdir $(INSTALLABLE_LIB)),$(call get_prefix,$*)$(call get_wrap_lib_name,$(INSTALLABLE_LIB)).so)


-include $(INTERFACE_DEPS)

$(MODULE).%.swig_wrap.so: TARGET_LANG = $*
$(MODULE).%.swig_wrap.so: DL_PREFIX = $(call get_prefix,$(TARGET_LANG))
$(MODULE).%.swig_wrap.so: WRAP_MODULE_NAME = $(call get_wrap_lib_name,$@)
$(MODULE).%.swig_wrap.so: WRAP_LIB_SO_NAME = $(DL_PREFIX)$(WRAP_MODULE_NAME).so
$(MODULE).%.swig_wrap.so: SWIG_RPATH_FLAG = $(if $(filter-out release,$(PROJECT_CONFIGURATION_TYPE)),$(,)-rpath=$(CURDIR),)

$(MODULE).%.swig_wrap.so: $(MODULE).%.swig_wrap.o $(DY_LIB_NAME)
	g++ -shared -Wl,-soname=$@$(SWIG_RPATH_FLAG) -o $@ $< -L. -l$(LIB_NAME_STEM)
	@$(make_link $@,$(WRAP_LIB_SO_NAME))

$(MODULE).%.swig_wrap.cc: $(MODULE).%.swig_wrap.swg
	$(call swig_depend,$<,cc,$(MODULE).$*.swig_wrap.d,-I$(PROJECT_INCLUDE_PATH))
	swig -c++ -$(TARGET_LANG) -module $(WRAP_MODULE_NAME) -I$(PROJECT_INCLUDE_PATH) $(SWIG_FLAGS) -o $@ $<

#$(MODULE).python.swig_wrap.cc: SWIG_FLAGS += -classic
$(MODULE).python.swig_wrap.o: LIB_INCLUDE_PATHS += $(SWIG_INCLUDE_python)

$(MODULE).r.swig_wrap.o: LIB_INCLUDE_PATHS += $(SWIG_INCLUDE_r)

#%.o: %.cc
#	g++ -c -g -fPIC -o $@ $(INCLUDE_FLAGS) $<


#usage $(call interface_file,c++_suffix,dep_file,flags)
define swig_depend
swig -c++ -MM $4 $1 | sed 's/\.cxx:/\.$2:/' > $3
endef

PREFIXED_LANGS = python
define get_prefix
$(if $(findstring $1,$(PREFIXED_LANGS)),_)
endef

define get_wrap_lib_name
$(subst .,_,$(basename $(notdir $1)))
endef

#usage $(call get_lang,filename,separator)
define get_lang
$(filter-out $(MODULE) swig_wrap swig wrap, $(subst $2,$( ),$1))
endef

#usage $(call make_link,target,linkname)
define make_link
ln -fsv $1 $(join $(dir $1),$2)
endef
