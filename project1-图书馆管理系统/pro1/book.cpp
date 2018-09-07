#include<iostream>
#include"book.h"
using namespace std;
void Book::show_() {		//显示书本信息 
	cout << "Book name: 《" << name << "》\n"
	<< "Book number: " << no << endl
	<< "Total sum: " << sum << endl
	<< "Borrowed: " << borrow << endl
	<< "Left: " << left << endl;
}
//
void Book::add_() {				//新增一本书到已有的书种 
	sum += 1;
	left += 1;
}
//
void Book::delete_() {				//删除一本书 
	sum -= 1;
	left -= 1;
}
//
void Book::borrow_() {				//借出一本书 
	left -= 1;
	borrow += 1;
}
//
void Book::return_() {				//归还一本书 
	left += 1;
	borrow -= 1;
}
