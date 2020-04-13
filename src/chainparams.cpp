// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2018-2020 The VIP  developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "libzerocoin/Params.h"
#include "chainparams.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

#define NEVER 2035454400

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (0, uint256("0x000007e8f7dcdcd4a2d699a306c5ed9df0cf5b90c8754570b2148ea2eb80d2bf"))
	(230, uint256("0xfbec0d8bb8c17b2152703d13dba2d9a2fa4200465824e462403efeeff7edab7e"))        
    (17664, uint256("0xe6bb541553bd7cffbe9bf45fbe4559881a9e3fb748ee4a1c53dc74e496140dbe"))
    (29739, uint256("0x5d03b8ad6b1ab5d8295e032c4bef9da90418c204341cf3e68bffff629c1af68f"))
    (64396, uint256("0x597edf272b7b8d7a406e8787ae4e1c502eaab8f799b3e8569d75a0e3fe107659"))
    (81478, uint256("0x56c88b5593b3e049b6ae6cc3eda4ff0d5b74940fbf5aca3ca6566857d3f1f609"))
    (125825, uint256("0x6123f48a940914158e79037a8013d4ab625145e2efff561139d2260d58595087"))
    (134592, uint256("0x1cd0014edce316b5de082ed7927d312d5dcf22b19266ddb5bea73f6074d6402b"))
    (384824, uint256("0x44787c5cf947ccab7ab6da1e6ab174a11a8567f45c92535e8b015c7894eb875f"))
    (394431, uint256("0x5a33fe4a8902042a0a5094e07eac5a221ac20df5d2ee646b4aec8f2427870756"))
    (395000, uint256("0x73a9012fe0525984c03f0cd9a69a444f2c719f63d7b17f1064a38a62a89aa323"))
    (648300, uint256("0x5FD25630D6B2BD847EFCA1E6513CFC5380464C011B8464AC9E00831914053B91"))
    ;
static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1545495546, // * UNIX timestamp of last checkpoint block
    1157185,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    2000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x0000022a3c4c98c850d22e5e3ec23e4ac3c927acd665e81f7444ed7d2ad5341b"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1545432546,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x00000372d06054846ee809edef9dd0e2c486c3c718b26d750ece21bc16f49adc"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1454124731,
    0,
    100};

libzerocoin::ZerocoinParams* CChainParams::Zerocoin_Params(bool useModulusV1) const
{
    assert(this);
    static CBigNum bnHexModulus = 0;
    if (!bnHexModulus)
        bnHexModulus.SetHex(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParamsHex = libzerocoin::ZerocoinParams(bnHexModulus);
    static CBigNum bnDecModulus = 0;
    if (!bnDecModulus)
        bnDecModulus.SetDec(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParamsDec = libzerocoin::ZerocoinParams(bnDecModulus);

    if (useModulusV1)
        return &ZCParamsHex;

    return &ZCParamsDec;
}

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x25;
        pchMessageStart[1] = 0xf8;
        pchMessageStart[2] = 0xc3;
        pchMessageStart[3] = 0x47;
        vAlertPubKey = ParseHex("04647D36FF5978B16625459FD1BC563C4C4174408F961C4A3D25452EB8D5B0E7A093153F00B2F3E68E41968C6DAB2EEEEE7330990D0BB9083D4D0CCC9CB86C2F7F");
        nDefaultPort = 28181;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // VIP starting difficulty is 1 / 2^12
        nSubsidyHalvingInterval = 210000;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // VIP: 1 day
        nTargetSpacing = 1 * 60;  // VIP: 1 minute
        nMaturity = 10;
        nMasternodeCountDrift = 10;
        nMasternodeCollateralAmt = 4000;
        nMaxMoneyOut = 1000000 * COIN;
		strDeveloperFeePayee = "VBkHCDZSf3znuDPtZJck6dmSXhPzzAzF5E";
		
        /** Height or Time Based Activations **/
        nLastPOWBlock = 395200;
        nBlockTimeChange = 670000;
        nModifierUpdateBlock = 615800;
        nBadPosStartBlockTime = 1546604168; //01/04/2019 @ 12:16pm (UTC)
        nBadPosStartBlocknBits = 0x1e014d1f;
        nZerocoinStartHeight = NEVER;
        nZerocoinStartTime = NEVER;
        nBlockEnforceSerialRange = NEVER;       //Enforce serial range starting this block
        nBlockRecalculateAccumulators = NEVER; //Trigger a recalculation of accumulators
        nBlockFirstFraudulent = NEVER;          //First block that bad serials emerged
        nBlockLastGoodCheckpoint = NEVER; //Last valid accumulator checkpoint
        nBlockEnforceInvalidUTXO = NEVER; //Start enforcing the invalid UTXO's
        nInvalidAmountFiltered = 0*COIN; //Amount of invalid coins filtered through exchanges, that should be considered valid
        nBlockZerocoinV2 = NEVER; //!> The block that zerocoin v2 becomes active - roughly Tuesday, May 8, 2018 4:00:00 AM GMT
		


        const char* pszTimestamp = "Vip, Value is Precious, 22 December 2018 The Day of Krakatau tsunami";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 0 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04ffff001d0104445669702c2056616c75652069732050726563696f75732c20323220446563656d62657220323031382054686520446179206f66204b72616b61746175207473756e616d69") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1545495546;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 819875;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x000007e8f7dcdcd4a2d699a306c5ed9df0cf5b90c8754570b2148ea2eb80d2bf"));
        assert(genesis.hashMerkleRoot == uint256("0xdd92973198a0995713770a8232b33473fd4b90c43048a1e7f91a6a1b4e2c864d"));

        vSeeds.push_back(CDNSSeedData("mainseed.vipseednodes.org", "mainseed.vipseednodes.org"));
        vSeeds.push_back(CDNSSeedData("mainseed2.vipseednodes.org", "mainseed2.vipseednodes.org"));
		
        vSeeds.push_back(CDNSSeedData("1", "168.235.86.63:28181"));
        vSeeds.push_back(CDNSSeedData("2", "144.217.84.127:28181"));
        vSeeds.push_back(CDNSSeedData("3", "198.245.53.210:28181"));
        vSeeds.push_back(CDNSSeedData("4", "54.38.194.26:28181"));
        vSeeds.push_back(CDNSSeedData("5", "45.63.14.154:28181"));
        vSeeds.push_back(CDNSSeedData("6", "82.169.168.31:28181"));
        vSeeds.push_back(CDNSSeedData("7", "142.93.115.23:28181"));
        vSeeds.push_back(CDNSSeedData("8", "192.99.212.38:28181"));
        vSeeds.push_back(CDNSSeedData("9", "45.77.217.47:28181"));
        vSeeds.push_back(CDNSSeedData("10", "54.39.150.22:28181"));
        vSeeds.push_back(CDNSSeedData("11", "192.99.212.38:28181"));
        vSeeds.push_back(CDNSSeedData("12", "45.77.217.47:28181"));
        vSeeds.push_back(CDNSSeedData("13", "109.172.59.29:28181"));
        vSeeds.push_back(CDNSSeedData("14", "140.213.45.103:28181"));
        vSeeds.push_back(CDNSSeedData("15", "176.223.136.85:28181"));
	    vSeeds.push_back(CDNSSeedData("16", "77.219.132.146:28181"));
	    vSeeds.push_back(CDNSSeedData("17", "155.138.217.218:28181"));
	    vSeeds.push_back(CDNSSeedData("18", "115.178.237.116:28181"));
	    vSeeds.push_back(CDNSSeedData("19", "60.54.90.163:28181"));
	    vSeeds.push_back(CDNSSeedData("20", "171.50.204.82:28181"));
	    vSeeds.push_back(CDNSSeedData("21", "103.75.189.59:28181"));
	    vSeeds.push_back(CDNSSeedData("22", "103.75.189.29:28181"));
	    vSeeds.push_back(CDNSSeedData("23", "175.142.84.174:28181"));
	    vSeeds.push_back(CDNSSeedData("24", "77.217.30.41:28181"));
	    vSeeds.push_back(CDNSSeedData("25", "45.169.109.39:28181"));
	    vSeeds.push_back(CDNSSeedData("26", "167.114.114.243:28181"));
        vSeeds.push_back(CDNSSeedData("27", "155.138.164.230:28181"));
        vSeeds.push_back(CDNSSeedData("28", "45.32.222.211:28181"));
        vSeeds.push_back(CDNSSeedData("29", "155.138.197.141:28181"));
        vSeeds.push_back(CDNSSeedData("30", "207.246.118.22:28181"));
        vSeeds.push_back(CDNSSeedData("31", "144.202.30.246:28181"));
	    vSeeds.push_back(CDNSSeedData("32", "155.138.160.37:28181"));
	    vSeeds.push_back(CDNSSeedData("33", "103.75.191.86:28181"));
	    vSeeds.push_back(CDNSSeedData("34", "66.42.81.117:28181"));
	    vSeeds.push_back(CDNSSeedData("35", "54.227.211.235:28181"));
	    vSeeds.push_back(CDNSSeedData("36", "158.69.197.220:28181"));
	    vSeeds.push_back(CDNSSeedData("37", "167.114.152.3:28181"));
	    vSeeds.push_back(CDNSSeedData("38", "144.217.4.52:28181"));
	    vSeeds.push_back(CDNSSeedData("39", "54.39.149.191:28181"));
	    vSeeds.push_back(CDNSSeedData("40", "202.143.111.151:28181"));
		
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 70);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 106);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 56);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();
        // 	BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0xD6)(0xD8).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        nEnforceNewSporkKey = 1566748666; //!> Sporks signed after 08/25/2019 @ 3:57pm (UTC) must use the new spork key
        nRejectOldSporkKey = 1568073600;  //!> Fully reject old spork key after 09/10/2019 @ 12:00am (UTC)

        strSporkKey = "02b233adf70ac36e778015ae2eb8cf7d9092183c3334e98fad0e2aea5723ef271d";
        strSporkKeyOld = "049e53e687fdafd78fd42d730fad0e7ea1819396176a2cb85d7a76fa4559cdbd2c2f05330a6f5cbadb44a6c1d324f167e679e9f3e95d9d5649761a3e7f59bf4500";
        strObfuscationPoolDummyAddress = "VBkHCDZSf3znuDPtZJck6dmSXhPzzAzF5E";

        /** Zerocoin */
        zerocoinModulus = "25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784"
            "4069182906412495150821892985591491761845028084891200728449926873928072877767359714183472702618963750149718246911"
            "6507761337985909570009733045974880842840179742910064245869181719511874612151517265463228221686998754918242243363"
            "7259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133"
            "8441436038339044149526344321901146575444541784240209246165157233507787077498171257724679629263863563732899121548"
            "31438167899885040445364023527381951378636564391212010397122822120720357";
        nMaxZerocoinSpendsPerTransaction = 7; // Assume about 20kb each
        nMinZerocoinMintFee = 1 * CENT; //high fee required for zerocoin mints
        nMintRequiredConfirmations = 20; //the maximum amount of confirmations until accumulated in 19
        nRequiredAccumulation = 1;
        nDefaultSecurityLevel = 100; //full security level for accumulators
        nZerocoinHeaderVersion = 4; //Block headers must be this version once zerocoin is active
        nZerocoinRequiredStakeDepth = 200; //The required confirmations for a zVIP to be stakable

        nBudget_Fee_Confirmations = 6; // Number of confirmations for the finalization fee
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0x64;
        pchMessageStart[1] = 0x44;
        pchMessageStart[2] = 0x65;
        pchMessageStart[3] = 0x54;
        vAlertPubKey = ParseHex("04e1d34432d3a5803312f33cf20686b1801835ea8efb18ad77d50b5ec1ce5ca73de65c36c082ca5c51880f8ffb5a296d8dc780f1dc02f22eba4dde1816a6a54b75");
        nDefaultPort = 28189;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // VIP: 1 day
        nTargetSpacing = 1 * 60;  // VIP: 1 minute
        nLastPOWBlock = 200;
        nBlockTimeChange = 670000;
        nMaturity = 15;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 51197; //approx Mon, 17 Apr 2017 04:00:00 GMT
        nMaxMoneyOut = 100000000  * COIN;
        nZerocoinStartHeight = 1000000;
        nZerocoinStartTime = 1501776000;
        nBlockEnforceSerialRange = 1; //Enforce serial range starting this block
        nBlockRecalculateAccumulators = 9908000; //Trigger a recalculation of accumulators
        nBlockFirstFraudulent = 9891737; //First block that bad serials emerged
        nBlockLastGoodCheckpoint = 9891730; //Last valid accumulator checkpoint
        nBlockEnforceInvalidUTXO = 9902850; //Start enforcing the invalid UTXO's
        nInvalidAmountFiltered = 0; //Amount of invalid coins filtered through exchanges, that should be considered valid
        nBlockZerocoinV2 = 444020; //!> The block that zerocoin v2 becomes active
        nEnforceNewSporkKey = 1521604800; //!> Sporks signed after Wednesday, March 21, 2018 4:00:00 AM GMT must use the new spork key
        nRejectOldSporkKey = 1522454400; //!> Reject old spork key after Saturday, March 31, 2018 12:00:00 AM GMT

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1545432546;
        genesis.nNonce = 1952421;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x0000022a3c4c98c850d22e5e3ec23e4ac3c927acd665e81f7444ed7d2ad5341b"));

        vFixedSeeds.clear();
        vSeeds.clear();
		
        vSeeds.push_back(CDNSSeedData("185.52.3.126:28181", "185.52.3.126:28189"));
        vSeeds.push_back(CDNSSeedData("168.235.85.225:28181", "168.235.85.225:28189"));
        vSeeds.push_back(CDNSSeedData("168.235.85.173:28181", "168.235.85.173:28189"));
        vSeeds.push_back(CDNSSeedData("168.235.85.54:28181", "168.235.85.54:28189"));
        vSeeds.push_back(CDNSSeedData("168.235.96.66:28181", "168.235.96.66:28189"));
        vSeeds.push_back(CDNSSeedData("168.235.86.63:28181", "168.235.86.63:28189"));
		
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 83); // Testnet vip addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 18);  // Testnet vip script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 193);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)

        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();

        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();

        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "049e53e687fdafd78fd42d730fad0e7ea1819396176a2cb85d7a76fa4559cdbd2c2f05330a6f5cbadb44a6c1d324f167e679e9f3e95d9d5649761a3e7f59bf4500";
        strObfuscationPoolDummyAddress = "";
        nStartMasternodePayments = 1510272000;
        nBudget_Fee_Confirmations = 3;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0x14;
        pchMessageStart[1] = 0x54;
        pchMessageStart[2] = 0x95;
        pchMessageStart[3] = 0x64;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // VIP: 1 day
        nTargetSpacing = 1 * 60;        // VIP: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1454124731;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 447568;

        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 55700;
        assert(hashGenesisBlock == uint256("0x00000372d06054846ee809edef9dd0e2c486c3c718b26d750ece21bc16f49adc"));

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 51478;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
