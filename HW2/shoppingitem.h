#pragma once

#include "product.h"
#include "stringfuncs.h"

typedef struct {
	char* barcode;
	float price;
	int amount;
}Shoppingitem;

void printShoppingItem(const Shoppingitem* pShoppingItem);
void initShoppingItem(Shoppingitem* pShoppingItem);
void insertShoppingItem(Shoppingitem* pShoppingItem);