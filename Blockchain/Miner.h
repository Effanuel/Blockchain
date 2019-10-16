#pragma once
#include "User.h"
#include "Blockchain.h"
#include <numeric>


struct MinedTransactions {
	vector<string> transactions;
	string merkel_root_hash;
	uint64_t nonce;
};


class Miner : User {

public:
	std::vector<string> unT_txId;
	Miner() : User{} {}

	void getUnconfirmedTransactions(Blockchain& blockchain) {
		if (blockchain.unconfirmedTransactions.size() < 100) return;

		//copy first 100 of transactions into miner's transaction list



		vector<Transaction>::const_iterator first = blockchain.unconfirmedTransactions.begin();
		vector<Transaction>::const_iterator last = blockchain.unconfirmedTransactions.begin() + 100;

		vector<Transaction> newVec(first, last);
		for (const auto& elem : newVec) {
			unT_txId.push_back(elem.txId);
		}
	}



	

	MinedTransactions startMining() {


		std::string string_of_transactions;
		for (const auto& tx : unT_txId) string_of_transactions += tx;
		std::string merkel_root_hash = hash128(string_of_transactions);

		uint64_t nonce = 0;
		string hashed;
		std::cout << "Started mining..." << std::endl;
		do {
			nonce+=8;
			hashed = hash128(merkel_root_hash + std::to_string(nonce));

		} while (hashed.find("00000") != 0);
		std::cout << "Mined hash: " << hashed << std::endl;
		std::cout << "Nonce: " << nonce << std::endl;
		return MinedTransactions{ unT_txId, merkel_root_hash, nonce };
	}
};