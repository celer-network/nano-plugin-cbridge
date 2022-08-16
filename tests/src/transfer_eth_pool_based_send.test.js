import "core-js/stable";
import "regenerator-runtime/runtime";
import {
  waitForAppScreen,
  zemu,
  nano_models,
  txFromEtherscan,
} from "./test.fixture";

// Test from replayed transaction: https://etherscan.io/tx/0x9de7a0ded6f6ca7e33dfb4bd6482f67da446200abfa0cd6f12e27d5ae01a90cc
const testSendErc20Contract = (model) => {
  test(
    "[Nano " + model.letter + "] Send ERC20 tokens",
    zemu(model, async (sim, eth) => {
      // The rawTx of the tx up above is accessible through: https://etherscan.io/getRawTx?tx=0x9de7a0ded6f6ca7e33dfb4bd6482f67da446200abfa0cd6f12e27d5ae01a90cc
      const serializedTx = txFromEtherscan(
        "0x02f901320181df8459682f00850a8436dfa683018fe1945427fefa711eff984124bfbb1ab6fbf5e3da182080b8c4a5977fbb000000000000000000000000cdaefd7363009fe8e48aef4593e5271d87e7c08e000000000000000000000000a0b86991c6218b36c1d19d4a2e9eb0ce3606eb4800000000000000000000000000000000000000000000000000000000773594000000000000000000000000000000000000000000000000000000000000000038000000000000000000000000000000000000000000000000000001823ade10e00000000000000000000000000000000000000000000000000000000000000db2c001a0c9deef3913ca92f69feeaca2411f35d53a6022d5f76190fd8e1ce32c9fb729e6a072debced867fc4c5f7c458a5b01281362f426446d61c26efcb5f25363e714fcc"
      );

      const tx = eth.signTransaction("44'/60'/0'/0", serializedTx);

      const right_clicks = model.letter === "S" ? 7 : 5;

      // Wait for the application to actually load and parse the transaction
      await waitForAppScreen(sim);
      // Navigate the display by pressing the right button `right_clicks` times, then pressing both buttons to accept the transaction.
      await sim.navigateAndCompareSnapshots(
        ".",
        "ethereum_poolbased_send_" + model.name + "_cbridge",
        [right_clicks, 0]
      );

      await tx;
    })
  );
};

nano_models.forEach(function (model) {
  testSendErc20Contract(model);
});
