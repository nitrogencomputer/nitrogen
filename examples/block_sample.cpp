#include <iostream>
#include <string>
#include <chrono>
#include "../src/block/block.hpp"

using namespace std::chrono;

void block_sample()
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

    BlockOps<std::string>* new_block_opx = new BlockOps<std::string>();
    auto block_opx_init = new_block_opx->create_new_blockops(*new_block_struct);
    new_block_init->create_new_block(block_opx_init);

    free(new_block_struct);
    free(new_block_opx);
    free(new_block_init);
}

int main(int argc, char** argv)
{
   block_sample();
   return 0;
}