#include "shoppingitem.h"

void printShoppingItem(const Shoppingitem* pShoppingItem)
{
	printf("BARCODE: %s, Price: %f, Stock: %d\n", pShoppingItem->barcode, pShoppingItem->price, pShoppingItem->amount);
}

void initShoppingItem(Shoppingitem* pShoppingItem)
{
	Shoppingitem* tempItem = (Shoppingitem*)malloc(sizeof(Shoppingitem));
	tempItem->barcode = NULL;
	pShoppingItem = *tempItem;
}

void insertShoppingItem(Shoppingitem* pShoppingItem)
{

}