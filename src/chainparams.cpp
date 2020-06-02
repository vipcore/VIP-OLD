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
    (0, uint256("0x000004589d9a041118abe6aaf5c22ff30d5f1bca5835ad39d8fe35e88b95afc9"))
    (10, uint256("0x00000c3c85dd4e5e6f87c7a33a3fce93e286585cd165d98a91a66268fa4b62f4"))
    (20, uint256("0x0000088efcdefd3010db9e96af95709ba88cf982135f62e35d8350f0b7f3f6ad"))
    (30, uint256("0x0000050bd2243fc32ab07cfacd6427e5ba7cb4bcac78575f67f8b70f73b03cab"))
    ;
static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1588909447, // * UNIX timestamp of last checkpoint block
    1157185,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    2000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x000001c99ad9325fd6a1ab85127706c188cbf625f999cf8a182265e8810188b2"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1588563847,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x00000ff05aa1f65b42cb37fd1808f9ee1aef03552d59b72f542558f8ded9723c"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1588563847,
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
        pchMessageStart[0] = 0x93;
        pchMessageStart[1] = 0x05;
        pchMessageStart[2] = 0x17;
        pchMessageStart[3] = 0x19;
        vAlertPubKey = ParseHex("0497dfcea626dca270cfe2eebf1160733b07352af966926e30058ca53dae05bbc71d64dbaa0c66e373211e324a23b361fc33e1e2dece1fb90afcefc707643a28f5");
        nDefaultPort = 28181;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // VIP starting difficulty is 1 / 2^12  //20
        nSubsidyHalvingInterval = 210000;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // VIP: 1 day
        nTargetSpacing = 2 * 60;  // VIP: 2 minute
        nLastPOWBlock = 250;
        nMaturity = 20;
        nMasternodeCountDrift = 20;
        nMasternodeColleteral = 4000; //Collateral Amount
        nModifierUpdateBlock = 1; // we use the version 2 for dmd
        nMaxMoneyOut = 1000000 * COIN;
        strDeveloperFeePayee = "WckWBhY8UUHepdh9e9qpGvQCJmg5xZrBVa";

        const char* pszTimestamp = "Corona Virus outbreak, Seems to be scary - 10/May/2020";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 0 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("040fbf75ea45bf7eb65f9075e8342b7520d077b66f964e9b1963c96cefd9a2c52e93d0def918e0cd3c91f42821f429b2be4505552dede31c96f95f0d843da0beae") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1588909447;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 1859864;
        
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x000004589d9a041118abe6aaf5c22ff30d5f1bca5835ad39d8fe35e88b95afc9"));
        assert(genesis.hashMerkleRoot == uint256("0x8b7c3f00d6c414dce8892df35a72053ecbaa9fb99211451b370693e31290de09"));


        vSeeds.push_back(CDNSSeedData("85.25.138.64", "85.25.138.64"));
        vSeeds.push_back(CDNSSeedData("85.25.251.198", "85.25.251.198"));
        vSeeds.push_back(CDNSSeedData("85.25.251.199", "85.25.251.199"));
        
        vSeeds.push_back(CDNSSeedData("80.209.227.9", "80.209.227.9"));
        vSeeds.push_back(CDNSSeedData("80.209.228.190", "80.209.228.190"));
        vSeeds.push_back(CDNSSeedData("80.209.228.191", "80.209.228.191"));
        vSeeds.push_back(CDNSSeedData("80.209.228.192", "80.209.228.192"));
        vSeeds.push_back(CDNSSeedData("80.209.228.193", "80.209.228.193"));
        vSeeds.push_back(CDNSSeedData("80.209.228.189", "80.209.228.189"));
        vSeeds.push_back(CDNSSeedData("80.209.228.194", "80.209.228.194"));
        vSeeds.push_back(CDNSSeedData("80.209.228.197", "80.209.228.197"));
        vSeeds.push_back(CDNSSeedData("80.209.228.196", "80.209.228.196"));
        vSeeds.push_back(CDNSSeedData("80.209.228.195", "80.209.228.195"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 73);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 34);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 17);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();
        //  BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md 109   0x8000006d
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
        nEnforceNewSporkKey = 1566748666; //!> Sporks signed after 08/25/2019 @ 3:57pm (UTC) must use the new spork key
        nRejectOldSporkKey = 1568073600;  //!> Fully reject old spork key after 09/10/2019 @ 12:00am (UTC)
        strSporkKey = "02be3fd03929233a4926a13d405d2a8cf5a1bc5572fdb80316f6d380a7cc988dfc";
        strSporkKeyOld = "049e53e687fdafd78fd42d730fad0e7ea1819396176a2cb85d7a76fa4559cdbd2c2f05330a6f5cbadb44a6c1d324f167e679e9f3e95d9d5649761a3e7f59bf4500";
        strDarksendPoolDummyAddress = "VBkHCDZSf3znuDPtZJck6dmSXhPzzAzF5E";
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
        nDefaultPort = 55600;
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
        genesis.nTime = 1588563847;
        genesis.nNonce = 2352558;
        
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x000001c99ad9325fd6a1ab85127706c188cbf625f999cf8a182265e8810188b2"));

        vFixedSeeds.clear();
        vSeeds.clear();
        
        vSeeds.push_back(CDNSSeedData("85.25.138.64", "85.25.138.64"));
        vSeeds.push_back(CDNSSeedData("85.25.251.198", "85.25.251.198"));
        vSeeds.push_back(CDNSSeedData("85.25.251.199", "85.25.251.199"));
        
        vSeeds.push_back(CDNSSeedData("80.209.227.9", "80.209.227.9"));
        vSeeds.push_back(CDNSSeedData("80.209.228.190", "80.209.228.190"));
        vSeeds.push_back(CDNSSeedData("80.209.228.191", "80.209.228.191"));
        vSeeds.push_back(CDNSSeedData("80.209.228.192", "80.209.228.192"));
        vSeeds.push_back(CDNSSeedData("80.209.228.193", "80.209.228.193"));
        vSeeds.push_back(CDNSSeedData("80.209.228.189", "80.209.228.189"));
        vSeeds.push_back(CDNSSeedData("80.209.228.194", "80.209.228.194"));
        vSeeds.push_back(CDNSSeedData("80.209.228.197", "80.209.228.197"));
        vSeeds.push_back(CDNSSeedData("80.209.228.196", "80.209.228.196"));
        vSeeds.push_back(CDNSSeedData("80.209.228.195", "80.209.228.195"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 83);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 18);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 193);
        // Testnet vip BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet vip BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet vip BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));


        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;



        nPoolMaxTransactions = 3;
        nEnforceNewSporkKey = 1566748666; //!> Sporks signed after 08/25/2019 @ 3:57pm (UTC) must use the new spork key
        nRejectOldSporkKey = 1568073600;  //!> Fully reject old spork key after 09/10/2019 @ 12:00am (UTC)
        strSporkKey = "02b233adf70ac36e778015ae2eb8cf7d9092183c3334e98fad0e2aea5723ef271d";
        strSporkKeyOld = "049e53e687fdafd78fd42d730fad0e7ea1819396176a2cb85d7a76fa4559cdbd2c2f05330a6f5cbadb44a6c1d324f167e679e9f3e95d9d5649761a3e7f59bf4500";
        strDarksendPoolDummyAddress = "VBkHCDZSf3znuDPtZJck6dmSXhPzzAzF5E";
        nStartMasternodePayments = 1510272000; //11/10/2017 @ 12:00am (UTC)
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
        genesis.nTime = 1588304647;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 845604;
        
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 55700;
        assert(hashGenesisBlock == uint256("0x00000ff05aa1f65b42cb37fd1808f9ee1aef03552d59b72f542558f8ded9723c"));

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
