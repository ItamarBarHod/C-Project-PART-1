#pragma once
#include "shoppingitem.h"

typedef struct {
	Shoppingitem* itemsArr;
	int itemsArrSize;
}Shoppingcart;

void printShoppingCart(const Shoppingcart* pShoppingCart);
int calcShoppingCart(const Shoppingcart* pShoppingCart);
void addItemToCart(Shoppingcart* pShoppingCart, const Shoppingitem* pShoppingitem);
int getShoppingcartSize(const Shoppingcart* pShoppingCart);
int checkBarcodeExists(const Shoppingitem* pShoppingItem);
void deleteShoppingCart(Shoppingcart* pShoppingCart);