#include <iostream>
#include "Blockchain.h"
#include "User.h"
#include "Hash.h"
#include "Miner.h"
#include <exception>

#include <thread>

void startMining(Blockchain&);
Blockchain initBlockchain();


int main() {
	Blockchain blockchain = initBlockchain();
	startMining(blockchain);	
	blockchain.print();
}



void startMining(Blockchain& blockchain) {
	/// Init miner class
	Miner miner{};
	while (true) {
		try {
			MinedParameters M_body = miner.startMining(blockchain); //mined body

			///RETURNED HEADER AND BODY PARAMETERS
			uint64_t M_nonce = M_body.nonce;
			string M_merkel_root_hash = M_body.merkel_root_hash;
			vector<Transaction> M_transactions = M_body.transactions;

			/// Add mined block to blockchain
			blockchain.addNode(M_transactions, M_merkel_root_hash, M_nonce);
		}
		catch (std::exception& e) {
			std::cout << std::string(50, '-') << std::endl;
			std::cout << e.what() << std::endl;
			std::cout << std::string(50, '-') << std::endl;
			break;
		}	
	}	
}

Blockchain initBlockchain() {
	unsigned int userCount = 1000;
	int transactionCount = 10000;
	std::cout << "Initializing blockchain with " <<
		userCount << " users and " <<
		transactionCount << " transactions...\n" << std::string(50, '=') << std::endl;
	Blockchain blockchain;
	vector<User> users = generateUsers(userCount);
	generateTransactions(blockchain, users, transactionCount);
	return blockchain;
}