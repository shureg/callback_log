LIB_NAME_STEM ?= $(PROJECT_NAME)

LIB_SRC_SUFFIX ?= .cc

LIB_OBJ_SUFFIX ?= .o

LIB_SRC_DEP_SUFFIX ?= .d

LIB_EXT_DEPS ?= boost_date_time

#LIB_EXT_DEP_PATHS ?= /usr/local/lib

#BOOST_INCLUDE_PATH ?= /usr/local/include/boost-1_39

#LIB_INCLUDE_PATHS += $(BOOST_INCLUDE_PATH)

LIB_WARNINGS = all overloaded-virtual
