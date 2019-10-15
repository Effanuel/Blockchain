#pragma once
#include "User.h"
#include "Blockchain.h"
#include <numeric>


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


	void startMining() {


		std::string toMineString;
		for (const auto& piece : unT_txId) toMineString += piece;

		int nonce = 0;
		string hashed;
		std::cout << "Started mining..." << std::endl;
		do {
			nonce+=8;
			hashed = hash128(toMineString + std::to_string(nonce));

		} while (hashed.find("000") != 0);
		std::cout << "Mined hash: " << hashed << std::endl;
		std::cout << "Nonce: " << nonce << std::endl;

	}
};