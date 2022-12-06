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
void customerPay(Supermarket* pSuperMarket);
void printProductType(const Supermarket* pSupermarket);

// extra / helpers
void customerCheckout(Supermarket* pSupermarket, char* name, int customerPos);
int checkProductExists(const Supermarket* pSupermarket, const char* barcode, int* productPos);
int checkCustomerExists(const Supermarket* pSupermarket, char* pCustomerName, int* customerPos);
void deleteSuperMarket(Supermarket* pSupermarket);
void addProductHelper(Supermarket* pSupermarket, char* barcode);
void addCustomerHelper(Supermarket* pSupermarket, char* name);
void returnShoppingCart(Supermarket* pSupermarket, int customerPos);
int getProductPos(Supermarket* pSupermarket, Shoppingitem item);