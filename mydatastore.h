#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <iostream>
#include <string>
#include <set>
#include <map>
#include <vector>
#include <algorithm>
#include "datastore.h"

class Mydatastore: public DataStore{
	public:
	  Mydatastore();
		~Mydatastore();
	  void addProduct(Product* p);
		void addUser(User* u);
		std::vector<Product*> search(std::vector<std::string>& terms, int type);
		void AddCart(std::string u, Product* p);
		void ViewCart(std::string u);
		void BuyCart(std::string u);
		void dump(std::ostream& ofile);
	private:
	  std::set<Product*> Product_list; // contains product
		std::set<User*> User_list; // contains product
		std::map<std::string, std::set<Product*>>Search_list;// get the product matches keywords
		std::map<std::string, User*>Name_list; // get the user matches the username
		std::map<std::string, std::vector<Product*>> Cart; // cart 

};
#endif