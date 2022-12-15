#include "shoppingcart.h"

void printShoppingCart(const Shoppingcart* pShoppingCart)
{
	for (int i = 0; i < pShoppingCart->shoppingCartSize; i++)
	{
		printShoppingItem(pShoppingCart->itemsArr[i]);
	}
	printf("\n");
}

Shoppingcart* initShoppingCart()
{
	Shoppingcart* tempCart = (Shoppingcart*)malloc(sizeof(Shoppingcart));
	if (!tempCart)
	{
		printf("MEMORY ERROR\n");
		return NULL;
	}
	tempCart->shoppingCartSize = 0;
	tempCart->itemsArr = NULL;
	return tempCart;
}

double calcShoppingCart(const Shoppingcart* pShoppingCart)
{
	double sum = 0;
	for (int i = 0; i < pShoppingCart->shoppingCartSize; i++)
	{
		int amount = pShoppingCart->itemsArr[i]->amount;
		double price = pShoppingCart->itemsArr[i]->price;
		sum += amount * price;
	}
	return sum;
}

void deleteShoppingCart(Shoppingcart* pShoppingCart)
{
	for (int i = 0; i < pShoppingCart->shoppingCartSize; i++)
	{
		freeShoppingItem(pShoppingCart->itemsArr[i]);
	}
	free(pShoppingCart->itemsArr);
	pShoppingCart->shoppingCartSize = 0;
	pShoppingCart = NULL;
}

int addItemToCart(Shoppingcart* pShoppingCart, const Product* pProduct, int numberToPurchase) // check works
{
	int cartSize = pShoppingCart->shoppingCartSize;
	Shoppingitem** tempArr = (Shoppingitem**)realloc(pShoppingCart->itemsArr, (cartSize + 1) * sizeof(Shoppingitem*));
	if (!tempArr)
	{
		printf("MEMORY ERROR\n");
		return 0;
	}
	Shoppingitem* newItem = initShoppingItem(); // malloc
	if (!newItem)
	{
		printf("MEMORY ERROR\n");
		return 0;
	}
	tempArr[cartSize] = newItem;
	tempArr[cartSize]->amount = numberToPurchase;
	tempArr[cartSize]->price = pProduct->price;
	tempArr[cartSize]->barcode = _strdup(pProduct->barcode); // malloc
	if (tempArr[cartSize]->barcode == NULL)
	{
		printf("MEMORY ERROR\n");
		return 0;
	}
	pShoppingCart->shoppingCartSize++;
	pShoppingCart->itemsArr = tempArr;
	return 1;
}

int checkItemExists(const Shoppingcart* pShoppingCart, const Product* pProduct)
{
	for (int i = 0; i < pShoppingCart->shoppingCartSize; i++)
	{
		int equal = strcmp(pShoppingCart->itemsArr[i]->barcode, pProduct->barcode);
		if (equal == 0)
		{
			return 1;
		}
	}
	return 0;
}

int getItemPos(const Shoppingcart* pShoppingCart, const Product* pProduct)
{
	for (int i = 0; i < pShoppingCart->shoppingCartSize; i++)
	{
		int equal = strcmp(pShoppingCart->itemsArr[i]->barcode, pProduct->barcode);
		if (equal == 0)
		{
			return i;
		}
	}
	return -1;
}