#pragma once

#include <string.h>
#include "stringfuncs.h"

char* getAddressFromUser();
char* getNameFromUser(int maxStrSize);
char* getBarcodeFromUser();
float getNumberFromUser();
int getProductTypeFromUser();
int askUserToContinue();