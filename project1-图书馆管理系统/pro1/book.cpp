#include<iostream>
#include"book.h"
using namespace std;
void Book::show_() {		//��ʾ�鱾��Ϣ 
	cout << "Book name: ��" << name << "��\n"
	<< "Book number: " << no << endl
	<< "Total sum: " << sum << endl
	<< "Borrowed: " << borrow << endl
	<< "Left: " << left << endl;
}
//
void Book::add_() {				//����һ���鵽���е����� 
	sum += 1;
	left += 1;
}
//
void Book::delete_() {				//ɾ��һ���� 
	sum -= 1;
	left -= 1;
}
//
void Book::borrow_() {				//���һ���� 
	left -= 1;
	borrow += 1;
}
//
void Book::return_() {				//�黹һ���� 
	left += 1;
	borrow -= 1;
}
