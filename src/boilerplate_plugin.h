#pragma once

#include "eth_internals.h"
#include "eth_plugin_interface.h"
#include <string.h>

// Number of selectors defined in this plugin. Should match the enum
// `selector_t`.
#define NUM_SELECTORS 5

// Name of the plugin.
#define PLUGIN_NAME "cBridge"

// Enumeration of the different selectors possible.
// Should follow the exact same order as the array declared in main.c
typedef enum {
  POOL_BASED_SEND_ERC20 = 0,
  POOL_BASED_SEND_NATIVE = 1,
  PEGGED_TOKEN_DEPOSIT_MINT = 2,
  PEGGED_TOKEN_BURN_WITHDRAW = 3,
  POOL_BASED_TOKEN_REFUND = 4,
} selector_t;

// Enumeration used to parse the smart contract data.
typedef enum {
  RECEIVER = 0,
  TOKEN,
  AMOUNT_IN,
  DST_CHAIN_ID,
  NONCE,
  MAX_SLIPPAGE,
  // BENEFICIARY,
  // PATH_OFFSET,
  // PATH_LENGTH,
  UNEXPECTED_PARAMETER,
} parameter;

extern const uint32_t CBRIDGE_SELECTORS[NUM_SELECTORS];

// Shared global memory with Ethereum app. Must be at most 5 * 32 bytes.
typedef struct context_t {
  // For display.
  uint8_t receiver[ADDRESS_LENGTH];
  uint8_t token[ADDRESS_LENGTH];
  uint8_t amount_in[INT256_LENGTH];
  uint8_t dst_chain_id[4];

  char ticker[MAX_TICKER_LEN];
  uint8_t decimals;
  uint8_t token_found;

  // For parsing data.
  uint8_t next_param; // Set to be the next param we expect to parse.
  uint16_t offset;    // Offset at which the array or struct starts.
  bool go_to_offset;  // If set, will force the parsing to iterate through
                     // parameters until `offset` is reached.

  // For both parsing and display.
  selector_t selectorIndex;
} context_t;

// Piece of code that will check that the above structure is not bigger than 5
// * 32. Do not remove this check.
_Static_assert(sizeof(context_t) <= 5 * 32, "Structure of parameters too big.");

void handle_provide_parameter(void *parameters);
void handle_query_contract_ui(void *parameters);
void handle_init_contract(void *parameters);
void handle_finalize(void *parameters);
void handle_provide_token(void *parameters);
void handle_query_contract_id(void *parameters);