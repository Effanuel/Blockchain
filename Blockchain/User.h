#pragma once
#include <string>
#include <vector>
#include <ctime>
#include <algorithm>
#include <random>
#include <cmath>

#include "Hash.h"

using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::endl;


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

	double getBalance() const {
		return _balance;
	}
	void setBalance(double amount) {
		_balance += amount;
	}



private:
	double _balance;
	string _publicKey;
	string _privateKey;

	string _init_walletId(size_t);
	double _init_balance(int);
};


User::User(double balance) :
	_balance{ balance },
	walletId{ _init_walletId(64) },
	_publicKey{ hash128(walletId) },
	_privateKey{ hash128(_publicKey) } {}
User::User() :
	_balance{ _init_balance(1e6) },
	walletId{ _init_walletId(64) },
	_publicKey{ hash128(walletId) },
	_privateKey{ hash128(_publicKey) } {}




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

	return hash128(str);

}

double User::_init_balance(int limit) {

	std::random_device device;
	static std::mt19937 gen(device()); // CHANGE LATER
	//gen.seed(std::random_device()());
	static std::uniform_int_distribution<int> distr(1000, limit);
	return distr(gen);
}