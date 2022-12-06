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

// main funcs
void initSuperMarket(Supermarket* pSupermarket);
void printMarket(const Supermarket* pSupermarket);
void addProduct(Supermarket* pSupermarket);
void addCustomer(Supermarket* pSupermarket);
void customerShopping(Supermarket* pSupermarket);
void printCustomerShoppingCart(const Supermarket* pSupermarket);
void customerPay(const Supermarket* pSuperMarket);
void printProductType(const Supermarket* pSupermarket);

// extra / helpers
void customerCheckout(const Supermarket* pSupermarket, const char* name, int customerPos);
int checkProductExists(const Supermarket* pSupermarket, const char* barcode, int* productPos);
int checkCustomerExists(const Supermarket* pSupermarket, char* pCustomerName, int* customerPos);
char* getCustomerNameToShop(const Supermarket* pSupermarket);
int checkSupermarketStock(const Supermarket* pSupermarket);
void deleteSuperMarket(Supermarket* pSupermarket);
void customerShoppingHelper(Supermarket* pSupermarket, const char* customerName);
void addProductHelper(Supermarket* pSupermarket, const char* barcode);
void addCustomerHelper(Supermarket* pSupermarket, const char* name);
int getBarcodePosition(const Supermarket* pSupermarket, const char* barcode);
int getProductPos(const Supermarket* pSupermarket, const Shoppingitem item);
void printCustomers(const Supermarket* pSupermarket);