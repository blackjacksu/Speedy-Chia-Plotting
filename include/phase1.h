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

#ifndef SRC_CPP_PHASE1_HPP_
#define SRC_CPP_PHASE1_HPP_

#ifndef _WIN32
#include <semaphore.h>
#include <unistd.h>
#endif

#include <math.h>
#include <stdio.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
#include <thread>
#include <memory>
#include <mutex>

#include "chia_filesystem.h"

#include "calculate_bucket.h"
#include "entry_sizes.h"
#include "exceptions.h"
#include "pos_constants.h"
#include "sort_manager.h"
#include "threading.h"
#include "util.h"
#include "progress.h"
#include "phases.h"

struct THREADDATA {
    int index;
    Sem::type* mine;
    Sem::type* theirs;
    uint64_t right_entry_size_bytes;
    uint8_t k;
    uint8_t table_index;
    uint8_t metadata_size;
    uint32_t entry_size_bytes;
    uint8_t pos_size;
    uint64_t prevtableentries;
    uint32_t compressed_entry_size_bytes;
    std::vector<FileDisk>* ptmp_1_disks;
};

struct GlobalData {
    uint64_t left_writer_count;
    uint64_t right_writer_count;
    uint64_t matches;
    std::unique_ptr<SortManager> L_sort_manager;
    std::unique_ptr<SortManager> R_sort_manager;
    uint64_t left_writer_buf_entries;
    uint64_t left_writer;
    uint64_t right_writer;
    uint64_t stripe_size;
    uint8_t num_threads;
};


PlotEntry GetLeftEntry(
    uint8_t const table_index,
    uint8_t const* const left_buf,
    uint8_t const k,
    uint8_t const metadata_size,
    uint8_t const pos_size);

void* phase1_thread(THREADDATA* ptd);

void* F1thread(int const index, uint8_t const k, const uint8_t* id, std::mutex* smm);

// This is Phase 1, or forward propagation. During this phase, all of the 7 tables,
// and f functions, are evaluated. The result is an intermediate plot file, that is
// several times larger than what the final file will be, but that has all of the
// proofs of space in it. First, F1 is computed, which is special since it uses
// ChaCha8, and each encryption provides multiple output values. Then, the rest of the
// f functions are computed, and a sort on disk happens for each table.
std::vector<uint64_t> RunPhase1(
    std::vector<FileDisk>& tmp_1_disks,
    uint8_t const k,
    const uint8_t* const id,
    std::string const tmp_dirname,
    std::string const filename,
    uint64_t const memory_size,
    uint32_t const num_buckets,
    uint32_t const log_num_buckets,
    uint32_t const stripe_size,
    uint8_t const num_threads,
    uint8_t const flags);
