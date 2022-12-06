#include "product.h"

void printProduct(const Product* pProduct) // CHECK WORKS PROPERLY
{
	printf("%s %s %s %.2f %d\n", pProduct->productName, pProduct->barcode, productTypes[pProduct->type], pProduct->price, pProduct->stock);
}
void insertProductData(Product* pProduct, char* barcode)
{
	printf("please enter a product name, maximum size %d\n", PRODUCT_SIZE - 1);
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