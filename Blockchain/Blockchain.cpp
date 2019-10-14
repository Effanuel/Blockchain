#include <iostream>
#include "Blockchain.h"
#include "User.h"
#include "Hash.h"

#include <thread>



int main() {
	Blockchain list;
	User user1{};
	User user2{};
	//std::cout << user1.getPublic() <<
	//	" " << user1.getPrivate() << " " << user1.walletId << std::endl;

	//std::cout << user2.getPublic() <<
	//	" " << user2.getPrivate() << " " << user2.walletId << std::endl;

	////add transaction between user1 and user2
	//list.addTransaction(Transaction{ user1.walletId, user2.walletId, 5, 0.00 });
	vector<User> users = generateUsers(1000);
	generateTransactions(list, users, 100);

	for (const auto& elem : list.unconfirmedTransactions)
	{
		std::cout << elem.amount <<" "<< elem.txId << std::endl;
	}

	



	//Hash hash{"a"};

	//std::cout << hash.hash128() << std::endl;


	list.add(111);
	list.add(222);
	list.add(313);

	list.print();

}