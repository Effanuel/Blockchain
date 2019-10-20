#include <iostream>
#include "Blockchain.h"
#include "User.h"
#include "Hash.h"
#include "Miner.h"
#include "Functions.h"
#include <exception>
#include <thread>

void startMining(Blockchain&);
Blockchain initBlockchain();


int main() {



	Blockchain blockchain = initBlockchain();
	startMining(blockchain);	
	blockchain.print(); /// Print blockchain blocks
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
			miner.setBalance(blockchain.reward);



			/// Calculate sum of transaction fees
			double sumOfFees = std::accumulate(M_transactions.begin(), M_transactions.end(), 0, [&](double sum, const Transaction & transaction) {
				return sum + transaction.fee;
				});
			std::cout << ">>>>>Block reward : " << blockchain.reward + sumOfFees << " : to miner "<< miner.walletId << std::endl;
			/// Reward for mined block to a miner
			miner.setBalance(blockchain.reward + sumOfFees); 
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
	unsigned int transactionCount = 10000;
	std::cout << "Initializing blockchain with " <<
		userCount << " users and " <<
		transactionCount << " transactions...\n" << std::string(50, '=') << std::endl;
	Blockchain blockchain;
	/// Store generated Users
	vector<User> users = generateUsers(userCount);
	blockchain.setUsers(users); 
	/// Store generated transactions
	generateTransactions(blockchain, transactionCount);

	return blockchain;
}