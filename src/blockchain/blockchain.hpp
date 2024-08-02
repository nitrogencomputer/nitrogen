#ifndef BLOCKCHAIN_HPP 
#define BLOCKCHAIN_HPP

#include <iostream>
#include <vector>
#include "../block/block.hpp" 

namespace nitrogenx
{
    template <typename T>
    /* Abstract base class defining the interface for blockchain operations */
    class BlockchainInterface
    {
        /* Pure virtual function to get the blockchain */
        virtual std::vector<Block> blockchain(BlockOps<T>& blockops) = 0;
        /* Pure virtual function to remove a block from the blockchain */ 
        virtual std::vector<Block> remove_block(std::vector<Block*> blockchain, std::size_t hash) = 0;
        /* Pure virtual function to add a block to the blockchain */
        virtual std::vector<Block> new_block(BlockOps<Blockstructure>& blockops) = 0;
    };

    /* Templated Blockchain class inheriting from BlockchainInterface */
    template <typename T>
    class Blockchain : public BlockchainInterface<T>
    {
    public:
        Blockchain();
        Blockchain(const Blockchain& blockc);

        /* overload the << operator for outputting the Block object  */
        friend std::ostream& operator<<(std::ostream& stream, const Block& blockc){
            stream << blockc.block_hash;
        }

        /* Function to get the blockchain with specific block operations */
        std::vector<T> blockchain(BlockOps<T>& blockops) override;

        /* Function to remove a block from the blockchain by its hash value */
        std::vector<T> remove_block(std::vector<Block*> blockchain, std::size_t hash) override;

        /* Function to add a new block to the blockchain  */
        std::vector<T> new_block(BlockOps<Blockstructure>& blockops) override;
    };
}
#endif