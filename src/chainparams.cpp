// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2015-2017 The VIP developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "random.h"
#include "util.h"
#include "utilstrencodings.h"
#include "bignum.h"
#include <assert.h>

#include <boost/assign/list_of.hpp>


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
    (17664, uint256("0xe6bb541553bd7cffbe9bf45fbe4559881a9e3fb748ee4a1c53dc74e496140dbe"))
    (29739, uint256("0x5d03b8ad6b1ab5d8295e032c4bef9da90418c204341cf3e68bffff629c1af68f"))
    (64396, uint256("0x597edf272b7b8d7a406e8787ae4e1c502eaab8f799b3e8569d75a0e3fe107659"))
    (81478, uint256("0x56c88b5593b3e049b6ae6cc3eda4ff0d5b74940fbf5aca3ca6566857d3f1f609"))
    ;
static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1545495546, // * UNIX timestamp of last checkpoint block
    1157185,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    2000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x0000022a3c4c98c850d22e5e3ec23e4ac3c927acd665e81f7444ed7d2ad5341b"))
    ;
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1545432546,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x00000372d06054846ee809edef9dd0e2c486c3c718b26d750ece21bc16f49adc"))
    ;
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1454124731,
    0,
    100};

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
        bnProofOfWorkLimit = ~uint256(0) >> 20; // VIP starting difficulty is 1 / 2^12  //20
        nSubsidyHalvingInterval = 210000;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // VIP: 1 day
        nTargetSpacing = 1 * 60;  // VIP: 1 minute
        nLastPOWBlock = 230;
        nMaturity = 10;
        nMasternodeCountDrift = 20;
		nMasternodeColleteralLimxDev = 4000; //Params().MasternodeColleteralLimxDev()
        nModifierUpdateBlock = 1; // we use the version 2 for dmd
        nMaxMoneyOut = 1000000 * COIN;
		strDeveloperFeePayee = "VTdRMLkJ9fZqg3RZT8xY7qDrW2p1hRH7Hx";

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


        vSeeds.push_back(CDNSSeedData("168.235.85.91:28181", "168.235.85.91:28181"));
        vSeeds.push_back(CDNSSeedData("185.52.3.182:28181", "185.52.3.182:28181"));
        vSeeds.push_back(CDNSSeedData("168.235.65.99:28181", "168.235.65.99:28181"));
        vSeeds.push_back(CDNSSeedData("168.235.65.84:28181", "168.235.65.84:28181"));
        vSeeds.push_back(CDNSSeedData("23.226.231.182:28181", "23.226.231.182:28181"));
        vSeeds.push_back(CDNSSeedData("107.161.24.202:28181", "107.161.24.202:28181"));
        vSeeds.push_back(CDNSSeedData("23.226.231.18:28181", "123.226.231.18:28181"));
        vSeeds.push_back(CDNSSeedData("168.235.103.52:28181", "168.235.103.52:28181"));
        vSeeds.push_back(CDNSSeedData("185.52.3.166:28181", "185.52.3.166:28181"));
        vSeeds.push_back(CDNSSeedData("185.52.3.126:28181", "185.52.3.126:28181"));
        vSeeds.push_back(CDNSSeedData("168.235.85.225:28181", "168.235.85.225:28181"));
        vSeeds.push_back(CDNSSeedData("168.235.85.173:28181", "168.235.85.173:28181"));
        vSeeds.push_back(CDNSSeedData("168.235.85.54:28181", "168.235.85.54:28181"));
        vSeeds.push_back(CDNSSeedData("168.235.96.66:28181", "168.235.96.66:28181"));
        vSeeds.push_back(CDNSSeedData("168.235.86.63:28181", "168.235.86.63:28181"));
	vSeeds.push_back(CDNSSeedData("40.76.88.70:28181", "40.76.88.70:28181"));
	vSeeds.push_back(CDNSSeedData("175.145.111.189:28181", "175.145.111.189:28181"));
	vSeeds.push_back(CDNSSeedData("167.114.152.3:28181", "167.114.152.3:28181"));
	vSeeds.push_back(CDNSSeedData("54.39.150.22:28181", "54.39.150.22:28181"));
	vSeeds.push_back(CDNSSeedData("192.99.212.38:28181", "192.99.212.38:28181"));
	vSeeds.push_back(CDNSSeedData("77.216.165.232:28181", "77.216.165.232:28181"));
	vSeeds.push_back(CDNSSeedData("37.0.171.247:28181", "37.0.171.247:28181"));
	vSeeds.push_back(CDNSSeedData("198.245.53.210:28181", "198.245.53.210:28181"));
	vSeeds.push_back(CDNSSeedData("115.178.235.250:28181", "115.178.235.250:28181"));
	vSeeds.push_back(CDNSSeedData("62.201.85.194:28181", "62.201.85.194:28181"));


        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 70); //Vip Start with V
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 106);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 56);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();
        // 	BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md 109 	0x8000006d
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x6d).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;


        nPoolMaxTransactions = 3;
        strSporkKey = "049e53e687fdafd78fd42d730fad0e7ea1819396176a2cb85d7a76fa4559cdbd2c2f05330a6f5cbadb44a6c1d324f167e679e9f3e95d9d5649761a3e7f59bf4500";
        strDarksendPoolDummyAddress = "VTdRMLkJ9fZqg3RZT8xY7qDrW2p1hRH7Hx";
        nStartMasternodePayments = 1510272000; //11/10/2017 @ 12:00am (UTC)
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
        nMaturity = 15;
        nModifierUpdateBlock = 51197; //approx Mon, 17 Apr 2017 04:00:00 GMT
        nMaxMoneyOut = 100000000 * COIN;

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1545432546;
        genesis.nNonce = 1952421;
        
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x0000022a3c4c98c850d22e5e3ec23e4ac3c927acd665e81f7444ed7d2ad5341b"));

        vFixedSeeds.clear();
        vSeeds.clear();
		
	    vSeeds.push_back(CDNSSeedData("185.52.3.126:28181", "185.52.3.126:28181"));
        vSeeds.push_back(CDNSSeedData("168.235.85.225:28181", "168.235.85.225:28181"));
        vSeeds.push_back(CDNSSeedData("168.235.85.173:28181", "168.235.85.173:28181"));
        vSeeds.push_back(CDNSSeedData("168.235.85.54:28181", "168.235.85.54:28181"));
        vSeeds.push_back(CDNSSeedData("168.235.96.66:28181", "168.235.96.66:28181"));
        vSeeds.push_back(CDNSSeedData("168.235.86.63:28181", "168.235.86.63:28181"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 83);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 18);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 193);
        // Testnet alqo BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet alqo BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet alqo BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));


        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;



        nPoolMaxTransactions = 2;
        strSporkKey = "049e53e687fdafd78fd42d730fad0e7ea1819396176a2cb85d7a76fa4559cdbd2c2f05330a6f5cbadb44a6c1d324f167e679e9f3e95d9d5649761a3e7f59bf4500";
        strDarksendPoolDummyAddress = "";
        nStartMasternodePayments = 1510272000;
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
        nTargetSpacing = 1 * 60;        // Vip: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1454124731;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 447568;
		
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 55700;
        assert(hashGenesisBlock == uint256("0x00000372d06054846ee809edef9dd0e2c486c3c718b26d750ece21bc16f49adc"));

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
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

        fRequireRPCPassword = false;
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
