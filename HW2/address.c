#include "address.h"

void printAddress(const Address* pAdd)
{
	printf("Address: %s, %d, %s\n", pAdd->streetName, pAdd->streetNum, pAdd->city);
}

Address* getAddressData()
{
	char* address = getAddressFromUser();
	if (address == NULL)
	{
		printf("MEMORY ERROR\n");
		return NULL;
	}
	Address* newAddress = (Address*)malloc(sizeof(Address));
	if (newAddress == NULL)
	{
		printf("MEMORY ERROR\n");
		return NULL;
	}
	fixValidAddress(newAddress, address);
	return newAddress;
}

void freeAddress(Address* pAdd)
{
	free(pAdd->city);
	free(pAdd->streetName);
}

void fixValidAddress(Address* pAdd, char* address)
{
	const char* delimiter = "#";
	char* street = strtok(address, delimiter);
	char* streetNum = strtok(NULL, delimiter);
	char* city = strtok(NULL, delimiter);
	pAdd->streetName = fixAddressStreetAndCity(street);
	pAdd->streetNum = atoi(streetNum);
	pAdd->city = fixAddressStreetAndCity(city);
}