#pragma once
#include "User.h"
#include "Blockchain.h"
#include <numeric>


struct MinedParameters {
	vector<Transaction> transactions;
	string merkel_root_hash;
	uint64_t nonce;
};


class Miner : User {

public:
	std::vector<Transaction> transactions_to_mine;
	Miner() : User{} {}

	/// Store transactions to mine
	void getUnconfirmedTransactions(Blockchain& blockchain) {
		if (blockchain.unT.size() < 100) {
			throw std::exception("Not enough unconfirmed transactions to mine.");
		};
		//copy first 100 of transactions into miner's transaction list
		vector<Transaction>::const_iterator first = blockchain.unT.begin();
		vector<Transaction>::const_iterator last = blockchain.unT.begin() + 100;
		vector<Transaction> transactions(first, last);
		transactions_to_mine = transactions;
	}



	
	/// Mining algorithm
	MinedParameters startMining(Blockchain& blockchain) {

		/// Get a list of transacations to mine
		getUnconfirmedTransactions(blockchain);
		/// Get merkel root hash
		std::string merkel_root_hash = _find_merkel_root_hash();
		/// Start mining
		std::cout << "\nStarted mining...\n" << std::string(50, '=') << std::endl;
		uint64_t nonce = 0;
		string hashed;
		do {
			nonce+=8;
			hashed = hash128(merkel_root_hash + std::to_string(nonce));

		} while (hashed.find("00") != 0); // zeroes at the start
		std::cout << "Mined hash:\t" << hashed << std::endl;
		/// Return mined transactions with merkel root and nonce for validations
		return MinedParameters{ transactions_to_mine, merkel_root_hash, nonce };
	}

private:
	/// Get merkel root hash based on transactions' txId
	string _find_merkel_root_hash() {
		vector<string> unT_txId;
		std::string string_of_transactions;
		for (const auto& tx : transactions_to_mine) {
			string_of_transactions += tx.txId;
		}
		/// Hash all transactions' txIds'
		return hash128(string_of_transactions);
	}
};