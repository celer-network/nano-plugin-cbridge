import "core-js/stable";
import "regenerator-runtime/runtime";
import {
  waitForAppScreen,
  zemu,
  nano_models,
  txFromEtherscan,
} from "./test.fixture";

const testSendNativeContract = (model) => {
  test(
    "[Nano " + model.letter + "] Send native tokens",
    zemu(model, async (sim, eth) => {
      // The rawTx of the tx up above is accessible through: https://etherscan.io/getRawTx?tx=0x88307c4b59adf91a51e49326d10976a1e4c262c1a64e850319aa148c9b993705
      const serializedTx = txFromEtherscan(
        "0x02f9011901278459682f008503dd09334a83014797945427fefa711eff984124bfbb1ab6fbf5e3da1820880a118ddc565082d8b8a43f2e5fc3000000000000000000000000d98bed08bcfdb1a3145323dbe9df5623041141560000000000000000000000000000000000000000000000000a118ddc565082d80000000000000000000000000000000000000000000000000000000000000038000000000000000000000000000000000000000000000000000001826783ee950000000000000000000000000000000000000000000000000000000000002a22c001a0cf22318ebb692130d07d2cd6a509260a8eab6f40c3664a69d501acf8cc907995a00c7db25d2df2fd6fa6e58d94179f4e2468b5cae90e0bb70db6111f2c5086c0d0"
      );

      const tx = eth.signTransaction("44'/60'/0'/0", serializedTx);

      const right_clicks = model.letter === "S" ? 8 : 5;

      // Wait for the application to actually load and parse the transaction
      await waitForAppScreen(sim);
      // Navigate the display by pressing the right button `right_clicks` times, then pressing both buttons to accept the transaction.
      await sim.navigateAndCompareSnapshots(
        ".",
        "ethereum_poolbased_send_native_" + model.name + "_cbridge",
        [right_clicks, 0]
      );

      await tx;
    })
  );
};

nano_models.forEach(function (model) {
  testSendNativeContract(model);
});
