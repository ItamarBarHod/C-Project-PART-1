#pragma once

#include <stdio.h>
#include <ctype.h>
#include "product.h"

#define MAX_SIZE 255

int isValidBarcode(const char* str);
int checkDigitsCount(const char* str);
int isLowercase(const char* str);
int IsAlphanumeric(const char* str);
int isValidCharacterPosition(const char* str);
int isValidAddressFormat(const char* str);
int isValidAddressSections(const char* str);
int validTokens(const char* str);
int isValidStreetNumber(const char* str);
char* fixAddressString(char* str);
