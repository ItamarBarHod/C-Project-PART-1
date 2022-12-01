#pragma once

typedef struct {
	int num;
	char* house;
	char* city;
}Address;

void printAddress(const Address* pAdd);
void initAddress(Address* pAdd);