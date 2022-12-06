#pragma once

#include <string.h>
#include <stdlib.h>
#include "stringfuncs.h"
#include "address.h"

char* getAddressFromUser();
char* getNameFromUser(int maxStrSize);
char* getBarcodeFromUser();
float getNumberFromUser();
int getProductTypeFromUser();