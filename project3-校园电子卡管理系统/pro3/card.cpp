#include<iostream>
#include<string>
#include<fstream>
#include<cstring>
#include<ctime> 
using namespace std;
//���� 
class card {
	double record[1000];						//��¼��ˮ��Ϣ�е���֧��� 
	string miaoshu[1000];						//��¼��Ӧ��ˮ��Ϣ�ĸ���˵�� 
	int line_num;								//��ˮ��Ϣ���� 
	public:
		card() {line_num = 0;}
		virtual bool pay(double m) {}
		virtual void inquire1() {}
		virtual void inquire2();
		virtual ~card() {}
		virtual bool deposit_money(double m, string g) {}
		int get_line_num() {return line_num;}
		void set_record(double m, string h) {
			record[line_num] = m;
			miaoshu[line_num] = h;
			line_num++;
		}
		double get_record(int i) {
			return record[i];
		}
		string get_miaoshu(int i) {
			return miaoshu[i];
		}
};
//У԰�� 
class campus_card : virtual public card {
	string student_id;							//ѧ�� 
	string student_name;						//���� 
	string student_institute;					//ѧԺ 
	double money_left;								//У԰����� 
	public:
		virtual bool pay(double m);				//֧�� 
		virtual void inquire1();				//��ѯУ԰��������Ϣ 
		virtual void inquire2();				//��ѯУ԰����ˮ��Ϣ 
		virtual bool deposit_money(double m, string g);		//��Ǯ 
		string get_student_id() {return student_id;}
		string get_student_name() {return student_name;}
		string get_student_institute() {return student_institute;}
		double get_campus_money_left() {return money_left;}
		void set_student_id(string m) {student_id = m;}
		void set_student_name(string m) {student_name = m;}
		void set_student_institute(string m) {student_institute = m;}
		void set_campus_money_left(double m) {money_left = m;}
};
//��� 
class deposit_card : virtual public card {
	string bank_card_id;						//���п��� 
	string bank_card_date;						//�������� 
	string owner_name;							//�ֿ������� 
	double money_left;							//���п���� 
	double money_overdraw;						//͸֧��� 
	double has_over;							//��͸֧�Ľ�� 
	public:
		virtual bool pay(double m);				//֧�� 
		virtual void inquire1();				//��ѯ���п�������Ϣ 
		virtual void inquire2();				//��ѯ���п���ˮ��Ϣ 
		virtual bool deposit_money(double m, string g);		//��Ǯ 
		double get_over() {return has_over;}			//�����Ѿ�͸֧�Ľ�� 
		string get_bank_card_id() {return bank_card_id;}
		string get_bank_card_date() {return bank_card_date;}
		string get_owner_name() {return owner_name;}
		double get_deposit_money_left() {return money_left;}
		double get_money_overdraw() {return money_overdraw;}
		void set_bank_card_id(string m) {bank_card_id = m;}
		void set_bank_card_date(string m) {bank_card_date = m;}
		void set_owner_name(string m) {owner_name = m;}
		void set_deposit_money_left(double m) {money_left = m;}
		void set_money_overdraw(double m) {money_overdraw = m;}
		void set_has_over(double m) {has_over = m;}
};
//�󶨿�
class binding_card : public campus_card, public deposit_card {
	public:
		deposit_card num[10];									//���Ŵ��
		int dep_num;											//�󶨵Ĵ������ 
		string get_binding_card_id() {						//���ذ󶨿���ӦУ԰����Ӧѧ�� 
			string temp = campus_card::get_student_id();
			return temp;
		}
		virtual bool pay(double m);
		virtual void inquire1();							//��ѯ�󶨿�������Ϣ 
		virtual void inquire2();							//��ѯ�󶨿���ˮ��Ϣ 
		virtual bool deposit_money(double m, string g);				//��Ǯ 
		int get_dep_num() {return dep_num;}
};
//
string time_now() {							//��ȡ��ǰʱ�� 
	time_t rawtime;
	struct tm* timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	char s[200];
	strftime(s, sizeof(s), "%Y��%m��%d��%X", localtime(&rawtime));
	return s;
}
//
void card::inquire2() {
	int i;
	for (i = 0; i < line_num; i++) {
		cout << miaoshu[i];
		if (record[i] > 0) {
			cout << "����" << record[i] << "Ԫ" << endl;
		} else {
			cout << "֧��" << (0 - record[i]) << "Ԫ" << endl;
		}
	}
}
//
void campus_card::inquire2() {
	card::inquire2();
}
//
void campus_card::inquire1() {
	cout << "ѧ�������� " << student_name << endl;
	cout << "ѧ��ѧ�ţ� " << student_id << endl;
	cout << "ѧ������ѧԺ�� " << student_institute << endl;
	cout << "У԰���� " << money_left << endl;
}
//
void deposit_card::inquire1() {
	cout << "������ţ� " << bank_card_id << endl;
	cout << "�ֿ��������� " << owner_name << endl;
	cout << "�������ڣ� " << bank_card_date << endl;
	cout << "����� " << money_left << endl;
	cout << "��͸֧��ȣ� " << money_overdraw << endl;
	cout << "��͸֧�� " << has_over << endl;
}
//
void deposit_card::inquire2() {
	card::inquire2();
}
//
bool campus_card::deposit_money(double m, string te) {		//te�Ǹ�����ˮ��Ϣ 
	string time = time_now();			//��ȡ��ǰʱ�� 
	string final = time + "��" + te; 
	money_left += m;
	card::set_record(m, final); 			//���¼�¼ 
	return true;
}
//
bool deposit_card::deposit_money(double m, string te) {
	if (has_over > 0) {					//��͸֧ 
		if (m > has_over) {				//�������͸֧�����࣬�Ȼ� 
			money_left = m - has_over;
			has_over = 0;
		} else {						//�������͸֧�����٣��Ȼ� 
			has_over = has_over - m;
		}
	} else {
		money_left += m;
	}
	string time = time_now();			//��ȡ��ǰʱ�� 
	string final = time + "��" + te; 
	card::set_record(m, final); 			//���¼�¼ 
	return true;
}
// 
bool campus_card::pay(double m) {
	if (m <= money_left) {			//����㹻 
		money_left = money_left - m;
		m = -m;
		string time = time_now();		//��ȡ��ǰʱ�� 
		cout << "�������㵱ǰ���ڵص㣺";
		string point;
		getline(cin, point);					//���뵱ǰ���ڵص�
		string final = time + "��" + point;
		card::set_record(m, final);			//���¼�¼ 
		return true;
	} else {
		return false;
	}
}
//
bool deposit_card::pay(double m) {
	if (m <= (money_left + money_overdraw - has_over)) {		//��֧���㹻 
		if (m <= money_left) {									//����֧�� 
			money_left = money_left - m;
		} else {												//����֧�� 
			has_over = has_over + (m - money_left);
			money_left = 0; 
		}
		m = -m;
		string time = time_now();		//��ȡ��ǰʱ�� 
		cout << "�������㵱ǰ���ڵص㣺";
		string point;
		getline(cin, point);					//���뵱ǰ���ڵص�
		string final = time + "��" + point;
		set_record(m, final);										//���¼�¼ 
		return true;
	} else {
		return false;
	}
}
//
bool binding_card::pay(double m) {
	int i;
	bool hp = campus_card::pay(m);
	if (hp == false) {
		for (i = 0; i < dep_num; i++) {
			hp = num[i].pay(m);
			if (hp == true) {
				int p = num[i].get_line_num();
				string q = num[i].get_miaoshu(p - 1);
				set_record (0 - m, q);
				break;
			}
		}
	}
	return hp;
}
//
void binding_card::inquire1() {
	campus_card::inquire1();
	int i;
	for (i = 0; i < dep_num; i++) {
		num[i].inquire1();
	}
}
//
void binding_card::inquire2() {
	card::inquire2();
}
//
bool binding_card::deposit_money(double m, string g) {
	int i;
	double te = 0;
	for (i = 0; i < dep_num; i++) {
		te += num[i].get_over();		//�õ����д��������͸֧��� 
	}
	if (te == 0) {			//δ͸֧����Ǯ����У԰������ 
		campus_card::deposit_money(m, g);
	} else {				//͸֧������͸֧�黹��ʣ�ಿ�ִ���У԰������ 
		if (m > te) {		//������������͸֧�� 
			for (i = 0; i < dep_num; i++) {
				num[i].deposit_money(num[i].get_over(), g);
				int p = num[i].get_line_num();
				string q = num[i].get_miaoshu(p - 1);
				set_record (num[i].get_over(), q);
			}
			campus_card::deposit_money(m - te, g);
		} else {			//����������͸֧�� 
			double h;
			for (i = 0; i < dep_num; i++) {
						h = num[i].get_over();
					if (h < m) {
						num[i].deposit_money(h, g);
						int p = num[i].get_line_num();
						string q = num[i].get_miaoshu(p - 1);
						set_record (h, q);
						m = m - h;
					} else {
						num[i].deposit_money(m, g);
						int p = num[i].get_line_num();
						string q = num[i].get_miaoshu(p - 1);
						set_record (m, q);
						break;
					}
			}
		}
	}
	return true;
} 
// 
campus_card campus_card_line[1000];		//��������У԰����Ϣ 
int max_campus_card;					//У԰������
deposit_card deposit_card_line[1000];	//�����������п���Ϣ
int max_deposit_card;					//���п�����
binding_card binding_card_line[1000];	//�������а󶨿���Ϣ
int max_binding_card;					//�󶨿����� 


int menu() {
	cout << "0����ѡ���˳�ϵͳ\n"
		<< "1����ѡ���У԰�����в���\n"
		<< "2����ѡ��Դ�����в���\n"
		<< "3����ѡ��԰󶨿����в���\n"
		<< "������0~3�������ѡ��: ";
		string choose;
		getline(cin, choose);
		while (choose != "0"&&choose != "1"&&choose != "2"&&choose != "3") {
			cout << "��������������0~3�������ѡ��: ";
			getline(cin, choose); 
		}
		int m;
		if (choose == "0") {
			m = 0;
		} else if (choose == "1") {
			m = 1;
		} else if (choose == "2") {
			m = 2;
		} else if (choose == "3") {
			m = 3;
		}
		return m;
}
//
int judge_campus(string & ID) {			//��δ�ҵ���ӦУ԰���򷵻�-1���ҵ����򷵻�У԰���������е�λ��i 
	int i;
	bool m = false;
	for (i = 0; i < max_campus_card; i++) {
		if (ID == campus_card_line[i].get_student_id()) {
			m = true; break;
		}
	}
	if (m == false) {
		return -1;
	} else {
		return i;
	}
}
// 
int judge_deposit(string & bank_id) {	//��δ�ҵ���Ӧ����򷵻�-1���ҵ����򷵻ش���������е�λ��i 
	int i;
	bool m = false;
	for (i = 0; i < max_deposit_card; i++) {
		if (bank_id == deposit_card_line[i].get_bank_card_id()) {
			m = true; break;
		}
	}
	if (m == false) {
		return -1;
	} else {
		return i;
	}
}
//
int judge_binding(string & binding_id) {	//��δ�ҵ���Ӧ�󶨿��򷵻�-1���ҵ����򷵻ش���������е�λ��i 
	int i;
	bool m = false;
	for (i = 0; i < max_binding_card; i++) {
		if (binding_id == binding_card_line[i].get_student_id()) {
			m = true; break;
		}
	}
	if (m == false) {
		return -1;
	} else {
		return i;
	}
}
//
void xiaoyuanka() {
	cout << "������У԰����Ӧѧ��: ";
	string ID;
	getline(cin, ID);
	int demp;
	demp = judge_campus(ID);
	while (demp == -1) {
		cout << "����ʧ�ܣ��볢����������ѧ��: ";
		getline(cin, ID);
		demp = judge_campus(ID);
	}
	//�˴��õ���dempΪУ԰����Ӧλ�ã� 
	cout << "���ҳɹ�������У԰����\n"
	<< "1����ѡ��֧��\n"
	<< "2����ѡ���ѯУ԰��������Ϣ\n"
	<< "3����ѡ���ѯУ԰����ˮ��Ϣ\n"
	<< "4����ѡ��Ӵ����Ǯ��У԰��\n"
	<< "������1~4�������ѡ��: ";
	string choose;
	getline(cin, choose);
	while (choose != "1"&&choose != "2"&&choose != "3"&&choose != "4") {
		cout << "��������������1~4�������ѡ��: ";
		getline(cin, choose);
	}
	int m;
	if (choose == "1") {	//֧�� 
		cout << "��ѡ�����֧����������֧�����: ";
		double money;
		cin >> money;
		cin.get();//��ȥ���� 
		bool p;
		p = campus_card_line[demp].pay(money);
		if (p == true) {
			cout << "֧���ɹ���У԰���ɹ�֧��" << money << "Ԫ\n";
		} else {
			cout << "֧��ʧ��\n";
		}
	} else if (choose == "2") {		//��ѯ 1 
		cout << "��ѡ���ѯУ԰��������Ϣ: \n";
		campus_card_line[demp].inquire1();
	} else if (choose == "3") {
		cout << "��ѡ���ѯУ԰����ˮ��Ϣ: \n";
		campus_card_line[demp].inquire2();
	} else if (choose == "4") {
		cout << "��ѡ��Ӵ����Ǯ��У԰���������봢�����: ";
		string bank_id;
		getline(cin, bank_id);
		int de;
		de = judge_deposit(bank_id);
		while (de == -1) {
			cout << "����ʧ�ܣ��볢���������뿨��: ";
			getline(cin, bank_id);
			de = judge_deposit(bank_id);
		}
		//�˴��õ���deΪ�����Ӧλ�ã�
		cout << "���ҳɹ���������Ҫת�˵Ľ��: ";
		double zhuanzhang;
		cin >> zhuanzhang;		//����ת�˽��
		cin.get();
		bool hp; 
		hp = deposit_card_line[de].pay(zhuanzhang);
		if (hp == true) {			//�������㹻ת�� 
			string fuzhu = "���" + bank_id; 
			campus_card_line[demp].deposit_money(zhuanzhang, fuzhu);
			cout << "ת�˳ɹ����Ӵ����У԰��ת��" << zhuanzhang << "Ԫ\n"; 
		} else {
			cout << "ת��ʧ��\n";
		}
	}
}
//
void chuxuka() {
	cout << "�����봢�����: ";
	string ID;
	getline(cin, ID);
	int demp;
	demp = judge_deposit(ID);
	while (demp == -1) {
		cout << "����ʧ�ܣ��볢���������뿨��: ";
		getline(cin, ID);
		demp = judge_deposit(ID);
	}
	//�˴��õ���dempΪ�����Ӧλ�ã�
	cout << "���ҳɹ����������\n"
	 << "1����ѡ��֧��\n"
	 << "2����ѡ���ѯ���������Ϣ\n"
	 << "3����ѡ���ѯ�����ˮ��Ϣ\n"
	 << "4����ѡ��Ӵ˿�ת��������һ�Ŵ��\n"
	 << "5����ѡ��Ӵ˿�ת����У԰��\n"
	 << "6����ѡ�����ֽ��ֵ���\n"
	 << "7����ѡ�������������ֵ�˿�\n"
	 << "������1~7�������ѡ��";
	 string choose;
	 getline(cin, choose);
	 while (choose != "1"&&choose != "2"&&choose != "3"&&choose != "4"&&choose != "5"&&choose != "6"&&choose != "7") {
		cout << "��������������1~7�������ѡ��";
		getline(cin, choose); 
	 }
	 if (choose == "1") {
		cout << "��ѡ�����֧����������֧�����: ";
		double money;
		cin >> money;
		cin.get();
		bool p; 
		p = deposit_card_line[demp].pay(money);
		if (p == true) {
			cout << "֧���ɹ�������ɹ�֧��" << money << "Ԫ\n";
		} else {
			cout << "֧��ʧ��\n";
		}
	 } else if (choose == "2") {
		cout << "��ѡ���ѯ���������Ϣ\n";
		deposit_card_line[demp].inquire1();
	 } else if (choose == "3") {
	 	cout << "��ѡ���ѯ�����ˮ��Ϣ\n";
	 	deposit_card_line[demp].inquire2();
	 } else if (choose == "4") {
	 	cout << "��ѡ��Ӵ˿�ת��������һ�Ŵ������������һ�Ŵ�����ţ�";
	 	string bank_id;
		getline(cin, bank_id);
		int de;
		de = judge_deposit(bank_id);
		while (de == -1) {
			cout << "����ʧ�ܣ��볢���������뿨��: ";
			getline(cin, bank_id);
			de = judge_deposit(bank_id);
		}
		//�˴��õ���deΪ�����Ӧλ�ã�
		cout << "���ҳɹ���������Ҫת�˵Ľ��: ";
		double zhuanzhang;
		cin >> zhuanzhang;		//����ת�˽��
		cin.get();
		bool hp;
		hp = deposit_card_line[demp].pay(zhuanzhang);
		if (hp == true) {			//�������㹻ת�� 
			string fuzhu = "���" + ID;
			deposit_card_line[de].deposit_money(zhuanzhang, fuzhu);
			cout << "ת�˳ɹ����Ӵ˿�������һ�Ŵ��ת��" << zhuanzhang << "Ԫ\n"; 
		} else {
			cout << "ת��ʧ��\n";
		}
	 } else if (choose == "5") {
	 	cout << "��ѡ��Ӵ˿�ת����У԰����������У԰����Ӧѧ�ţ�";
	 	string id;
		getline(cin, id);
		int de;
		de = judge_campus(id);
		while (de == -1) {
			cout << "����ʧ�ܣ��볢����������ѧ��: ";
			getline(cin, id);
			de = judge_campus(id);
		}
		//�˴��õ���deΪУ԰����Ӧλ�ã�
		cout << "���ҳɹ���������Ҫת�˵Ľ��: ";
		double zhuanzhang;
		cin >> zhuanzhang;		//����ת�˽��
		cin.get();
		bool hp;
		hp = deposit_card_line[demp].pay(zhuanzhang);
		if (hp == true) {			//�������㹻ת�� 
			string final = "���" + ID;
			campus_card_line[de].deposit_money(zhuanzhang, final);
			cout << "ת�˳ɹ����Ӵ˿���У԰��ת��" << zhuanzhang << "Ԫ\n"; 
		} else {
			cout << "ת��ʧ��\n";
		}
	 } else if (choose == "6") {
		cout << "��ѡ�����ֽ��ֵ������������ֵ�ֽ��";
		double money;
		cin >> money;					//������ 
		cin.get();
		string final = "�ֽ�"; 
		deposit_card_line[demp].deposit_money(money, final);
		cout << "��ֵ�ɹ����ֽ��ֵ" << money << "Ԫ\n";
	 } else if (choose == "7") {
		cout << "��ѡ�������������ֵ�˿�����������һ�Ŵ�����ţ�";
		string bank_id;
		getline(cin, bank_id);
		int de;
		de = judge_deposit(bank_id);
		while (de == -1) {
			cout << "����ʧ�ܣ��볢���������뿨��: ";
			getline(cin, bank_id);
			de = judge_deposit(bank_id);
		}
		//�˴��õ���deΪ�����Ӧλ�ã�
		cout << "���ҳɹ���������Ҫת��Ľ��: ";
		double money;
		cin >> money;		//�����ֵ���
		cin.get();
		bool hp;
		hp = deposit_card_line[de].pay(money);
		if (hp == true) {			//�������㹻��ֵ 
			string final = "���" + bank_id;
			deposit_card_line[demp].deposit_money(money, final);
			cout << "��ֵ�ɹ��������������ת��˿�" << money << "Ԫ\n";
		} else {
			cout << "��ֵʧ��\n";
		}
	 }
}
//
void bangdingka() {
	cout << "������󶨿���У԰�����ֶ�Ӧѧ��: ";
	string ID;
	getline(cin, ID);
	int demp, i;
	demp = judge_binding(ID);
	while (demp == -1) {
		cout << "����ʧ�ܣ��볢����������ѧ��: ";
		getline(cin, ID);
		demp = judge_binding(ID);
	}
	//�˴��õ���dempΪ�󶨿���Ӧλ�ã�
	cout << "���ҳɹ�������󶨿���\n"
	<< "1����ѡ��֧��\n"
	<< "2����ѡ���ѯ�󶨿�������Ϣ\n"
	<< "3����ѡ���ѯ�󶨿���ˮ��Ϣ\n"
	<< "4����ѡ��Ӵ˿�ת��������һ�Ű󶨿�\n"
	<< "5����ѡ��Ӵ˿�ת���봢�\n"
	<< "6����ѡ��Ӵ˿�ת����У԰��\n"
	<< "7����ѡ�����ֽ��ֵ�˿�\n"
	<< "8����ѡ���ô����ֵ�˿�\n"
	<< "9����ѡ��������һ�Ű󶨿���ֵ�˿�\n"
	<< "������1~9�������ѡ��";
	string choose;
	getline(cin, choose);
	while (choose != "1"&&choose != "2"&&choose != "3"&&choose != "4"&&choose != "5"&&choose != "6"&&choose != "7"&&choose != "8"&&choose != "9") {
		cout << "��������������1~9�������ѡ��";
		getline(cin, choose); 
	}
	if (choose == "1") {
		cout << "��ѡ���˽���֧����������֧����";
		double money;
		cin >> money;								//����֧����� 
		cin.get();
		bool hp = binding_card_line[demp].pay(money);
		if (hp == true) {							//֧���ɹ� 
			cout << "֧���ɹ����󶨿��ɹ�֧��" << money << "Ԫ\n";
		} else {
			cout << "֧��ʧ��\n";		//֧��ʧ�� 
		}
	} else if (choose == "2") {
		cout << "��ѡ���ѯ�󶨿�������Ϣ: \n";
		binding_card_line[demp].inquire1();
	} else if (choose == "3") {
		cout << "��ѡ���ѯ�󶨿���ˮ��Ϣ: \n";
		binding_card_line[demp].inquire2();
	} else if (choose == "4") {
		cout << "��ѡ��Ӵ˿�ת��������һ�Ű󶨿�������������һ�Ű󶨿���У԰�����ֶ�Ӧѧ�ţ�";
		string id;
		getline(cin, id);
		int de;
		de = judge_binding(id);
		while (de == -1) {
			cout << "����ʧ�ܣ��볢����������ѧ��: ";
			getline(cin, id);
		}
		//�˴��õ�deΪ�󶨿���Ӧλ�� 
		cout << "���ҳɹ���������ת�˽�";
		double zhuanzhang;
		cin >> zhuanzhang;					//����ת�˽�� 
		cin.get();
		bool hp = binding_card_line[demp].pay(zhuanzhang);
		if (hp == true) {						//ת�˳ɹ� 
			string final = "�󶨿�" + ID;
			binding_card_line[de].deposit_money(zhuanzhang, final);
			cout << "ת�˳ɹ����Ӵ˿�������һ�Ű󶨿�ת��" << zhuanzhang << "Ԫ\n";  
		} else {								//ת��ʧ�� 
			cout << "ת��ʧ��\n";
		}
	} else if (choose == "5") {
		cout << "��ѡ��Ӵ˿�ת���봢��������봢����ţ�";
		string bank_id;
		getline(cin, bank_id);
		int de;
		de = judge_deposit(bank_id);
		while (de == -1) {
			cout << "����ʧ�ܣ��볢���������뿨�ţ�";
			getline(cin, bank_id);
		}
		//�˴��õ�deΪ�����Ӧλ�� 
		cout << "���ҳɹ���������ת�˽�";
		double zhuanzhang;
		cin >> zhuanzhang;					//����ת�˽�� 
		cin.get();
		bool hp = binding_card_line[demp].pay(zhuanzhang);
		if (hp == true) {					//ת�˳ɹ� 
			string final = "�󶨿�" + ID;
			deposit_card_line[de].deposit_money(zhuanzhang, final);
			cout << "ת�˳ɹ����Ӵ˿����ת��" << zhuanzhang << "Ԫ\n";  
		} else {							//ת��ʧ�� 
			cout << "ת��ʧ��\n";
		}
	} else if (choose == "6") {
		cout << "��ѡ��Ӵ˿�ת����У԰����������У԰����Ӧѧ�ţ�";
		string stu_id;
		getline(cin, stu_id);
		int de;
		de = judge_campus(stu_id);
		while (de == -1) {
			cout << "���������볢����������ѧ�ţ�";
			getline(cin, stu_id);
		}
		//�˴��õ�deΪУ԰����Ӧλ�� 
		cout << "���ҳɹ���������ת�˽�";
		double zhuanzhang;
		cin >> zhuanzhang;			//����ת�˽�� 
		cin.get();
		bool hp = binding_card_line[demp].pay(zhuanzhang);
		if (hp == true) {				//ת�˳ɹ� 
			string final = "�󶨿�" + ID;
			campus_card_line[de].deposit_money(zhuanzhang, final);
			cout << "ת�˳ɹ����Ӵ˿���У԰��ת��" << zhuanzhang << "Ԫ\n"; 
		} else {
			cout << "ת��ʧ��\n";
		}
	} else if (choose == "7") {
		cout << "��ѡ�����ֽ��ֵ�󶨿����������ֵ�ֽ��";
		double money;
		cin >> money;				//�����ֵ�ֽ��� 
		cin.get();
		string final = "�ֽ�";
		binding_card_line[demp].deposit_money(money, final);
		cout << "��ֵ�ɹ����ֽ��ֵ" << money << "Ԫ\n";
	} else if (choose == "8") {
		cout << "��ѡ���ô����˿���ֵ�������봢����ţ�";
		string bank_id;
		getline(cin, bank_id);
		int de;
		de = judge_deposit(bank_id);
		while (de == -1) {
			cout << "����ʧ�ܣ��볢���������뿨�ţ�";
			getline(cin, bank_id);
		}
		//�˴��õ�deΪ�����Ӧλ�� 
		cout << "���ҳɹ����������ֵ��";
		double money;
		cin >> money;				//�����ֵ�ֽ��� 
		cin.get();
		bool hp = deposit_card_line[de].pay(money);
		if (hp == true) {			//��ֵ�ɹ� 
			string final = "���" + bank_id;
			binding_card_line[demp].deposit_money(money, final);
			cout << "��ֵ�ɹ����ɴ����˿���ֵ" << money << "Ԫ\n"; 
		} else {
			cout << "��ֵʧ��\n";
		}
	} else if (choose == "9") {
		cout << "��ѡ���������󶨿���˿���ֵ�������������󶨿���У԰�����ֶ�Ӧѧ�ţ�";
		string stu_id;
		getline(cin, stu_id);
		int de;
		de = judge_binding(stu_id);
		while (de == -1) {
			cout << "����ʧ�ܣ��볢����������ѧ�ţ�";
			getline(cin, stu_id);
		}
		//�˴��õ�deΪ�󶨿���Ӧλ��
		cout << "���ҳɹ����������ֵ��";
		double money;
		cin >> money;				//�����ֵ��� 
		cin.get();
		bool hp = binding_card_line[de].pay(money);
		if (hp == true) {			//��ֵ�ɹ� 
			string final = "�󶨿�" + stu_id;
			binding_card_line[demp].deposit_money(money, final);
			cout << "��ֵ�ɹ����������󶨿���˿���ֵ" << money << "Ԫ\n";  
		} else {
			cout << "��ֵʧ��\n";
		}
	}
}
//
void read_the_file() {
	ifstream fin;//����ifstream���� 
	fin.open("E:\\campus_cards.txt");//��У԰����Ϣ�ļ� 
	string temp;
	string fuzhu;
	fin >> max_campus_card;//У԰������ 
	fin.get();//�����ֺ�Ļ��ж�ȡ�� 
	int i;
	double left_money;
	double m_record;
	char ch;
	//��ȡУ԰����Ϣ 
	for (i = 0; i < max_campus_card; i++) {
		//У԰����Ϣ���� 
		getline(fin, temp);//��ѧ������������temp�� 
		campus_card_line[i].set_student_name(temp);//��ѧ���������Ƶ��������ȥ 
		getline(fin, temp);//��ѧ�Ŵ���
		campus_card_line[i].set_student_id(temp);//���Ƶ��������
		getline(fin, temp);//��ѧԺ����
		campus_card_line[i].set_student_institute(temp);//���Ƶ������
		fin >> left_money;//У԰����� 
		campus_card_line[i].set_campus_money_left(left_money);
		fin.get();
		fin.get(ch);
		while (ch == '+'||ch == '-') {//��ȡ��¼ 
			if (ch == '+') {
				fin >> m_record;
			} else {
				fin >> m_record;
				m_record = 0 - m_record;
			}
			fin.get();
			getline(fin, fuzhu);
			campus_card_line[i].set_record(m_record, fuzhu);
			fin.get(ch);
		}
	}
	fin.close();//�ر��ļ� 
	//�����Ϣ����
	double over_money;
	double hasover; 
	fin.open("E:\\deposit_cards.txt");//�򿪴����Ϣ�ļ� 
	fin >> max_deposit_card;
	fin.get();
	for (i = 0; i < max_deposit_card; i++) {
		getline(fin, temp);//��ȡ�ֿ�������
		deposit_card_line[i].set_owner_name(temp);
		getline(fin, temp);//��ȡ����
		deposit_card_line[i].set_bank_card_id(temp);
		getline(fin, temp);//��ȡ��������
		deposit_card_line[i].set_bank_card_date(temp);
		fin >> left_money;//��ȡ������ 
		fin.get();
		deposit_card_line[i].set_deposit_money_left(left_money);
		fin >> over_money;//��ȡ͸֧���
		fin.get();
		deposit_card_line[i].set_money_overdraw(over_money);  
		fin >> hasover;//��ȡ�Ѿ�͸֧�Ľ�� 
		fin.get();
		deposit_card_line[i].set_has_over(hasover);
		fin.get(ch);
		while (ch == '+'||ch == '-') {
			if (ch == '+') {
				fin >> m_record;
			} else {
				fin >> m_record;
				m_record = 0 - m_record;
			}
			fin.get();
			getline(fin, fuzhu);
			deposit_card_line[i].set_record(m_record, fuzhu);//��ȡ��ˮ��Ϣ 
			fin.get(ch);
		}
	}
	fin.close();//�ر��ļ�
	//�󶨿���Ϣ����
	int dep_n;
	int j;
	fin.open("E:\\binding_cards.txt");//�򿪰󶨿���Ϣ�ļ� 
	fin >> max_binding_card;
	fin.get();
	for (i = 0; i < max_binding_card; i++) {
		getline(fin, temp);//��ȡУ԰����Ӧ����
		binding_card_line[i].set_student_name(temp);
		getline(fin, temp);//��ȡѧ�� 
		binding_card_line[i].set_student_id(temp);
		getline(fin, temp);
		binding_card_line[i].set_student_institute(temp);
		fin >> left_money;//��ȡУ԰����� 
		fin.get();
		binding_card_line[i].set_campus_money_left(left_money);
		fin >> dep_n;//��ȡ�󶨴������ 
		fin.get();
		binding_card_line[i].dep_num = dep_n;
		for (j = 0; j < dep_n; j++) {
			getline(fin, temp);//��ȡ����ֿ������� 
			binding_card_line[i].num[j].set_owner_name(temp);
			getline(fin, temp);//��ȡ������� 
			binding_card_line[i].num[j].set_bank_card_id(temp);
			getline(fin, temp);//��ȡ�������� 
			binding_card_line[i].num[j].set_bank_card_date(temp);
			fin >> left_money;//��ȡ������ 
			fin.get();
			binding_card_line[i].num[j].set_deposit_money_left(left_money);
			fin >> over_money;//��ȡ͸֧���
			fin.get();
			binding_card_line[i].num[j].set_money_overdraw(over_money);
			fin >> hasover;//��ȡ�Ѿ�͸֧�Ľ�� 
			fin.get();
			binding_card_line[i].num[j].set_has_over(hasover);
		}
		fin.get(ch);
		while (ch == '+'||ch == '-') {
			if (ch == '+') {
				fin >> m_record;
			} else {
				fin >> m_record;
				m_record = 0 - m_record;
			}
			fin.get();
			getline(fin, fuzhu);
			binding_card_line[i].set_record(m_record, fuzhu);
			fin.get(ch);
		}
	}
	fin.close();//�ر��ļ� 
}
//
void update_the_file() {
	ofstream fout;//����һ��ofstream����
	fout.open("E:\\campus_cards.txt");//��У԰����Ϣ�ļ� 
	int i, num, j;
	double te;
	fout << max_campus_card << endl;
	for (i = 0; i < max_campus_card; i++) {
		if (i != 0) {
			fout << '*';
		}
		fout << campus_card_line[i].get_student_name() << endl;
		fout << campus_card_line[i].get_student_id() << endl;
		fout << campus_card_line[i].get_student_institute() << endl;
		fout << campus_card_line[i].get_campus_money_left() << endl;
		num = campus_card_line[i].get_line_num();
		for (j = 0; j < num; j++) {
			te = campus_card_line[i].get_record(j);
			if (te > 0) {
				fout << '+' << te << " ";
			} else {
				fout << te << " ";
			}
			fout << campus_card_line[i].get_miaoshu(j) << endl;
		}
	}
	fout << '*';
	fout.close();
	fout.open("E:\\deposit_cards.txt");//�򿪴����Ϣ�ļ� 
	fout << max_deposit_card << endl;
	for (i = 0; i < max_deposit_card; i++) {
		if (i != 0) {
			fout << '*';
		}
		fout << deposit_card_line[i].get_owner_name() << endl;
		fout << deposit_card_line[i].get_bank_card_id() << endl;
		fout << deposit_card_line[i].get_bank_card_date() << endl;
		fout << deposit_card_line[i].get_deposit_money_left() << endl;
		fout << deposit_card_line[i].get_money_overdraw() << endl;
		fout << deposit_card_line[i].get_over() << endl;
		num = deposit_card_line[i].get_line_num();
		for (j = 0; j < num; j++) {
			te = deposit_card_line[i].get_record(j);
			if (te > 0) {
				fout << '+' << te << " ";
			} else {
				fout << te << " ";
			}
			fout << deposit_card_line[i].get_miaoshu(j) << endl;
		}
	}
	fout << '*';
	fout.close();
	fout.open("E:\\binding_cards.txt");//�򿪰󶨿���Ϣ�ļ� 
	fout << max_binding_card << endl;
	for (i = 0; i < max_binding_card; i++) {
		if (i != 0) {
			fout << '*';
		}
		fout << binding_card_line[i].get_student_name() << endl;
		fout << binding_card_line[i].get_student_id() << endl;
		fout << binding_card_line[i].get_student_institute() << endl;
		fout << binding_card_line[i].get_campus_money_left() << endl;
		fout << binding_card_line[i].dep_num << endl;
		for (j = 0; j < binding_card_line[i].dep_num; j++) {
			fout << binding_card_line[i].num[j].get_owner_name() << endl;
			fout << binding_card_line[i].num[j].get_bank_card_id() << endl;
			fout << binding_card_line[i].num[j].get_bank_card_date() << endl;
			fout << binding_card_line[i].num[j].get_deposit_money_left() << endl;
			fout << binding_card_line[i].num[j].get_money_overdraw() << endl;
			fout << binding_card_line[i].num[j].get_over() << endl;
		}
		num = binding_card_line[i].get_line_num();
		for (j = 0; j < num; j++) {
			te = binding_card_line[i].get_record(j);
			if (te > 0) {
				fout << '+' << te << " ";
			} else {
				fout << te << " ";
			}
			fout << binding_card_line[i].get_miaoshu(j) << endl;
		}
	}
	fout << '*';
	fout.close();
}
//
int main() {
	//���ļ����ݵ��� 
	read_the_file();
	cout << "��ӭʹ��У԰���ӿ�����ϵͳ,��ϵͳ�������ڹ���У԰����������Լ�������Ϊһ��İ󶨿�.\n";
	int choose;
	choose = menu();
	while (choose != 0) {
		if (choose == 1) {	//У԰�� 
			xiaoyuanka();
		} else if (choose == 2) {	//��� 
			chuxuka();
		} else if (choose == 3) {	//�󶨿� 
			bangdingka();
		}
		update_the_file();
		//���ı䴢���ļ�
		system("pause");
		system("cls");
		choose = menu();
	}
	cout << "��ѡ�����˳�ϵͳ\n";
	return 0;
}

