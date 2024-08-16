#include "blockchain.hpp"
#include <algorithm>

using namespace nitrogenx;

void nitrogen_error_stack(const char *msg);

template <typename T>
std::vector<Block<T>*> blockchain(std::vector<Block<T>*> block)
{
    std::vector<Block<T>*> blockd;
    for (size_t i = 0; i < block.size(); ++i)
    {
        Block<T>* current = block[i];
        while (current != nullptr)
        {
            blockd.push_back(current);
            current = current->next_block_node;
        }
    }
    return blockd;
}
template <typename T>
std::vector<Block<T>*>  remove_block(std::vector<Block<T> *> blockchain, std::size_t hash)
{
    typename std::vector<Block<T>*>::iterator it = std::find(blockchain.begin(), blockchain.end(), hash);
    if(it != blockchain.end())
        blockchain.erase(it);
    for(int i = 0; i < blockchain.size(); ++i)
        std::cout << blockchain[i] << std::endl;
    return blockchain;
}

template <typename T>
std::vector<T> Blockchain<T>::new_block(BlockOps<Blockstructure> &blockops)
{
    Block<T> *new_block_node = new Block<T>();
    if (blockops.blockstructure.block_header == "genesis")
        nitrogen_error_stack("genesis block already exists");

    for (int i = 0; i < new_block_node->transactions.size(); ++i)
    {
        blockops.curr_hash = new_block_node->transactions[i] +
                             blockops.blockstructure.block_header;
    }

    new_block_node->block_hash = std::stoul(blockops.curr_hash);
    new_block_node->next_block_node = nullptr;

    Block<T> *second_layer_block = new Block<T>();
    second_layer_block->block_hash = std::stoul(blockops.curr_hash);
    new_block_node->next_block_node->next_block_node = second_layer_block;
    return new_block_node;
}

void nitrogen_error_stack(const char *msg)
{
    perror(msg);
    exit(1);
}
