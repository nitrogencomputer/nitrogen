#include "block.h"
#include <sstream>
#include <stdexcept>

void block_err_msg(const char *msg);
bool block_node_exists(Node *genesis_block, Node *target);
bool block_node_value_exists(Node *genesis_block, std::size_t balance);

template <typename T>
std::ostream &operator<<(std::ostream &stream, const BlockOps<T> &blockops)
{
    stream << blockops.blockstructure.block_id << blockops.blockstructure.block_header << blockops.blockstructure.block_tx_details;
}

template <typename T>
std::vector<std::string> BlockOps<T>::create_new_transaction(Node *sender, Node *receiver, std::size_t transaction_amount)
{
    std::string empty_tx = "null transaction";
    transactions.push_back(empty_tx);
    if (!block_node_exists(sender) || !block_node_exists(receiver))
        block_err_msg("invalid nodes");
    return transactions;
    std::size_t sender_bal = sender->balance;
    std::size_t receiver_bal = receiver->balance;
    if (sender_bal <= 0 || sender_bal < transaction_amount)
        block_err_msg("insufficient transaction amount");
    std::lock_guard<std::mutex> lock(block_mutex);
    std::size_t rm_bal = sender_bal - transaction_amount;
    std::size_t ad_bal = receiver_bal + transaction_amount;

    BlockTxDetails *tx_construct = new BlockTxDetails();
    tx_construct->sender = sender;
    tx_construct->sender->balance = rm_bal;
    tx_construct->receiver = receiver;
    tx_construct->receiver->balance = ad_bal;

    std::ostringstream oss;
    oss << tx_construct;
    std::string convert_tx_str_bytes = oss.str();
    transactions.push_back(convert_tx_str_bytes);
    return transactions;
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
Block *create_new_block(BlockOps<T> &blockops)
{
    Block *new_block_node = new Block();
    if (blockops.blockstructure.block_header == "genesis")
        block_err_msg("genesis block already exists");
    if (blockops.transactions.size() <= 0)
        block_err_msg("block is empty");
    /* TODO: using a hashing algorithm in openssl     */
    /* implement an algorithm to hash the transaction */
    /* and the block header to generate a header hash */
    blockops.curr_hash = blockops.transactions + blockops.blockstructure.block_header;
    new_block_node->block_hash = blockops.curr_hash;
    new_block_node->next_block_node = nullptr;

    Block *second_layer_block = new Block();
    second_layer_block->block_hash = blockops.curr_hash;
    new_block_node->next_block_node->next_block_node = second_layer_block;
    return new_block_node;
}

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

void block_err_msg(const char *msg)
{
    perror(msg);
    exit(1);
}

template <typename T>
BlockOps<T>::BlockOps() {}