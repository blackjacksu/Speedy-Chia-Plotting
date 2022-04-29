// Copyright 2018 Chia Network Inc

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//    http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef SRC_CPP_UTIL_HPP_
#define SRC_CPP_UTIL_HPP_

#include <cassert>
#include <chrono>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

template <typename Int, typename Int2>
constexpr inline Int cdiv(Int a, Int2 b) { return (a + b - 1) / b; }
#ifdef _WIN32
#define NOMINMAX
#include <windows.h>
#include <processthreadsapi.h>
#include "uint128_t.h"
#else
// __uint__128_t is only available in 64 bit architectures and on certain
// compilers.
typedef __uint128_t uint128_t;

// Allows printing of uint128_t
// The inline keyword I add is to fix multiple definition for operator<< declaration
// Another fix for this is to move this to a class then add friend
inline std::ostream &operator<<(std::ostream &strm, uint128_t const &v)
{
    strm << "uint128(" << (uint64_t)(v >> 64) << "," << (uint64_t)(v & (((uint128_t)1 << 64) - 1))
         << ")";
    return strm;
}
// class hi{
//     public:
//     friend std::ostream &operator<<(std::ostream &strm, uint128_t const &v)
//     {
//         strm << "uint128(" << (uint64_t)(v >> 64) << "," << (uint64_t)(v & (((uint128_t)1 << 64) - 1))
//              << ")";
//         return strm;
//     }
// }



#endif

// compiler-specific byte swap macros.
#if defined(_MSC_VER)

#include <cstdlib>

// https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/byteswap-uint64-byteswap-ulong-byteswap-ushort?view=msvc-160
inline uint16_t bswap_16(uint16_t x) { return _byteswap_ushort(x); }
inline uint32_t bswap_32(uint32_t x) { return _byteswap_ulong(x); }
inline uint64_t bswap_64(uint64_t x) { return _byteswap_uint64(x); }

#elif defined(__clang__) || defined(__GNUC__)

inline uint16_t bswap_16(uint16_t x) { return __builtin_bswap16(x); }
inline uint32_t bswap_32(uint32_t x) { return __builtin_bswap32(x); }
inline uint64_t bswap_64(uint64_t x) { return __builtin_bswap64(x); }

#else
#error "unknown compiler, don't know how to swap bytes"
#endif

/* Platform-specific cpuid include. */
#if defined(_WIN32)
#include <intrin.h>
#elif defined(__x86_64__)
#include <cpuid.h>
#endif

class Timer {
public:
    Timer();

    static char *GetNow();

    void PrintElapsed(const std::string &name);

private:
    std::chrono::time_point<std::chrono::steady_clock> wall_clock_time_start_;
#if _WIN32
    FILETIME ft_[4];
#else
    clock_t cpu_time_start_;
#endif

};
    void hi();

namespace Util {

    template <typename X>
    inline X Mod(X i, X n);

    inline uint32_t ByteAlign(uint32_t num_bits);

    inline std::string HexStr(const uint8_t *data, size_t len);

    inline void IntToTwoBytes(uint8_t *result, const uint16_t input);

    // Used to encode deltas object size
    inline void IntToTwoBytesLE(uint8_t *result, const uint16_t input);

    inline uint16_t TwoBytesToInt(const uint8_t *bytes);

    /*
     * Converts a 64 bit int to bytes.
     */
    inline void IntToEightBytes(uint8_t *result, const uint64_t input);

    /*
     * Converts a byte array to a 64 bit int.
     */
    inline uint64_t EightBytesToInt(const uint8_t *bytes);

    static void IntTo16Bytes(uint8_t *result, const uint128_t input);

    /*
     * Retrieves the size of an integer, in Bits.
     */
    inline uint8_t GetSizeBits(uint128_t value);

    // 'bytes' points to a big-endian 64 bit value (possibly truncated, if
    // (start_bit % 8 + num_bits > 64)). Returns the integer that starts at
    // 'start_bit' that is 'num_bits' long (as a native-endian integer).
    //
    // Note: requires that 8 bytes after the first sliced byte are addressable
    // (regardless of 'num_bits'). In practice it can be ensured by allocating
    // extra 7 bytes to all memory buffers passed to this function.
    inline uint64_t SliceInt64FromBytes(
        const uint8_t *bytes,
        uint32_t start_bit,
        const uint32_t num_bits);

    inline uint64_t SliceInt64FromBytesFull(
        const uint8_t *bytes,
        uint32_t start_bit,
        uint32_t num_bits);

    inline uint128_t SliceInt128FromBytes(
        const uint8_t *bytes,
        const uint32_t start_bit,
        const uint32_t num_bits);

    void GetRandomBytes(uint8_t *buf, uint32_t num_bytes);

    inline uint64_t ExtractNum(
        const uint8_t *bytes,
        uint32_t len_bytes,
        uint32_t begin_bits,
        uint32_t take_bits);

    // The number of memory entries required to do the custom SortInMemory algorithm, given the
    // total number of entries to be sorted.
    inline uint64_t RoundSize(uint64_t size);

    /*
     * Like memcmp, but only compares starting at a certain bit.
     */
    inline int MemCmpBits(
        uint8_t *left_arr,
        uint8_t *right_arr,
        uint32_t len,
        uint32_t bits_begin);

    inline double RoundPow2(double a);

#if defined(_WIN32) || defined(__x86_64__)
    void CpuID(uint32_t leaf, uint32_t *regs);

    bool HavePopcnt(void);

#endif /* defined(_WIN32) || defined(__x86_64__) */

    inline uint64_t PopCount(uint64_t n);
}

#endif  // SRC_CPP_UTIL_HPP_
