#include <iostream>
#include "Blockchain.h"
#include "User.h"
#include "Hash.h"
#include "Miner.h"
#include "Functions.h"
#include <exception>
#include <thread>
#include <future>

void startMining(Blockchain&);
Blockchain initBlockchain();
void startMining_concurrent(Blockchain& blockchain);


int main() {

	//std::vector<int> v{ 1, 2, 3, 4, 5, 6 };
	//auto f1 = [](std::vector<int> & v,
	//	unsigned int left, unsigned int right) {
	//		unsigned long long acm = 0;
	//		for (int i = left; i < right; ++i) {
	//			acm += v[i];
	//		}
	//		return acm;
	//};
	//auto t1 = std::async(f1, std::ref(v), 0, v.size());
	//auto t2 = std::async(f1, std::ref(v), 0, 1);

	//{
	//	unsigned long long acm11;
	//	unsigned long long acm22;
	//	if ((acm11 = t1.get()) || (acm22 = t2.get())) {

	//		std::cout << "acm1: " << acm22 << endl;
	//	}
	//}


	//unsigned long long acm1 = t1.get();
	//unsigned long long acm2 = t2.get();

	//std::cout << "acm1: " << acm1 << endl;
	//std::cout << "acm2: " << acm2 << endl;
	//std::cout << "acm1 + acm2: " << acm1 + acm2 << endl;

	Blockchain blockchain = initBlockchain();
	startMining_concurrent(blockchain);	
	blockchain.print(); /// Print blockchain blocks
}

void startMining_concurrent(Blockchain& blockchain) {
	/// Init miner class
	Miner miner1{};
	Miner miner2{};
	Miner miner3{};
	Miner miner4{};
	Miner miner5{};

	MinedParameters M_body{};
	uint64_t nonce = 0;
	unsigned int tries = 500;
	while (true) {
		try {
			
			while (true) {
				try {
					/// """CONCURRENT""" MINERS
					miner1.startMining_concurrent(blockchain, tries, nonce);
					miner2.startMining_concurrent(blockchain, tries, nonce);
					miner3.startMining_concurrent(blockchain, tries, nonce);
					miner4.startMining_concurrent(blockchain, tries, nonce);
					miner5.startMining_concurrent(blockchain, tries, nonce);
					nonce += tries;
					tries += 100;
				}
				catch (const MinedParameters& minedBlock) {
					M_body = minedBlock;
					nonce = 0;
					tries = 500;
					break;
				}
				catch (const char* noMoreTransactionsLeft) { ///std::exception doesnt work properly on command line
					/// No more transactions to mine
					throw noMoreTransactionsLeft;
				}

			}

			///RETURNED HEADER AND BODY PARAMETERS
			uint64_t M_nonce = M_body.nonce;
			string M_merkel_root_hash = M_body.merkel_root_hash;
			vector<Transaction> M_transactions = M_body.transactions;
			

			/// Add mined block to blockchain
			blockchain.addNode(M_transactions, M_merkel_root_hash, M_nonce);
			miner4.setBalance(blockchain.reward);



			/// Calculate sum of transaction fees
			double sumOfFees = std::accumulate(M_transactions.begin(), M_transactions.end(), 0, [&](double sum, const Transaction & transaction) {
				return sum + transaction.fee;
				});
			std::cout << ">>>>>Block reward : " << blockchain.reward + sumOfFees << " : to miner "<< M_body.whoMined.walletId << "\n\n";
			/// Reward for mined block to a miner
			M_body.whoMined.setBalance(blockchain.reward + sumOfFees);
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
	unsigned int transactionCount = 500;
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



//void startMining(Blockchain& blockchain) {
//	/// Init miner class
//	Miner miner{};
//
//
//	while (true) {
//		try {
//			MinedParameters M_body = miner.startMining(blockchain); //mined body
//
//			///RETURNED HEADER AND BODY PARAMETERS
//			uint64_t M_nonce = M_body.nonce;
//			string M_merkel_root_hash = M_body.merkel_root_hash;
//			vector<Transaction> M_transactions = M_body.transactions;
//
//
//			/// Add mined block to blockchain
//			blockchain.addNode(M_transactions, M_merkel_root_hash, M_nonce);
//			miner.setBalance(blockchain.reward);
//
//
//
//			/// Calculate sum of transaction fees
//			double sumOfFees = std::accumulate(M_transactions.begin(), M_transactions.end(), 0, [&](double sum, const Transaction & transaction) {
//				return sum + transaction.fee;
//				});
//			std::cout << ">>>>>Block reward : " << blockchain.reward + sumOfFees << " : to miner " << miner.walletId << std::endl;
//			/// Reward for mined block to a miner
//			miner.setBalance(blockchain.reward + sumOfFees);
//		}
//		catch (std::exception & e) {
//			std::cout << std::string(50, '-') << std::endl;
//			std::cout << e.what() << std::endl;
//			std::cout << std::string(50, '-') << std::endl;
//			break;
//		}
//	}
//}