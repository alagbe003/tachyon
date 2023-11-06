#include "tachyon/zk/base/halo2_random_field_generator.h"

#include "gtest/gtest.h"

#include "tachyon/math/elliptic_curves/bn/bn254/fq.h"

namespace tachyon::zk {

namespace {

class Halo2RandomFieldGeneratorTest : public testing::Test {
 public:
  using F = tachyon::math::bn254::Fq;

  static void SetUpTestSuite() { F::Init(); }
};

}  // namespace

TEST_F(Halo2RandomFieldGeneratorTest, FromUint512) {
  uint64_t limbs4[4] = {
      0x1f8905a172affa8a,
      0xde45ad177dcf3306,
      0xaaa7987907d73ae2,
      0x24d349431d468e30,
  };
  uint64_t limbs8[8] = {0xaaaaaaaaaaaaaaaa, 0xaaaaaaaaaaaaaaaa,
                        0xaaaaaaaaaaaaaaaa, 0xaaaaaaaaaaaaaaaa,
                        0xaaaaaaaaaaaaaaaa, 0xaaaaaaaaaaaaaaaa,
                        0xaaaaaaaaaaaaaaaa, 0xaaaaaaaaaaaaaaaa};
  EXPECT_EQ(F(math::BigInt<4>(limbs4)),
            Halo2RandomFieldGenerator<F>::FromUint512(limbs8));
}

TEST_F(Halo2RandomFieldGeneratorTest, Random) {
  const char* kHexes[100] = {
      "0x04c0df95382d049b3f56cefbdebef7dc581a26714b42aa21726c2cfe23481d5a",
      "0x08c6d7817f7a5cb6758026c475fa2b7ea7494096c1909c8c95f518d996764d12",
      "0x051c8acd0aabc82eb4d2a8fdc63e3c1f5efaa3fdc77d92e4457828dde0f44f57",
      "0x28e1c531c820a3fbd30315fdd199e2bf19cfa1a24ccd7be082d3cf079a602a76",
      "0x2d5036b931a10dab382a642845414d9399c84c29e7db8fe8b7734c30f03368d5",
      "0x16e4466b9893ed39d6be48229b5d6975bc883632f287873d82995386087c2475",
      "0x057719f52e98c4a879b066c245fb5be56a73a39b5a3799b0abf8d8f1933f1191",
      "0x23e9b8ad937dae0d113d2e7c307848a410d969d3116222cffd1e634fb201a363",
      "0x1e46210497db66cf2b934fc182ff1b2c5f18da53af66f94632ba8949191e9b59",
      "0x27d8590e96092285e77322c171ec04bc0cacb73bbe6ace60f53b48181ca1d40f",
      "0x2abe4c782144af9046bf61a3b46fb5f45990438e39d0d1d8f3022aecc7096a27",
      "0x1597a7d12553ec239ceb6afcc3f49e8c9ff817d129d779b1cc822e2402edd670",
      "0x23e7df5dbe66aa13863387e29d22d24a629ed53c81addb37404bf0a515ce51d9",
      "0x0eb29e372d5dc28817305251710020d46a594c099b2602853d0901885ee422ac",
      "0x2a8ead7809cfec3724716f358778b980dc3554ae2a55bc2959ddd64fbe16d55f",
      "0x1bc5c35a19739a1ebf803ee0d62e54a4a2e526d6346ddffa8d136cb4e4d57238",
      "0x00955bbc5644fe6457736cf837b04f006d883026a9d58f33906bbd05ed5ca83c",
      "0x042b36010b0278aac9100c60d485d093b0c5a3f6c4905421086d3d1d19d2e342",
      "0x01b0fa4335106b48f8c1f97911c3dc9aa5518c26000f4d6bad49482d6b75f4b5",
      "0x1a521f6df72ab428175cb044bb2096f9eddcd3eeda42de3f540a2d4922a6c90e",
      "0x1dd7ea53479574deedd41f679c3745537f3611bbe0b146d163260268430c148e",
      "0x15a71302f85a77665c5851b4a4cbe5bcfd405b68fe351e9d503f41f7003c360b",
      "0x1dcbb36fa28e0d1da5cbcf9c49203b047a249a0fd0ec58642b4641b205e70aa0",
      "0x208ace355e9a9c0db9926a0216e77bcafdcff2c36811d1c3650a842a7ba66793",
      "0x10ed8d8524b4d3bd666b9fcbb2dd96d3e60c2c0e73a527123656894528ef3508",
      "0x01e4ececcf2224251b23bf1c487a63486d7638560cac59175db921be841b845c",
      "0x29cb73f3df698cf5ecb15645bd86d6c554d9779f3d748d62b8671cfa4c0c3b7a",
      "0x1420a19bb322c3f3d9227a385661b1590537d07f8b9f2c01825e17f4c9691e75",
      "0x11f073e249d5e0fc3069e041581ad2e64bac88c9896d50dfe7e4c2a7055e5905",
      "0x1a53132780f543ead917b371cdae8738eb0242a7c868647f426489e74e9eada9",
      "0x2653bdbf4ce9064b52ebe805b60554a297e94d428eb67c0ef44e289143f115b1",
      "0x0b72a8b0fcde9f4264a898276e756aac7755651ef0d30badcf18b94880079fd6",
      "0x1b01a1b8bd81bba5a0f898b269a3de7a77ebdc712814bf843f62fd57138aadcb",
      "0x0f3062d2897d996ed991a47f9e6d88d23a8f324c2a558947ebc9070b56dcd23a",
      "0x272368a1b275ededd904841cb256b0a5347275e3a54aa0b00c1d3b361945083a",
      "0x08f9cfe12b60f0badc3eb1f64e889c6fd71d1b433017fdbdd95b4881ddbfdc88",
      "0x2d78263a43e61e0e6cdeaa8b74a2b588ce3770d6f19b968e2c0c3a923e47b1ee",
      "0x26860edd85d8f942d8a046095fdc1fc0ad762a5a653e0ec7480b42051d471dbf",
      "0x261b42d48ee22d4a6cb0a6b07abd8ba0cbce43e430237d7522aa4d3e91636c95",
      "0x1846961eeaecab911bb14c20b5384572ad05d194d875d3c8d601321cc6f7c3ae",
      "0x0b85e81ae4f123e0202c0aa171f4086179b1abf04dd59c1d020e2f423f08b548",
      "0x1c6a6c4381bc777b8795d6068de21ef34628723f1dac53bf01c8c5e64b5e76eb",
      "0x2d3cdab29809b5a85d7e66eeb02b8511e1dbf2bab6faa85c9aff698594321c7c",
      "0x04f9fa4d2c21eaeed9f4fe31b594edb1eedf34e402f843c7b9e20b1b5b7a2709",
      "0x08d46c2d481bffa90e8442161be2cff717fe2b6c05e44e5a6e11cd8eec31fab7",
      "0x236e2a2bae21ef371ea7adbe7bdb388f7a6a2e61bd84a7111406dad355258bc3",
      "0x22dcb608834a4a53a3adce415fecf74c23fc2d946d16bb825e8ee2a1c9efe7de",
      "0x01fe3570358e2e6944a35bbc0b7f55b2b20a9b52610772f18e871f6a03380b50",
      "0x25417d08811b2b6e10dcde0222c0c49bcf5a431976898015a6276852d19ad361",
      "0x09835b9c6d253092bf85ee4313489d3c96b1766489ed5264124a49c7ca4ceba4",
      "0x06ff2920f3be9e964bf662af2bf51bb191aff6206ef912ee550bc3412ca33926",
      "0x067239e7df206e993f580ac8e56307584883a13fd9b199eb142ec7dff0880254",
      "0x0b49940fa89118550cc0cc5e8774ad162f143ca615509bba35b6549c4367830f",
      "0x2930de6691bf0c0a97b9399116201feb9610bbc7b0faf1e7ad12c69754b742eb",
      "0x1275a7aa719e716a6877539f2e860013ec55ea33c311227864956fb7a4897dcc",
      "0x2f4030a22b740b6364d1ac5c6a6b88a69adf1a730b7d3ff5081d0710f9701cc8",
      "0x074d89a8bc3a19211fbe3b2b60b9a5c28d53513cfb0ce7a1b645346508aef057",
      "0x0f38098ffaac74b743150e137d60b642deb895088ebbef8c9398ad56971c8e94",
      "0x16cc0e0b1abc680184ea8fd0cc28011f0a1374bb3a8676533acbdd610a2c888f",
      "0x297e264e5624095a4503ad9d556dafee1d04b2366813093c1e9e0e959d2cbdcb",
      "0x182fdb9fc272ecaf6ae4893d59b2c64fa2c9904ba917259bfe3448e6f937781c",
      "0x11bcb82c4be4f8b16f3c13163307e71a893e2240636680ef27d1e1d5089ed228",
      "0x08a017fca03c7a2882b31a6b28b87f47ef12904faddaf8fd3d6981e77bc834b9",
      "0x1e550895743a5a9c28d2c8c713710a570843f4823af815e9535d2f40d48d90d9",
      "0x1d007c6eb2f3ced2ec0ff19431b11d0a5b2ceb90ee2f2376b80eaf832113508e",
      "0x18db52504caa6c543e32122da8bb44a63d4c1b412a8bb66193e0299d7e4bde6e",
      "0x1c25d411573b9d0e638faf27a6818fae08586dd788d6ba741a12428c11a1f63c",
      "0x1074c2b043d4569c6934889a2499a70f8ae33a2154df203acee322a3ac179ed9",
      "0x0639d90550920397f0aa9a7236f92f5acf35877022138f8b6c41d492480aba8a",
      "0x1438e75d34d08ebfbb4488f83e7392cca504cfbdd3c9a098c62ba48ca75fb8bc",
      "0x209c6837a41441e98094fdd2cf102320237bc071c7ec96e58deb52d8fda0a03a",
      "0x00d654fcdebb22be811e42504cedb78d1346e72aadde501c9e5411c93639436b",
      "0x1e2192ab1607dc8fd0f250496d38bc2cc1297af9625a28685be017f9cc6cf583",
      "0x2406995ea444a2abeae77aef98bf4b304036419c73209d073baccf67b12de705",
      "0x23cc42bbd88a4bf15859afbaa6f47f81e6d2ffaa4dc683e252877636fb5819fa",
      "0x259ea37ca43f2d367cdb213ad999080d1be0d2312347279d4466c3b6dc8c52c7",
      "0x1270b3dfeff7c7041872ab640b836ba59055262d4c7b41fd31f2cac0483848ba",
      "0x04e5d81ac6519cc3a73c17eb0cd2471db8c910011d8fd090476f7f065a1a22d1",
      "0x18f99bcf3b3ebe30d043a3323d7ae9d92a3642c2dc2ddd1b04b437c92a989074",
      "0x29d30e669dc42608a50d58c3909e7de6c123849f1ee89203aaeeb1013775b68b",
      "0x0ed793fd47fbcc85bd3beb65ecb2a47dd197437b6eb892728fbe0035f006fdc0",
      "0x1bc9e7393b108034e339bd1c54de786b6f4250fd5186a7c1f9950f89bb7a70c1",
      "0x00ed226122b847cfa97deab27fcf5bfa952556884277e4cd6bf1c0f4f5f0abdd",
      "0x0f2acf93f165dcf49e7f1c3aa6213659e4ec5fce125a20e8cc7a2d148e773e0d",
      "0x1730f609d6c5172884db17ac3c132220f82e27585894f118f471eecb7d4eb704",
      "0x2e92d081f869a21c16559ab6ef4fd6729fd45a6aef77460cbc043455fba0ff2c",
      "0x23ddf85c1c485b84d5f7dc972911a660ef0821e4261dd0e1865b6d05e0bd21ad",
      "0x051dfd20c837b49ba68ff57b864db715b881e822018cd41ab877443101b03889",
      "0x12667b3c4c3c12c693a932330075c7ef1c08e66c8440b991c4bd6deafcefe275",
      "0x1161e8a2a44e7f42df4617df8b1197f0baad597e46a833c34351b00844538283",
      "0x02c2bdf17784ad108566daaa49b0f4a0e83a6541358dab3c29cdaa5853759cf6",
      "0x10ece8b3080ae081896314d52622b5a8812d535dd0aab61e51e8ab0d4ceade8d",
      "0x0535a539ab7f6bda53e9f053d3b621f2e714e74d8b96e2a6d49042be973393e5",
      "0x174393c2923b4cba2855fca4a6ba99adcc168a4e8ab2bd0000e1d88ba82040e7",
      "0x024dcba6ecbb810cf03a0979a9200ea8c2979e0f4e1905701d8f4a6c931ecd28",
      "0x0fe54c45d80610c9c5bed17daf58612eb3a3f02ec5d79c3ab2af094bee8ad2b1",
      "0x08b9b0d1543647d7bb4491fd119440b9cd7eebcf237f38471eb2ccfe941063d3",
      "0x035cf5267e698abcabcfd582ed43d982ecc31a4abaad018541aceeb0001db968",
      "0x0046a64362dc3f318d709d0d4059b1696da8fffe483f81c34383e1e092f370b0",
      "0x30606e181a9ba2b56a662dff4543ed30da6aad5fa1c41126dd287c95734ea0af",
  };

  uint8_t seed[16] = {0x59, 0x62, 0xbe, 0x5d, 0x76, 0x3d, 0x31, 0x8d,
                      0x17, 0xdb, 0x37, 0x32, 0x54, 0x06, 0xbc, 0xe5};
  crypto::XORShiftRNG rng = crypto::XORShiftRNG::FromSeed(seed);
  Halo2RandomFieldGenerator<F> generator(&rng);
  for (size_t i = 0; i < 100; ++i) {
    EXPECT_EQ(generator.Generate(), F::FromHexString(kHexes[i]));
  }
}

}  // namespace tachyon::zk
