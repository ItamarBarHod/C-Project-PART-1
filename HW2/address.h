#pragma once

#include <stdio.h>
#include "stringfuncs.h"
#include "userinput.h"

typedef struct {
	char* streetName;
	int streetNum;
	char* city;
}Address;

void printAddress(const Address* pAdd);
Address* getAddressData();