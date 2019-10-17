#pragma once
#include <string>
#include <ctime>
#include "Hash.h"
using std::string;


struct Transaction {
public:
	string senderWallet;
	string receiverWallet;
	double amount;
	double fee;
	string _timestamp;
	string txId;


	Transaction(string _senderWallet,
		string _receiverWallet,
		double _amount,
		double _fee) :
		senderWallet{ _senderWallet },
		receiverWallet{ _receiverWallet },
		amount{ _amount },
		fee{ _fee },
		//_timestamp{ __getTimestamp() },
		/// TxId is calculated with
		/// sender, receiver, ammount and timestamp
		txId{ hash128(_senderWallet +
			_receiverWallet +
			std::to_string(amount) +
			std::to_string(fee) +
			_timestamp
		) }
	{}

	string __getTimestamp();
};


string Transaction::__getTimestamp() {
	auto timenow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	//char arr[26];
	//ctime_s(arr, sizeof(arr), &timenow);
	//string str(arr);
	auto tm = *std::localtime(&timenow);

	std::ostringstream oss;
	oss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
	auto str = oss.str();
	return str;
}