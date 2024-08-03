#include "blockchain.hpp"
#include "../block/block.hpp"
#include <algorithm>

using namespace nitrogenx;

void nitrogen_error_stack(const char *msg);
template <typename T>
std::vector<T> blockchain(std::vector<Block *> block)
{
    /* Lookup to see if the block head is empty */
    /* mem allocate sample blocks to block head */
    std::vector<T> blockd;
    std::vector<Block *>::iterator bitr;
    /* check if the lookup vcblock is not a nullptr */
    /* also check to see that its not a dangling pointer*/
    for (int i = 0; i < block.size(); ++i)
    {
        /* provided the loop does not see a nullptr block */
        /* blocks should be added until the end where the */
        /* next block node is a nullptr then end the loop */
        while (block[i] != nullptr)
            blockd.push_back(block[i]);
        block[i] = block[i]->next_block_node;
    }
    return blockd;
}

template <typename T>
std::vector<T> remove_block(std::vector<Block *> blockchain, std::size_t hash)
{
    /* using a vector iterator traverse the items */
    /* existing in the blockchain to get b[i] data */
    std::vector<Block*>::iterator it = std::find(blockchain.begin(), blockchain.end(), hash);
    if(it != blockchain.end())
    /* if the hash passed in the function matches */
    /* any of the blocks when looped then remove  */
        blockchain.erase(it);
    /* print out the blockchain data after removal */
    /* to verify that the blockchain removal worked */
    for(int i = 0; i < blockchain.size(); ++i)
        std::cout << blockchain[i] << std::endl;
    return blockchain;
}

/* handles the creation of a new block from */
/* pre existing block operation data initiated */
template <typename T>
std::vector<T> Blockchain<T>::new_block(BlockOps<Blockstructure> &blockops)
{
    /* perform pre block creation validation */
    /* if the header is genesis throw exception */
    Block *new_block_node = new Block();
    if (blockops.blockstructure.block_header == "genesis")
        nitrogen_error_stack("genesis block already exists");

    /* holds and sets the current hash of the block */
    /* generated from the Tx and the block header  */
    for (int i = 0; i < blockops.transactions.size(); ++i)
    {
        blockops.curr_hash = blockops.transactions[i] +
                             blockops.blockstructure.block_header;
    }

    /* set the block hash for the new node to be */
    /* the pre-generated current hash as above   */
    /* also as in a Linked List set the node null*/
    new_block_node->block_hash = std::stoul(blockops.curr_hash);
    new_block_node->next_block_node = nullptr;

    /* create a second Layer after the initial */
    /* set the initial block node to the second*/
    /* Layer of the generated node. run with hash*/
    Block *second_layer_block = new Block();
    second_layer_block->block_hash = std::stoul(blockops.curr_hash);
    new_block_node->next_block_node->next_block_node = second_layer_block;
    /* we fetch each data for the block using the hash*/
    /* ensure the hash is deterministic based on data */
    return new_block_node;
}

/* handle the error in a graceful way */
/* refactor later for complex scenarios */
void nitrogen_error_stack(const char *msg)
{
    perror(msg);
    exit(1);
}

template <typename T>
std::ostream& operator<<(std::ostream& stream, const Block& blockc)
{
    /* overriding the left turbo fish operator for */
    /* data visualization on the terminal when run */
    stream << blockc.block_hash 
           << blockc.next_block_node;
}