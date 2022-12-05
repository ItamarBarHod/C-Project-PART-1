#include "product.h"

void printProduct(const Product* pProduct) // CHECK WORKS PROPERLY
{
	printf("%s %s %s %f %d\n", pProduct->productName, pProduct->barcode, productTypes[pProduct->type], pProduct->price, pProduct->stock);
}
void getProductData(Product* pProduct, char* barcode)
{
	printf("please enter a product name, maximum size %d\n", PRODUCT_SIZE - 1);
	getNameFromUser(pProduct->productName, PRODUCT_SIZE);
	pProduct->barcode = barcode;
	pProduct->type = getProductTypeFromUser();
	printf("please enter the price\n");
	pProduct->price = getNumberFromUser();
	printf("please enter the amount (stock count)\n");
	pProduct->stock = (int)getNumberFromUser();
}

void initProduct(Product* pProduct)
{
	Product* tempProd = (Product*)malloc(sizeof(Product));
	tempProd->barcode = NULL;
	tempProd->productName = NULL;
	pProduct = *tempProd;
}