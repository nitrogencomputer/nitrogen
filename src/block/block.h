#include <iostream>
#include <memory>
#include <atomic>
#include <vector>
#include <string>
#include <mutex>
#include <cstddef>
#include <iomanip>
#include <forward_list>

typedef struct Node
{
    std::size_t balance;
    Node *preceding_node;
} Node;

typedef struct BlockTxDetails
{
    Node *sender;
    Node *receiver;
    std::string tx_hash;
} BlockTxDetails;

std::ostream &operator<<(std::ostream &stream, const BlockTxDetails &blockTx)
{
    stream << std::setw(2) << "sender:" << blockTx.sender << "sender balance:" << blockTx.sender->balance << "receiver:" << blockTx.receiver << "receiver balance:" << blockTx.receiver->balance;
    return stream;
}

typedef struct Blockstructure
{
    int block_id;
    time_t transaction_time;
    std::size_t tx_amount;
    std::string block_header;
    BlockTxDetails block_tx_details;
} Blockstructure;

typedef struct Block
{
    std::size_t block_hash;
    Block *next_block_node;
} Block;

template <typename T>
class BlockOps
{
private:
    Blockstructure blockstructure;
    std::string prev_hash;
    std::string curr_hash;
    std::vector<std::string> transactions;

    std::forward_list<T> data;
    std::vector<T> blocks;
    std::vector<T> genesis;
    std::mutex block_mutex;

public:
    BlockOps();
    BlockOps(const BlockOps &block);
    bool block_node_value_exists(Node *genesis_block, std::size_t balance);
    bool block_node_exists(Node *genesis_block, Node *target);
    Block* create_new_block(BlockOps<T> &blockops);
    BlockOps create_new_blockops(Blockstructure blockstructure);
    std::vector<std::string> create_new_transaction(Node *sender, Node *receiver, std::size_t transaction_amount);
    friend std::ostream &operator<<(std::ostream &stream, const BlockOps &blockops);
};
