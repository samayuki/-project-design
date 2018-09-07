#include<iostream>
#include<string>
#include<fstream>
#include<cstring>
#include<ctime> 
using namespace std;
//基类 
class card {
	double record[1000];						//记录流水信息中的收支情况 
	string miaoshu[1000];						//记录相应流水信息的附加说明 
	int line_num;								//流水信息条数 
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
//校园卡 
class campus_card : virtual public card {
	string student_id;							//学号 
	string student_name;						//名字 
	string student_institute;					//学院 
	double money_left;								//校园卡余额 
	public:
		virtual bool pay(double m);				//支付 
		virtual void inquire1();				//查询校园卡基本信息 
		virtual void inquire2();				//查询校园卡流水信息 
		virtual bool deposit_money(double m, string g);		//存钱 
		string get_student_id() {return student_id;}
		string get_student_name() {return student_name;}
		string get_student_institute() {return student_institute;}
		double get_campus_money_left() {return money_left;}
		void set_student_id(string m) {student_id = m;}
		void set_student_name(string m) {student_name = m;}
		void set_student_institute(string m) {student_institute = m;}
		void set_campus_money_left(double m) {money_left = m;}
};
//储蓄卡 
class deposit_card : virtual public card {
	string bank_card_id;						//银行卡号 
	string bank_card_date;						//发卡日期 
	string owner_name;							//持卡人姓名 
	double money_left;							//银行卡余额 
	double money_overdraw;						//透支额度 
	double has_over;							//已透支的金额 
	public:
		virtual bool pay(double m);				//支付 
		virtual void inquire1();				//查询银行卡基本信息 
		virtual void inquire2();				//查询银行卡流水信息 
		virtual bool deposit_money(double m, string g);		//存钱 
		double get_over() {return has_over;}			//返回已经透支的金额 
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
//绑定卡
class binding_card : public campus_card, public deposit_card {
	public:
		deposit_card num[10];									//多张储蓄卡
		int dep_num;											//绑定的储蓄卡张数 
		string get_binding_card_id() {						//返回绑定卡对应校园卡对应学号 
			string temp = campus_card::get_student_id();
			return temp;
		}
		virtual bool pay(double m);
		virtual void inquire1();							//查询绑定卡基本信息 
		virtual void inquire2();							//查询绑定卡流水信息 
		virtual bool deposit_money(double m, string g);				//存钱 
		int get_dep_num() {return dep_num;}
};
//
string time_now() {							//获取当前时间 
	time_t rawtime;
	struct tm* timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	char s[200];
	strftime(s, sizeof(s), "%Y年%m月%d日%X", localtime(&rawtime));
	return s;
}
//
void card::inquire2() {
	int i;
	for (i = 0; i < line_num; i++) {
		cout << miaoshu[i];
		if (record[i] > 0) {
			cout << "存入" << record[i] << "元" << endl;
		} else {
			cout << "支出" << (0 - record[i]) << "元" << endl;
		}
	}
}
//
void campus_card::inquire2() {
	card::inquire2();
}
//
void campus_card::inquire1() {
	cout << "学生姓名： " << student_name << endl;
	cout << "学生学号： " << student_id << endl;
	cout << "学生所属学院： " << student_institute << endl;
	cout << "校园卡余额： " << money_left << endl;
}
//
void deposit_card::inquire1() {
	cout << "储蓄卡卡号： " << bank_card_id << endl;
	cout << "持卡人姓名： " << owner_name << endl;
	cout << "发卡日期： " << bank_card_date << endl;
	cout << "储蓄卡余额： " << money_left << endl;
	cout << "可透支额度： " << money_overdraw << endl;
	cout << "已透支金额： " << has_over << endl;
}
//
void deposit_card::inquire2() {
	card::inquire2();
}
//
bool campus_card::deposit_money(double m, string te) {		//te是辅助流水信息 
	string time = time_now();			//获取当前时间 
	string final = time + "由" + te; 
	money_left += m;
	card::set_record(m, final); 			//更新记录 
	return true;
}
//
bool deposit_card::deposit_money(double m, string te) {
	if (has_over > 0) {					//有透支 
		if (m > has_over) {				//存入金额比透支量更多，先还 
			money_left = m - has_over;
			has_over = 0;
		} else {						//存入金额比透支量更少，先还 
			has_over = has_over - m;
		}
	} else {
		money_left += m;
	}
	string time = time_now();			//获取当前时间 
	string final = time + "由" + te; 
	card::set_record(m, final); 			//更新记录 
	return true;
}
// 
bool campus_card::pay(double m) {
	if (m <= money_left) {			//余额足够 
		money_left = money_left - m;
		m = -m;
		string time = time_now();		//获取当前时间 
		cout << "请输入你当前所在地点：";
		string point;
		getline(cin, point);					//输入当前所在地点
		string final = time + "在" + point;
		card::set_record(m, final);			//更新记录 
		return true;
	} else {
		return false;
	}
}
//
bool deposit_card::pay(double m) {
	if (m <= (money_left + money_overdraw - has_over)) {		//可支出足够 
		if (m <= money_left) {									//余额可支付 
			money_left = money_left - m;
		} else {												//余额不足支付 
			has_over = has_over + (m - money_left);
			money_left = 0; 
		}
		m = -m;
		string time = time_now();		//获取当前时间 
		cout << "请输入你当前所在地点：";
		string point;
		getline(cin, point);					//输入当前所在地点
		string final = time + "在" + point;
		set_record(m, final);										//更新记录 
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
		te += num[i].get_over();		//得到所有储蓄卡部分已透支金额 
	}
	if (te == 0) {			//未透支，则将钱存入校园卡部分 
		campus_card::deposit_money(m, g);
	} else {				//透支过，则将透支归还后将剩余部分存入校园卡部分 
		if (m > te) {		//存入量大于总透支量 
			for (i = 0; i < dep_num; i++) {
				num[i].deposit_money(num[i].get_over(), g);
				int p = num[i].get_line_num();
				string q = num[i].get_miaoshu(p - 1);
				set_record (num[i].get_over(), q);
			}
			campus_card::deposit_money(m - te, g);
		} else {			//存入量少于透支量 
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
campus_card campus_card_line[1000];		//储存所有校园卡信息 
int max_campus_card;					//校园卡总数
deposit_card deposit_card_line[1000];	//储存所有银行卡信息
int max_deposit_card;					//银行卡总数
binding_card binding_card_line[1000];	//储存所有绑定卡信息
int max_binding_card;					//绑定卡总数 


int menu() {
	cout << "0代表选择退出系统\n"
		<< "1代表选择对校园卡进行操作\n"
		<< "2代表选择对储蓄卡进行操作\n"
		<< "3代表选择对绑定卡进行操作\n"
		<< "请输入0~3做出你的选择: ";
		string choose;
		getline(cin, choose);
		while (choose != "0"&&choose != "1"&&choose != "2"&&choose != "3") {
			cout << "输入有误，请输入0~3做出你的选择: ";
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
int judge_campus(string & ID) {			//若未找到对应校园卡则返回-1，找到了则返回校园卡在数组中的位置i 
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
int judge_deposit(string & bank_id) {	//若未找到对应储蓄卡则返回-1，找到了则返回储蓄卡在数组中的位置i 
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
int judge_binding(string & binding_id) {	//若未找到对应绑定卡则返回-1，找到了则返回储蓄卡在数组中的位置i 
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
	cout << "请输入校园卡对应学号: ";
	string ID;
	getline(cin, ID);
	int demp;
	demp = judge_campus(ID);
	while (demp == -1) {
		cout << "查找失败，请尝试重新输入学号: ";
		getline(cin, ID);
		demp = judge_campus(ID);
	}
	//此处得到的demp为校园卡对应位置； 
	cout << "查找成功，管理校园卡：\n"
	<< "1代表选择支付\n"
	<< "2代表选择查询校园卡基本信息\n"
	<< "3代表选择查询校园卡流水信息\n"
	<< "4代表选择从储蓄卡存钱入校园卡\n"
	<< "请输入1~4做出你的选择: ";
	string choose;
	getline(cin, choose);
	while (choose != "1"&&choose != "2"&&choose != "3"&&choose != "4") {
		cout << "输入有误，请输入1~4做出你的选择: ";
		getline(cin, choose);
	}
	int m;
	if (choose == "1") {	//支付 
		cout << "你选择进行支付，请输入支付金额: ";
		double money;
		cin >> money;
		cin.get();//除去换行 
		bool p;
		p = campus_card_line[demp].pay(money);
		if (p == true) {
			cout << "支付成功，校园卡成功支出" << money << "元\n";
		} else {
			cout << "支付失败\n";
		}
	} else if (choose == "2") {		//查询 1 
		cout << "你选择查询校园卡基本信息: \n";
		campus_card_line[demp].inquire1();
	} else if (choose == "3") {
		cout << "你选择查询校园卡流水信息: \n";
		campus_card_line[demp].inquire2();
	} else if (choose == "4") {
		cout << "你选择从储蓄卡存钱入校园卡，请输入储蓄卡卡号: ";
		string bank_id;
		getline(cin, bank_id);
		int de;
		de = judge_deposit(bank_id);
		while (de == -1) {
			cout << "查找失败，请尝试重新输入卡号: ";
			getline(cin, bank_id);
			de = judge_deposit(bank_id);
		}
		//此处得到的de为储蓄卡对应位置；
		cout << "查找成功，请输入要转账的金额: ";
		double zhuanzhang;
		cin >> zhuanzhang;		//输入转账金额
		cin.get();
		bool hp; 
		hp = deposit_card_line[de].pay(zhuanzhang);
		if (hp == true) {			//储蓄卡金额足够转账 
			string fuzhu = "储蓄卡" + bank_id; 
			campus_card_line[demp].deposit_money(zhuanzhang, fuzhu);
			cout << "转账成功，从储蓄卡向校园卡转入" << zhuanzhang << "元\n"; 
		} else {
			cout << "转账失败\n";
		}
	}
}
//
void chuxuka() {
	cout << "请输入储蓄卡卡号: ";
	string ID;
	getline(cin, ID);
	int demp;
	demp = judge_deposit(ID);
	while (demp == -1) {
		cout << "查找失败，请尝试重新输入卡号: ";
		getline(cin, ID);
		demp = judge_deposit(ID);
	}
	//此处得到的demp为储蓄卡对应位置；
	cout << "查找成功，管理储蓄卡：\n"
	 << "1代表选择支付\n"
	 << "2代表选择查询储蓄卡基本信息\n"
	 << "3代表选择查询储蓄卡流水信息\n"
	 << "4代表选择从此卡转账入另外一张储蓄卡\n"
	 << "5代表选择从此卡转账入校园卡\n"
	 << "6代表选择用现金充值储蓄卡\n"
	 << "7代表选择用其他储蓄卡充值此卡\n"
	 << "请输入1~7做出你的选择：";
	 string choose;
	 getline(cin, choose);
	 while (choose != "1"&&choose != "2"&&choose != "3"&&choose != "4"&&choose != "5"&&choose != "6"&&choose != "7") {
		cout << "输入有误，请输入1~7做出你的选择：";
		getline(cin, choose); 
	 }
	 if (choose == "1") {
		cout << "你选择进行支付，请输入支付金额: ";
		double money;
		cin >> money;
		cin.get();
		bool p; 
		p = deposit_card_line[demp].pay(money);
		if (p == true) {
			cout << "支付成功，储蓄卡成功支出" << money << "元\n";
		} else {
			cout << "支付失败\n";
		}
	 } else if (choose == "2") {
		cout << "你选择查询储蓄卡基本信息\n";
		deposit_card_line[demp].inquire1();
	 } else if (choose == "3") {
	 	cout << "你选择查询储蓄卡流水信息\n";
	 	deposit_card_line[demp].inquire2();
	 } else if (choose == "4") {
	 	cout << "你选择从此卡转账入另外一张储蓄卡，请输入另一张储蓄卡卡号：";
	 	string bank_id;
		getline(cin, bank_id);
		int de;
		de = judge_deposit(bank_id);
		while (de == -1) {
			cout << "查找失败，请尝试重新输入卡号: ";
			getline(cin, bank_id);
			de = judge_deposit(bank_id);
		}
		//此处得到的de为储蓄卡对应位置；
		cout << "查找成功，请输入要转账的金额: ";
		double zhuanzhang;
		cin >> zhuanzhang;		//输入转账金额
		cin.get();
		bool hp;
		hp = deposit_card_line[demp].pay(zhuanzhang);
		if (hp == true) {			//储蓄卡金额足够转账 
			string fuzhu = "储蓄卡" + ID;
			deposit_card_line[de].deposit_money(zhuanzhang, fuzhu);
			cout << "转账成功，从此卡向另外一张储蓄卡转入" << zhuanzhang << "元\n"; 
		} else {
			cout << "转账失败\n";
		}
	 } else if (choose == "5") {
	 	cout << "你选择从此卡转账入校园卡，请输入校园卡对应学号：";
	 	string id;
		getline(cin, id);
		int de;
		de = judge_campus(id);
		while (de == -1) {
			cout << "查找失败，请尝试重新输入学号: ";
			getline(cin, id);
			de = judge_campus(id);
		}
		//此处得到的de为校园卡对应位置；
		cout << "查找成功，请输入要转账的金额: ";
		double zhuanzhang;
		cin >> zhuanzhang;		//输入转账金额
		cin.get();
		bool hp;
		hp = deposit_card_line[demp].pay(zhuanzhang);
		if (hp == true) {			//储蓄卡金额足够转账 
			string final = "储蓄卡" + ID;
			campus_card_line[de].deposit_money(zhuanzhang, final);
			cout << "转账成功，从此卡向校园卡转入" << zhuanzhang << "元\n"; 
		} else {
			cout << "转账失败\n";
		}
	 } else if (choose == "6") {
		cout << "你选择用现金充值储蓄卡，请输入充值现金金额：";
		double money;
		cin >> money;					//输入金额 
		cin.get();
		string final = "现金"; 
		deposit_card_line[demp].deposit_money(money, final);
		cout << "充值成功，现金充值" << money << "元\n";
	 } else if (choose == "7") {
		cout << "你选择用其他储蓄卡充值此卡，请输入另一张储蓄卡卡号：";
		string bank_id;
		getline(cin, bank_id);
		int de;
		de = judge_deposit(bank_id);
		while (de == -1) {
			cout << "查找失败，请尝试重新输入卡号: ";
			getline(cin, bank_id);
			de = judge_deposit(bank_id);
		}
		//此处得到的de为储蓄卡对应位置；
		cout << "查找成功，请输入要转入的金额: ";
		double money;
		cin >> money;		//输入充值金额
		cin.get();
		bool hp;
		hp = deposit_card_line[de].pay(money);
		if (hp == true) {			//储蓄卡金额足够充值 
			string final = "储蓄卡" + bank_id;
			deposit_card_line[demp].deposit_money(money, final);
			cout << "充值成功，从其他储蓄卡处转入此卡" << money << "元\n";
		} else {
			cout << "充值失败\n";
		}
	 }
}
//
void bangdingka() {
	cout << "请输入绑定卡中校园卡部分对应学号: ";
	string ID;
	getline(cin, ID);
	int demp, i;
	demp = judge_binding(ID);
	while (demp == -1) {
		cout << "查找失败，请尝试重新输入学号: ";
		getline(cin, ID);
		demp = judge_binding(ID);
	}
	//此处得到的demp为绑定卡对应位置；
	cout << "查找成功，管理绑定卡：\n"
	<< "1代表选择支付\n"
	<< "2代表选择查询绑定卡基本信息\n"
	<< "3代表选择查询绑定卡流水信息\n"
	<< "4代表选择从此卡转账入另外一张绑定卡\n"
	<< "5代表选择从此卡转账入储蓄卡\n"
	<< "6代表选择从此卡转账入校园卡\n"
	<< "7代表选择用现金充值此卡\n"
	<< "8代表选择用储蓄卡充值此卡\n"
	<< "9代表选择用另外一张绑定卡充值此卡\n"
	<< "请输入1~9做出你的选择：";
	string choose;
	getline(cin, choose);
	while (choose != "1"&&choose != "2"&&choose != "3"&&choose != "4"&&choose != "5"&&choose != "6"&&choose != "7"&&choose != "8"&&choose != "9") {
		cout << "输入有误，请输入1~9做出你的选择：";
		getline(cin, choose); 
	}
	if (choose == "1") {
		cout << "你选择了进行支付，请输入支付金额：";
		double money;
		cin >> money;								//输入支付金额 
		cin.get();
		bool hp = binding_card_line[demp].pay(money);
		if (hp == true) {							//支付成功 
			cout << "支付成功，绑定卡成功支出" << money << "元\n";
		} else {
			cout << "支付失败\n";		//支付失败 
		}
	} else if (choose == "2") {
		cout << "你选择查询绑定卡基本信息: \n";
		binding_card_line[demp].inquire1();
	} else if (choose == "3") {
		cout << "你选择查询绑定卡流水信息: \n";
		binding_card_line[demp].inquire2();
	} else if (choose == "4") {
		cout << "你选择从此卡转账入另外一张绑定卡，请输入另外一张绑定卡中校园卡部分对应学号：";
		string id;
		getline(cin, id);
		int de;
		de = judge_binding(id);
		while (de == -1) {
			cout << "查找失败，请尝试重新输入学号: ";
			getline(cin, id);
		}
		//此处得到de为绑定卡对应位置 
		cout << "查找成功，请输入转账金额：";
		double zhuanzhang;
		cin >> zhuanzhang;					//输入转账金额 
		cin.get();
		bool hp = binding_card_line[demp].pay(zhuanzhang);
		if (hp == true) {						//转账成功 
			string final = "绑定卡" + ID;
			binding_card_line[de].deposit_money(zhuanzhang, final);
			cout << "转账成功，从此卡向另外一张绑定卡转账" << zhuanzhang << "元\n";  
		} else {								//转账失败 
			cout << "转账失败\n";
		}
	} else if (choose == "5") {
		cout << "你选择从此卡转账入储蓄卡，请输入储蓄卡卡号：";
		string bank_id;
		getline(cin, bank_id);
		int de;
		de = judge_deposit(bank_id);
		while (de == -1) {
			cout << "查找失败，请尝试重新输入卡号：";
			getline(cin, bank_id);
		}
		//此处得到de为储蓄卡对应位置 
		cout << "查找成功，请输入转账金额：";
		double zhuanzhang;
		cin >> zhuanzhang;					//输入转账金额 
		cin.get();
		bool hp = binding_card_line[demp].pay(zhuanzhang);
		if (hp == true) {					//转账成功 
			string final = "绑定卡" + ID;
			deposit_card_line[de].deposit_money(zhuanzhang, final);
			cout << "转账成功，从此卡向储蓄卡转账" << zhuanzhang << "元\n";  
		} else {							//转账失败 
			cout << "转账失败\n";
		}
	} else if (choose == "6") {
		cout << "你选择从此卡转账入校园卡，请输入校园卡对应学号：";
		string stu_id;
		getline(cin, stu_id);
		int de;
		de = judge_campus(stu_id);
		while (de == -1) {
			cout << "输入有误，请尝试重新输入学号：";
			getline(cin, stu_id);
		}
		//此处得到de为校园卡对应位置 
		cout << "查找成功，请输入转账金额：";
		double zhuanzhang;
		cin >> zhuanzhang;			//输入转账金额 
		cin.get();
		bool hp = binding_card_line[demp].pay(zhuanzhang);
		if (hp == true) {				//转账成功 
			string final = "绑定卡" + ID;
			campus_card_line[de].deposit_money(zhuanzhang, final);
			cout << "转账成功，从此卡向校园卡转账" << zhuanzhang << "元\n"; 
		} else {
			cout << "转账失败\n";
		}
	} else if (choose == "7") {
		cout << "你选择用现金充值绑定卡，请输入充值现金金额：";
		double money;
		cin >> money;				//输入充值现金金额 
		cin.get();
		string final = "现金";
		binding_card_line[demp].deposit_money(money, final);
		cout << "充值成功，现金充值" << money << "元\n";
	} else if (choose == "8") {
		cout << "你选择用储蓄卡向此卡充值，请输入储蓄卡卡号：";
		string bank_id;
		getline(cin, bank_id);
		int de;
		de = judge_deposit(bank_id);
		while (de == -1) {
			cout << "查找失败，请尝试重新输入卡号：";
			getline(cin, bank_id);
		}
		//此处得到de为储蓄卡对应位置 
		cout << "查找成功，请输入充值金额：";
		double money;
		cin >> money;				//输入充值现金金额 
		cin.get();
		bool hp = deposit_card_line[de].pay(money);
		if (hp == true) {			//充值成功 
			string final = "储蓄卡" + bank_id;
			binding_card_line[demp].deposit_money(money, final);
			cout << "充值成功，由储蓄卡向此卡充值" << money << "元\n"; 
		} else {
			cout << "充值失败\n";
		}
	} else if (choose == "9") {
		cout << "你选择用其他绑定卡向此卡充值，请输入其他绑定卡中校园卡部分对应学号：";
		string stu_id;
		getline(cin, stu_id);
		int de;
		de = judge_binding(stu_id);
		while (de == -1) {
			cout << "查找失败，请尝试重新输入学号：";
			getline(cin, stu_id);
		}
		//此处得到de为绑定卡对应位置
		cout << "查找成功，请输入充值金额：";
		double money;
		cin >> money;				//输入充值金额 
		cin.get();
		bool hp = binding_card_line[de].pay(money);
		if (hp == true) {			//充值成功 
			string final = "绑定卡" + stu_id;
			binding_card_line[demp].deposit_money(money, final);
			cout << "充值成功，由其他绑定卡向此卡充值" << money << "元\n";  
		} else {
			cout << "充值失败\n";
		}
	}
}
//
void read_the_file() {
	ifstream fin;//创建ifstream对象 
	fin.open("E:\\campus_cards.txt");//打开校园卡信息文件 
	string temp;
	string fuzhu;
	fin >> max_campus_card;//校园卡总数 
	fin.get();//将数字后的换行读取掉 
	int i;
	double left_money;
	double m_record;
	char ch;
	//读取校园卡信息 
	for (i = 0; i < max_campus_card; i++) {
		//校园卡信息储存 
		getline(fin, temp);//将学生姓名储存在temp中 
		campus_card_line[i].set_student_name(temp);//将学生姓名复制到类对象中去 
		getline(fin, temp);//将学号储存
		campus_card_line[i].set_student_id(temp);//复制到类对象中
		getline(fin, temp);//将学院储存
		campus_card_line[i].set_student_institute(temp);//复制到类对象
		fin >> left_money;//校园卡余额 
		campus_card_line[i].set_campus_money_left(left_money);
		fin.get();
		fin.get(ch);
		while (ch == '+'||ch == '-') {//读取记录 
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
	fin.close();//关闭文件 
	//储蓄卡信息储存
	double over_money;
	double hasover; 
	fin.open("E:\\deposit_cards.txt");//打开储蓄卡信息文件 
	fin >> max_deposit_card;
	fin.get();
	for (i = 0; i < max_deposit_card; i++) {
		getline(fin, temp);//读取持卡人名字
		deposit_card_line[i].set_owner_name(temp);
		getline(fin, temp);//读取卡号
		deposit_card_line[i].set_bank_card_id(temp);
		getline(fin, temp);//读取发卡日期
		deposit_card_line[i].set_bank_card_date(temp);
		fin >> left_money;//读取储蓄卡余额 
		fin.get();
		deposit_card_line[i].set_deposit_money_left(left_money);
		fin >> over_money;//读取透支额度
		fin.get();
		deposit_card_line[i].set_money_overdraw(over_money);  
		fin >> hasover;//读取已经透支的金额 
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
			deposit_card_line[i].set_record(m_record, fuzhu);//读取流水信息 
			fin.get(ch);
		}
	}
	fin.close();//关闭文件
	//绑定卡信息储存
	int dep_n;
	int j;
	fin.open("E:\\binding_cards.txt");//打开绑定卡信息文件 
	fin >> max_binding_card;
	fin.get();
	for (i = 0; i < max_binding_card; i++) {
		getline(fin, temp);//读取校园卡对应姓名
		binding_card_line[i].set_student_name(temp);
		getline(fin, temp);//读取学号 
		binding_card_line[i].set_student_id(temp);
		getline(fin, temp);
		binding_card_line[i].set_student_institute(temp);
		fin >> left_money;//读取校园卡余额 
		fin.get();
		binding_card_line[i].set_campus_money_left(left_money);
		fin >> dep_n;//读取绑定储蓄卡张数 
		fin.get();
		binding_card_line[i].dep_num = dep_n;
		for (j = 0; j < dep_n; j++) {
			getline(fin, temp);//读取储蓄卡持卡人姓名 
			binding_card_line[i].num[j].set_owner_name(temp);
			getline(fin, temp);//读取储蓄卡卡号 
			binding_card_line[i].num[j].set_bank_card_id(temp);
			getline(fin, temp);//读取发卡日期 
			binding_card_line[i].num[j].set_bank_card_date(temp);
			fin >> left_money;//读取储蓄卡余额 
			fin.get();
			binding_card_line[i].num[j].set_deposit_money_left(left_money);
			fin >> over_money;//读取透支额度
			fin.get();
			binding_card_line[i].num[j].set_money_overdraw(over_money);
			fin >> hasover;//读取已经透支的金额 
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
	fin.close();//关闭文件 
}
//
void update_the_file() {
	ofstream fout;//创建一个ofstream变量
	fout.open("E:\\campus_cards.txt");//打开校园卡信息文件 
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
	fout.open("E:\\deposit_cards.txt");//打开储蓄卡信息文件 
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
	fout.open("E:\\binding_cards.txt");//打开绑定卡信息文件 
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
	//将文件内容导入 
	read_the_file();
	cout << "欢迎使用校园电子卡管理系统,此系统可以用于管理校园卡，储蓄卡，以及集二者为一体的绑定卡.\n";
	int choose;
	choose = menu();
	while (choose != 0) {
		if (choose == 1) {	//校园卡 
			xiaoyuanka();
		} else if (choose == 2) {	//储蓄卡 
			chuxuka();
		} else if (choose == 3) {	//绑定卡 
			bangdingka();
		}
		update_the_file();
		//将改变储存文件
		system("pause");
		system("cls");
		choose = menu();
	}
	cout << "你选择了退出系统\n";
	return 0;
}

