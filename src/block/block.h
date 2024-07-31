#include <iostream>
#include <memory>
#include <atomic>
#include <vector> 
#include <string>
#include <mutex>
#include <cstddef>
#include <forward_list>

typedef struct Node {
    std::size_t balance;
    Node* preceding_node;
}Node;

typedef struct BlockTxDetails {
    Node* sender;
    Node* receiver;
    std::string tx_hash;
}BlockTxDetails;

typedef struct Blockstructure {
    int block_id;
    time_t transaction_time;
    std::size_t tx_amount;
    std::string block_header;
    BlockTxDetails block_tx_details;
}Blockstructure;

typedef struct Block{
    std::size_t block_hash;
    Block* next_block_node;
}Block;

template<typename T> 
class BlockOps{
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
    BlockOps(const BlockOps& block);
    std::string create_block_header(int block_id, time_t transaction_time, std::size_t tx_amount);
    BlockOps create_new_block(Blockstructure blockstructure);
    friend std::ostream& operator<<(std::ostream& stream, const BlockOps& block);
    friend std::istream& operator>>(std::istream& stream, const BlockOps& block);
    char& operator[](unsigned int index){return blocks[index];}
};
