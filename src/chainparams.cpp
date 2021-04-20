// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2018-2021 The Vip developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "libzerocoin/Params.h"
#include "chainparams.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"
#include <assert.h>
#include <boost/assign/list_of.hpp>
#include <stdio.h>

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
    (0, uint256("0x00000b586fcc1602de66f9a2733d0ba9fda25002eaf8f941a15569182c6e6cee"))
    (8, uint256("0x0000004cd8e124bd3281cc348daef1d64044e9fde653686980e7036f3da55b7e"))
    ;

    
static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1548447987,
    285737,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    500        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of
    (0, uint256("0x00000f9a2581ddf4d8dcccee1260d389d7890b15cf367a5281d18389352159dd"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
     1535535865,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of
    (0, uint256("0x0000089feee47328787e5d7aee4028467723af5db97ee7a87de118020482876d"));	
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1535536258,
    0,
    100};

libzerocoin::ZerocoinParams* CChainParams::Zerocoin_Params() const
{
    assert(this);
    static CBigNum bnTrustedModulus(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParams = libzerocoin::ZerocoinParams(bnTrustedModulus);

    return &ZCParams;
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
        pchMessageStart[0] = 0xce;
        pchMessageStart[1] = 0xde;
        pchMessageStart[2] = 0xfa;
        pchMessageStart[3] = 0xf1;
        vAlertPubKey = ParseHex("0472258635716F4057D5EE35D4E831EED6A23D477E5ABEBAF30BCE5309A2905741BD69EBA5BBE5C8245ECA0D964C591419CBDE2B7153E2B417E8231D16BA61B55D0472258635716F4057D5EE35D4E831EED6A23D477E5ABEBAF30BCE5309A2905741BD69EBA5BBE5C8245ECA0D964C591419CBDE2B7153E2B417E8231D16BA61B55D");
        nDefaultPort = 11945;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // Vip starting difficulty is 1 / 2^12
        nSubsidyHalvingInterval = 350400;   // halving every year ~ 350400 blocks
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 60 * 60; // Vip: 1 hour
        nTargetSpacing = 60;  // Vip: 60 seconds
        nMaturity = 60;  
        nMasternodeCollateral = 10000; // 10000 VIP
        nMasternodeCountDrift = 20;
        nMaxMoneyOut =  1000000 * COIN; //60M VIP
        nSwiftTxMinFee = 0.01 * COIN;   

        /** Height or Time Based Activations **/
        //nPresaleStartBlock = 9000; // Presale Start
        //nPresaleEndBlock = 15000; // Presale End 15000 
        
        nLastPOWBlock = 950000; // POW ends at block 13000
        nBlockEnforceSerialRange = 1; //Enforce serial range starting this block
        nBlockRecalculateAccumulators = -1; //Trigger a recalculation of accumulators
        nBlockFirstFraudulent = -1; //First block that bad serials emerged
        nBlockLastGoodCheckpoint = 0; //Last valid accumulator checkpoint
        nBlockEnforceInvalidUTXO = 1; //Start enforcing the invalid UTXO's

        /** Information for generating Genesis Block**/
        const char* pszTimestamp = "Bitcoin price near to 1,067.00 - 17/Apr/2021";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 504365040 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 100 * COIN; // initial reward for genesis block
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04c84e4324beaccb35ee195c4a09c4a83c1c4592766521adae08b466f29432fc23e867dda7a601b92a5ac785079eab8c2f3dabe18c207adf41d80da902c8e8d7f5") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
	    genesis.nTime = 1618668565;
        genesis.nBits = 0x1e0ffff0;
	    genesis.nNonce = 4224990;
	
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00000b586fcc1602de66f9a2733d0ba9fda25002eaf8f941a15569182c6e6cee"));
	    assert(genesis.hashMerkleRoot == uint256("0x09198a17d2a502316eccbd55b8f2f995f63db8dc2d6d7ffa02d2be63e9ef6b57"));
	    
    
        // Zerocoin, disabled
        nZerocoinStartHeight = 2147483647; // Tuesday, January 19, 2038 3:14:07 AM
        nZerocoinStartTime = 2147483647; // Tuesday, January 19, 2038 3:14:07 AM

        // DNS Seeders maintaining a dynamic list of active nodes
        vSeeds.push_back(CDNSSeedData("vipcore.vip", "seed.vipcore.vip"));      // Primary DNS Seeder, need to have a domain name
        vSeeds.push_back(CDNSSeedData("95.216.112.67:11945", "95.216.112.67"));
        vSeeds.push_back(CDNSSeedData("155.138.162.108", "155.138.162.108"));
        vSeeds.push_back(CDNSSeedData("46.151.159.53", "46.151.159.53"));
        vSeeds.push_back(CDNSSeedData("82.169.168.31", "82.169.168.31"));
        vSeeds.push_back(CDNSSeedData("95.216.118.219", "95.216.118.219"));
        vSeeds.push_back(CDNSSeedData("116.202.172.79", "116.202.172.79"));
 
        // Base58prefixes Information:  https://en.bitcoin.it/wiki/List_of_address_prefixes      
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 58);   
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 14);    
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 144);      
        
        // BIP32 format: 0x0420BD3A for spub and 0x0420B900 for sprv        
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x20)(0xBD)(0x3A).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x20)(0xB9)(0x00).convert_to_container<std::vector<unsigned char> >();

        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x19)(0x89).convert_to_container<std::vector<unsigned char> >();

        // Hardcoded seed node generated in chainparamsseeds.h
        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = true;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "03738a07dfc3f2fdaf431e71ce939fed9c579cc17adc722e910e3b1fe1c2b1cd5a";
        strObfuscationPoolDummyAddress = "QVoXZT7RSwtPcyEKqT4Lhgj8RNhgg4zfFm";
        nStartMasternodePayments = genesis.nTime + 60 * 60; // 1 hr after genesis 

        /** Zerocoin */
        // See https://github.com/Zerocoin/libzerocoin/wiki/Generating-Zerocoin-parameters
        // http://zerocoin.org/media/pdf/ZerocoinOakland.pdf
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
        pchMessageStart[0] = 0x6e;
        pchMessageStart[1] = 0x1f;
        pchMessageStart[2] = 0x8a;
        pchMessageStart[3] = 0xc8;
        vAlertPubKey = ParseHex("04d9baf06665c63c3afb5a79ceb6818e3003b42abbcd649c454df6919fd60efbf5e9d18e1020d1559c25c48f031ece9ad69e9ec980f66c663ab912104c146792e5");
        nDefaultPort = 11942;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 60 * 60; // Vip: 1 hour
        nTargetSpacing = 90;  // Vip: 90 seconds
        nLastPOWBlock = 1000;  
        nMaturity = 10;  
        nMasternodeCountDrift = 4;
        //nModifierUpdateBlock = 0; // Vip TBD
        nMaxMoneyOut =  60000000 * COIN; // Vip maxcap 60M
        
        //! Modify the testnet genesis block so the timestamp is valid for a later start.
	    genesis.nTime = 1618673884;
        genesis.nBits = 0x1e0ffff0;
	    genesis.nNonce = 1896879;

        
        hashGenesisBlock = genesis.GetHash();
  	    assert(hashGenesisBlock == uint256("0x00000f9a2581ddf4d8dcccee1260d389d7890b15cf367a5281d18389352159dd"));      
        
        // Zerocoin, disabled by default
        nZerocoinStartHeight = 2147483647; // Tuesday, January 19, 2038 3:14:07 AM
        nZerocoinStartTime = 2147483647;  //Tuesday, January 19, 2038 3:14:07 AM

        vFixedSeeds.clear();
        vSeeds.clear();
        
        // Add seeder node information here
        vSeeds.push_back(CDNSSeedData("vipcore.vip", "seed.vipcore.vip"));      // Primary DNS Seeder, need to have a domain name
        vSeeds.push_back(CDNSSeedData("51.15.127.79", "51.15.127.79"));
        vSeeds.push_back(CDNSSeedData("51.15.98.254", "51.15.98.254"));
        vSeeds.push_back(CDNSSeedData("51.15.37.133", "51.15.37.133"));      
        vSeeds.push_back(CDNSSeedData("51.15.96.177", "51.15.96.177"));
        vSeeds.push_back(CDNSSeedData("51.15.112.87", "51.15.112.87"));
        
        // base58Prefixes information 
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 125);    
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 112);    
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 253);       
        
        // 0x0420BD3A for spub and 0x0420B900 for sprv        
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x20)(0xBD)(0x3A).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x20)(0xB9)(0x00).convert_to_container<std::vector<unsigned char> >();
        
        // Testnet vip BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "04bff6b362b7a4bc8f7cbbe2c0666166fded0cd531d0390bcc6e32e42a059a29b5bb3c034a652fbf6d1dfe9f5dabad16fc0a5696eb18167821d35195b78ced58df";
        strObfuscationPoolDummyAddress = "SffPqR2Dd8Bs1kjXJPmDxDV1aiTNHAeVN2";
        nStartMasternodePayments = genesis.nTime + 3600; // 1 hr after genesis
        nBudget_Fee_Confirmations = 3; // Number of confirmations for the finalization fee. 
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
        pchMessageStart[0] = 0x6e;
        pchMessageStart[1] = 0x1f;
        pchMessageStart[2] = 0x8a;
        pchMessageStart[3] = 0xc7;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 60 * 60; // Vip: 1 hour
        nTargetSpacing = 90;        // Vip: 90 seconds
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        
	    genesis.nTime = 1618674359;
        genesis.nBits = 0x1e0ffff0;
	    genesis.nNonce = 1944030;
     
        hashGenesisBlock = genesis.GetHash();
  	    assert(hashGenesisBlock == uint256("0x0000089feee47328787e5d7aee4028467723af5db97ee7a87de118020482876d"));      
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
        nDefaultPort = 18993;
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
