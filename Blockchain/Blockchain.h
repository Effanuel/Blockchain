#pragma once
#include <iostream>
#include <ctime>
#include <chrono>

#include "Block.h"

class Blockchain {

public:
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