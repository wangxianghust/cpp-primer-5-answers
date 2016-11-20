#ifndef E21_H
#define E21_H

#include <iostream>
#include <string.h>

using namespace std;

class Sales_data;
istream &read(istream &is, Sales_data &item);

class Sales_data
{
friend Sales_data add(const Sales_data&, const Sales_data&);
friend ostream &print(ostream &os, const Sales_data &item);
friend istream &read(istream &is, Sales_data &item);
public:
	Sales_data() : units_sold(0), revenue(0) {}
	Sales_data(const string &s) : bookNo(s) {}
	Sales_data(const string &s, unsigned u, double n) : bookNo(s), units_sold(u), revenue(u*n) {}
	Sales_data(istream &);

	string isbn() const {return bookNo;}
	Sales_data &combine(const Sales_data &);



private:
	double avg_price() const;
	string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;
};

// non-member function
istream &read(istream &is, Sales_data &item) {
	double price = 0;
	is >> item.bookNo >> item.units_sold >> price;
	item.revenue = price * item.units_sold;
	return is;
}

ostream &print(ostream &os, const Sales_data &item) {
	os << item.isbn() << " " << item.units_sold << " " << item.revenue;
	return os;
}

// member functions
Sales_data& Sales_data::combine(const Sales_data& rhs) {
	units_sold += rhs.units_sold;
	revenue += rhs.revenue;
	return *this;
} 

Sales_data::Sales_data(istream &is) {
	read(is, *this);
}

#endif