#pragma once

#include <stdlib.h>
#include "shoppingitem.h"

typedef struct {
	Shoppingitem* itemsArr;
	int shoppingCartSize;
}Shoppingcart;

void printShoppingCart(const Shoppingcart* pShoppingCart);
void addItemToCart(Shoppingcart* pShoppingCart, const Shoppingitem* pShoppingitem);
void returnShoppingCart(Shoppingcart* pShoppingCart);
double calcShoppingCart(const Shoppingcart* pShoppingCart);
Shoppingcart* initShoppingCart();