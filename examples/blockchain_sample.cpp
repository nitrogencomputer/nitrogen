#include <iostream>
#include <string>
#include <chrono>
#include "../src/blockchain/blockchain.hpp"

using namespace std::chrono;

void blockchain_sample()
{

    struct Block* new_block_init = new Block();
    Blockstructure* new_block_struct = new Blockstructure();
    new_block_struct->block_id= 1;
    new_block_struct->transaction_time = high_resolution_clock::now();
    new_block_struct->tx_amount = 20;
    new_block_struct->block_header = "sample_header";

    Node* snode = new Node();
    Node* rnode = new Node();
    snode->balance = 300;
    snode->preceding_node = nullptr;
    
    rnode->balance = 400;
    rnode->preceding_node = nullptr;

    BlockTxDetails* new_blockTx_data = new BlockTxDetails();
    new_blockTx_data->sender = snode;
    new_blockTx_data->receiver = rnode;
    new_blockTx_data->tx_hash = "sample_hash";

    new_block_struct->block_tx_details.receiver = new_blockTx_data->receiver;
    new_block_struct->block_tx_details.sender = new_blockTx_data->sender;
    new_block_struct->block_tx_details.tx_hash = new_blockTx_data->tx_hash;

    BlockOps<Blockstructure>* new_block_opx = new BlockOps<Blockstructure>();
    BlockOps<Blockstructure> block_opx_init = new_block_opx->create_new_blockops(*new_block_struct);

     nitrogenx::Blockchain<std::string>* chain;
     std::vector<std::string> new_block = chain->new_block(block_opx_init);
     for(int i = 0; i < new_block.size(); ++i)
        std::cout << new_block[i] << std::endl;
}

int main(int argc, char** argv)
{
   blockchain_sample();
   return 0;
}