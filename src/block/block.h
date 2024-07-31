#include <iostream>
#include <memory>
#include <atomic>
#include <vector>
#include <string>
#include <mutex>
#include <cstddef>
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
    std::string nonce;
    std::string curr_hash;
    std::vector<std::string> transactions;

    std::forward_list<T> data;
    std::vector<T> blocks;
    std::vector<T> genesis;
    std::mutex block_mutex;

public:
    BlockOps();
    BlockOps(const BlockOps &block);
    
    Node* create_new_block(BlockOps& blockops);
    bool block_node_value_exists(Node* genesis_block, std::size_t balance);
    bool block_node_exists(Node* genesis_block, Node* target);

    BlockOps create_new_blockops(Blockstructure blockstructure);
    BlockOps create_new_transaction(Node* sender, Node* receiver, std::size_t transaction_amount);
   
    friend std::ostream &operator<<(std::ostream &stream, const BlockOps &blockops)
    {
        stream << blockops.blockstructure.block_id << blockops.blockstructure.block_header << blockops.blockstructure.block_tx_details;
    }
    char &operator[](unsigned int index)
    {
        return blocks[index];
    }
};
