#pragma once

#include <stdlib.h>
#include "shoppingitem.h"

typedef struct {
	Shoppingitem* itemsArr;
	int shoppingCartSize;
}Shoppingcart;

Shoppingcart* initShoppingCart();
void printShoppingCart(const Shoppingcart* pShoppingCart);
void addItemToCart(Shoppingcart* pShoppingCart, Product* pProduct, int numberToPurchase);
double calcShoppingCart(const Shoppingcart* pShoppingCart);
int checkItemExists(Shoppingcart* pShoppingCart, Product* pProduct);
int getItemPos(Shoppingcart* pShoppingCart, Product* pProduct);
void deleteShoppingCart(Shoppingcart* pShoppingCart);
