SM := 35

GC := gcc
GCC := g++
NVCC := nvcc

CFLAGS = -std=c99
NVCCFLAGS = -O3

GENCODE_FLAGS = -gencode arch=compute_$(SM),code=sm_$(SM)
LIB_FLAGS = -lcudadevrt -lcudart

BUILDDIR = build
CHIASRCDIR = src

TARGET = ChiaGPUPlotter
all: $(BUILDDIR)/$(TARGET)

$(TARGET): $(BUILDDIR)/dlink.o $(BUILDDIR)/main.o $(BUILDDIR)/$(TARGET).o
	$(GCC) $(CFLAGS) $^ -o $@ $(LIB_FLAGS)

$(BUILDDIR)/dlink.o: $(BUILDDIR)/$(TARGET).o 
	$(NVCC) $(NVCCFLAGS) $^ -o $@ $(GENCODE_FLAGS) -dlink

$(BUILDDIR)/main.o: main.cpp
	$(GCC) $(CFLAGS) -c $< -o $@

## The following are source libraries
$(BUILDDIR)/$(TARGET).o: $(CHIASRCDIR)/chacha8.cu $(CHIASRCDIR)/chacha8.h
	$(NVCC) $(NVCCFLAGS) -c $< -o $@ $(GENCODE_FLAGS) 

clean:
	rm -f $(BUILDDIR)/*.o $(TARGET) 
