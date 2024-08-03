# Socket Operability
The socket implementation uses the low level apis provided by the host system and incorporates the TCP protocol for peer to peer interactions, based on the operating principle of how P2P network works. 

# Private & Public Keys
We generate the keys by hashing the data from each individual nodes or computer systems and then generating two pairs of keys one secret and one public which is used for user and node validations

# Node Discovery
A bootstrap Node server is launched and keeps on polling for other nodes, these other nodes connect to the server and hence is hooked up to other nodes, we use a generic socket implementation to discover nodes. we plan to switch to MDNS on a v0.0.2

# Message Sharing
In this case message is passed generically either when a transaction ```tx ``` has been completed or when a new node joins the chain. we have plans to switch to Yamux (yet another multiplexer) which incorporates floodsub and gossipsub

# Storing Data
Storing of data is done to a generic text file ```genesis.txt``` for the gensis block and ```nitrogen.txt``` for the other blocks and corresponding chain information, we plan to use the DHT (distributed hash table: kademlia) subsequently.