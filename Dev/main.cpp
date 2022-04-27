
// #include <src/phase1.hpp>
// #include <src/phase2.hpp>
// #include <src/phase3.hpp>
// #include <src/phase4.hpp>
// #include <src/util.hpp>
// #include <src/copy.h>


// #include <string>
// #include <csignal>

// #ifndef _WIN32
// #include <sys/resource.h>
// #endif
#include <chacha8.h>

#include <stdio.h>
#include <stdlib.h>


void perform_get_keystream(const struct chacha8_ctx *_x, uint64_t _pos, uint32_t _n_blocks, uint8_t *_c, const uint8_t N);

int main(int argc, char** argv)
{
    uint8_t N = 1;
    uint64_t pos = 1;
    uint32_t n_blocks = 1;
    uint8_t c[64];
    struct chacha8_ctx ctx = {1};

    perform_get_keystream(&ctx, pos, n_blocks, c, N);
    printf("Hello Chia~\n");

    return 0;
}