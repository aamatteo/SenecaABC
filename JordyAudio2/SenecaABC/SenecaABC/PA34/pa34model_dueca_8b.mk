# Copyright 1994-2007 The MathWorks, Inc.
#
# File    : grt_malloc_lcc.tmf   $Revision: 1.1.1.1 $
#
# Abstract:
#	Real-Time Workshop template makefile for building a PC based
#	stand-alone malloc generic real-time version of Simulink model using
#	generated C code and
#			LCC compiler Version 2.4
# 	This makefile attempts to conform to the guidelines specified in the
# 	IEEE Std 1003.2-1992 (POSIX) standard. It is designed to be used
#       with GNU Make (gmake) which is located in matlabroot/bin/win32.
#
# 	Note that this template is automatically customized by the Real-Time
#	Workshop build procedure to create "<model>.mk"
#
#       The following defines can be used to modify the behavior of the
#	build:
#	  OPT_OPTS       - Optimization options. Default is none. To enable 
#                          debugging specify as OPT_OPTS=-g4. 
#	  OPTS           - User specific compile options.
#	  USER_SRCS      - Additional user sources, such as files needed by
#			   S-functions.
#	  USER_INCLUDES  - Additional include paths
#			   (i.e. USER_INCLUDES="-Iwhere-ever -Iwhere-ever2")
#			   (For Lcc, have a '/'as file seperator before the 
#			   file name instead of a '\' . 
#			   i.e.,  d:\work\proj1/myfile.c - reqd for 'gmake')
#
#       This template makefile is designed to be used with a system target
#       file that contains 'rtwgensettings.BuildDirSuffix' see 
#       grt_malloc.tlc


#------------------------ Macros read by make_rtw ------------------------------
#
# The following macros are read by the Real-Time Workshop build procedure:
#
#  MAKECMD         - This is the command used to invoke the make utility
#  HOST            - What platform this template makefile is targeted for
#                    (i.e. PC or UNIX)
#  BUILD           - Invoke make from the Real-Time Workshop build procedure
#                    (yes/no)?
#  SYS_TARGET_FILE - Name of system target file.

MAKECMD         = "%MATLAB%\bin\win32\gmake"
SHELL           = cmd
HOST            = PC
BUILD           = yes
SYS_TARGET_FILE = grt_malloc.tlc
BUILD_SUCCESS	= Created executable
COMPILER_TOOL_CHAIN = lcc

MAKEFILE_FILESEP = /

#---------------------- Tokens expanded by make_rtw ----------------------------
#
# The following tokens, when wrapped with "|>" and "<|" are expanded by the
# Real-Time Workshop build procedure.
#
#  MODEL_NAME          - Name of the Simulink block diagram
#  MODEL_MODULES       - Any additional generated source modules
#  MAKEFILE_NAME       - Name of makefile created from template makefile <model>.mk
#  MATLAB_ROOT         - Path to were MATLAB is installed.
#  MATLAB_BIN          - Path to MATLAB executable.
#  S_FUNCTIONS         - List of S-functions.
#  S_FUNCTIONS_LIB     - List of S-functions libraries to link.
#  SOLVER              - Solver source file name
#  NUMST               - Number of sample times
#  TID01EQ             - yes (1) or no (0): Are sampling rates of continuous task
#                        (tid=0) and 1st discrete task equal.
#  NCSTATES            - Number of continuous states
#                        for one instance of the model.
#  BUILDARGS           - Options passed in at the command line.
#  MULTITASKING        - yes (1) or no (0): Is solver mode multitasking
#  EXT_MODE            - yes (1) or no (0): Build for external mode
#  TMW_EXTMODE_TESTING - yes (1) or no (0): Build ext_test.c for external mode
#                        testing.
#  EXTMODE_TRANSPORT   - Name of transport mechanism (e.g. tcpip, serial) for extmode
#  EXTMODE_STATIC      - yes (1) or no (0): Use static instead of dynamic mem alloc.
#  EXTMODE_STATIC_SIZE - Size of static memory allocation buffer.

MODEL                = pa34model_dueca_8b
MODULES              = pa34model_dueca_8b_data.c rt_atan2.c rt_logging.c rt_rand.c 
MAKEFILE             = pa34model_dueca_8b.mk
MATLAB_ROOT          = C:/Program Files (x86)/MATLAB/R2007b
ALT_MATLAB_ROOT      = C:/PROGRA~2/MATLAB/R2007b
MATLAB_BIN           = C:/Program Files (x86)/MATLAB/R2007b/bin
ALT_MATLAB_BIN       = C:/PROGRA~2/MATLAB/R2007b/bin
S_FUNCTIONS          = 
S_FUNCTIONS_LIB      = 
SOLVER               = ode4.c
NUMST                = 2
TID01EQ              = 1
NCSTATES             = 17
BUILDARGS            =  GENERATE_REPORT=0 MODELLIB=pa34model_dueca_8blib.lib RELATIVE_PATH_TO_ANCHOR=.. MODELREF_TARGET_TYPE=NONE
MULTITASKING         = 0
EXT_MODE             = 0
TMW_EXTMODE_TESTING  = 0
EXTMODE_TRANSPORT    = 0
EXTMODE_STATIC       = 0
EXTMODE_STATIC_SIZE  = 1000000
OPTIMIZATION_FLAGS      = 

#-- In the case when directory name contains space ---
ifneq ($(MATLAB_ROOT),$(ALT_MATLAB_ROOT))
MATLAB_ROOT := $(ALT_MATLAB_ROOT)
endif
ifneq ($(MATLAB_BIN),$(ALT_MATLAB_BIN))
MATLAB_BIN := $(ALT_MATLAB_BIN)
endif

#--------------------------- Tool Specifications -------------------------------

LCC = $(MATLAB_ROOT)\sys\lcc
include $(MATLAB_ROOT)\rtw\c\tools\lcctools.mak

#------------------------------ Include Path -----------------------------------

# Additional includes

ADD_INCLUDES = \
	-ID:/OSTROO~1/OLAFWE~1/SIMONA/AFSTUD~1/HERMAN~1/PA34/20150714/PA34MO~1 \
	-ID:/OSTROO~1/OLAFWE~1/SIMONA/AFSTUD~1/HERMAN~1/PA34/20150714 \
	-I$(MATLAB_ROOT)/rtw/c/libsrc \


# see MATLAB_INCLUDES and COMPILER_INCLUDES from lcctools.mak

INCLUDES = -I. -I.. $(MATLAB_INCLUDES) $(ADD_INCLUDES) \
           $(COMPILER_INCLUDES) $(USER_INCLUDES)

#----------------------------- External mode -----------------------------------
# Uncomment -DVERBOSE to have information printed to stdout
# To add a new transport layer, see the comments in
#   <matlabroot>/toolbox/simulink/simulink/extmode_transports.m
ifeq ($(EXT_MODE),1)
  EXT_CC_OPTS = -DEXT_MODE -DWIN32 # -DVERBOSE
  ifeq ($(EXTMODE_TRANSPORT),0) #tcpip
    EXT_SRC = ext_svr.c updown.c ext_work.c ext_svr_tcpip_transport.c
    EXT_LIB = $(MATLAB_ROOT)\sys\lcc\lib\wsock32.lib
  endif
  ifeq ($(EXTMODE_TRANSPORT),1) #serial_win32
    EXT_SRC  = ext_svr.c updown.c ext_work.c ext_svr_serial_transport.c
    EXT_SRC += ext_serial_pkt.c ext_serial_win32_port.c
  endif
  ifeq ($(TMW_EXTMODE_TESTING),1)
    EXT_SRC     += ext_test.c
    EXT_CC_OPTS += -DTMW_EXTMODE_TESTING
  endif
  ifeq ($(EXTMODE_STATIC),1)
    EXT_SRC     += mem_mgr.c
    EXT_CC_OPTS += -DEXTMODE_STATIC -DEXTMODE_STATIC_SIZE=$(EXTMODE_STATIC_SIZE)
  endif
endif

#----------------------------- RTModel Flags -----------------------------------
RTM_CC_OPTS = -DUSE_RTMODEL

#-------------------------------- C Flags --------------------------------------


# Optimization Options
OPT_OPTS = $(DEFAULT_OPT_OPTS)

# General User Options
OPTS =

# Compiler options, etc:
ifneq ($(OPTIMIZATION_FLAGS),)
CC_OPTS = $(OPTIMIZATION_FLAGS) $(OPTS) $(ANSI_OPTS) $(EXT_CC_OPTS) $(RTM_CC_OPTS)
else
CC_OPTS = $(OPT_OPTS) $(OPTS) $(ANSI_OPTS) $(EXT_CC_OPTS) $(RTM_CC_OPTS)
endif

CPP_REQ_DEFINES = -DMODEL=$(MODEL) -DRT -DNUMST=$(NUMST) \
                  -DTID01EQ=$(TID01EQ) -DNCSTATES=$(NCSTATES) \
                  -DRT_MALLOC -DMT=$(MULTITASKING) -DHAVESTDIO

CFLAGS  = $(CC_OPTS) $(CPP_REQ_DEFINES) $(INCLUDES) -noregistrylookup

ifeq ($(OPT_OPTS),$(DEFAULT_OPT_OPTS))
LDFLAGS = -s -L$(LIB)
else
LDFLAGS = -L$(LIB)
endif

#------------------------- Additional Libraries -------------------------------

LIBS =

ifeq ($(OPT_OPTS),$(DEFAULT_OPT_OPTS))
LIBS += $(MATLAB_ROOT)/rtw/c/lib/win32\rtwlib_lcc.lib
else
LIBS += rtwlib.lib
endif 

LIBS += $(EXT_LIB) $(S_FUNCTIONS_LIB)

#----------------------------- Source Files ------------------------------------

REQ_SRCS  = $(MODEL).c $(MODULES) grt_malloc_main.c rt_sim.c rt_nonfinite.c \
            $(EXT_SRC)
USER_SRCS =

USER_OBJS       = $(USER_SRCS:.c=.obj)
LOCAL_USER_OBJS = $(notdir $(USER_OBJS))

SRCS = $(REQ_SRCS) $(S_FUNCTIONS) $(SOLVER)
OBJS      = $(SRCS:.c=.obj) $(USER_OBJS)
LINK_OBJS = $(SRCS:.c=.obj) $(LOCAL_USER_OBJS)

PROGRAM = ../$(MODEL).exe

#--------------------------------- Rules ---------------------------------------

$(PROGRAM) : $(OBJS) $(LIBS)
	$(LD) $(LDFLAGS) -o $@ $(LINK_OBJS) $(LIBS)
	@cmd /C "echo ### $(BUILD_SUCCESS): $(MODEL).exe"

%.obj : %.c
	$(CC) -c -Fo$(@F) $(CFLAGS) $<

%.obj : ../%.c
	$(CC) -c -Fo$(@F) -I../$(<F:.c=cn_rtw) $(CFLAGS) $<

%.obj : $(MATLAB_ROOT)/rtw/c/grt_malloc/%.c
	$(CC) -c -Fo$(@F) $(CFLAGS) $<

%.obj : $(MATLAB_ROOT)/rtw/c/src/%.c
	$(CC) -c -Fo$(@F) $(CFLAGS) $<

%.obj : $(MATLAB_ROOT)/rtw/c/src/ext_mode/common/%.c
	$(CC) -c -Fo$(@F) $(CFLAGS) $<

%.obj : $(MATLAB_ROOT)/rtw/c/src/ext_mode/tcpip/%.c
	$(CC) -c -Fo$(@F) $(CFLAGS) $<

%.obj : $(MATLAB_ROOT)/rtw/c/src/ext_mode/serial/%.c
	$(CC) -c -Fo$(@F) $(CFLAGS) $<

%.obj : $(MATLAB_ROOT)/rtw/c/src/ext_mode/custom/%.c
	$(CC) -c -Fo$(@F) $(CFLAGS) $<

%.obj : $(MATLAB_ROOT)/rtw/c/src/%.c
	$(CC) -c -Fo$(@F) $(CFLAGS) $<

%.obj : $(MATLAB_ROOT)/rtw/c/libsrc/%.c
	$(CC) -c -Fo$(@F) $(CFLAGS) $<



%.obj : $(MATLAB_ROOT)/simulink/src/%.c
	$(CC) -c -Fo$(@F) $(CFLAGS) $<

# Libraries:



MODULES_rtwlib = \
	rt_backsubcc_dbl.obj \
	rt_backsubcc_sgl.obj \
	rt_backsubrc_dbl.obj \
	rt_backsubrc_sgl.obj \
	rt_backsubrr_dbl.obj \
	rt_backsubrr_sgl.obj \
	rt_enab.obj \
	rt_forwardsubcc_dbl.obj \
	rt_forwardsubcc_sgl.obj \
	rt_forwardsubcr_dbl.obj \
	rt_forwardsubcr_sgl.obj \
	rt_forwardsubrc_dbl.obj \
	rt_forwardsubrc_sgl.obj \
	rt_forwardsubrr_dbl.obj \
	rt_forwardsubrr_sgl.obj \
	rt_look.obj \
	rt_look1d.obj \
	rt_look1d32.obj \
	rt_look2d32_general.obj \
	rt_look2d32_normal.obj \
	rt_look2d_general.obj \
	rt_look2d_normal.obj \
	rt_look32.obj \
	rt_lu_cplx.obj \
	rt_lu_cplx_sgl.obj \
	rt_lu_real.obj \
	rt_lu_real_sgl.obj \
	rt_matdivcc_dbl.obj \
	rt_matdivcc_sgl.obj \
	rt_matdivcr_dbl.obj \
	rt_matdivcr_sgl.obj \
	rt_matdivrc_dbl.obj \
	rt_matdivrc_sgl.obj \
	rt_matdivrr_dbl.obj \
	rt_matdivrr_sgl.obj \
	rt_matmultandinccc_dbl.obj \
	rt_matmultandinccc_sgl.obj \
	rt_matmultandinccr_dbl.obj \
	rt_matmultandinccr_sgl.obj \
	rt_matmultandincrc_dbl.obj \
	rt_matmultandincrc_sgl.obj \
	rt_matmultandincrr_dbl.obj \
	rt_matmultandincrr_sgl.obj \
	rt_matmultcc_dbl.obj \
	rt_matmultcc_sgl.obj \
	rt_matmultcr_dbl.obj \
	rt_matmultcr_sgl.obj \
	rt_matmultrc_dbl.obj \
	rt_matmultrc_sgl.obj \
	rt_matmultrr_dbl.obj \
	rt_matmultrr_sgl.obj \
	rt_sat_div_int16.obj \
	rt_sat_div_int32.obj \
	rt_sat_div_int8.obj \
	rt_sat_div_uint16.obj \
	rt_sat_div_uint32.obj \
	rt_sat_div_uint8.obj \
	rt_sat_prod_int16.obj \
	rt_sat_prod_int32.obj \
	rt_sat_prod_int8.obj \
	rt_sat_prod_uint16.obj \
	rt_sat_prod_uint32.obj \
	rt_sat_prod_uint8.obj \


rtwlib.lib : $(MAKEFILE) rtw_proj.tmw $(MODULES_rtwlib)
	@cmd /C "echo ### Creating $@"
	@if exist $@ del $@
	$(LIBCMD) /out:$@ $(MODULES_rtwlib)
	@cmd /C "echo ### $@ Created"



#----------------------------- Dependencies ------------------------------------

$(OBJS) : $(MAKEFILE) rtw_proj.tmw


#--------- Miscellaneous rules to purge, clean and lint (sol2 only) ------------
purge : clean
	@cmd /C "echo ### Deleting the generated source code for $(MODEL)"
	@del $(MODEL).c $(MODEL).h $(MODEL)_types.h $(MODEL)_data.c \
	        $(MODEL)_private.h $(MODEL).rtw $(MODULES) rtw_proj.tmw $(MAKEFILE)

clean :
	@cmd /C "echo ### Deleting the objects and $(PROGRAM)"
	@del $(LINK_OBJS) ..\$(MODEL).exe

# EOF: grt_malloc_lcc.tmf


