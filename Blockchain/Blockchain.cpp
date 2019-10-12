//#include <iostream>
//#include "Blockchain.h"
//#include <stdlib.h>
//
//int main()
//{
//	Blockchain* blockchain{};
//	srand(NULL);
//	blockchain->add(rand() % 100);
//	blockchain->print();
//	std::cout << "List Length: " << blockchain->length << std::endl;
//	delete blockchain;
//
//}
//
#include <iostream>
#include "Blockchain.h"
#include "User.h"
#include "Hash.h"

#include <thread>



int main() {
	Blockchain list;
	User user1{};
	User user2{};
	std::cout << user1.getPublic() <<
		" " << user1.getPrivate() << " " << user1.walletId << std::endl;

	std::cout << user2.getPublic() <<
		" " << user2.getPrivate() << " " << user2.walletId << std::endl;

	list.add(111);
	list.add(222);
	list.add(313);

	list.print();

}