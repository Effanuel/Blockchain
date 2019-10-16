#pragma once
#include <iostream>
#include <ctime>
#include <chrono>
#include <map>

#include "Block.h"
#include "Hash.h"

struct Transaction {
	string senderWallet;
	string receiverWallet;
	double amount;
	double fee;
	string txId;

	Transaction(string _senderWallet,
		string _receiverWallet,
		double _amount,
		double _fee) :	
		senderWallet{ _senderWallet },
		receiverWallet {_receiverWallet},
		amount{_amount},
		fee{_fee},
		txId{ hash128(_senderWallet + _receiverWallet) } {}
};



class Blockchain {

public:
	std::vector<Transaction> unconfirmedTransactions;


	Blockchain() : _genesisBlock{ nullptr }, length{ 0 } { /*unconfirmedTransactions.reserve(100);*/ }


	~Blockchain() {
		Block* _prevHash = _genesisBlock;

		while (_prevHash) {
			Block* deleteMe = _prevHash;
			_prevHash = _prevHash->_prevHash;
			delete deleteMe;
		}
	}

	void add(vector<string>& body, string& merkel_root_hash, uint64_t& nonce) {
		std::cout << "Adding block with merkel: " << merkel_root_hash << std::endl;
		std::cout << "Adding block with nonce: " << nonce << std::endl;
		Block* node = new Block();

		node->confirmedTransactions = body;
		node->_prevHash = _genesisBlock;
		//Header
		node->_timestamp = __getTimestamp();
		node->_merkel_root_hash = merkel_root_hash;
		node->_nonce = nonce;
		//
		_genesisBlock = node;
		std::cout << "Added block. Done." << std::endl;
	}

	void addTransaction(Transaction transaction) {
		unconfirmedTransactions.push_back(transaction);
	}
	void addTransaction(vector<Transaction>& transactions) {
		unconfirmedTransactions = std::move(transactions);
	}




	void print() {
		Block* node = this->_genesisBlock;
		int i = 1;
		while (_genesisBlock) {
			std::cout <<"Block: " << i <<
				"\n:Merkel:\t" << _genesisBlock->_merkel_root_hash <<
				"\n:Timestamp:\t" << _genesisBlock->_timestamp <<
				"\n:Nonce:\t" << _genesisBlock->_nonce << std::endl;
			_genesisBlock = _genesisBlock->_prevHash;
			++i;
		}
	}



private:
	Block* _genesisBlock;
	int length;





	string __getTimestamp() {
		auto timenow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		char arr[26];
		ctime_s(arr, sizeof(arr), &timenow);
		string str(arr);
		return str;
	}
};