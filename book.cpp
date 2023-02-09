#include <sstream>
#include <iomanip>
#include "book.h"
#include "util.h"

using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty, std::string aName, std::string bNumber): Product(category, name, price, qty), authorName_(aName), ISBNnumber_(bNumber)
{

}

Book::~Book()
{

}

std::set<std::string> Book::keywords() const
{ // create a new set 
  set<std::string> results_keywords;
  // insert keywords 
	set<std::string> book_name = parseStringToWords(convToLower(name_));
	results_keywords.insert(book_name.begin(), book_name.end());
	set<std::string> author_name = parseStringToWords(convToLower(authorName_));
	results_keywords.insert(author_name.begin(), author_name.end());
	results_keywords.insert(ISBNnumber_);
	// return set 
	return results_keywords;

}

std::string Book::displayString() const
{
	std::string book_info;
	book_info += name_;
	book_info += "\n";
	book_info += "Author: ";
	book_info += authorName_;
	book_info += " ISBN: ";
	book_info += ISBNnumber_;
	book_info += "\n";
	book_info += to_string(price_);
	book_info += " ";
	book_info += to_string(qty_);
	book_info += " left.";

	return book_info;
}

void Book::dump(std::ostream& os) const
{
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << ISBNnumber_ << "\n" << authorName_ << endl;

}