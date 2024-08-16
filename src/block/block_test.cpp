#ifdef TEST_BUILD
#include <iostream>
#include <string>

#include "./block.hpp"
#include <gtest/gtest.h>

struct BlockTest : testing::Test
{
    Block<std::string> *block;
    Blockstructure *blockst;
    BlockTxDetails *blocktx;
    BlockOps<std::string> *blockop;
    Node *snode, *rnode;

    void setUp()
    {
        block = new Block<std::string>();
        blockst = new Blockstructure();
        blockst->block_id = 1;
        blockst->tx_amount = 1002;
        blockst->block_header = "0x012223345";

        blocktx = new BlockTxDetails();
        snode = new Node();
        rnode = new Node();
        snode->balance = 450;
        snode->preceding_node = rnode;
        rnode->balance = 200;
        rnode->preceding_node = nullptr;

        blocktx->sender = snode;
        blocktx->receiver = rnode;
        blockst->block_tx_details = blocktx;

        blockop = new BlockOps<std::string>();
        blockop->create_new_blockops(blockst);
        block->create_new_block(blockop);
    }
    void tearDown() 
    { 
        delete blockop;
        delete block;
        delete blockst;
        delete blocktx;
        delete snode;
        delete rnode; 
        }
};

TEST_F(BlockTest, BlockStructure_Hash_Test)
{
    if (blockst->block_id > 0)
        std::cout << "Hash_00\n";
    ASSERT_EQ(blockst->block_header, "0x012223345");
}

TEST_F(BlockTest, BlockStructure_TxAmount_Valid)
{
    if (blockst->block_id < 0 ||
        blockst->block_header != "0x012223345")
    {
        std::cout << "invalid block_id or block_header";
        std::cout << "___NITROGEN_BLOCK_HEADER_ERROR__";
        EXPECT_NE(blockst->block_header, "0x012223345");
    }
    else
    {
        ASSERT_NE(blockst->tx_amount, 0);
        ASSERT_EQ(blockst->tx_amount, 1002);
        ASSERT_GT(blockst->tx_amount, 500);
    }
}

TEST_F(BlockTest, BlockTxDetails_Sender_Balance_Valid)
{
    if (blocktx->sender != nullptr && blocktx->receiver != nullptr)
    {
        ASSERT_NE(blocktx->sender->balance, 0);
        ASSERT_LT(blocktx->sender->balance, blockst->tx_amount);
        ASSERT_EQ(blocktx->sender->balance, 450);
    }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#endif