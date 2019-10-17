#pragma once

#include <string>
#include <vector>
#include <ctime>
#include "Transaction.h"
using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::endl;



struct Block {
	Block* _prevHash;
	string _timestamp; //+
	string _merkel_root_hash;
	uint64_t _nonce; //+
	unsigned int _difficulty;
	uint64_t _version;
	string _blockHash;
	vector<Transaction> confirmedTransactions;
};