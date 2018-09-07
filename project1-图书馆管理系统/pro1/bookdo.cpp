#include<iostream>
#include<fstream>
#include<cstring>
#include<cstdlib>
#include"book.h"
#include"book.cpp"

using namespace std;

int total;
Book bookline[100];
bool did;
const char * file = "library.txt";
int exit();//����Book���������ж������ҵ���Ŀ�Ƿ���� 
void read_the_file();
void save_the_change();
int show_choice();
void do1();			//���� 
void do2();			//���� 
void do3();			//���� 
void do4();			//������ 
void do5();			//ɾ���� 
void newbook(char * s);		//�µ����� 

int main() {//������ 
	read_the_file();
	int choice;
	int ID;
	cout << "Welcome to this systerm.\n";
	cout << "Now, please enter you student ID: ";
	cin >> ID;
	system("pause");
	cout << "Hello, " << ID << endl;
	choice = show_choice();
	while (choice) {
		if (choice == 1) {
			do1();
		}else if (choice == 2) {
			do2();
		} else if (choice == 3) {
			do3();
		} else if (choice == 4) {
			do4();
		} else if (choice == 5) {
			do5();
		} else {
			cout << "Please enter one number from 0 to 5.\n";
		}
		save_the_change();//�����޸� 
		system("pause");
		cin.get();
		system("cls");
		choice = show_choice();
	}
	cout << "End up!\n";
	cout << "We are waiting for your coming next time.\n";
	return 0;
}


//���ļ��е����ݶ��洢��Book�������� 
void read_the_file() {
	ifstream fin;//����ifstream���� 
	fin.open(file);//���ļ� 
	fin >> total;//�õ��ܵ����ж����� 
	fin.get();//�����ֺ�Ļ��ж�ȡ�� 
	int i;
	int m_no, m_sum, m_borrow, m_left;
	char s[30];
	for (i = 0; i < total; i++) {
		fin.getline(s, 30);//�������ȴ浽һ����ʱ������
		bookline[i].setName(s);//���������Ƶ�����ȥ 
		fin >> m_no;//�������ȴ浽һ����ʱ������
		fin.get();//������ȥ�� 
		bookline[i].setNo(m_no);//�����Ÿ��Ƶ�����ȥ
		fin >> m_sum;//���������ȴ浽һ����ʱ������
		fin.get();//������ȥ�� 
		bookline[i].setSum(m_sum);//���������Ƶ�����ȥ 
		fin >> m_borrow;
		fin.get();
		bookline[i].setBorrow(m_borrow);
		fin >> m_left;
		fin.get();
		bookline[i].setLeft(m_left);
	}
	fin.close();//�ر��ļ� 
}

//���޸ĺ�������ٴε����ļ� 
void save_the_change() {
	ofstream fout;//����һ��ofstream����
	int i;
	fout.open(file);
	fout << total << endl;
	for (i = 0; i < total; i++) {
		if (bookline[i].getSum() != 0) {		//����Ϊ0����ɾ�����׵��Ѿ��������� 
			fout << bookline[i].getName() << endl;
			fout << bookline[i].getNo() << endl;
			fout << bookline[i].getSum() << endl;
			fout << bookline[i].getBorrow() << endl;
			fout << bookline[i].getLeft() << endl;
		}
	}
	fout.close();
}



int exitm(int m_no) {
	did = false;//���Ȼ��ɲ����� 
	int i;
	int h = 0;
	for (i = 0; i < total; i++) {
		if(bookline[i].getNo() == m_no&&bookline[i].getSum() != 0) {//�ҵ���Ӧ���鲢����������Ϊ0 
			h = 1;
			break; 
		}
	}
	if (h == 1) {
		did = true;
		return i;
	} else {
		return 0;
	}
}



int show_choice() {//ѡ�������Ŀ 
	int m;
	cout << "Please choose what you want to do:\n"
	<< "enter 0 to end up\n"
	<< "enter 1 to search for some books\n"
	<<  "enter 2 to borrow books\n"
	<< "enter 3 to return books\n"
	<<"enter 4 to add books\n"
	<< "enter 5 to delete books\n";
	cin >> m;
	cin.get();//����������еĻ��ж�ȡ��
	return m;
}

void newbook(char * s) {
	int m;
	m = total - 1;
	bookline[m].setName(s);
	bookline[m].setNo(total);
	bookline[m].setSum(1);
	bookline[m].setBorrow(0);
	bookline[m].setLeft(1);
} 



void do1() {
	cout << "Please enter the book's NO:\n";
	int m_no;
	cin >> m_no;
	cin.get();
	int m;
	m = exitm(m_no);
	if (did == true) {
		cout << "We find it!\n";
		bookline[m].show_();
	} else {
		cout << "Sorry. We cannot find the book.\n";
	}
}
void do2() {
	cout << "Please enter the book's NO:\n";
	int m_no;
	cin >> m_no;
	cin.get();
	int m;
	m = exitm(m_no);
	if (did == true) {
		if (bookline[m].getLeft() == 0) {
			cout << "Sorry. All of this kind of books had been borrowed.\n";
		} else {
			bookline[m].borrow_();
			cout << "Operation succeed\nYou have borrowed it from our library.\n";
		}
	} else {
		cout << "Sorry. We cannot find the book.\n";
	}
}
void do3() {
	cout << "Please enter the book's NO:\n";
	int m_no;
	cin >> m_no;
	cin.get();
	int m;
	m = exitm(m_no);
	if (did == true) {
		bookline[m].return_();
		cout << "Operation succeed\nYou have returned it to our library.\n";
	} else {
		cout << "Sorry. We cannot find the book.\n";
	}
}
void do4() {
	did = false;
	cout << "Please enter the book's name.\n";//������ 
	char s[30];
	cin.getline(s, 30);//�õ����� 
	int i, j;
	for (i = 0; i < total; i++) {//һ��һ������ 
		if (strcmp(bookline[i].getName(), s) == 0) {//�ַ�����ͬ 
			 did = true;
			 break;
		}
	}
	if (did == true) {//ԭ�����Ȿ����� 
		bookline[i].add_();
		cout << "We find that this kind of book had exited, so we add it!\n";
	} else {//�½�һ����Ŀ
		cout << "It is a new kind of book, so we create it.\n";
		total++;//����������һ 
		newbook(s); 
	}
}
void do5() {
	cout << "Please enter the book's NO:\n";
	int m_no;
	cin >> m_no;
	cin.get();
	int m;
	m = exitm(m_no);
	if (did == true) {
		if (bookline[m].getLeft() == 0) {
			cout << "Sorry! This kind of books had all been borrowed, so we can't delete at once.\n";
		} else {
			cout << "Operation succeed\nYou have delete one book.\n";
			bookline[m].delete_();
		}
	} else {
		cout << "Sorry! We can find this book.\n";
	}
}
