#include "cbridge_plugin.h"

static void
handle_send_erc_20_tokens_paramters(ethPluginProvideParameter_t *msg,
                                    context_t *context) {
  if (context->go_to_offset) {
    return;
  }

  switch (context->next_param) {
  case RECEIVER:
    copy_address(context->receiver, msg->parameter, sizeof(context->receiver));
    context->next_param = TOKEN;
    break;
  case TOKEN:
    copy_address(context->token, msg->parameter, sizeof(context->token));
    context->next_param = AMOUNT_IN;
    break;
  case AMOUNT_IN: // transfer amount in
    copy_parameter(context->amount_in, msg->parameter,
                   sizeof(context->amount_in));
    context->next_param = DST_CHAIN_ID;
    break;
  case DST_CHAIN_ID:
    U4BE_from_parameter(context->dst_chain_id, msg->parameter);

    context->next_param = NONCE;
    context->go_to_offset = true;
    break;
  default:
    PRINTF("Param not supported: %d\n", context->next_param);
    msg->result = ETH_PLUGIN_RESULT_ERROR;
    break;
  }
}

static void
handle_send_native_tokens_paramters(ethPluginProvideParameter_t *msg,
                                    context_t *context) {
  if (context->go_to_offset) {
    return;
  }

  switch (context->next_param) {
  case RECEIVER:
    copy_address(context->receiver, msg->parameter, sizeof(context->receiver));
    context->next_param = AMOUNT_IN;
    break;
  case AMOUNT_IN: // transfer amount in
    copy_parameter(context->amount_in, msg->parameter,
                   sizeof(context->amount_in));
    context->next_param = DST_CHAIN_ID;
    break;
  case DST_CHAIN_ID:
    U4BE_from_parameter(context->dst_chain_id, msg->parameter);

    context->next_param = NONCE;
    context->go_to_offset = true;
    break;
  default:
    PRINTF("Param not supported: %d\n", context->next_param);
    msg->result = ETH_PLUGIN_RESULT_ERROR;
    break;
  }
}

static void handle_pegged_token_deposit(ethPluginProvideParameter_t *msg,
                                        context_t *context) {
  if (context->go_to_offset) {
    return;
  }

  switch (context->next_param) {
  case TOKEN:
    copy_address(context->token, msg->parameter, sizeof(context->token));
    context->next_param = AMOUNT_IN;
    break;
  case AMOUNT_IN: // transfer amount in
    copy_parameter(context->amount_in, msg->parameter,
                   sizeof(context->amount_in));
    context->next_param = DST_CHAIN_ID;
    break;
  case DST_CHAIN_ID:
    U4BE_from_parameter(context->dst_chain_id, msg->parameter);
    context->next_param = NONCE;
    context->go_to_offset = true;
    break;
  default:
    PRINTF("Param not supported: %d\n", context->next_param);
    msg->result = ETH_PLUGIN_RESULT_ERROR;
    break;
  }
}

static void handle_pegged_token_burn(ethPluginProvideParameter_t *msg,
                                     context_t *context) {
  if (context->go_to_offset) {
    return;
  }

  switch (context->next_param) {
  case TOKEN:
    copy_address(context->token, msg->parameter, sizeof(context->token));
    context->next_param = AMOUNT_IN;
    break;
  case AMOUNT_IN: // transfer amount in
    copy_parameter(context->amount_in, msg->parameter,
                   sizeof(context->amount_in));
    context->next_param = DST_CHAIN_ID;
    context->go_to_offset = true;
    break;
  default:
    PRINTF("Param not supported: %d\n", context->next_param);
    msg->result = ETH_PLUGIN_RESULT_ERROR;
    break;
  }
}

void handle_provide_parameter(void *parameters) {
  ethPluginProvideParameter_t *msg = (ethPluginProvideParameter_t *)parameters;
  context_t *context = (context_t *)msg->pluginContext;
  // We use `%.*H`: it's a utility function to print bytes. You first give
  // the number of bytes you wish to print (in this case, `PARAMETER_LENGTH`)
  // and then the address (here `msg->parameter`).
  semihosted_printf("plugin provide parameter: offset %d\nBytes: %.*H\n",
                    msg->parameterOffset, PARAMETER_LENGTH, msg->parameter);

  msg->result = ETH_PLUGIN_RESULT_OK;

  switch (context->selectorIndex) {
  case POOL_BASED_SEND_ERC20:
    handle_send_erc_20_tokens_paramters(msg, context);
    break;
  case POOL_BASED_SEND_NATIVE:
    handle_send_native_tokens_paramters(msg, context);
    break;
  case PEGGED_TOKEN_DEPOSIT_MINT:
    handle_pegged_token_deposit(msg, context);
    break;
  case PEGGED_TOKEN_BURN_WITHDRAW:
    handle_pegged_token_burn(msg, context);
    break;
  case POOL_BASED_TOKEN_REFUND:
    break;
  default:
    PRINTF("Selector Index not supported: %d\n", context->selectorIndex);
    msg->result = ETH_PLUGIN_RESULT_ERROR;
    break;
  }
}