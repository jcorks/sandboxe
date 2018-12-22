LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)



DYNACOE_INSTALL_PATH_CORRECTED := $(shell cat ./PATH)
DYNACOE_VER         = $(shell cat "$(DYNACOE_INSTALL_PATH_CORRECTED)/userspace/ver/DEFAULT")
DYNACOE_ROOT        = $(DYNACOE_INSTALL_PATH_CORRECTED)/userspace/ver/$(DYNACOE_VER)/
DYNACOE_LIB_PATH    = $(DYNACOE_ROOT)/build/lib/

# Basic makefile for Dynacoe

OUTPUT_NAME = $(shell cat ./PROJECT)

SRCS = $(shell cat ../SOURCES)
INCS = $(shell if [ -f ../INCLUDES ] ; then cat ../INCLUDES ; fi)
FLGS = $(shell cat "$(DYNACOE_LIB_PATH)lib_compileropts") $(shell if [ -f ../FLAGS ] ; then cat ../FLAGS ; fi)
LIBS = $(shell if [ -f ../LIBRARIES ] ; then cat ../LIBRARIES ; fi)

# Turn all 
SRCS := $(patsubst %,../%,$(SRCS))






# Define Dynacoe assets
#DYNACOE_INPUT_BACKEND_LIBS_GAINPUT = -lgainputstatic
DYNACOE_INC_PATHS   = /DynacoeSrc/includes/  /$(shell cat "$(DYNACOE_LIB_PATH)/lib_incpaths")
DYNACOE_LIB_PATHS   = $(shell cat "$(DYNACOE_LIB_PATH)lib_libpaths")   
DYNACOE_LIB_NAME    = -ldynacoe

DYNACOE_LIBS        =  $(shell cat "$(DYNACOE_LIB_PATH)build_libs") 


DYNACOE_INC_PATHS := $(patsubst %,-I$(DYNACOE_ROOT)%, $(DYNACOE_INC_PATHS))
DYNACOE_LIB_PATHS := $(patsubst %,-L$(DYNACOE_ROOT)%, $(DYNACOE_LIB_PATHS)) "-L$(DYNACOE_LIB_PATH)"




# Gather proper vars

TEMP := $(LIBS)
LIBS := $(DYNACOE_LIB_NAME) $(DYNACOE_LIBS) $(LIBS) 


TEMP := $(INCS)
INCS := $(DYNACOE_INC_PATHS) $(INCS)

USER_OBJS    := $(patsubst %,%.o, $(SRCS))
ALL_SRCS := $(filter-out %main.cc,$(SRCS))



LOCAL_CFLAGS := -DDC_BACKENDS_GLES_X11 -DDC_BACKENDS_GLESFRAMEBUFFER_X11 -DDC_BACKENDS_NOINPUT -DDC_BACKENDS_NOAUDIO -DDC_BACKENDS_NODISPLAY





LOCAL_MODULE    := libsandboxe

LOCAL_SRC_FILES := $(ALL_SRCS)





LOCAL_C_INCLUDES :=  $(patsubst -I%,%, $(INCS))

#LOCAL_SHARED_LIBRARIES := -lz
LOCAL_EXPORT_LDLIBS := -lm -lpng -lz -lfreetype -lvorbisfile -lvorbis -logg -ldynacoe
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/.

#include $(BUILD_SHARED_LIBRARY)
include $(BUILD_STATIC_LIBRARY)
