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

#include <thread>



int main() {
	Blockchain list;

	list.add(111);
	list.add(222);
	list.add(313);
	list.add(111);
	list.add(222);
	list.add(111);
	list.add(222);
	list.add(313);
	list.add(111);
	list.add(222);
	list.add(111);
	list.add(222);
	list.add(313);
	list.add(111);
	list.add(222);
	list.add(111);
	list.add(222);
	list.add(313);
	list.add(111);
	list.add(222);
	list.add(111);
	list.add(222);
	list.add(313);
	list.add(111);
	list.add(222);
	list.add(111);
	list.add(222);
	list.add(313);
	list.add(111);
	list.add(222);
	list.add(111);
	list.add(222);
	list.add(313);
	list.add(111);
	list.add(222);
	list.add(111);
	list.add(222);
	list.add(313);
	list.add(111);
	list.add(222);
	list.add(111);
	list.add(222);
	list.add(313);
	list.add(111);
	list.add(222);


	list.print();

}