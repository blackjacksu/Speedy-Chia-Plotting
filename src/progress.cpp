#include "../include/progress.h"

void progress(int phase, int64_t n, int64_t max_n) {
    float p = (100.0 / 4) * ((phase - 1.0) + (1.0 * n / max_n));
    std::cout << "Progress: " << p << std::endl;
}
