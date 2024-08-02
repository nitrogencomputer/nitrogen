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

/* implement a forward reference for the class */
/* for usage inside the block struct construct */
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
    BlockTxDetails& operator=(const BlockTxDetails& other){
        this->receiver = other.receiver;
        this->sender = other.sender;
        this->tx_hash = other.tx_hash;
        return *this;
    }
};

std::ostream &operator<<(std::ostream &stream, const BlockTxDetails &blockTx)
{
    stream << std::setw(2) 
           << "sender:" 
           << blockTx.sender 
           << "sender balance:" 
           << blockTx.sender->balance 
           << "receiver:" 
           << blockTx.receiver 
           << "receiver balance:" 
           << blockTx.receiver->balance;
    return stream;
}

struct Blockstructure
{
    int block_id;
    steady_clock::time_point transaction_time;
    std::size_t tx_amount;
    std::string block_header;
    BlockTxDetails block_tx_details;
    Blockstructure& operator=(const Blockstructure& bs){}
};

struct Block
{
    std::size_t block_hash;
    Block *next_block_node;
    template<typename T>
    Block* create_new_block(BlockOps<T> &blockops);
};

template <typename T>
class BlockOps
{
private:
    std::forward_list<T> data;
    std::vector<T> blocks;
    std::vector<T> genesis;
    std::mutex block_mutex;
    bool validated;

public:
    Blockstructure blockstructure;
    std::string prev_hash;
    std::string curr_hash;  
    std::vector<std::string> transactions;

    BlockOps();
    BlockOps(const BlockOps &block);
    bool block_node_value_exists(Node *genesis_block, std::size_t balance);
    bool block_node_exists(Node *genesis_block, Node *target);
    Block* create_new_block(BlockOps<T> &blockops);
    BlockOps create_new_blockops(Blockstructure blockstructure);
    std::vector<std::string> create_new_transaction(Node *sender, Node *receiver, std::size_t transaction_amount);
    friend std::ostream &operator<<(std::ostream &stream, const BlockOps &blockops);
};
#endif