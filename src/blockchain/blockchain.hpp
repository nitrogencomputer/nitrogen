#include <iostream>
#include <vector>
#include "../block/block.hpp" 

namespace nitrogenx
{
    /* Abstract base class defining the interface for blockchain operations */
    class BlockchainInterface
    {
        /* Pure virtual function to get the blockchain */
        virtual std::vector<Block> blockchain() = 0;
        /* Pure virtual function to remove a block from the blockchain */ 
        virtual std::vector<Block> remove_block() = 0;
        /* Pure virtual function to add a block to the blockchain */
        virtual std::vector<Block> add_block() = 0;
    };

    // Templated Blockchain class inheriting from BlockchainInterface
    template <typename T>
    class Blockchain : public BlockchainInterface
    {
    public:
        Blockchain();
        Blockchain(const Blockchain& blockc);

        /* overload the << operator for outputting the Block object  */
        friend std::ostream& operator<<(std::ostream& stream, const Block& blockc);

        /* Function to get the blockchain with specific block operations */
        std::vector<T> blockchain(BlockOps<T>& blockops);

        /* Function to remove a block from the blockchain by its hash value */
        std::vector<T> remove_block(std::vector<Block*> blockchain, std::size_t hash);

        /* Function to add a new block to the blockchain  */
        std::vector<T> new_block(BlockOps<Blockstructure>& blockops);
    };
}
