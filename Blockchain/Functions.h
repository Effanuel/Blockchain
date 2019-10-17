#pragma once
#include "Blockchain.h"
#include "User.h"



///Generates a vector of unconfirmed transactions with class 'Transaction'
vector<User> generateUsers(unsigned int number) {
	vector<User> users;
	users.reserve(number);
	for (unsigned int i = 0; i < number; ++i) {
		users.push_back(User{});
	}
	return users;
}

///Generates a vector of unconfirmed transactions with class 'Transaction'
///and sets it to 'Blockchain' unconfirmed transactions
void generateTransactions(Blockchain& blockchain, unsigned int numberOfTransactions) {

	vector<User> blockchain_Users = blockchain.getUsers();

	std::random_device device;
	static std::mt19937 gen(device()); // CHANGE LATER
	//gen.seed(std::random_device()());
	static std::uniform_int_distribution<int> distr(0, blockchain_Users.size() - 1); //error???
	static std::uniform_real_distribution<double> distr_amount(5.0, 50.0);
	static std::uniform_real_distribution<double> distr_fee(0.0, 2.0);

	vector<Transaction> unconfirmedTransactions;
	unconfirmedTransactions.reserve(numberOfTransactions);


	double senderID;
	for (unsigned int i = 0; i < numberOfTransactions; ++i) {

		senderID = distr(gen);

		unconfirmedTransactions.push_back(
			Transaction{
				blockchain_Users[senderID].walletId,			/// SENDER WALLET
				blockchain_Users[distr(gen)].walletId,			/// RECEIVER WALLET
				blockchain_Users[senderID].getBalance()*0.2,	/// SEND ONLY 20% OF BALANCE
				distr_fee(gen) });								/// FEE
	}

	blockchain.addTransaction(unconfirmedTransactions);
	unconfirmedTransactions.clear();
}







