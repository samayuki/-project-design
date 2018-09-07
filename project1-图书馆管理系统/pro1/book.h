#ifndef BOOK_H_
#define BOOK_H_
#include<iostream>
#include<cstring>
class Book {
	int no;//图书编号 
	char name[30];//书名 
	int sum;//同样的书的总数 
	int borrow;//借出的书的数量 
	int left;//还未被借出的书的数量
	public:
	void show_();//查询后显示书的信息 
	void add_();//新增旧种  
	void delete_();//删除 
	void borrow_();//借出 
	void return_();//归还 
	void setName(char * s) {		//获取书名 
		strcpy(name, s);
	}
	void setNo(int m_no) {			//获取编号 
		no = m_no;
	}
	void setSum(int m_sum) {		//获取数量 
		sum = m_sum;
	}
	void setBorrow(int m_borrow) {	//获取借出量 
		borrow = m_borrow;
	}
	void setLeft(int m_left) {		//获取存量 
		left = m_left;
	}
	int getNo() {
		return no;					//读出书本编码 
	}
	int getSum() {					//读出书本数量 
		return sum;
	}
	int getLeft() {
		return left;
	}
	int getBorrow() {
		return borrow;
	}
	char * getName() {
		return name;
	}
};
#endif
