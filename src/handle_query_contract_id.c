#include "boilerplate_plugin.h"

// Sets the first screen to display.
void handle_query_contract_id(void *parameters) {
    ethQueryContractID_t *msg = (ethQueryContractID_t *) parameters;
    const context_t *context = (const context_t *) msg->pluginContext;
    // msg->name will be the upper sentence displayed on the screen.
    // msg->version will be the lower sentence displayed on the screen.

    // For the first screen, display the plugin name.
    strlcpy(msg->name, PLUGIN_NAME, msg->nameLength);

    if (context->selectorIndex == POOL_BASED_SEND_ERC20) {
        strlcpy(msg->version, "Transfer", msg->versionLength);
        msg->result = ETH_PLUGIN_RESULT_OK;
    } else if(context->selectorIndex == POOL_BASED_SEND_NATIVE) {
        strlcpy(msg->version, "Transfer", msg->versionLength);
        msg->result = ETH_PLUGIN_RESULT_OK;
    } else if(context->selectorIndex == PEGGED_TOKEN_DEPOSIT_MINT) {
        strlcpy(msg->version, "Transfer", msg->versionLength);
        msg->result = ETH_PLUGIN_RESULT_OK;
    } else if(context->selectorIndex == PEGGED_TOKEN_BURN_WITHDRAW) {
        strlcpy(msg->version, "Transfer", msg->versionLength);
        msg->result = ETH_PLUGIN_RESULT_OK;
    } else if(context->selectorIndex == POOL_BASED_TOKEN_REFUND){
        strlcpy(msg->version, "Refund", msg->versionLength);
        msg->result = ETH_PLUGIN_RESULT_OK;
    } else {
        PRINTF("Selector index: %d not supported\n", context->selectorIndex);
        msg->result = ETH_PLUGIN_RESULT_ERROR;
    }
}