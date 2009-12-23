space :=
space +=
$(space) :=
$(space) +=

SWIG_INCLUDE_python = /usr/include/python2.5
SWIG_INCLUDE_r = /usr/share/R/include

MODULE := $(PROJECT_NAME)

TARGET_LANGS = python

RUNTIME_SUFFIXES = pyc py R

.PHONY: swigclean wrap

wrap: $(foreach l,$(TARGET_LANGS),$(MODULE).$l.swig_wrap.so)

swigclean:
	@rm -rfv *$(MODULE)*swig_wrap.so
	@rm -rfv $(MODULE).*.swig_wrap.cc
	@find . -regextype posix-extended -type f -regex ".*\.($(subst $( ),,$(foreach s,$(RUNTIME_SUFFIXES),|$s)))" -exec rm -rfv '{}' \;

vimclean:
	@find . -regextype posix-extended -regex ".*(~|.swp)" -exec rm -rfv '{}' \;

-include $(foreach l,$(TARGET_LANGS),$(MODULE).$l.swig_wrap.d)

$(MODULE).%.swig_wrap.so: TARGET_LANG = $*
$(MODULE).%.swig_wrap.so: DL_PREFIX = $(call get_prefix,$(TARGET_LANG))
$(MODULE).%.swig_wrap.so: WRAP_LIB_LN_NAME = $(call get_wrap_lib_name,$@)

$(MODULE).%.swig_wrap.so: $(MODULE).%.swig_wrap.o $(DY_LIB_NAME)
	g++ -shared -Wl,-rpath=$(CURDIR),-soname=$@ -o $@ $< -L$(CURDIR) -l$(LIB_NAME_STEM)
	ln -fs $@ $(join $(dir $@),$(DL_PREFIX)$(WRAP_LIB_LN_NAME).so)

.INTERMEDIATE: %.swig_wrap.cc
$(MODULE).%.swig_wrap.cc: $(MODULE).%.swig_wrap.i
	$(call swig_depend,$<,cc,$(MODULE).$*.swig_wrap.d,-I$(PROJECT_INCLUDE_PATH))
	swig -c++ -$(TARGET_LANG) -module $(WRAP_LIB_LN_NAME) -I$(PROJECT_INCLUDE_PATH) $(SWIG_FLAGS) -o $@ $<

$(MODULE).python.swig_wrap.cc: SWIG_FLAGS += -classic
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
