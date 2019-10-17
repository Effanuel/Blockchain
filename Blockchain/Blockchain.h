#pragma once
#include <iostream>
#include <ctime>
#include <chrono>
#include <map>

#include "Block.h"
#include "Hash.h"
#include "Transaction.h"




class Blockchain {

public:
	std::vector<Transaction> unT;
	unsigned int length;


	Blockchain() : _genesisBlock{ nullptr }, length{ 0 } { /*unT.reserve(100);*/ }
	~Blockchain();

	bool contains(const Transaction& src);

	void addNode(vector<Transaction>& body, string& merkel_root_hash, uint64_t& nonce);

	void addTransaction(Transaction transaction);
	void addTransaction(vector<Transaction>& transactions);

	void print();

private:
	Block* _genesisBlock;

	string __getTimestamp();

	void __removeConfirmedTransactions(vector<Transaction>);
};













/// PUBLIC MEMBER FUNCTIONS

Blockchain::~Blockchain() {
	Block* _prevHash = _genesisBlock;

	while (_prevHash) {
		Block* deleteMe = _prevHash;
		_prevHash = _prevHash->_prevHash;
		delete deleteMe;
	}
}


bool Blockchain::contains(const Transaction& src) {
	auto iter = std::find_if(unT.begin(), unT.end(),
		[&](const Transaction& ts) {return ts.txId == src.txId; });
	return iter != unT.end();
}


void Blockchain::addNode(vector<Transaction>& body, string& merkel_root_hash, uint64_t& nonce) {
	std::cout << "Adding block with merkel: " << merkel_root_hash << std::endl;
	std::cout << "Adding block with nonce: " << nonce << std::endl;
	Block* node = new Block();
	std::cout << "Unconfirmed transactions left: " << unT.size() << std::endl;
	node->_prevHash = _genesisBlock;


	///Header
	node->_timestamp = __getTimestamp();
	node->_merkel_root_hash = merkel_root_hash;
	node->_nonce = nonce;
	/// Body
	node->confirmedTransactions = body;

	_genesisBlock = node;
	std::cout << "Added block. Done." << std::endl;
	/// Count number of blocks
	++length;

	/// Remove confirmed transactions
	__removeConfirmedTransactions(body);
	std::cout << "Unconfirmed transactions left: " << unT.size() << std::endl;



	
	/// insert for ea in vector
	/// for ea transaction get amount and +to receiver-fee -sender


}

void Blockchain::addTransaction(Transaction transaction) {
	unT.push_back(transaction);
}
void Blockchain::addTransaction(vector<Transaction>& transactions) {
	unT = std::move(transactions);
}



void Blockchain::print() {
	Block* node = this->_genesisBlock;
	int i = 0;
	while (_genesisBlock) {
		std::cout << "Block: " << length - i <<
			"\n:Merkel:\t" << _genesisBlock->_merkel_root_hash <<
			"\n:Timestamp:\t" << _genesisBlock->_timestamp <<
			":Nonce:\t\t" << _genesisBlock->_nonce << std::endl;
		std::cout << std::string(50, '-') << std::endl;
		_genesisBlock = _genesisBlock->_prevHash;
		++i;
	}
}




/// PRIVATE MEMBER FUNCTIONS
string Blockchain::__getTimestamp() {
	auto timenow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	char arr[26];
	ctime_s(arr, sizeof(arr), &timenow);
	string str(arr);
	return str;
}


void Blockchain::__removeConfirmedTransactions(vector<Transaction> body) {
	for (const auto& elem : body) {
		//unT.erase(std::remove(unT.begin(), unT.end(), elem), unT.end());
		unT.erase(
			std::remove_if(unT.begin(), unT.end(), [&](Transaction const& pet) {
				return pet.txId == elem.txId;
				}),
			unT.end());
	}
}