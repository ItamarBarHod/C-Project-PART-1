#include "shoppingitem.h"

void printShoppingItem(const Shoppingitem* pShoppingItem)
{
	printf("BARCODE: %s, Price: %.2f, Stock: %d\n", pShoppingItem->barcode, pShoppingItem->price, pShoppingItem->amount);
}

Shoppingitem* initShoppingItem()
{
	Shoppingitem* tempItem = (Shoppingitem*)malloc(sizeof(Shoppingitem));
	if (tempItem == NULL)
	{
		printf("MEMORY ERROR\n");
		return NULL;
	}
	tempItem->barcode = NULL;
	return tempItem;
}

void freeShoppingItem(Shoppingitem* pShoppingitem)
{
	free(pShoppingitem->barcode);
}
