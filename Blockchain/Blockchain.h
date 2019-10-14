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


	Blockchain() : _genesisBlock{ nullptr }, length{ 0 } {}


	~Blockchain() {
		Block* _prevHash = _genesisBlock;

		while (_prevHash) {
			Block* deleteMe = _prevHash;
			_prevHash = _prevHash->_prevHash;
			delete deleteMe;
		}
	}

	void add(int body) {
		Block* node = new Block();

		node->body = body;
		node->_prevHash = _genesisBlock;
		node->_timestamp = __getTimestamp();
		_genesisBlock = node;
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
			std::cout << i << " : " << _genesisBlock->body << " : " << _genesisBlock->_timestamp << std::endl;
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