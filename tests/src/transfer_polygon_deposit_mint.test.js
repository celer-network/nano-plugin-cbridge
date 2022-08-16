import "core-js/stable";
import "regenerator-runtime/runtime";
import {
  waitForAppScreen,
  zemu,
  nano_models,
  populateTransaction,
} from "./test.fixture";

const contractAddr = "0x5427fefa711eff984124bfbb1ab6fbf5e3da1820";
const pluginName = "cBridge";
const abi_path =
  `../networks/ethereum/${pluginName}/abis/` + contractAddr + ".json";
const abi = require(abi_path);

const testPolygonDepositMint = (model) => {
  test(
    "[Nano " + model.letter + "] send tokens on polygon",
    zemu(
      model,
      async (sim, eth) => {
        const rawTx =
          "0x2346362400000000000000000000000004b33078ea1aef29bf3fb29c6ab7b200c58ea12600000000000000000000000000000000000000000000086093dc3cf87f6390ec00000000000000000000000000000000000000000000000000000000000000380000000000000000000000009ec92985871152af80d0851237ac36678a1068bd000000000000000000000000000000000000000000000000000001828c96f593";
        // const resolution = await ledgerService.resolveTransaction("fd8e412d4646115cd52d330486796faf30b28de13ff36cce9c20032778af2161");

        const serializedTx = populateTransaction(
          "0xc1a2d967dfaa6a10f3461bc21864c23c1dd51eea",
          rawTx,
          137
        );

        const tx = eth.signTransaction("44'/60'/0'/0", serializedTx);

        const right_clicks = model.letter === "S" ? 8 : 6;

        // Wait for the application to actually load and parse the transaction
        await waitForAppScreen(sim);
        // Navigate the display by pressing the right button `right_clicks` times, then pressing both buttons to accept the transaction.
        await sim.navigateAndCompareSnapshots(
          ".",
          "polygon_deposit_mint_" + model.name + "_cbridge",
          [right_clicks, 0]
        );

        await tx;
      },
      "polygon"
    )
  );
};

nano_models.forEach(function (model) {
  testPolygonDepositMint(model);
});
