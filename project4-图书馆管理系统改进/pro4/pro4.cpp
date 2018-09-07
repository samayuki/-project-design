#include<iostream>
#include<cstring>
#include<fstream>
#include<cstdlib>
#include<ctime>
using namespace std;
int book_total;
int user_total;
int lib_total;
int DEMP;	//用户对应下标 
string who;		//who = "user"或who = "librarian" 
//
string time_now();



//
class Record {		//记录 
	private:
		string name;	//书的记录则是借阅者的名字，借阅者的记录则是书名 
		string date;	//借阅时间 
		string limit;	//借阅期限 
	public:
		Record() {}
		void set_name(string s) {name = s;}
		string get_name() {return name;}
		void set_date(string s) {date = s;}
		string get_date() {return date;}
		void set_limit(string s) {limit = s;}
		string get_limit() {return limit;}
		friend ostream & operator<<(ostream & os, Record & te);
};
ostream & operator<<(ostream & os, Record & te) {
	os << te.get_name() << endl;
	os << te.get_date() << endl;
	os << te.get_limit() << endl;
	return os;
}
//
class Book {
	private:
		string name;		//书名 
		string author;		//作者
		string out_date;	//出版日期 
		string ISBN;		//国际标准书号
		int sum;			//书的总量
		int borrow;			//借出的书的数量 
		int left;			//还未被借出的书的数量 
		Record record[500];	//被借阅记录
		int record_num;		//记录条数 
	public:
		Book() {
			sum = borrow = left = record_num = 0;
		}
		void show_basic();		//查询后显示书的信息 
		void show_record();
		void borrow_(string s) {
			borrow++;
			left--;
			//更新记录
			string s1 = s;
			string s2 = time_now();
			string s3 = "一个月内归还";
			set_record(s1, s2, s3);
		}
		void return_() {
			borrow--;
			left++;
		}
		void set_name(string s) {name = s;}		//更改书名 
		string get_name() {return name;}		//返回书名 
		void set_author(string s) {author = s;}	//更改作者 
		string get_author() {return author;}	//返回作者 
		void set_out_date(string s) {out_date = s;}	//更改出版日期 
		string get_out_date() {return out_date;}	//返回出版日期 
		void set_ISBN(string s) {ISBN = s;}	//更改国际标准书号 
		string get_ISBN() {return ISBN;}	//返回国际标准书号 
		void set_sum(int m) {sum = m;}			//更改书的总量 
		int get_sum() {return sum;}				//返回书的总量 
		void set_borrow(int m) {borrow = m;}	//更改已借出书的数量 
		int get_borrow() {return borrow;}		//返回已借出书的总量 
		void set_left(int m) {left = m;}		//更改剩余书的数量 
		int get_left() {return left;}			//返回剩余书的总量 
		void set_record_num(int m) {record_num = m;}	//更改记录条数
		int get_record_num() {return record_num;}		//返回记录条数 
		void set_record(string s1, string s2, string s3) {	//新增记录 
			record[record_num].set_name(s1);
			record[record_num].set_date(s2);
			record[record_num].set_limit(s3);
			record_num++;
		}
		Record get_record(int t) {		//返回第t条记录 
			return record[t];
		}
};
void Book::show_basic() {		//显示书本信息 
	cout << "书名：" << name << endl
		<< "作者：" << author << endl
		<< "出版日期：" << out_date << endl
		<< "ISBN：" << ISBN << endl
		<< "总数量：" << sum << endl
		<< "现存量：" << left << endl
		<< "已借出量：" << borrow << endl;
		
}
void Book::show_record() {
	cout << "以下是借阅记录：" << endl;
	int i;
	for (i = 0; i < record_num; i++) {
		cout << "借阅者：" << record[i].get_name() << endl
			<< "借阅时间：" << record[i].get_date() << endl
			<< "借阅期限：" << record[i].get_limit() << endl << endl;
	}
}
// 
Book bookline[1000];
//
class User {
	string name;		//用户姓名 
	string password;	//密码
	string ID;			//用户ID  
	public:
		void set_name(string s) {name = s;}
		string get_name() {return name;}
		void set_password(string s) {password = s;}
		string get_password() {return password;}
		void set_ID(string s) {ID = s;}
		string get_ID() {return ID;}
		virtual ~User() {}
};
//
class normal_user : public User {
	private:
		Record user_record[200];
		int user_record_num;
	public:
		normal_user() {user_record_num = 0;}
		void set_user_record(string s1, string s2, string s3) {	//新增记录 
			user_record[user_record_num].set_name(s1);
			user_record[user_record_num].set_date(s2);
			user_record[user_record_num].set_limit(s3);
			user_record_num++;
		}
		Record get_user_record(int t) {		//返回第t条记录 
			return user_record[t];
		}
		int get_user_record_num() {return user_record_num;}
		
		void borrow_book(int t) {
			string s = this->get_name();
			bookline[t].borrow_(s);
			string s1 = bookline[t].get_name();
			string s2 = time_now();
			string s3 = "一个月内归还";
			set_user_record(s1, s2, s3);
		}
		void return_book(int t) {
			bookline[t].return_();
		}
		void search_my_record() {
			int i;
			for (i = 0; i < user_record_num; i++) {
				cout << "借阅书名：" << user_record[i].get_name() << endl
					 << "借阅时间：" << user_record[i].get_date() << endl
					 << "借阅期限：" << user_record[i].get_limit() << endl << endl;
			}
		}
};
class librarian : public User {
	//string black_list[100];		//黑名单 
};
//
normal_user userline[500];
librarian libline[100];
//
//
void read_the_file();		//读取文件内容 
void save_the_change();		//将内容写入文件 
int menu();					//初始界面 
int find_user();			//登录时查找普通用户 
int find_librarian();		//登录时查找管理员 
int create_user();			//注册普通用户 
int create_librarian();		//注册管理员 
int into_system(int choice);//进入系统 
int judge_book(string s);	//判断书名为s的书是否存在 
int user_func();			//普通用户的功能 
int lib_func();				//管理员的功能 
//
//
string time_now() {							//获取当前时间 
	time_t rawtime;
	struct tm* timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	char s[200];
	strftime(s, sizeof(s), "%Y年%m月%d日", localtime(&rawtime));
	return s;
}
//
void read_the_file() {
	ifstream fin;//创建ifstream对象 
	//读取书籍信息 
	fin.open("E:\\library.txt");//打开文件 
	fin >> book_total;//得到总的书有多少种 
	fin.get();//将数字后的换行读取掉 
	int i, k;
	string m_name, m_author, m_date, m_ISBN, m_limit;
	int m_sum, m_borrow, m_left, m_record_num;
	for (i = 0; i < book_total; i++) {
		getline(fin, m_name);
		bookline[i].set_name(m_name);			//书名 
		getline(fin, m_author);
		bookline[i].set_author(m_author);		//作者 
		getline(fin, m_date);
		bookline[i].set_out_date(m_date);		//出版日期 
		getline(fin, m_ISBN);
		bookline[i].set_ISBN(m_ISBN);			//国际标准书号 
		fin >> m_sum;
		fin.get();
		bookline[i].set_sum(m_sum);				//书总数量
		fin >> m_borrow;
		fin.get();
		bookline[i].set_borrow(m_borrow);		//已借出量 
		fin >> m_left;
		fin.get();
		bookline[i].set_left(m_left);			//剩余量 
		fin >> m_record_num;
		fin.get();
		for (k = 0; k < m_record_num&&m_record_num != 0; k++) {
			getline(fin, m_name);
			getline(fin, m_date);
			getline(fin, m_limit);
			bookline[i].set_record(m_name, m_date, m_limit);	//借阅记录 
		}
		fin.get();
	}
	fin.close();//关闭文件 
	//读取普通用户信息 
	fin.open("E:\\normal_user.txt"); 
	fin >> user_total;
	fin.get();
	string m_secrt, m_id;
	for (i = 0; i < user_total; i++) {
		getline(fin, m_name);
		userline[i].set_name(m_name);
		getline(fin, m_secrt);
		userline[i].set_password(m_secrt);
		getline(fin, m_id);
		userline[i].set_ID(m_id);
		fin >> m_record_num;
		fin.get();
		for (k = 0; k < m_record_num&&m_record_num != 0; k++) {
			getline(fin, m_name);
			getline(fin, m_date);
			getline(fin, m_limit);
			userline[i].set_user_record(m_name, m_date, m_limit);
		}
		fin.get();
	}
	fin.close();
	//读取管理员信息 
	fin.open("E:\\librarian.txt");
	fin >> lib_total;
	fin.get();
	for (i = 0; i < lib_total; i++) {
		getline(fin, m_name);
		libline[i].set_name(m_name);
		getline(fin, m_secrt);
		libline[i].set_password(m_secrt);
		getline(fin, m_id);
		libline[i].set_ID(m_id);
		fin.get();
	}
	fin.close();
}
//将修改后的数据再次导入文件 
void save_the_change() {
	ofstream fout;//创建一个ofstream变量
	int i, k;
	fout.open("E:\\library.txt");
	fout << book_total << endl;
	for (i = 0; i < book_total + 1; i++) {
		if (bookline[i].get_sum() != 0) {		//总数为0代表删除彻底的已经不存在了 
			fout << bookline[i].get_name() << endl;
			fout << bookline[i].get_author() << endl;
			fout << bookline[i].get_out_date() << endl;
			fout << bookline[i].get_ISBN() << endl;
			fout << bookline[i].get_sum() << endl;
			fout << bookline[i].get_borrow() << endl;
			fout << bookline[i].get_left() << endl;
			fout << bookline[i].get_record_num() << endl;
			for (k = 0; k < bookline[i].get_record_num()&&bookline[i].get_record_num() != 0; k++) {
				Record A = bookline[i].get_record(k);
				fout << A.get_name() << endl;
				fout << A.get_date() << endl;
				fout << A.get_limit() << endl;
			}
			fout << endl;
		}
	}
	fout.close();
	//普通用户 
	fout.open("E:\\normal_user.txt");
	fout << user_total << endl;
	for (i = 0; i < user_total; i++) {
		fout << userline[i].get_name() << endl;
		fout << userline[i].get_password() << endl;
		fout << userline[i].get_ID() <<endl;
		fout << userline[i].get_user_record_num() << endl;
		for (k = 0; k < userline[i].get_user_record_num()&&userline[i].get_user_record_num() != 0; k++) {
			Record A = userline[i].get_user_record(k);
			fout << A.get_name() << endl;
			fout << A.get_date() << endl;
			fout << A.get_limit() << endl;
		}
		fout << endl;
	}
	fout.close();
	//管理员 
	fout.open("E:\\librarian.txt");
	fout << lib_total << endl;
	for (i = 0; i < lib_total; i++) {
		fout << libline[i].get_name() << endl;
		fout << libline[i].get_password() << endl;
		fout << libline[i].get_ID() <<endl;
		fout << endl;
	}
	fout.close();
}
//
int menu() {		//开始菜单 
	cout << "欢迎使用图书馆管理系统\n"
		 << "1.登录\n"
		 << "2.注册\n"
		 << "0.退出\n"
		 << "请选择你需要的操作对应的数字：";
	string te;
	getline(cin, te);
	while (te != "1"&&te != "2"&&te != "0") {
		cout << "输入有误！请重新输入操作对应数字：";
		getline(cin, te);
	}
	if (te == "1") {
		cout << "你选择了登录帐号\n";
		return 1;
	} else if (te == "2") {
		cout << "你选择了注册帐号\n";
		return 2;
	} else {
		cout << "你选择了退出系统\n";
		return 0;
	}
}
//
int find_user() {		//返回用户在userline中的下标 
	int i;
	int h = -1;
	string id, pass;
	cout << "请输入你的用户ID和密码：\n";
	cout << "ID  ：";
	getline(cin, id);
	cout << "密码：";
	getline(cin, pass);
	for (i = 0; i < user_total; i++) {
		if (id == userline[i].get_ID()) {
			h = -2;			//找到用户 
			if (pass == userline[i].get_password()) {
				h = i;		//密码正确 
				break;
			}
		}
	}
	while (h < 0) {
		if (h == -1) {
			cout << "你所输入的用户不存在，请重新输入：";
		} else {
			cout << "密码错误，请重新输入：";
		}
		cout << "ID  ：";
		getline(cin, id);
		cout << "密码：";
		getline(cin, pass);
		for (i = 0; i < user_total; i++) {
			if (id == userline[i].get_ID()) {
				h = -2;			//找到用户 
				if (pass == userline[i].get_password()) {
					h = i;		//密码正确 
					break;
				}
			}
		}
	}
	//成功进入 
	return h; 
}
//
int find_librarian() {
	int i;
	int h = -1;
	string id, pass;
	cout << "请输入你的用户ID和密码：\n";
	cout << "ID  ：";
	getline(cin, id);
	cout << "密码：";
	getline(cin, pass);
	for (i = 0; i < lib_total; i++) {
		if (id == libline[i].get_ID()) {
			h = -2;			//找到用户 
			if (pass == libline[i].get_password()) {
				h = i;		//密码正确 
				break;
			}
		}
	}
	while (h < 0) {
		if (h == -1) {
			cout << "你所输入的用户不存在，请重新输入：\n";
		} else {
			cout << "密码错误，请重新输入：\n";
		}
		cout << "ID  ：";
		getline(cin, id);
		cout << "密码：";
		getline(cin, pass);
		for (i = 0; i < lib_total; i++) {
			if (id == libline[i].get_ID()) {
				h = -2;			//找到用户 
				if (pass == libline[i].get_password()) {
					h = i;		//密码正确 
					break;
				}
			}
		}
	}
	//成功进入 
	return h; 
} 
//
int create_user() {					//注册后会自动登录，返回用户下标 
	int i, h = 0;
	string id, pass, m_name;
	cout << "请输入你的姓名：";
	getline(cin, m_name);
	cout << "请设置你的用户ID和密码：\n";
	cout << "ID  ：";
	getline(cin, id);
	cout << "密码：";
	getline(cin, pass);
	for (i = 0; i < user_total; i++) {
		if (id == userline[i].get_ID()) {
			h = -1;			//用户ID已被占用 
			break;
		}
	}
	while (h == -1) {
		h = 0;
		cout << "此ID已被占用，请重新设置：\n";
		cout << "ID  ：";
		getline(cin, id);
		cout << "密码：";
		getline(cin, pass);
		for (i = 0; i < user_total; i++) {
			if (id == userline[i].get_ID()) {
				h = -1;			//用户ID已被占用 
				break;
			}
		}
	}
	//设置新增 
	userline[user_total].set_ID(id);
	userline[user_total].set_password(pass);
	userline[user_total].set_name(m_name);
	user_total++;
	cout << "帐号创建成功，已自动登录。\n"; 
	return (user_total - 1);
}
//
int create_librarian() {					//注册后会自动登录，返回用户下标 
	int i, h = 0;
	string id, pass, m_name;
	cout << "请输入你的姓名：";
	getline(cin, m_name);
	cout << "请设置你的用户ID和密码：\n";
	cout << "ID  ：";
	getline(cin, id);
	cout << "密码：";
	getline(cin, pass);
	for (i = 0; i < lib_total; i++) {
		if (id == libline[i].get_ID()) {
			h = -1;			//用户ID已被占用 
			break;
		}
	}
	while (h == -1) {
		h = 0;
		cout << "此ID已被占用，请重新设置：\n";
		cout << "ID  ：";
		getline(cin, id);
		cout << "密码：";
		getline(cin, pass);
		for (i = 0; i < lib_total; i++) {
			if (id == libline[i].get_ID()) {
				h = -1;			//用户ID已被占用 
				break;
			}
		}
	}
	//设置新增 
	libline[lib_total].set_ID(id);
	libline[lib_total].set_password(pass);
	libline[lib_total].set_name(m_name);
	lib_total++;
	cout << "帐号创建成功，已自动登录。\n";
	return (lib_total - 1);
}
// 
int into_system(int choice) {		//返回用户下标 
	string m_id, m_password;
	int h;
	string a;
	if (choice == 1) {	//登录 
		cout << "你可以选择普通用户登录，或管理员登录：\n";
		cout << "1.普通用户登录\n";
		cout << "2.管理员登录\n";
		cout << "请输入你的选择：";
		getline(cin, a);
		while (a != "1"&&a != "2") {
			cout << "输入有误，请重新输入：";
			getline(cin, a);
		}
		if (a == "1") {		//普通用户 
			h = find_user();
			who = "user";
			return h;
		} else {			//管理员 
			h = find_librarian();
			who = "librarian";
			return h;
		}
	} else {			//注册 
		cout << "你可以选择普通用户注册，或管理员登录：\n";
		cout << "1.普通用户注册\n";
		cout << "2.管理员注册\n";
		cout << "请输入你的选择：";
		getline(cin, a);
		while (a != "1"&&a != "2") {
			cout << "输入有误，请重新输入：";
			getline(cin, a);
		}
		if (a == "1") {		//普通用户 
			h = create_user();
			who = "user";
			return h;
		} else {			//管理员 
			h = create_librarian();
			who = "librarian";
			return h;
		}
	}
}
//
int judge_book(string s) {					//找到则返回下标，否则返回-1 
	int i, h = -1;
	for (i = 0; i < book_total; i++) {
		if (s == bookline[i].get_name()&&bookline[i].get_sum() != 0) {
			h = i; break;
		}
	}
	return h;
}

int user_func() {		//普通用户功能 若退出，返回0，否则返回1 
	string choice, m_name;
	int demp;
	cout << "以下是你可选择的操作：\n";
	cout << "0.退出\n"
		 << "1.借阅书籍\n"
		 << "2.归还书籍\n"
		 << "3.查找所有书籍\n"
		 << "4.查找我的借阅记录\n" 
		 << "5.查找某本书的借阅记录\n"
		 << "请选择你需要的操作：";
	getline(cin, choice);
	while (choice != "0"&&choice != "1"&&choice != "2"&&choice != "3"&&choice != "4"&&choice != "5") {
		cout << "输入有误，请重新输入：";
		getline(cin, choice);
	}
	//输入选项成功 
	if (choice == "0") {
		return 0;
	} else {
		if (choice == "1") {
			cout << "你选择了借阅书籍，请输入书名：";
			getline(cin, m_name);	//输入书名 
			demp = judge_book(m_name);
			if (demp == -1) {
				cout << "图书馆中没有此类书籍。\n";
			} else {
				if (bookline[demp].get_left() == 0) {
					cout << "图书馆中有此类书籍，但已全部借出。\n";
				} else {
					userline[DEMP].borrow_book(demp);
					cout << "借书成功。\n";
				}
			}
		} else if (choice == "2") {
			cout << "你选择了归还书籍，请输入书名：";
			getline(cin, m_name);	//输入书名 
			demp = judge_book(m_name);
			if (demp == -1) {
				cout << "图书馆中没有此类书籍。\n";
			} else {
				if (bookline[demp].get_borrow() == 0) {
					cout << "图书馆中有此类书籍，但未借出。\n";
				} else {
					userline[DEMP].return_book(demp);
					cout << "还书成功。\n";
				}
			}
		} else if (choice == "3") {
			cout << "你选择了查找所有书籍。\n";
			int i;
			for (i = 0; i < book_total; i++) {
				bookline[i].show_basic();
			}
		} else if (choice == "4") {
			cout << "你选择了查找自己的借阅记录：\n";
			userline[DEMP].search_my_record();
		} else if (choice == "5") {
			cout << "你选择了查找某本书的借阅记录，请输入想查找的书名：";
			getline(cin, m_name);	//输入书名 
			demp = judge_book(m_name);
			if (demp == -1) {
				cout << "图书馆中没有此类书籍。\n";
			} else {
				bookline[demp].show_record();
			}
		}
		return 1;
	}
}
int lib_func() {		//管理员功能 若退出，返回0，否则返回1 
	int i;
	string choice, m_name;
	int demp;
	cout << "以下是你可选择的操作：\n"
		 << "0.退出\n"
		 << "1.帮助用户借阅书籍\n"
		 << "2.帮助用户归还书籍\n"
		 << "3.上架新书\n"
		 << "4.下架某书\n"
		 << "5.修改某书籍数量\n"
		 << "请选择你需要的操作：";
	getline(cin, choice);
	while (choice != "0"&&choice != "1"&&choice != "2"&&choice != "3"&&choice != "4"&&choice != "5") {
		cout << "输入有误，请重新输入：";
		getline(cin, choice);
	}
	//输入选项成功 
	if (choice == "0") {
		return 0;
	} else {
		if (choice == "1") {
			string id;
			int au = -1;
			cout << "你选择了帮助用户借阅书籍，请输入此用户ID：";
			getline(cin, id);
			for (i = 0; i < user_total; i++) {
				if (id == userline[i].get_ID()) {
					au = i; break;
				}
			}
			if (au == -1) {
				cout << "用户不存在。\n";
			} else {
				DEMP = au;
				cout << "请输入书名：";
				getline(cin, m_name);	//输入书名 
				demp = judge_book(m_name);
				if (demp == -1) {
					cout << "图书馆中没有此类书籍。\n";
				} else {
					if (bookline[demp].get_left() == 0) {
						cout << "图书馆中有此类书籍，但已全部借出。\n";
					} else {
						userline[DEMP].borrow_book(demp);
						cout << "借书成功。\n";
					}
				}
			}
		} else if (choice == "2") {
			string id;
			int au = -1;
			cout << "你选择了帮助用户归还书籍，请输入此用户ID：";
			getline(cin, id);
			for (i = 0; i < user_total; i++) {
				if (id == userline[i].get_ID()) {
					au = i; break;
				}
			}
			if (au == -1) {
				cout << "用户不存在。\n";
			} else {
				cout << "请输入书名：";
				getline(cin, m_name);	//输入书名 
				demp = judge_book(m_name);
				if (demp == -1) {
					cout << "图书馆中没有此类书籍。\n";
				} else {
					if (bookline[demp].get_borrow() == 0) {
						cout << "图书馆中有此类书籍，但未借出。\n";
					} else {
						userline[au].return_book(demp);
						cout << "还书成功。\n";
					}
				}
			}
		} else if (choice == "3") {
			string m_author, m_ISBN, m_date;
			int m_sum; 
			cout << "你选择了上架新书，请输入书名：";
			getline(cin, m_name);
			demp = judge_book(m_name);
			if (demp != -1) {
				cout << "图书馆中已有此类书籍，只能改变数量，不能再次上架。\n";
			} else {
				bookline[book_total].set_name(m_name); 
				cout << "请输入作者姓名：";
				getline(cin, m_author);
				bookline[book_total].set_author(m_author);
				cout << "请输入出版日期：";
				getline(cin, m_date);
				bookline[book_total].set_out_date(m_date);
				cout << "请输入此书的ISBN：";
				getline(cin, m_ISBN);
				bookline[book_total].set_ISBN(m_ISBN);
				cout << "请输入书的数量：";
				cin >> m_sum;
				cin.get();
				bookline[book_total].set_sum(m_sum);
				bookline[book_total].set_left(m_sum);
				bookline[book_total].set_borrow(0);
				book_total++;
				cout << "上架成功。\n"; 
			}
		} else if (choice == "4") {
			cout << "你选择了下架某书籍，请输入书名：";
			getline(cin, m_name);
			demp = judge_book(m_name);
			if (demp == -1) {
				cout << "图书馆中没有此类书籍。\n";
			} else {
				 if (bookline[demp].get_borrow() != 0) {
				 	cout << "此类书籍不完全在图书馆内，有外借本，暂时无法下架。\n";
				 } else {
				 	bookline[demp].set_sum(0);
				 	cout << "下架成功。\n";
				 	book_total--; 
				 }
			}
		} else if (choice == "5") {
			int num;
			cout << "你选择了更改书籍数量，请输入书名：";
			getline(cin, m_name);
			demp = judge_book(m_name);
			if (demp == -1) {
				cout << "图书馆中没有此类书籍。\n";
			} else {
				cout << "此书籍的基本信息如下：\n";
				bookline[demp].show_basic();
				cout << "请输入修改后的书籍总量：";
				cin >> num;
				cin.get();
				bookline[demp].set_sum(num);
				int l = bookline[demp].get_borrow();
				int g = num - l;
				bookline[demp].set_left(g);
				cout << "修改完成。\n"; 
			}
		}
		return 1;
	}
}

int main() {
	int i, j;
	read_the_file();
	int choice;
	choice = menu();
	if (choice != 0) {
		DEMP = into_system(choice);			//返回用户下标 
	} else {
		cout << "你选择了退出。\n";
		return 0;
	}
	choice = 1;
	while (choice != 0) {
		if (who == "user") {
			choice = user_func();
		} else {
			choice = lib_func();
		}
		save_the_change();
		system("pause");
		system("cls");
	}
	cout << "你选择了退出。\n";
	return 0;
}
