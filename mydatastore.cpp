#include <sstream>
#include <iomanip>
#include <set>
#include <vector>
#include "mydatastore.h"
#include "util.h"

using namespace std;

Mydatastore::Mydatastore()
{
}

Mydatastore::~Mydatastore()
{	
	//delete
	for(auto it = Product_list.begin(); it != Product_list.end(); ++it) {
        delete *it;
  }
	for(auto it = User_list.begin(); it != User_list.end(); ++it) {
        delete *it;
  }

}

void Mydatastore::addProduct(Product* p)
{
	Product_list.insert(p);

	std::set<string> keyword_list = p -> keywords();

	for(set<string>::iterator it=keyword_list.begin(); it!= keyword_list.end(); ++it){
		//  do not have keywords
		if(Search_list.find(*it) == Search_list.end()){
			set<Product*> temp;
			temp.insert(p);
			Search_list.insert(make_pair((*it), temp));
		}
		// have keywords 
		else{
			Search_list[*it].insert(p);
		}
	}
	
}

void Mydatastore::addUser(User* u)
{
	User_list.insert(u);
	Name_list.insert(make_pair(u -> getName(), u));
}

std::vector<Product*> Mydatastore::search(std::vector<std::string>& terms, int type)
{ 
	std::set<Product*> curr;
	std::vector<Product*> results;
	bool first = true;
	for (std::vector<std::string>::iterator it = terms.begin(); it != terms.end(); ++it){
		if(Search_list.find(*it) != Search_list.end()){
			if (first){
				curr = Search_list[*it];
				first = false;
			} else {
				if (type == 0){ // AND
					curr = setIntersection(curr, Search_list[*it]);
				} else { // OR
          curr = setUnion(curr, Search_list[*it]);
				}
			}
		}
	}

	for (std::set<Product*>::iterator it = curr.begin(); it!= curr.end(); ++it){
		results.push_back(*it);
	}

	return results;
}

void Mydatastore::AddCart(std::string u, Product* p)
{
	
		if(Name_list.find(u) == Name_list.end()){
			std::cout << "Invalid request" << std::endl;
		}
		else{
			if(Cart.find(u) != Cart.end()){ 
				// find the username
				Cart[u].push_back(p);
		  }
			else{
				// not find username
				std::vector<Product*> P;
				P.push_back(p);
				Cart.insert(make_pair(u,P));
			}	

		}
			
}

void Mydatastore::ViewCart(std::string u)
{
	int count = 1;
	// if cannot find the username
	if(Cart.find(u)== Cart.end()){
		std::cout << "Invalid username" << std::endl;
	}else{
		for (std::vector<Product*>::iterator it = Cart[u].begin(); it != Cart[u].end(); ++it){
			std::cout << "Item " << count << std::endl;
			std::cout << (*it) -> displayString() << std::endl;
			count ++;
		}
	}
	
}

void Mydatastore::BuyCart(std::string u)
{
	std::vector<Product*> NotBuy_List; // create a set contains not buy products
  
	if(Cart.find(u) != Cart.end()){
		for (std::vector<Product*>::iterator it = Cart[u].begin(); it != Cart[u].end(); ++it){
		double price = (*it) -> getPrice();
		// item is not in stock or the user does not have enough credit
			if((*it) -> getQty() == 0 || Name_list[u] -> getBalance() < price ){
				NotBuy_List.push_back(*it);
				continue;
			} 
			else{
				(*it)->subtractQty(1);
				Name_list[u] -> deductAmount(price);
			}
	  }
	}
	else{
		std::cout << "Invalid username" << std::endl;
	}

	Cart[u] = NotBuy_List; // update the cart for this user
}

void Mydatastore::dump(std::ostream& ofile)
{
	ofile << "<products>" << std::endl;

	for (std::set<Product*>::iterator it = Product_list.begin(); it != Product_list.end(); ++it){
		(*it) -> dump(ofile);

	}
	ofile << "</products>" << std::endl;

	ofile << "<users>" << std::endl;

	for (std::set<User*>::iterator it = User_list.begin(); it != User_list.end(); ++it){
		(*it) -> dump(ofile);
	}

	ofile << "</users>" << std::endl;

}

