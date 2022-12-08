#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "product.h"
#include "customer.h"
#include "address.h"


typedef struct {
	char* marketName;
	Address marketAddress;
	Customer* customerArr;
	int customerArrSize;
	Product** productArr;
	int productArrSize;
}Supermarket;

void createSuperMarket(Supermarket* pSupermarket);

// main funcs
void printMarket(const Supermarket* pSupermarket);
void addProduct(Supermarket* pSupermarket);
void addCustomer(Supermarket* pSupermarket);
void customerShopping(Supermarket* pSupermarket);
void printCustomerShoppingCart(const Supermarket* pSupermarket);
void customerCheckout(const Supermarket* pSuperMarket);
void printProductType(const Supermarket* pSupermarket);
void deleteSuperMarket(Supermarket* pSupermarket);

// helpers / extra
// 1: printMarket
void printCustomers(const Supermarket* pSupermarket);
// 2: addProduct
void addProductHelper(Supermarket* pSupermarket, Product* pProduct);
void addStockToProduct(Supermarket* pSupermarket, Product* pProduct);
// 3: addCustomer
void addCustomerHelper(Supermarket* pSupermarket, Customer* pCustomer);
// 4: customerShopping
void customerShoppingHelper(Supermarket* pSupermarket, Customer* pCustomer);
int getValidBarcodeAndPos(const Supermarket* pSupermarket);
int checkBarcodeExists(const Supermarket* pSupermarket, const char* barcode);
void putItemInCustomerCart(Supermarket* pSupermarket, const Customer* pCustomer, int numberToPurchase, int productPos);
// 5: printCustomerShoppingCart - none
// 6: customerCheckout
void customerCheckoutHelper(const Supermarket* pSupermarket, const Customer* pCustomer);
// 7: printProductType
void printProductTypeHelper(const Supermarket* pSupermarket, int type);

// general functions
int getSupermarketEntireStock(const Supermarket* pSupermarket);
Product* checkProductExists(const Supermarket* pSupermarket, const Product* pProduct);
Customer* checkCustomerExists(const Supermarket* pSupermarket, const Customer* pCustomer);
int getProductPos(const Supermarket* pSupermarket, const Product* pProduct);
int validMarket(Supermarket* pSupermarket);