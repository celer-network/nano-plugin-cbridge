#include "boilerplate_plugin.h"

void handle_finalize(void *parameters) {

    ethPluginFinalize_t *msg = (ethPluginFinalize_t *) parameters;
    context_t *context = (context_t *) msg->pluginContext;

    msg->uiType = ETH_UI_TYPE_GENERIC;

    msg->numScreens = 2;

    if (context->selectorIndex == PEGGED_TOKEN_BURN_WITHDRAW) {
        msg->numScreens = 1;
    } else if (context->selectorIndex == POOL_BASED_TOKEN_REFUND) {
        msg->numScreens = 0;
    }

    // token addresses you will info for (such as decimals, ticker...).
    msg->tokenLookup1 = context->token;

    msg->result = ETH_PLUGIN_RESULT_OK;

}
