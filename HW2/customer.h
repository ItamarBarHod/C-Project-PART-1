#pragma once

#include "shoppingcart.h"
#include "stringfuncs.h"

typedef struct {
	char* name;
	Shoppingcart cart;
}Customer;

void printCustomer(const Customer* pCustomer);
void insertCustomerData(Customer* pCustomer, char* name);
void initCustomer(Customer* pCustomer);