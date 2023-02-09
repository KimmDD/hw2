#include <sstream>
#include <iomanip>
#include "clothing.h"
#include "util.h"

using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, std::string size, std::string brand): Product(category, name, price, qty), sizeName_(size), brandName_(brand)
{

}

Clothing::~Clothing()
{

}

std::set<std::string> Clothing::keywords() const
{ // create a new set 
  set<std::string> results_keywords;
  // insert keywords  
	set<std::string> clothing_name = parseStringToWords(convToLower(name_));
	results_keywords.insert(clothing_name.begin(), clothing_name.end());
	set<std::string> brand_name = parseStringToWords(convToLower(brandName_));
	results_keywords.insert(brand_name.begin(), brand_name.end());
	// return set 
	return results_keywords;

}

std::string Clothing::displayString() const
{
	std::string clothing_info;
	clothing_info += name_;
	clothing_info += "\n";
	clothing_info += "Size: ";
	clothing_info += sizeName_;
	clothing_info += " Brand: ";
	clothing_info += brandName_;
	clothing_info += "\n";
	clothing_info += to_string(price_); 
	clothing_info += " ";
	clothing_info += to_string(qty_); 
	clothing_info += " left.";

	return clothing_info;
}

void Clothing::dump(std::ostream& os) const
{
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << sizeName_ << "\n" << brandName_ << endl;

}