#ifndef BLOCKCHAIN_HPP 
#define BLOCKCHAIN_HPP

#include <iostream>
#include <vector>
#include "../block/block.hpp" 

namespace nitrogenx
{
    template <typename T>
    class BlockchainInterface
    {
        virtual std::vector<Block> blockchain(BlockOps<T>& blockops) = 0;
        virtual std::vector<Block> remove_block(std::vector<Block*> blockchain, std::size_t hash) = 0;
        virtual std::vector<Block> new_block(BlockOps<Blockstructure>& blockops) = 0;
    };

    template <typename T>
    class Blockchain : public BlockchainInterface<T>
    {
    public:
        Blockchain();
        Blockchain(const Blockchain& blockc);
        friend std::ostream& operator<<(std::ostream& stream, const Block& blockc){
            stream << blockc.block_hash;
        }
        std::vector<T> blockchain(BlockOps<T>& blockops) override;
        std::vector<T> remove_block(std::vector<Block*> blockchain, std::size_t hash) override;
        std::vector<T> new_block(BlockOps<Blockstructure>& blockops) override;
    };
}
#endif