#include "cbridge_plugin.h"

// List of selectors supported by this plugin.
/**
function send(
        address _receiver,
        address _token,
        uint256 _amount,
        uint64 _dstChainId,
        uint64 _nonce,
        uint32 _maxSlippage // slippage * 1M, eg. 0.5% -> 5000
    )
*/
static const uint32_t SEND_ERC20_TOKENS_SELECTOR = 0xa5977fbb;

/**
function sendNative(
        address _receiver,
        uint256 _amount,
        uint64 _dstChainId,
        uint64 _nonce,
        uint32 _maxSlippage
    )
*/
static const uint32_t SEND_NATIVE_TOKENS_SELECTOR = 0x3f2e5fc3;

/**
 function deposit(
        address _token,
        uint256 _amount,
        uint64 _mintChainId,
        address _mintAccount,
        uint64 _nonce
    )
*/
static const uint32_t DEPOSIT_MINT_SELECTOR = 0x23463624;
/**
function withdraw(
        bytes calldata _request,
        bytes[] calldata _sigs,
        address[] calldata _signers,
        uint256[] calldata _powers
    )
*/
static const uint32_t BURN_WITHDRAW_SELECTOR = 0xde790c7e;

/*
function withdraw(
        bytes calldata _request,
        bytes[] calldata _sigs,
        address[] calldata _signers,
        uint256[] calldata _powers
)
*/
static const uint32_t REFUND = 0xa21a9280;


// Array of all the different boilerplate selectors. Make sure this follows the
// same order as the enum defined in `boilerplate_plugin.h`
const uint32_t CBRIDGE_SELECTORS[NUM_SELECTORS] = {
    SEND_ERC20_TOKENS_SELECTOR,
    SEND_NATIVE_TOKENS_SELECTOR,
    DEPOSIT_MINT_SELECTOR,
    BURN_WITHDRAW_SELECTOR,
    REFUND,
};