import "core-js/stable";
import "regenerator-runtime/runtime";
import {
  waitForAppScreen,
  zemu,
  nano_models,
  txFromEtherscan,
  populateTransaction,
} from "./test.fixture";

// https://bscscan.com/tx/0xfd8e412d4646115cd52d330486796faf30b28de13ff36cce9c20032778af2161
const testBscTransferContract = (model) => {
  test(
    "[Nano " + model.letter + "] send tokens on bsc",
    zemu(
      model,
      async (sim, eth) => {
        const rawTx =
          "0xa5977fbb00000000000000000000000082571c922d3faaf48df53c74bb0f116e48c34f9300000000000000000000000055d398326f99059ff775485246999027b31979550000000000000000000000000000000000000000000000013f306a2409fc000000000000000000000000000000000000000000000000000000000000000000fa000000000000000000000000000000000000000000000000000001810f3e9dfa00000000000000000000000000000000000000000000000000000000000088e6";
        // const resolution = await ledgerService.resolveTransaction("fd8e412d4646115cd52d330486796faf30b28de13ff36cce9c20032778af2161");

        const serializedTx = populateTransaction(
          "0xdd90e5e87a2081dcf0391920868ebc2ffb81a1af",
          rawTx,
          56
        );

        const tx = eth.signTransaction("44'/60'/0'/0", serializedTx);

        const right_clicks = 6;

        // Wait for the application to actually load and parse the transaction
        await waitForAppScreen(sim);
        // Navigate the display by pressing the right button `right_clicks` times, then pressing both buttons to accept the transaction.
        await sim.navigateAndCompareSnapshots(
          ".",
          "bsc_poolbased_send_" + model.name + "_cbridge",
          [right_clicks, 0]
        );

        await tx;
      },
      "bsc"
    )
  );
};

// https://etherscan.io/tx/0x74319484a8570e444c3cd306c5ec0bb10ca87a60dcdf83d602699244ee563f46
const testPeggedDeposit = (model) => {
  test(
    "[Nano " + model.letter + "] Send ERC20 tokens",
    zemu(model, async (sim, eth) => {
      // The rawTx of the tx up above is accessible through: https://etherscan.io/getRawTx?tx=0x74319484a8570e444c3cd306c5ec0bb10ca87a60dcdf83d602699244ee563f46
      const serializedTx = txFromEtherscan(
        "0x02f90113018201478459682f00850e57c5584c83013e8994b37d31b2a74029b5951a2778f959282e2d51859580b8a423463624000000000000000000000000c02aaa39b223fe8d0a0e5c4f27ead9083c756cc2000000000000000000000000000000000000000000000000fb301e1a229200000000000000000000000000000000000000000000000000000000000000000250000000000000000000000000129ddf9c3958d5ae6a5a61a40110beb8d7ca8e7d000000000000000000000000000000000000000000000000000001828822427cc001a0824be0a92f39a3087297c3096e0c4ae1b910b9af86ec1188b648dc83627b34faa011ae71129e7a5b113a0f5aaed6224b1689b527c88e3b105bc685d9df4307b332"
      );

      const tx = eth.signTransaction("44'/60'/0'/0", serializedTx);

      const right_clicks = model.letter === "S" ? 7 : 5;

      // Wait for the application to actually load and parse the transaction
      await waitForAppScreen(sim);
      // Navigate the display by pressing the right button `right_clicks` times, then pressing both buttons to accept the transaction.
      await sim.navigateAndCompareSnapshots(
        ".",
        "bsc_deposit_mint_" + model.name + "_cbridge",
        [right_clicks, 0]
      );

      await tx;
    })
  );
};

// https://bscscan.com/tx/0xda7db78ff7bce38fcaa3079f0532aaff20e3bb43c6ec08fb0de2e96945238ec0
const testPeggedBurn = (model) => {
  test(
    "[Nano " + model.letter + "] Token Burn and Withdraw",
    zemu(
      model,
      async (sim, eth) => {
        const serializedTx = populateTransaction(
          "0xd443fe6bf23a4c9b78312391a30ff881a097580e",
          "0xde790c7e000000000000000000000000bd7b8e4de08d9b01938f7ff2058f110ee1e0e8d4000000000000000000000000000000000000000000000f6f4fb76601ef9d47df000000000000000000000000477d057ee378168d33d62eca943c0247e8b04139000000000000000000000000000000000000000000000000000001828602d48b",
          56
        );

        const tx = eth.signTransaction("44'/60'/0'/0", serializedTx);

        const right_clicks = model.letter === "S" ? 7 : 5;

        // Wait for the application to actually load and parse the transaction
        await waitForAppScreen(sim);
        // Navigate the display by pressing the right button `right_clicks` times, then pressing both buttons to accept the transaction.
        await sim.navigateAndCompareSnapshots(
          ".",
          "bsc_burn_withdraw_" + model.name + "_cbridge",
          [right_clicks, 0]
        );

        await tx;
      },
      "bsc"
    )
  );
};

nano_models.forEach(function (model) {
  testBscTransferContract(model);
  testPeggedDeposit(model);
  testPeggedBurn(model);
});
