#pragma once

#include "product.h"
#include "customer.h"
#include "shoppingcart.h"
#include "address.h"

typedef struct {
	char* marketName;
	Address marketAddress;
	Customer* customerArr;
	int customerArrSize;
	Product** productArr;
	int productArrSize;
}Supermarket;

void initSuperMarket(Supermarket* pSupermarket);
void printMarket(const Supermarket* pSupermarket);
void addProduct(Supermarket* pSupermarket);
void addCustomer(Supermarket* pSupermarket);
void startPurchasing(Supermarket* pSupermarket);
void printShoppingCart(const Supermarket* pSupermarket);
void customerPayment(Supermarket* pSuperMarket);
void printProductType(const Supermarket* pSupermarket);

int checkProductExists(const Supermarket* pSupermarket, const Product* pProduct);
int checkCustomerExists(const Supermarket* pSupermarket, char* pCustomerName);
void updateStock(Supermarket* pSupermarket, Product** productArr, int numOfItems);
void checkOut(Supermarket* pSupermarket, Customer* pCustomer);
void deleteSuperMarket(Supermarket* pSupermarket); // loop productArr