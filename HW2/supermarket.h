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
void productExists(Supermarket* pSupermarket, Product* pProduct);
Product* checkProductExists(const Supermarket* pSupermarket, Product* pProduct);
int getProductPosition(Supermarket* pSupermarket, Product* pProduct);
Customer* checkCustomerExists(const Supermarket* pSupermarket, Customer* pCustomer);
int getValidBarcodeAndPosition(const Supermarket* pSupermarket);
Customer* getCustomerToShop(const Supermarket* pSupermarket);
int validMarket(Supermarket* pSupermarket);
void putItemInCustomerCart(Supermarket* pSupermarket, int numberToPurchase, int barcodePosition, char* customerName);
int checkSupermarketStock(const Supermarket* pSupermarket);
void deleteSuperMarket(Supermarket* pSupermarket);
void customerShoppingHelper(Supermarket* pSupermarket, char* customerName);
void addProductHelper(Supermarket* pSupermarket, Product* pProduct);
void addCustomerHelper(Supermarket* pSupermarket, Customer* pCustomer);
int getBarcodePosition(const Supermarket* pSupermarket, const char* barcode);
int getProductPos(const Supermarket* pSupermarket, const char* barcode);
void printProductTypeHelper(Supermarket* pSupermarket, int type);
void printCustomers(const Supermarket* pSupermarket);