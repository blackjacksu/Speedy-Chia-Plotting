// Include C++ header files.
#include <iostream>

// Include local CUDA header files.
#include "include/cuda_kernel.cuh"
#include "include/chacha8.cuh"

#include "../lib/include/picosha2.hpp"
#include "src/calculate_bucket.hpp"
#include "src/disk.hpp"
#include "src/plotter_disk.hpp"
#include "src/prover_disk.hpp"
#include "src/sort_manager.hpp"
#include "src/verifier.hpp"



int main() {

    // Initialize arrays A, B, and C.
    double A[3], B[3], C[3];

    // Populate arrays A and B.
    A[0] = 1; A[1] = 2; A[2] = 3;
    B[0] = 1; B[1] = 1; B[2] = 1;

    // Sum array elements across ( C[0] = A[0] + B[0] ) into array C using CUDA.
    kernel(A, B, C, 3);

    // Print out result.
    std::cout << "C = " << C[0] << ", " << C[1] << ", " << C[2] << std::endl;

    return 0;
}