#pragma once

#define PRODUCT_SIZE 21
#define BARCODE_SIZE 8

typedef enum { eShelf, eFrozen, eFridge, eFruitVegetable, eNofEnum } pType;
static const pType* productType[eNofEnum] = { "Shelf", "Frozen", "Fridge", "FruitVegetable" };


typedef struct {
	char productName[PRODUCT_SIZE];
	char barcode[BARCODE_SIZE];
	pType type;
	float price;
	int stock;
}Product;

void printProduct(const Product* pProduct);
void initProduct(Product* pProduct);
