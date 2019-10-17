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



class Block {


public:
	//Block(Block* prevHash,
	//	string timestamp,
	//	string merkel_root_hash,
	//	uint64_t nonce,
	//	unsigned int difficulty) :
	//	_prevHash(prevHash),
	//	_timestamp(timestamp),
	//	_merkel_root_hash(merkel_root_hash),
	//	_nonce(nonce),
	//	_difficulty(difficulty) {}
	Block* _prevHash;
	string _timestamp; //+
	string _merkel_root_hash;
	uint64_t _nonce; //+
	unsigned int _difficulty;
	vector<Transaction> confirmedTransactions;
};