#ifndef E44_H
#define E44_H

#include <memory>
using std::allocator;

#include <utility>
using std::pair;

#include <algorithm>
using std::for_each;

class String{
public:
	String():first(nullptr), last(nullptr) {}
	String(const char*);
	String(const String&);
	String& operator=(const String&);
	~String();
	char* begin() const { return first; }
	char* end() const { return last; }
	size_t size() const { return last - first; }
	void push_back(const char s);
private:
	static allocator<char> alloc;
	char* first;
	char* last;
private:
	// void chk_n_allocate();
	void free();
	// void reallocate();
	pair<char*, char*> alloc_n_copy(const char* b, const char* e);
	void alloc_n_move(const char* b, const char* e);
};

allocator<char> String::alloc = allocator<char>();

void String::alloc_n_move(const char* b, const char* e){
	auto newdata = alloc.allocate(e-b);
	auto dest = newdata;
	// for_each(first, last, [dest](char s){ alloc.construct(dest++, s) });
	for( ; first != last; ++first){
		alloc.construct(dest++, *first);
	}
	free();
}

pair<char*, char*> String::alloc_n_copy(const char* b, const char* e){
	auto newdata = alloc.allocate(e-b);
	auto dest = std::uninitialized_copy(b, e, newdata);
	return {newdata, dest};
}

void String::free(){
	if(first){
		for_each(first, last, [this](char& s) { alloc.destroy(&s); });
		alloc.deallocate(first, size());
	}
}

String::String(const char* s){
	auto start = s;
	while(*s != '\0'){
		++s;
	}
	auto ret = alloc_n_copy(start, s);
	first = ret.first;
	last = ret.second;
}

String& String::operator=(const String& s){
	auto ret = alloc_n_copy(s.first, s.last);
	free();
	first = ret.first;
	last = ret.second;
	return *this;
}

String::~String(){
	free();
}

void String::push_back(const char c){
	*last++ = c;
}

#endif