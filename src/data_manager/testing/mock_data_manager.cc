// Copyright 2010-2016, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "data_manager/testing/mock_data_manager.h"

#include "base/embedded_file.h"
#include "base/logging.h"
#include "base/port.h"
#include "dictionary/pos_matcher.h"
#include "dictionary/suffix_dictionary_token.h"
#include "rewriter/correction_rewriter.h"
#include "rewriter/counter_suffix.h"
#ifndef NO_USAGE_REWRITER
#include "rewriter/usage_rewriter_data_structs.h"
#endif  // NO_USAGE_REWRITER

using mozc::dictionary::SuffixToken;

namespace mozc {
namespace testing {
namespace {

// EmbeddedFile kMockMozcDataSet is defined in this header file.
#include "data_manager/testing/mock_mozc_data.h"

#ifndef MOZC_DATASET_MAGIC_NUMBER
#error "MOZC_DATASET_MAGIC_NUMBER is not defined by build system"
#endif  // MOZC_DATASET_MAGIC_NUMBER

const char kMagicNumber[] = MOZC_DATASET_MAGIC_NUMBER;

}  // namespace

MockDataManager::MockDataManager() {
  const StringPiece magic(kMagicNumber, arraysize(kMagicNumber) - 1);
  CHECK(manager_.InitFromArray(LoadEmbeddedFile(kMockMozcDataSet), magic))
      << "Embedded mock_mozc_data.h is broken";
}

MockDataManager::~MockDataManager() = default;

const uint8 *MockDataManager::GetPosGroupData() const {
  return manager_.GetPosGroupData();
}

void MockDataManager::GetConnectorData(const char **data,
                                       size_t *size) const {
  manager_.GetConnectorData(data, size);
}

void MockDataManager::GetSystemDictionaryData(const char **data,
                                              int *size) const {
  manager_.GetSystemDictionaryData(data, size);
}

void MockDataManager::GetSegmenterData(
    size_t *l_num_elements, size_t *r_num_elements,
    const uint16 **l_table, const uint16 **r_table,
    size_t *bitarray_num_bytes, const char **bitarray_data,
    const uint16 **boundary_data) const {
  manager_.GetSegmenterData(l_num_elements, r_num_elements,
                            l_table, r_table, bitarray_num_bytes,
                            bitarray_data, boundary_data);
}

namespace {
// The generated header defines kSuffixTokens[].
#include "data_manager/testing/suffix_data.h"
}  // namespace

void MockDataManager::GetSuffixDictionaryData(const SuffixToken **tokens,
                                              size_t *size) const {
  *tokens = kSuffixTokens;
  *size = arraysize(kSuffixTokens);
}

namespace {
// Include kReadingCorrections.
#include "data_manager/testing/reading_correction_data.h"
}  // namespace

void MockDataManager::GetReadingCorrectionData(
    const ReadingCorrectionItem **array,
    size_t *size) const {
  *array = kReadingCorrections;
  *size = arraysize(kReadingCorrections);
}

void MockDataManager::GetCollocationData(const char **array,
                                         size_t *size) const {
  manager_.GetCollocationData(array, size);
}

void MockDataManager::GetCollocationSuppressionData(const char **array,
                                                    size_t *size) const {
  manager_.GetCollocationSuppressionData(array, size);
}

void MockDataManager::GetSuggestionFilterData(const char **data,
                                              size_t *size) const {
  manager_.GetSuggestionFilterData(data, size);
}

namespace {
// Include kSymbolData_token_data and kSymbolData_token_size.
#include "data_manager/testing/symbol_rewriter_data.h"
}  // namespace

void MockDataManager::GetSymbolRewriterData(
    const EmbeddedDictionary::Token **data,
    size_t *size) const {
  *data = kSymbolData_token_data;
  *size = kSymbolData_token_size;
}

#ifndef NO_USAGE_REWRITER
namespace {
#include "rewriter/usage_rewriter_data.h"
}  // namespace

void MockDataManager::GetUsageRewriterData(
    const ConjugationSuffix **base_conjugation_suffix,
    const ConjugationSuffix **conjugation_suffix_data,
    const int **conjugation_suffix_data_index,
    const UsageDictItem **usage_data_value) const {
  *base_conjugation_suffix = kBaseConjugationSuffix;
  *conjugation_suffix_data = kConjugationSuffixData;
  *conjugation_suffix_data_index = kConjugationSuffixDataIndex;
  *usage_data_value = kUsageData_value;
}
#endif  // NO_USAGE_REWRITER

namespace {
#include "data_manager/testing/counter_suffix_data.h"
}  // namespace

void MockDataManager::GetCounterSuffixSortedArray(
    const CounterSuffixEntry **array, size_t *size) const {
  *array = kCounterSuffixes;
  *size = arraysize(kCounterSuffixes);
}

}  // namespace testing
}  // namespace mozc
