# Eduardo Ponce
# 9/2017
# Makefile for word2vec

# Get name of makefile
MKFILE := $(MAKEFILE_LIST)

# C compiler
CC := g++
#CC := icpc

# GNU compiler and linker options
# -mmx, -msse, -msse2, -msse3, -mssse3, -msse4.1, -msse4.2, -msse4 = SIMD extensions
# -mavx, -mavx2, -mavx512bw, -mavx512f, -mavx512pf, -mavx512er, -mavx512cd = SIMD extensions
# -fopenmp, -fopenmp-simd = enable OpenMP
#SIMDFLAG := -msse4.1
#SIMDFLAG := -mavx2
CFLAGS := $(SIMDFLAG) -pedantic -Wall -Wextra -Wno-unknown-pragmas -Wno-unused-result -pthread -O3 -march=native -std=c++98 -funroll-loops
#CFLAGS += -fopenmp

# INTEL compiler and linker options
#CFLAGS := $(SIMDFLAG) -pedantic -Wall -Wextra -Wno-unknown-pragmas -Wno-unused-result -pthread -O3 -march=native -std=c++98 -funroll-loops
#CFLAGS += -openmp

# Linker options
LFLAGS :=

# Preprocessor definitions
# -DSIMD_MODE, -DAVX512BW_VEC, -DAVX2_VEC, -DSSE4_1_VEC = enabled SIMD modes
# -DDEBUG = enable debugging
#
# -D_GNU_SOURCE = feature test macro (POSIX C and ISOC99)
# -D_POSIX_C_SOURCE=200112L
#
# -DOMP_NUM_THREADS=x = number of OpenMP threads
# -DOMP_NESTED=TRUE = enables nested parallelism
# -DOMP_PROC_BIND=TRUE = thread/processor affinity
# -DOMP_STACKSIZE=8M = stack size for non-master threads
DEFINES := -DSIMD_MODE   # auto SIMD mode
#DEFINES := -DSSE4_1_VEC
#DEFINES := -DAVX2_VEC
#DEFINES := -DAVX512_VEC  # AVX512BW SIMD mode
#DEFINES += -DOMP_PROC_BIND=TRUE -DOMP_NUM_THREADS=4
DEFINES += -D_POSIX_C_SOURCE=200112L

# Define header paths in addition to standard paths
INCDIR := -I. -Isimd/include

# Define library paths in addition to standard paths
LIBDIR :=

# Define libraries to link into executable
LIBS := -lm

# Header files
# NOTE: allow recompile if changed
HEADERS := simd/include/*.h

#######################################
# Testsuite
LFLAGS_TS :=
INCDIR_TS := -I. -Isimd/include -Isimd/testsuite/include
LIBDIR_TS :=
LIBS_TS := -lm

HEADERS_TS := simd/include/*.h simd/testsuite/include/*.h
TOPDIR_TS := simd/testsuite
SRC_TS := $(TOPDIR_TS)/src/test_simd.cpp $(TOPDIR_TS)/src/test_utils.cpp
DRIVER_TS := $(TOPDIR_TS)/src/test_suite.cpp
OBJDIR_TS := $(TOPDIR_TS)/obj
OBJ_TS := $(patsubst %.cpp, $(OBJDIR_TS)/%.o, $(notdir $(SRC_TS)))
#######################################

# Targets that are not real files to create
.PHONY: all clean

all: word2vec

word2vec : word2vec.cpp
	$(CC) $(CFLAGS) $(LFLAGS) $(DEFINES) $(INCDIR) $(LIBDIR) $< -o $@ $(LIBS)

distance : distance.cpp
	$(CC) $(CFLAGS) $(LFLAGS) $(DEFINES) $(INCDIR) $(LIBDIR) $< -o $@ $(LIBS)

#######################################
# Testsuite
testsuite : $(OBJ_TS) $(DRIVER_TS)
	$(CC) $(CFLAGS) $(LFLAGS_TS) $(DEFINES) $(INCDIR_TS) $(LIBDIR_TS) $(DRIVER_TS) -o $(TOPDIR_TS)/$@ $(OBJ_TS) $(LIBS_TS)

$(OBJDIR_TS)/%.o: $(TOPDIR_TS)/src/%.cpp
	@test ! -d $(OBJDIR_TS) && mkdir $(OBJDIR_TS) || true
	$(CC) $(CFLAGS) $(DEFINES) $(INCDIR_TS) $(LIBDIR_TS) -c $< -o $@ $(LIBS_TS)
#######################################

clean:
	@test -x word2vec && rm word2vec || true
	@test -x distance && rm distance || true
#######################################
# Testsuite
	@test -x $(TOPDIR_TS)/testsuite && rm $(TOPDIR_TS)/testsuite || true
	@test -d $(OBJDIR_TS) && rm -r $(OBJDIR_TS) || true
#######################################

