#pragma once
#include "User.h"
#include "Blockchain.h"
#include <numeric>
#include <deque>





class Miner : public User {

public:
	std::vector<Transaction> transactions_to_mine;
	Miner() : User{} {}



	/// Store transactions to mine
	void getUnconfirmedTransactions(Blockchain&);
	/// Store RANDOM transactions to mine
	void getUnconfirmedTransactions_random(Blockchain&);
	/// Mining algorithm
	//MinedParameters startMining(Blockchain&);
	/// Mining algorithm for multiple miners
	void startMining_concurrent(Blockchain&, unsigned int, uint64_t);

private:
	/// Get merkel root hash based on transactions' txId

	string _find_merkel_root_hash() {
		// CREATE TXID VECTOR
		std::vector<string> merkle;
		merkle.reserve(merkle.size());
		for (const auto& el : this->transactions_to_mine) {
			merkle.push_back(el.txId);
		}

		// CHECK VECTOR
		if (merkle.empty())
			return "00000000000000000000000000000000";
		else if (merkle.size() == 1)
			return "merkle";//merkle[0];;


		while (merkle.size() > 1) {
			if (merkle.size() % 2 != 0)
				merkle.push_back(merkle.back());

			std::vector<string> new_merkle;

			for (auto it = merkle.begin(); it != merkle.end(); it += 2) {
				new_merkle.push_back(hash128( (*it) + *(it+1)));
			}
			merkle = new_merkle;
		}
		std::cout << merkle[0] << std::endl;
		return merkle[0];
	}
};


struct MinedParameters {
	vector<Transaction> transactions;
	string merkel_root_hash;
	uint64_t nonce;
	Miner whoMined;
};



/// Store transactions to mine
void Miner::getUnconfirmedTransactions(Blockchain& blockchain) {
	if (blockchain.unT.size() < 100) {
		throw std::runtime_error("Not enough unconfirmed transactions to mine.");
	};
	//copy first 100 of transactions into miner's transaction list
	vector<Transaction>::const_iterator first = blockchain.unT.begin();
	vector<Transaction>::const_iterator last = blockchain.unT.begin() + 100;
	vector<Transaction> transactions(first, last);
	transactions_to_mine = transactions;
}

void Miner::getUnconfirmedTransactions_random(Blockchain& blockchain) {
	unsigned int t_count = blockchain.unT.size();
	if (t_count == 0) {
		throw std::runtime_error("Not enough unconfirmed transactions to mine.");
	};
	t_count = t_count < 100 ? t_count : 100;

	///Shuffle transactions to get random ones later
	vector<Transaction>::iterator start = blockchain.unT.begin();
	vector<Transaction>::iterator end = blockchain.unT.end();
	std::random_shuffle(start, end);

	//copy first 100 of transactions into miner's transaction list
	vector<Transaction>::const_iterator first = blockchain.unT.begin();
	vector<Transaction>::const_iterator last = blockchain.unT.begin() + t_count;
	


	vector<Transaction> transactions(first, last);
	transactions_to_mine = transactions;
}




/// Mining algorithm
//MinedParameters Miner::startMining(Blockchain& blockchain) {
//
//	/// Get a list of transacations to mine
//	this->getUnconfirmedTransactions(blockchain);
//	/// Get merkel root hash
//	std::string merkel_root_hash = _find_merkel_root_hash();
//	/// Start mining
//	std::cout << "\nStarted mining... Difficulty: " << blockchain.difficultyTarget << "\n" << std::string(50, '=') << std::endl;
//	uint64_t nonce = 0;
//	string hashed;
//	do {
//		nonce += 1;
//		hashed = hash128(merkel_root_hash + std::to_string(nonce));
//
//	} while (hashed.find(std::string(blockchain.difficultyTarget, '0')) != 0); // zeroes at the start
//	std::cout << "Mined hash:\t" << hashed << std::endl;
//	/// Return mined transactions with merkel root and nonce for validations
//	return MinedParameters{ transactions_to_mine, merkel_root_hash, nonce };
//}



/// Mining algorithm for multiple miners
void Miner::startMining_concurrent(Blockchain& blockchain, unsigned int tries, uint64_t nonce) {

	/// Get a list of transacations to mine
	this->getUnconfirmedTransactions_random(blockchain);
	/// Get merkel root hash
	std::string merkel_root_hash = this->_find_merkel_root_hash();
	/// Start mining
	//std::cout << "\nStarted mining... Difficulty: " << blockchain.difficultyTarget << "\n" << std::string(50, '=') << std::endl;
	string hashed;


	for (unsigned int i = 0; i < tries; ++i) {
		++nonce;
		hashed = hash128(merkel_root_hash + std::to_string(nonce));
		if (hashed.find(std::string(blockchain.difficultyTarget, '0')) == 0) {
			std::cout << "Mined hash:\t" << hashed << std::endl;
			throw MinedParameters{ transactions_to_mine, merkel_root_hash, nonce, *this };
		}
	}

}


