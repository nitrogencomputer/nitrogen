# Architecture
The architecture of this blockchain framework is as simple as it goes, basically the core use case of this blockchain is to serve for two purposes, ```Banking transactions``` and ```medical transactions``` purposes. Hence we try to be explicit in our technical implementations. Our block structure is modular and incorporates some base steps as shown below, but first the block signature is as below.

``` shell
/* memory allocation for new block */
 struct Block* new_block_init = new Block();
 
 /* deallocate memory */
 free(new_block_init);
```

Firstly, we create a ```blockstructure``` which creates the structure of our blockchain, it is modular and separated from the core logic of our block creation process, as shown below.

```shell
/* memory allocation for block structure */
Blockstructure* new_block_structure =  new Blockstructure();
...

/* heap memory deallocation */
free(new_block_structure)
```
When the blockstructure is created, it includes several fields shuch as the ```block_id``` ```transaction_time``` also the transaction amount denoted as in the bracket ( ```tx_amount``` ) and also the block header ```block_header```, furthermore, there is an extra field called the ```block_tx_details``` this holds the block transaction details, and this is also modular because it is created differently and also includes a separate implementation for Block Node creation.

```shell
/* memory allocation for block transaction details */
BlockTxDetails* new_blockTx = new BlockTxDetails();

...

/* Nodes have a LinkedList implementation */
/* incorporates for sender and receiver */
Node& sender_node;
sender_node.balance = 200;
sender_node.preceding_node = nullptr;

Node& recv_node;
sender_node.balance = 10;
sender_node.preceding_node = nullptr;

/* heap memory deallocation */
free(new_blockTx);

```

The Block transaction details is a modular structure and embeds the ```Node``` structure inside it which holds the core information for the transaction which is the transaction data ```balance``` and the next transaction node ```preceding_node``` this is used to populate the transaction.

Furthermore, the block transaction detail is used as a child object for the block stucture, which then is used to create a Block operation ```BlockOps``` from the blockops class as below.

```shell
/* memory allocation for block transaction details */
BlockOps<std::string>* new_blockOps = new BlockOps<std::string>();

...

/* heap memory deallocation */
free(new_blockOps);

```

The blockops class object is then passed as a parameter to the block struct which then abstracts the needed data, collates them with an internal computation to create a sample block.