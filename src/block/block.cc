#include "block.h"
#include <stdexcept>

template<typename T>
BlockOps<T>::BlockOps(){}

template<typename T>
std::string BlockOps<T>::create_block_header(int block_id, time_t transaction_time, std::size_t tx_amount){}

template<typename T>
BlockOps<T> BlockOps<T>::create_new_block(Blockstructure bs){
    BlockOps* new_block_ops = new BlockOps();
    std::forward_list<Blockstructure> new_block_store;

    if(bs.tx_amount <= 0 
        || bs.block_tx_details.sender == nullptr
        || bs.block_tx_details.receiver == nullptr) 
        throw std::runtime_error("invalid transaction");

    Blockstructure block_structure;
    block_structure.block_id = bs.block_id;
    block_structure.tx_amount = bs.tx_amount;
    block_structure.transaction_time = bs.transaction_time;
    block_structure.block_header = bs.block_header;
    block_structure.block_tx_details = bs.block_tx_details;

    if(block_structure.block_tx_details.tx_hash.empty())
        throw std::runtime_error("no transaction hash");
    if(block_structure.block_tx_details.sender->balance <= 0 )
        throw std::runtime_error("zero or negative balance");
    if(block_structure.block_tx_details.sender->balance >= 100)
        throw std::runtime_error("balance manipulation");
    
    new_block_store.push_front(block_structure);
    new_block_ops->data = new_block_store;
    free(new_block_ops);
    return new_block_ops;
}
