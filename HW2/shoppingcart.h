#pragma once

#include <stdlib.h>
#include "shoppingitem.h"

typedef struct {
	Shoppingitem* itemsArr;
	int shoppingCartSize;
}Shoppingcart;

void printShoppingCart(const Shoppingcart* pShoppingCart);
void addItemToCart(Shoppingcart* pShoppingCart, Product* pProduct);
double calcShoppingCart(const Shoppingcart* pShoppingCart);
void deleteShoppingCart(Shoppingcart* pShoppingCart);
Shoppingcart* initShoppingCart();