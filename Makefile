###########################################################

## USER SPECIFIC DIRECTORIES ##

# CUDA directory:
# CUDA_ROOT_DIR=/usr/local/cuda

##########################################################

## CC COMPILER OPTIONS ##

# CC compiler options:
CC=g++
CC_FLAGS=-std=c++17 -Wall
CC_LIBS=

##########################################################

## NVCC COMPILER OPTIONS ##

# NVCC compiler options:
NVCC=nvcc
NVCC_FLAGS=
NVCC_LIBS=

# CUDA library directory:
CUDA_LIB_DIR= -L$(CUDA_ROOT_DIR)/lib64
# CUDA include directory:
CUDA_INC_DIR= -I$(CUDA_ROOT_DIR)/include
# CUDA linking libraries:
CUDA_LINK_LIBS= -lcudart

##########################################################

## Project file structure ##

# Source file directory:
SRC_DIR = src
B3_DIR = b3

# Object file directory:
OBJ_DIR = bin

# Include header file diretory:
INC_DIR = include

##########################################################

## Make variables ##

# Target executable name:
EXE = run_test

# Object files:
OBJS = $(OBJ_DIR)/main.o $(OBJ_DIR)/b17phase2.o $(OBJ_DIR)/b17phase3.o $(OBJ_DIR)/b17phase4.o \
		$(OBJ_DIR)/b17sort_manager.o $(OBJ_DIR)/bitfield.o $(OBJ_DIR)/bitfield_index.o \
		$(OBJ_DIR)/bits.o $(OBJ_DIR)/calculate_bucket.o $(OBJ_DIR)/chia_filesystem.o \
		$(OBJ_DIR)/disk.o $(OBJ_DIR)/encoding.o $(OBJ_DIR)/entry_sizes.o \
		$(OBJ_DIR)/phase1.o $(OBJ_DIR)/phase2.o $(OBJ_DIR)/phase3.o $(OBJ_DIR)/phase4.o \
		$(OBJ_DIR)/phase.o $(OBJ_DIR)/plotter_disk.o $(OBJ_DIR)/pos_constants.o $(OBJ_DIR)/progress.o \
		$(OBJ_DIR)/prover_disk.o $(OBJ_DIR)/quicksort.o $(OBJ_DIR)/sort_manager.o $(OBJ_DIR)/threading.o \
		$(OBJ_DIR)/uniformsort.o $(OBJ_DIR)/util.o $(OBJ_DIR)/verifier.o $(OBJ_DIR)/exceptions.o 

# $(OBJ_DIR)/cuda_kernel.o $(OBJ_DIR)/chacha8.o $(OBJ_DIR)/cli.o 

##########################################################

## Compile ##

# Link c++ and CUDA compiled object files to target executable:
$(EXE) : $(OBJS)
	$(CC) $(CC_FLAGS) $(OBJS) -o $@ $(CUDA_INC_DIR) $(CUDA_LIB_DIR) $(CUDA_LINK_LIBS)

# Compile main .cpp file to object files:
$(OBJ_DIR)/%.o : %.cpp
	$(CC) $(CC_FLAGS) -c $< -o $@

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(CC) $(CC_FLAGS) -c $< -o $@

# # Compile C++ source files to object files:
# $(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp include/%.h
# 	$(CC) $(CC_FLAGS) -c $< -o $@

# Compile HPP source files to object files:
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.hpp
	$(CC) $(CC_FLAGS) -c $< -o $@

# Compile CUDA source files to object files:
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cu $(INC_DIR)/%.cuh
	$(NVCC) $(NVCC_FLAGS) -c $< -o $@ $(NVCC_LIBS)

# Clean objects in object directory.
clean:
	$(RM) bin/* *.o $(EXE)




