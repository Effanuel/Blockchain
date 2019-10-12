#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <ctime>
#include <algorithm>
#include <random>

#include "Hash.h"

using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::endl;


struct Transaction {
	string senderWallet;
	string receiverWallter;
	double amount;
	double fee;
};



class User {

public:
	string walletId;

	User(double balance);
	User();



	string getPublic() const {
		return _publicKey;
	}
	string getPrivate() const {
		return _privateKey;
	}



private:
	double _balance;
	string _publicKey;
	string _privateKey;

	string _init_walletId(size_t length);
	double _init_balance(size_t limit);
};


User::User(double balance) :
	_balance{ balance },
	walletId{ _init_walletId(25) },
	_publicKey{ hash64(walletId) },
	_privateKey{ hash64(_publicKey) } {}
User::User() :
	_balance{ _init_balance(500) },
	walletId{ _init_walletId(25) },
	_publicKey{ hash64(walletId) },
	_privateKey{ hash64(_publicKey) } {}




string User::_init_walletId(size_t length) {
	const char charset[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";
	const size_t max_index = (sizeof(charset) - 1);

	std::random_device device;
	static std::mt19937 gen(device()); // CHANGE LATER
	//gen.seed(std::random_device()());
	static std::uniform_int_distribution<int> distr(1, max_index);

	std::string str(length, 0);
	std::generate(str.begin(), str.end(), [&charset, &max_index]() {
		return charset[distr(gen) % max_index];
		});

	return hash64(str);

}

double User::_init_balance(size_t limit) {

	std::random_device device;
	static std::mt19937 gen(device()); // CHANGE LATER
	//gen.seed(std::random_device()());
	static std::uniform_int_distribution<int> distr(1, limit);
	return distr(gen);
}






