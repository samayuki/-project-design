#ifndef BOOK_H_
#define BOOK_H_
#include<iostream>
#include<cstring>
class Book {
	int no;//ͼ���� 
	char name[30];//���� 
	int sum;//ͬ����������� 
	int borrow;//������������ 
	int left;//��δ��������������
	public:
	void show_();//��ѯ����ʾ�����Ϣ 
	void add_();//��������  
	void delete_();//ɾ�� 
	void borrow_();//��� 
	void return_();//�黹 
	void setName(char * s) {		//��ȡ���� 
		strcpy(name, s);
	}
	void setNo(int m_no) {			//��ȡ��� 
		no = m_no;
	}
	void setSum(int m_sum) {		//��ȡ���� 
		sum = m_sum;
	}
	void setBorrow(int m_borrow) {	//��ȡ����� 
		borrow = m_borrow;
	}
	void setLeft(int m_left) {		//��ȡ���� 
		left = m_left;
	}
	int getNo() {
		return no;					//�����鱾���� 
	}
	int getSum() {					//�����鱾���� 
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
