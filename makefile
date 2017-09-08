# Eduardo Ponce
# 9/2017
# Makefile for word2vec

# Get name of makefile
MKFILE := $(MAKEFILE_LIST)

# C compiler
CC := g++
#CC := icc

# GNU compiler and linker options
# -mmx, -msse, -msse2, -msse3, -mssse3, -msse4.1, -msse4.2, -msse4 = SIMD extensions
# -mavx, -mavx2, -mavx512bw, -mavx512f, -mavx512pf, -mavx512er, -mavx512cd = SIMD extensions
# -fopenmp, -fopenmp-simd = enable OpenMP
SIMDFLAG := -msse4.1
#SIMDFLAG := -mavx2
CFLAGS := $(SIMDFLAG) -pedantic -Wall -Wextra -Wno-unknown-pragmas -Wno-unused-result -pthread -O3 -march=native -std=c++11 -funroll-loops
#CFLAGS += -fopenmp

# INTEL compiler and linker options
#CFLAGS := $(SIMDFLAG) -pedantic -Wall -Wextra -Wno-unknown-pragmas -Wno-unused-result -pthread -O3 -march=native -std=c++11 -funroll-loops
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
INCDIR := -I. -Iarch -Isimd

# Define library paths in addition to standard paths
LIBDIR :=

# Define libraries to link into executable
LIBS := -lm

# Header files
# NOTE: allow recompile if changed
HEADERS := arch/*.h simd/*.h

#######################################

# Targets that are not real files to create
.PHONY: all clean

all: word2vec

word2vec : word2vec.c
	$(CC) $(CFLAGS) $(LFLAGS) $(DEFINES) $(INCDIR) $(LIBDIR) word2vec.c -o word2vec $(LIBS)
distance : distance.c
	$(CC) $(CFLAGS) $(LFLAGS) $(DEFINES) $(INCDIR) $(LIBDIR) distance.c -o distance $(LIBS)

clean:
	rm -rf word2vec distance
