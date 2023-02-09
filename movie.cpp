#include <sstream>
#include <iomanip>
#include "movie.h"
#include "util.h"

using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty, std::string genre, std::string rating): Product(category, name, price, qty), genreName_(genre), ratingName_(rating)
{

}

Movie::~Movie()
{

}

std::set<std::string> Movie::keywords() const
{ // create a new set 
  set<std::string> results_keywords;
  // insert keywords 
	set<std::string> movie_name = parseStringToWords(convToLower(name_));
	results_keywords.insert(movie_name.begin(), movie_name.end());
  // insert keywords 
	results_keywords.insert(convToLower(genreName_));
	// return set 
	return results_keywords;

}

std::string Movie::displayString() const
{
	std::string movie_info;
	movie_info += name_;
	movie_info += "\n";
	movie_info += "Genre: ";
	movie_info += genreName_;
	movie_info += " Rating: ";
	movie_info += ratingName_;
	movie_info += "\n";
	movie_info += to_string(price_);
	movie_info += " ";
	movie_info += to_string(qty_);
	movie_info += " left.";

	return movie_info;
}

void Movie::dump(std::ostream& os) const
{
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genreName_ << "\n" << ratingName_ << endl;

}