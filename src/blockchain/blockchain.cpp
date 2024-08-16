#include "blockchain.hpp"
#include "../block/block.hpp"
#include <algorithm>

using namespace nitrogenx;

void nitrogen_error_stack(const char *msg);
template <typename T>
std::vector<T> blockchain(std::vector<Block *> block)
{
    std::vector<T> blockd;
    std::vector<Block *>::iterator bitr;
    for (int i = 0; i < block.size(); ++i)
    {
        while (block[i] != nullptr)
            blockd.push_back(block[i]);
        block[i] = block[i]->next_block_node;
    }
    return blockd;
}

template <typename T>
std::vector<T> remove_block(std::vector<Block *> blockchain, std::size_t hash)
{
    std::vector<Block*>::iterator it = std::find(blockchain.begin(), blockchain.end(), hash);
    if(it != blockchain.end())
        blockchain.erase(it);
    for(int i = 0; i < blockchain.size(); ++i)
        std::cout << blockchain[i] << std::endl;
    return blockchain;
}

template <typename T>
std::vector<T> Blockchain<T>::new_block(BlockOps<Blockstructure> &blockops)
{
    Block *new_block_node = new Block();
    if (blockops.blockstructure.block_header == "genesis")
        nitrogen_error_stack("genesis block already exists");

    for (int i = 0; i < blockops.transactions.size(); ++i)
    {
        blockops.curr_hash = blockops.transactions[i] +
                             blockops.blockstructure.block_header;
    }

    new_block_node->block_hash = std::stoul(blockops.curr_hash);
    new_block_node->next_block_node = nullptr;

    Block *second_layer_block = new Block();
    second_layer_block->block_hash = std::stoul(blockops.curr_hash);
    new_block_node->next_block_node->next_block_node = second_layer_block;
    return new_block_node;
}

void nitrogen_error_stack(const char *msg)
{
    perror(msg);
    exit(1);
}

template <typename T>
std::ostream& operator<<(std::ostream& stream, const Block& blockc)
{
    stream << blockc.block_hash 
           << blockc.next_block_node;
}