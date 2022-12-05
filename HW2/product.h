#pragma once

#include "stringfuncs.h"
#include "userinput.h"

#define PRODUCT_SIZE 21
#define BARCODE_SIZE 8

typedef enum { eShelf, eFrozen, eFridge, eFruitVegetable, eNofEnum } productType;
static const char* productTypes[eNofEnum] = { "Shelf", "Frozen", "Fridge", "FruitVegetable" };


typedef struct {
	char* productName;
	char* barcode;
	productType type;
	float price;
	int stock;
}Product;


void printProduct(const Product* pProduct);
void getProductData(Product* pProduct, char* barcode);
void initProduct(Product* pProduct);