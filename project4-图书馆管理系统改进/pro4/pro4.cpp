#include<iostream>
#include<cstring>
#include<fstream>
#include<cstdlib>
#include<ctime>
using namespace std;
int book_total;
int user_total;
int lib_total;
int DEMP;	//�û���Ӧ�±� 
string who;		//who = "user"��who = "librarian" 
//
string time_now();



//
class Record {		//��¼ 
	private:
		string name;	//��ļ�¼���ǽ����ߵ����֣������ߵļ�¼�������� 
		string date;	//����ʱ�� 
		string limit;	//�������� 
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
		string name;		//���� 
		string author;		//����
		string out_date;	//�������� 
		string ISBN;		//���ʱ�׼���
		int sum;			//�������
		int borrow;			//������������ 
		int left;			//��δ�������������� 
		Record record[500];	//�����ļ�¼
		int record_num;		//��¼���� 
	public:
		Book() {
			sum = borrow = left = record_num = 0;
		}
		void show_basic();		//��ѯ����ʾ�����Ϣ 
		void show_record();
		void borrow_(string s) {
			borrow++;
			left--;
			//���¼�¼
			string s1 = s;
			string s2 = time_now();
			string s3 = "һ�����ڹ黹";
			set_record(s1, s2, s3);
		}
		void return_() {
			borrow--;
			left++;
		}
		void set_name(string s) {name = s;}		//�������� 
		string get_name() {return name;}		//�������� 
		void set_author(string s) {author = s;}	//�������� 
		string get_author() {return author;}	//�������� 
		void set_out_date(string s) {out_date = s;}	//���ĳ������� 
		string get_out_date() {return out_date;}	//���س������� 
		void set_ISBN(string s) {ISBN = s;}	//���Ĺ��ʱ�׼��� 
		string get_ISBN() {return ISBN;}	//���ع��ʱ�׼��� 
		void set_sum(int m) {sum = m;}			//����������� 
		int get_sum() {return sum;}				//����������� 
		void set_borrow(int m) {borrow = m;}	//�����ѽ��������� 
		int get_borrow() {return borrow;}		//�����ѽ��������� 
		void set_left(int m) {left = m;}		//����ʣ��������� 
		int get_left() {return left;}			//����ʣ��������� 
		void set_record_num(int m) {record_num = m;}	//���ļ�¼����
		int get_record_num() {return record_num;}		//���ؼ�¼���� 
		void set_record(string s1, string s2, string s3) {	//������¼ 
			record[record_num].set_name(s1);
			record[record_num].set_date(s2);
			record[record_num].set_limit(s3);
			record_num++;
		}
		Record get_record(int t) {		//���ص�t����¼ 
			return record[t];
		}
};
void Book::show_basic() {		//��ʾ�鱾��Ϣ 
	cout << "������" << name << endl
		<< "���ߣ�" << author << endl
		<< "�������ڣ�" << out_date << endl
		<< "ISBN��" << ISBN << endl
		<< "��������" << sum << endl
		<< "�ִ�����" << left << endl
		<< "�ѽ������" << borrow << endl;
		
}
void Book::show_record() {
	cout << "�����ǽ��ļ�¼��" << endl;
	int i;
	for (i = 0; i < record_num; i++) {
		cout << "�����ߣ�" << record[i].get_name() << endl
			<< "����ʱ�䣺" << record[i].get_date() << endl
			<< "�������ޣ�" << record[i].get_limit() << endl << endl;
	}
}
// 
Book bookline[1000];
//
class User {
	string name;		//�û����� 
	string password;	//����
	string ID;			//�û�ID  
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
		void set_user_record(string s1, string s2, string s3) {	//������¼ 
			user_record[user_record_num].set_name(s1);
			user_record[user_record_num].set_date(s2);
			user_record[user_record_num].set_limit(s3);
			user_record_num++;
		}
		Record get_user_record(int t) {		//���ص�t����¼ 
			return user_record[t];
		}
		int get_user_record_num() {return user_record_num;}
		
		void borrow_book(int t) {
			string s = this->get_name();
			bookline[t].borrow_(s);
			string s1 = bookline[t].get_name();
			string s2 = time_now();
			string s3 = "һ�����ڹ黹";
			set_user_record(s1, s2, s3);
		}
		void return_book(int t) {
			bookline[t].return_();
		}
		void search_my_record() {
			int i;
			for (i = 0; i < user_record_num; i++) {
				cout << "����������" << user_record[i].get_name() << endl
					 << "����ʱ�䣺" << user_record[i].get_date() << endl
					 << "�������ޣ�" << user_record[i].get_limit() << endl << endl;
			}
		}
};
class librarian : public User {
	//string black_list[100];		//������ 
};
//
normal_user userline[500];
librarian libline[100];
//
//
void read_the_file();		//��ȡ�ļ����� 
void save_the_change();		//������д���ļ� 
int menu();					//��ʼ���� 
int find_user();			//��¼ʱ������ͨ�û� 
int find_librarian();		//��¼ʱ���ҹ���Ա 
int create_user();			//ע����ͨ�û� 
int create_librarian();		//ע�����Ա 
int into_system(int choice);//����ϵͳ 
int judge_book(string s);	//�ж�����Ϊs�����Ƿ���� 
int user_func();			//��ͨ�û��Ĺ��� 
int lib_func();				//����Ա�Ĺ��� 
//
//
string time_now() {							//��ȡ��ǰʱ�� 
	time_t rawtime;
	struct tm* timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	char s[200];
	strftime(s, sizeof(s), "%Y��%m��%d��", localtime(&rawtime));
	return s;
}
//
void read_the_file() {
	ifstream fin;//����ifstream���� 
	//��ȡ�鼮��Ϣ 
	fin.open("E:\\library.txt");//���ļ� 
	fin >> book_total;//�õ��ܵ����ж����� 
	fin.get();//�����ֺ�Ļ��ж�ȡ�� 
	int i, k;
	string m_name, m_author, m_date, m_ISBN, m_limit;
	int m_sum, m_borrow, m_left, m_record_num;
	for (i = 0; i < book_total; i++) {
		getline(fin, m_name);
		bookline[i].set_name(m_name);			//���� 
		getline(fin, m_author);
		bookline[i].set_author(m_author);		//���� 
		getline(fin, m_date);
		bookline[i].set_out_date(m_date);		//�������� 
		getline(fin, m_ISBN);
		bookline[i].set_ISBN(m_ISBN);			//���ʱ�׼��� 
		fin >> m_sum;
		fin.get();
		bookline[i].set_sum(m_sum);				//��������
		fin >> m_borrow;
		fin.get();
		bookline[i].set_borrow(m_borrow);		//�ѽ���� 
		fin >> m_left;
		fin.get();
		bookline[i].set_left(m_left);			//ʣ���� 
		fin >> m_record_num;
		fin.get();
		for (k = 0; k < m_record_num&&m_record_num != 0; k++) {
			getline(fin, m_name);
			getline(fin, m_date);
			getline(fin, m_limit);
			bookline[i].set_record(m_name, m_date, m_limit);	//���ļ�¼ 
		}
		fin.get();
	}
	fin.close();//�ر��ļ� 
	//��ȡ��ͨ�û���Ϣ 
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
	//��ȡ����Ա��Ϣ 
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
//���޸ĺ�������ٴε����ļ� 
void save_the_change() {
	ofstream fout;//����һ��ofstream����
	int i, k;
	fout.open("E:\\library.txt");
	fout << book_total << endl;
	for (i = 0; i < book_total + 1; i++) {
		if (bookline[i].get_sum() != 0) {		//����Ϊ0����ɾ�����׵��Ѿ��������� 
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
	//��ͨ�û� 
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
	//����Ա 
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
int menu() {		//��ʼ�˵� 
	cout << "��ӭʹ��ͼ��ݹ���ϵͳ\n"
		 << "1.��¼\n"
		 << "2.ע��\n"
		 << "0.�˳�\n"
		 << "��ѡ������Ҫ�Ĳ�����Ӧ�����֣�";
	string te;
	getline(cin, te);
	while (te != "1"&&te != "2"&&te != "0") {
		cout << "�����������������������Ӧ���֣�";
		getline(cin, te);
	}
	if (te == "1") {
		cout << "��ѡ���˵�¼�ʺ�\n";
		return 1;
	} else if (te == "2") {
		cout << "��ѡ����ע���ʺ�\n";
		return 2;
	} else {
		cout << "��ѡ�����˳�ϵͳ\n";
		return 0;
	}
}
//
int find_user() {		//�����û���userline�е��±� 
	int i;
	int h = -1;
	string id, pass;
	cout << "����������û�ID�����룺\n";
	cout << "ID  ��";
	getline(cin, id);
	cout << "���룺";
	getline(cin, pass);
	for (i = 0; i < user_total; i++) {
		if (id == userline[i].get_ID()) {
			h = -2;			//�ҵ��û� 
			if (pass == userline[i].get_password()) {
				h = i;		//������ȷ 
				break;
			}
		}
	}
	while (h < 0) {
		if (h == -1) {
			cout << "����������û������ڣ����������룺";
		} else {
			cout << "����������������룺";
		}
		cout << "ID  ��";
		getline(cin, id);
		cout << "���룺";
		getline(cin, pass);
		for (i = 0; i < user_total; i++) {
			if (id == userline[i].get_ID()) {
				h = -2;			//�ҵ��û� 
				if (pass == userline[i].get_password()) {
					h = i;		//������ȷ 
					break;
				}
			}
		}
	}
	//�ɹ����� 
	return h; 
}
//
int find_librarian() {
	int i;
	int h = -1;
	string id, pass;
	cout << "����������û�ID�����룺\n";
	cout << "ID  ��";
	getline(cin, id);
	cout << "���룺";
	getline(cin, pass);
	for (i = 0; i < lib_total; i++) {
		if (id == libline[i].get_ID()) {
			h = -2;			//�ҵ��û� 
			if (pass == libline[i].get_password()) {
				h = i;		//������ȷ 
				break;
			}
		}
	}
	while (h < 0) {
		if (h == -1) {
			cout << "����������û������ڣ����������룺\n";
		} else {
			cout << "����������������룺\n";
		}
		cout << "ID  ��";
		getline(cin, id);
		cout << "���룺";
		getline(cin, pass);
		for (i = 0; i < lib_total; i++) {
			if (id == libline[i].get_ID()) {
				h = -2;			//�ҵ��û� 
				if (pass == libline[i].get_password()) {
					h = i;		//������ȷ 
					break;
				}
			}
		}
	}
	//�ɹ����� 
	return h; 
} 
//
int create_user() {					//ע�����Զ���¼�������û��±� 
	int i, h = 0;
	string id, pass, m_name;
	cout << "���������������";
	getline(cin, m_name);
	cout << "����������û�ID�����룺\n";
	cout << "ID  ��";
	getline(cin, id);
	cout << "���룺";
	getline(cin, pass);
	for (i = 0; i < user_total; i++) {
		if (id == userline[i].get_ID()) {
			h = -1;			//�û�ID�ѱ�ռ�� 
			break;
		}
	}
	while (h == -1) {
		h = 0;
		cout << "��ID�ѱ�ռ�ã����������ã�\n";
		cout << "ID  ��";
		getline(cin, id);
		cout << "���룺";
		getline(cin, pass);
		for (i = 0; i < user_total; i++) {
			if (id == userline[i].get_ID()) {
				h = -1;			//�û�ID�ѱ�ռ�� 
				break;
			}
		}
	}
	//�������� 
	userline[user_total].set_ID(id);
	userline[user_total].set_password(pass);
	userline[user_total].set_name(m_name);
	user_total++;
	cout << "�ʺŴ����ɹ������Զ���¼��\n"; 
	return (user_total - 1);
}
//
int create_librarian() {					//ע�����Զ���¼�������û��±� 
	int i, h = 0;
	string id, pass, m_name;
	cout << "���������������";
	getline(cin, m_name);
	cout << "����������û�ID�����룺\n";
	cout << "ID  ��";
	getline(cin, id);
	cout << "���룺";
	getline(cin, pass);
	for (i = 0; i < lib_total; i++) {
		if (id == libline[i].get_ID()) {
			h = -1;			//�û�ID�ѱ�ռ�� 
			break;
		}
	}
	while (h == -1) {
		h = 0;
		cout << "��ID�ѱ�ռ�ã����������ã�\n";
		cout << "ID  ��";
		getline(cin, id);
		cout << "���룺";
		getline(cin, pass);
		for (i = 0; i < lib_total; i++) {
			if (id == libline[i].get_ID()) {
				h = -1;			//�û�ID�ѱ�ռ�� 
				break;
			}
		}
	}
	//�������� 
	libline[lib_total].set_ID(id);
	libline[lib_total].set_password(pass);
	libline[lib_total].set_name(m_name);
	lib_total++;
	cout << "�ʺŴ����ɹ������Զ���¼��\n";
	return (lib_total - 1);
}
// 
int into_system(int choice) {		//�����û��±� 
	string m_id, m_password;
	int h;
	string a;
	if (choice == 1) {	//��¼ 
		cout << "�����ѡ����ͨ�û���¼�������Ա��¼��\n";
		cout << "1.��ͨ�û���¼\n";
		cout << "2.����Ա��¼\n";
		cout << "���������ѡ��";
		getline(cin, a);
		while (a != "1"&&a != "2") {
			cout << "�����������������룺";
			getline(cin, a);
		}
		if (a == "1") {		//��ͨ�û� 
			h = find_user();
			who = "user";
			return h;
		} else {			//����Ա 
			h = find_librarian();
			who = "librarian";
			return h;
		}
	} else {			//ע�� 
		cout << "�����ѡ����ͨ�û�ע�ᣬ�����Ա��¼��\n";
		cout << "1.��ͨ�û�ע��\n";
		cout << "2.����Աע��\n";
		cout << "���������ѡ��";
		getline(cin, a);
		while (a != "1"&&a != "2") {
			cout << "�����������������룺";
			getline(cin, a);
		}
		if (a == "1") {		//��ͨ�û� 
			h = create_user();
			who = "user";
			return h;
		} else {			//����Ա 
			h = create_librarian();
			who = "librarian";
			return h;
		}
	}
}
//
int judge_book(string s) {					//�ҵ��򷵻��±꣬���򷵻�-1 
	int i, h = -1;
	for (i = 0; i < book_total; i++) {
		if (s == bookline[i].get_name()&&bookline[i].get_sum() != 0) {
			h = i; break;
		}
	}
	return h;
}

int user_func() {		//��ͨ�û����� ���˳�������0�����򷵻�1 
	string choice, m_name;
	int demp;
	cout << "���������ѡ��Ĳ�����\n";
	cout << "0.�˳�\n"
		 << "1.�����鼮\n"
		 << "2.�黹�鼮\n"
		 << "3.���������鼮\n"
		 << "4.�����ҵĽ��ļ�¼\n" 
		 << "5.����ĳ����Ľ��ļ�¼\n"
		 << "��ѡ������Ҫ�Ĳ�����";
	getline(cin, choice);
	while (choice != "0"&&choice != "1"&&choice != "2"&&choice != "3"&&choice != "4"&&choice != "5") {
		cout << "�����������������룺";
		getline(cin, choice);
	}
	//����ѡ��ɹ� 
	if (choice == "0") {
		return 0;
	} else {
		if (choice == "1") {
			cout << "��ѡ���˽����鼮��������������";
			getline(cin, m_name);	//�������� 
			demp = judge_book(m_name);
			if (demp == -1) {
				cout << "ͼ�����û�д����鼮��\n";
			} else {
				if (bookline[demp].get_left() == 0) {
					cout << "ͼ������д����鼮������ȫ�������\n";
				} else {
					userline[DEMP].borrow_book(demp);
					cout << "����ɹ���\n";
				}
			}
		} else if (choice == "2") {
			cout << "��ѡ���˹黹�鼮��������������";
			getline(cin, m_name);	//�������� 
			demp = judge_book(m_name);
			if (demp == -1) {
				cout << "ͼ�����û�д����鼮��\n";
			} else {
				if (bookline[demp].get_borrow() == 0) {
					cout << "ͼ������д����鼮����δ�����\n";
				} else {
					userline[DEMP].return_book(demp);
					cout << "����ɹ���\n";
				}
			}
		} else if (choice == "3") {
			cout << "��ѡ���˲��������鼮��\n";
			int i;
			for (i = 0; i < book_total; i++) {
				bookline[i].show_basic();
			}
		} else if (choice == "4") {
			cout << "��ѡ���˲����Լ��Ľ��ļ�¼��\n";
			userline[DEMP].search_my_record();
		} else if (choice == "5") {
			cout << "��ѡ���˲���ĳ����Ľ��ļ�¼������������ҵ�������";
			getline(cin, m_name);	//�������� 
			demp = judge_book(m_name);
			if (demp == -1) {
				cout << "ͼ�����û�д����鼮��\n";
			} else {
				bookline[demp].show_record();
			}
		}
		return 1;
	}
}
int lib_func() {		//����Ա���� ���˳�������0�����򷵻�1 
	int i;
	string choice, m_name;
	int demp;
	cout << "���������ѡ��Ĳ�����\n"
		 << "0.�˳�\n"
		 << "1.�����û������鼮\n"
		 << "2.�����û��黹�鼮\n"
		 << "3.�ϼ�����\n"
		 << "4.�¼�ĳ��\n"
		 << "5.�޸�ĳ�鼮����\n"
		 << "��ѡ������Ҫ�Ĳ�����";
	getline(cin, choice);
	while (choice != "0"&&choice != "1"&&choice != "2"&&choice != "3"&&choice != "4"&&choice != "5") {
		cout << "�����������������룺";
		getline(cin, choice);
	}
	//����ѡ��ɹ� 
	if (choice == "0") {
		return 0;
	} else {
		if (choice == "1") {
			string id;
			int au = -1;
			cout << "��ѡ���˰����û������鼮����������û�ID��";
			getline(cin, id);
			for (i = 0; i < user_total; i++) {
				if (id == userline[i].get_ID()) {
					au = i; break;
				}
			}
			if (au == -1) {
				cout << "�û������ڡ�\n";
			} else {
				DEMP = au;
				cout << "������������";
				getline(cin, m_name);	//�������� 
				demp = judge_book(m_name);
				if (demp == -1) {
					cout << "ͼ�����û�д����鼮��\n";
				} else {
					if (bookline[demp].get_left() == 0) {
						cout << "ͼ������д����鼮������ȫ�������\n";
					} else {
						userline[DEMP].borrow_book(demp);
						cout << "����ɹ���\n";
					}
				}
			}
		} else if (choice == "2") {
			string id;
			int au = -1;
			cout << "��ѡ���˰����û��黹�鼮����������û�ID��";
			getline(cin, id);
			for (i = 0; i < user_total; i++) {
				if (id == userline[i].get_ID()) {
					au = i; break;
				}
			}
			if (au == -1) {
				cout << "�û������ڡ�\n";
			} else {
				cout << "������������";
				getline(cin, m_name);	//�������� 
				demp = judge_book(m_name);
				if (demp == -1) {
					cout << "ͼ�����û�д����鼮��\n";
				} else {
					if (bookline[demp].get_borrow() == 0) {
						cout << "ͼ������д����鼮����δ�����\n";
					} else {
						userline[au].return_book(demp);
						cout << "����ɹ���\n";
					}
				}
			}
		} else if (choice == "3") {
			string m_author, m_ISBN, m_date;
			int m_sum; 
			cout << "��ѡ�����ϼ����飬������������";
			getline(cin, m_name);
			demp = judge_book(m_name);
			if (demp != -1) {
				cout << "ͼ��������д����鼮��ֻ�ܸı������������ٴ��ϼܡ�\n";
			} else {
				bookline[book_total].set_name(m_name); 
				cout << "����������������";
				getline(cin, m_author);
				bookline[book_total].set_author(m_author);
				cout << "������������ڣ�";
				getline(cin, m_date);
				bookline[book_total].set_out_date(m_date);
				cout << "����������ISBN��";
				getline(cin, m_ISBN);
				bookline[book_total].set_ISBN(m_ISBN);
				cout << "���������������";
				cin >> m_sum;
				cin.get();
				bookline[book_total].set_sum(m_sum);
				bookline[book_total].set_left(m_sum);
				bookline[book_total].set_borrow(0);
				book_total++;
				cout << "�ϼܳɹ���\n"; 
			}
		} else if (choice == "4") {
			cout << "��ѡ�����¼�ĳ�鼮��������������";
			getline(cin, m_name);
			demp = judge_book(m_name);
			if (demp == -1) {
				cout << "ͼ�����û�д����鼮��\n";
			} else {
				 if (bookline[demp].get_borrow() != 0) {
				 	cout << "�����鼮����ȫ��ͼ����ڣ�����豾����ʱ�޷��¼ܡ�\n";
				 } else {
				 	bookline[demp].set_sum(0);
				 	cout << "�¼ܳɹ���\n";
				 	book_total--; 
				 }
			}
		} else if (choice == "5") {
			int num;
			cout << "��ѡ���˸����鼮������������������";
			getline(cin, m_name);
			demp = judge_book(m_name);
			if (demp == -1) {
				cout << "ͼ�����û�д����鼮��\n";
			} else {
				cout << "���鼮�Ļ�����Ϣ���£�\n";
				bookline[demp].show_basic();
				cout << "�������޸ĺ���鼮������";
				cin >> num;
				cin.get();
				bookline[demp].set_sum(num);
				int l = bookline[demp].get_borrow();
				int g = num - l;
				bookline[demp].set_left(g);
				cout << "�޸���ɡ�\n"; 
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
		DEMP = into_system(choice);			//�����û��±� 
	} else {
		cout << "��ѡ�����˳���\n";
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
	cout << "��ѡ�����˳���\n";
	return 0;
}
