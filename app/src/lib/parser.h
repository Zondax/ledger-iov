/*******************************************************************************
*   (c) 2019 ZondaX GmbH
*
*  Licensed under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
*  Unless required by applicable law or agreed to in writing, software
*  distributed under the License is distributed on an "AS IS" BASIS,
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and
*  limitations under the License.
********************************************************************************/

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "parser_impl.h"
#include "zxmacros.h"

const char *parser_getErrorDescription(parser_error_t err);

//// parses a tx buffer
parser_error_t parser_parse(parser_context_t *ctx,
                            const uint8_t *data,
                            uint16_t dataLen);

//// verifies tx fields
parser_error_t parser_validate(const parser_context_t *ctx, bool_t isMainnet);

//// returns the number of items in the current parsing context
uint8_t parser_getNumItems(const parser_context_t *ctx);

// retrieves a readable output for each field / page
parser_error_t parser_getItem(const parser_context_t *ctx,
                              int8_t displayIdx,
                              char *outKey, uint16_t outKeyLen,
                              char *outValue, uint16_t outValueLen,
                              uint8_t pageIdx, uint8_t *pageCount);

__Z_INLINE parser_error_t parser_getItem_Send(const parser_context_t *ctx,
                                   int8_t displayIdx,
                                   char *outKey, uint16_t outKeyLen,
                                   char *outValue, uint16_t outValueLen,
                                   uint8_t pageIdx, uint8_t *pageCount);

__Z_INLINE parser_error_t parser_getItem_Vote(const parser_context_t *ctx,
                                              int8_t displayIdx,
                                              char *outKey, uint16_t outKeyLen,
                                              char *outValue, uint16_t outValueLen,
                                              uint8_t pageIdx, uint8_t *pageCount);

__Z_INLINE parser_error_t parser_getItem_Update(const parser_context_t *ctx,
                                              int8_t displayIdx,
                                              char *outKey, uint16_t outKeyLen,
                                              char *outValue, uint16_t outValueLen,
                                              uint8_t pageIdx, uint8_t *pageCount);

__Z_INLINE parser_error_t parser_getItem_Participant(const parser_context_t *ctx,
                                          int8_t displayIdx,
                                          char *outKey, uint16_t outKeyLen,
                                          char *outValue, uint16_t outValueLen,
                                          uint8_t pageIdx, uint8_t *pageCount);

__Z_INLINE parser_error_t parser_getItem_Elector(const parser_context_t *ctx,
                                                 int8_t displayIdx,
                                                 char *outKey, uint16_t outKeyLen,
                                                 char *outValue, uint16_t outValueLen,
                                                 uint8_t pageIdx, uint8_t *pageCount);

__Z_INLINE parser_error_t parser_getItem_CreateProposal(const parser_context_t *ctx,
                                                        int8_t displayIdx,
                                                        char *outKey, uint16_t outKeyLen,
                                                        char *outValue, uint16_t outValueLen,
                                                        uint8_t pageIdx, uint8_t *pageCount);

__Z_INLINE parser_error_t parser_getItem_UpdateElectorate(const parser_context_t *ctx,
                                                          int8_t displayIdx,
                                                          char *outKey, uint16_t outKeyLen,
                                                          char *outValue, uint16_t outValueLen,
                                                          uint8_t pageIdx, uint8_t *pageCount);

#ifdef __cplusplus
}
#endif
