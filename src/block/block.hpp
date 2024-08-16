#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
#include <memory>
#include <atomic>
#include <vector>
#include <string>
#include <mutex>
#include <cstddef>
#include <iomanip>
#include <forward_list>
#include <chrono>

using namespace std::chrono;

template <typename T>
class BlockOps;
struct Node
{
    std::size_t balance;
    Node *preceding_node;
};

struct BlockTxDetails
{
    Node *sender;
    Node *receiver;
    std::string tx_hash;
    BlockTxDetails &operator=(const BlockTxDetails &other)
    {
        this->receiver = other.receiver;
        this->sender = other.sender;
        this->tx_hash = other.tx_hash;
        return *this;
    }
};

struct Blockstructure
{
    int block_id;
    steady_clock::time_point transaction_time;
    std::size_t tx_amount;
    std::string block_header;
    BlockTxDetails *block_tx_details;
};

template <typename T>
class Block
{
public:
    std::size_t block_hash;
    Block *next_block_node;
    std::vector<std::string> transactions;
    Block *create_new_block(BlockOps<T>* blockops);
    std::vector<std::string> create_new_transaction(Node *sender, Node *receiver, std::size_t transaction_amount);
    inline std::ostream &operator<<(std::ostream &os)
    {
        os << "Block Hash: " << this->block_hash;
        return os;
    }
};

template <typename T>
class BlockOps
{
private:
    std::forward_list<T> data;
    std::vector<T> blocks;
    std::vector<T> genesis;
    bool validated;

public:
    Blockstructure blockstructure;
    std::string prev_hash;
    std::string curr_hash;

    BlockOps();
    BlockOps(const BlockOps &block);
    bool block_node_value_exists(Node *genesis_block, std::size_t balance);
    bool block_node_exists(Node *genesis_block, Node *target);
    BlockOps create_new_blockops(Blockstructure *blockstructure);
    inline friend std::ostream &operator<<(std::ostream &stream, const BlockOps &blockops);
};
#endif