#include "block.h"
#include <stdexcept>

template <typename T>
BlockOps<T>::BlockOps() {}

template <typename T>
bool block_node_value_exists(Node *genesis_block, std::size_t balance)
{
    if (genesis_block->balance <= 0 && genesis_block->preceding_node == nullptr)
        return false;
    Node *current = genesis_block;
    while (current != nullptr)
        if (current->balance == balance)
            return true;
    current = current->preceding_node;
    return false;
}

template <typename T>
bool block_node_exists(Node *genesis_block, Node *target)
{
    Node *current = genesis_block;
    while (current != nullptr)
        if (current == target)
            return true;
    current = current->preceding_node;
    return false;
}

template <typename T>
BlockOps<T> BlockOps<T>::create_new_transaction(Node *sender, Node *receiver, std::size_t transaction_amount)
{
}

template <typename T>
BlockOps<T> BlockOps<T>::create_new_blockops(Blockstructure bs)
{
    BlockOps *new_block_ops = new BlockOps();
    std::forward_list<Blockstructure> new_block_store;

    if (bs.tx_amount <= 0 || bs.block_tx_details.sender == nullptr || bs.block_tx_details.receiver == nullptr)
        throw std::runtime_error("invalid transaction");

    Blockstructure block_structure;
    block_structure.block_id = bs.block_id;
    block_structure.tx_amount = bs.tx_amount;
    block_structure.transaction_time = bs.transaction_time;
    block_structure.block_header = bs.block_header;
    block_structure.block_tx_details = bs.block_tx_details;

    if (block_structure.block_tx_details.tx_hash.empty())
        throw std::runtime_error("no transaction hash");
    if (block_structure.block_tx_details.sender->balance <= 0)
        throw std::runtime_error("zero or negative balance");
    if (block_structure.block_tx_details.sender->balance >= 100)
        throw std::runtime_error("balance manipulation");

    new_block_store.push_front(block_structure);
    new_block_ops->data = new_block_store;
    free(new_block_ops);
    return new_block_ops;
}

template <typename T> 
Node* create_new_block(BlockOps<T>& blockops)
{
    Node* new_block_node = new Node();
    
}
