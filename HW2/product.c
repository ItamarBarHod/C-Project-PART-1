#include "product.h"

void printProduct(const Product* pProduct)
{
	printf("%-*s %-*s %-*s %-*.2f %d\n", 27, pProduct->productName, 9, pProduct->barcode, 16, productTypes[pProduct->type], 14, pProduct->price, pProduct->stock);
}

void insertProductData(Product* pProduct)
{
	printf("Please enter a product name, maximum size %d\n", PRODUCT_SIZE - 1);
	pProduct->productName = getNameFromUser(PRODUCT_SIZE);
	if (!pProduct->productName)
	{
		return;
	}
	pProduct->type = getProductTypeFromUser();
	printf("Please enter the price: ");
	pProduct->price = getNumberFromUser();
	printf("Please enter the amount (stock count): ");
	pProduct->stock = (int)getNumberFromUser();
}

Product* createNewProduct()
{
	Product* tempProd = (Product*)malloc(sizeof(Product));
	if (!tempProd)
	{
		printf("MEMORY ERROR\n");
		return NULL;
	}
	printBarcodeInstructions();
	tempProd->barcode = getBarcodeFromUser(PRODUCT_SIZE);
	if (tempProd->barcode == NULL)
	{
		freeProduct(tempProd);
		return NULL;
	}
	tempProd->productName = NULL;
	return tempProd;
}

void freeProduct(Product* pProduct)
{
	free(pProduct->barcode);
	free(pProduct->productName);
}

void printBarcodeInstructions()
{
	printf("Enter product barcode Code should be of 7 length exactly\n");
	printf("UPPER CASE letter and digits\n");
	printf("Must have 3 to 5 digits\n");
	printf("First and last chars must be UPPER CASE letter\n");
	printf("For example A12B40C\n\n");
}
