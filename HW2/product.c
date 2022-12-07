#include "product.h"

void printProduct(const Product* pProduct)
{
	printf("%-*s %-*s %-*s %-*.2f %d\n", 27, pProduct->productName, 9, pProduct->barcode, 16, productTypes[pProduct->type], 14, pProduct->price, pProduct->stock);
}
void insertProductData(Product* pProduct, char* barcode)
{
	printf("Please enter a product name, maximum size %d\n", PRODUCT_SIZE - 1);
	pProduct->productName = getNameFromUser(PRODUCT_SIZE);
	pProduct->barcode = barcode;
	pProduct->type = getProductTypeFromUser();
	printf("please enter the price\n");
	pProduct->price = getNumberFromUser();
	printf("please enter the amount (stock count)\n");
	pProduct->stock = (int)getNumberFromUser();
}

Product* initProduct()
{
	Product* tempProd = (Product*)malloc(sizeof(Product));
	if (tempProd == NULL)
	{
		printf("MEMORY ERROR\n");
		return NULL;
	}
	tempProd->barcode = NULL;
	tempProd->productName = NULL;
	return tempProd;
}

void freeProduct(Product* pProduct)
{
	free(pProduct->barcode);
	free(pProduct->productName);
	pProduct = NULL;
}

void printBarcodeInstructions()
{
	printf("Enter product barcode Code should be of 7 length exactly\n");
	printf("UPPER CASE letter and digits\n");
	printf("Must have 3 to 5 digits\n");
	printf("First and last chars must be UPPER CASE letter\n");
	printf("For example A12B40C\n\n");
}
