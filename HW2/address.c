#include "address.h"

void printAddress(const Address* pAdd)
{
	printf("Address: %s, %d, %s\n", pAdd->streetName, pAdd->streetNum, pAdd->city);
}

Address* getAddressData() // TODO
{
	//char* address = getAddressFromUser();
	// if(address == NULL) 
	// 
	//char* token = "#";
	//char* ptr = strtok(address, token);
	//pAdd->streetName = fixAddressString(ptr);
	//ptr = strtok(NULL, token);
	//pAdd->streetNum = fixAddressString(ptr); // can use strtol?
	//ptr = strtok(NULL, token);
	//pAdd->city = fixAddressString(ptr);
}
