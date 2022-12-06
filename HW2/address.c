#include "address.h"

void printAddress(const Address* pAdd)
{
	printf("Address: %s, %d, %s\n", pAdd->streetName, pAdd->streetNum, pAdd->city);
}

void getAddressData(Address* pAdd) // TODO
{
	//char* address = getAddressFromUser();
	//char* token = "#";
	//char* ptr = strtok(address, token);
	//pAdd->streetName = fixAddressString(ptr);
	//ptr = strtok(NULL, token);
	//pAdd->streetNum = fixAddressString(ptr);
	//ptr = strtok(NULL, token);
	//pAdd->city = fixAddressString(ptr);
}
