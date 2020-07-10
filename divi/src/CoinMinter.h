#ifndef COIN_MINTER_H
#define COIN_MINTER_H
#include <stdint.h>
#include <memory>
#include <vector>
#include <map>

#include <I_CoinMinter.h>

class CWallet;
class CChain;
class CChainParams;
class PeerNotificationOfMintService;
class CNode;
class CMasternodeSync;
class CReserveKey;
typedef std::map<unsigned int, unsigned int> HashedBlockMap;
class CBlock;
class CBlockIndex;
class CBlockHeader;
class I_BlockFactory;
class CBlockTemplate;

class CoinMinter: public I_CoinMinter
{
    bool mintingIsRequested_;
    CWallet* pwallet_;
    CChain& chain_;
    const CChainParams& chainParameters_;
    std::shared_ptr<I_BlockFactory> blockFactory_;
    std::shared_ptr<PeerNotificationOfMintService> peerNotifier_;
    CMasternodeSync& masternodeSync_;
    HashedBlockMap& mapHashedBlocks_;
    bool haveMintableCoins_;
    int64_t lastTimeCheckedMintable_;
    int64_t timeToWait_;
    static const int64_t constexpr fiveMinutes_ = 5 * 60;

    bool hasMintableCoinForProofOfStake();
    bool satisfiesMintingRequirements() const;
    bool limitStakingSpeed() const;
    bool isAtProofOfStakeHeight() const;

    bool ProcessBlockFound(CBlock* block, CReserveKey& reservekey) const;
    void IncrementExtraNonce(CBlock* block, CBlockIndex* pindexPrev, unsigned int& nExtraNonce) const;
    void UpdateTime(CBlockHeader* block, const CBlockIndex* pindexPrev) const;

    void SetBlockHeaders(
        std::unique_ptr<CBlockTemplate>& pblocktemplate, 
        const bool& proofOfStake) const;
    void SetCoinBaseTransaction (
        std::unique_ptr<CBlockTemplate>& pblocktemplate,
        const bool& fProofOfStake) const;

    bool createProofOfStakeBlock(
        unsigned int nExtraNonce, 
        CReserveKey& reserveKey, 
        bool fProofOfStake) const;
    bool createProofOfWorkBlock(
        unsigned int nExtraNonce, 
        CReserveKey& reserveKey, 
        bool fProofOfStake) const;

public:
    CoinMinter(
        CWallet* pwallet,
        CChain& chain,
        const CChainParams& chainParameters,
        std::vector<CNode*>& peers,
        CMasternodeSync& masternodeSynchronization,
        HashedBlockMap& mapHashedBlocks);

    virtual bool CanMintCoins();
    virtual void sleep(uint64_t milliseconds) const;
    virtual void setMintingRequestStatus(bool newStatus);
    virtual bool mintingHasBeenRequested() const;

    virtual bool createNewBlock(
        unsigned int nExtraNonce, 
        CReserveKey& reserveKey, 
        bool fProofOfStake) const;
};

#endif // COIN_MINTER_H