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
int exit();//查找Book类数组以判断所查找的书目是否存在 
void read_the_file();
void save_the_change();
int show_choice();
void do1();			//查书 
void do2();			//借书 
void do3();			//还书 
void do4();			//新增书 
void do5();			//删除书 
void newbook(char * s);		//新的种类 

int main() {//主函数 
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
		save_the_change();//保存修改 
		system("pause");
		cin.get();
		system("cls");
		choice = show_choice();
	}
	cout << "End up!\n";
	cout << "We are waiting for your coming next time.\n";
	return 0;
}


//将文件中的数据都存储在Book类数组中 
void read_the_file() {
	ifstream fin;//创建ifstream对象 
	fin.open(file);//打开文件 
	fin >> total;//得到总的书有多少种 
	fin.get();//将数字后的换行读取掉 
	int i;
	int m_no, m_sum, m_borrow, m_left;
	char s[30];
	for (i = 0; i < total; i++) {
		fin.getline(s, 30);//将书名先存到一个临时数组中
		bookline[i].setName(s);//将书名复制到类中去 
		fin >> m_no;//将书编号先存到一个临时变量中
		fin.get();//将换行去掉 
		bookline[i].setNo(m_no);//将书编号复制到类中去
		fin >> m_sum;//将书总数先存到一个临时变量中
		fin.get();//将换行去掉 
		bookline[i].setSum(m_sum);//将书量复制到类中去 
		fin >> m_borrow;
		fin.get();
		bookline[i].setBorrow(m_borrow);
		fin >> m_left;
		fin.get();
		bookline[i].setLeft(m_left);
	}
	fin.close();//关闭文件 
}

//将修改后的数据再次导入文件 
void save_the_change() {
	ofstream fout;//创建一个ofstream变量
	int i;
	fout.open(file);
	fout << total << endl;
	for (i = 0; i < total; i++) {
		if (bookline[i].getSum() != 0) {		//总数为0代表删除彻底的已经不存在了 
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
	did = false;//首先化成不存在 
	int i;
	int h = 0;
	for (i = 0; i < total; i++) {
		if(bookline[i].getNo() == m_no&&bookline[i].getSum() != 0) {//找到相应的书并且其总量不为0 
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



int show_choice() {//选择操作项目 
	int m;
	cout << "Please choose what you want to do:\n"
	<< "enter 0 to end up\n"
	<< "enter 1 to search for some books\n"
	<<  "enter 2 to borrow books\n"
	<< "enter 3 to return books\n"
	<<"enter 4 to add books\n"
	<< "enter 5 to delete books\n";
	cin >> m;
	cin.get();//将输入队列中的换行读取掉
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
	cout << "Please enter the book's name.\n";//增加书 
	char s[30];
	cin.getline(s, 30);//得到书名 
	int i, j;
	for (i = 0; i < total; i++) {//一种一种书找 
		if (strcmp(bookline[i].getName(), s) == 0) {//字符串相同 
			 did = true;
			 break;
		}
	}
	if (did == true) {//原来有这本书存在 
		bookline[i].add_();
		cout << "We find that this kind of book had exited, so we add it!\n";
	} else {//新建一个书目
		cout << "It is a new kind of book, so we create it.\n";
		total++;//书种总数加一 
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
