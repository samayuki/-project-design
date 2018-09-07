#include<iostream>
#include<string>
#include<fstream> 
#include"多项式类.cpp"
using namespace std;

Polynomial Data_list[1000];								//储存从文件中读取的数据 
int num_of_poly = 0;									//Data_list中已经储存的多项式数目 

//
int functionList();
int getNumber();
void get_data_from_file();
void keep_data_to_file();
string need_help_or_not();
bool judge(string temp);
void add_poly();
void sub_poly();
Polynomial get_poly();
void quit();
void store_poly(Polynomial & temp);
void cons_poly();
void show_all();
void evaluation();
Polynomial get_duoxiangshi();
int exit(string & m_name);
void is_same();
void qiudao();
//

int main() {
	get_data_from_file();						//读取文件中数据 
	cout << "欢迎使用此软件\n"; 
	cout << "多项式输入要求: 多项式表示为数对的形式输入，如x^2+3,输入应该为p=(1,2)(3,0).第一个数字为系数，第二个数字为次数。"
		<< "当上述例子输入时有p=,则此多项式被储存在文档中，名字为p; 否则不储存。"
		<< "当然你可以输入已经储存了的多项式的名字来代替\n\n";
	cout << "请问您是否需要查看程序功能列表?\n"
		<< "请输入yes查看，或者输入no直接启用： ";
	string help_or_not;
	int choose;
	help_or_not = need_help_or_not();
	while (help_or_not != "yes"&&help_or_not != "no") {
		cout << "输入错误，请输入yes或no确定您是否需要查看功能列表: ";
		help_or_not = need_help_or_not();
	}
	if (help_or_not == "yes") {				//需要帮助，启用functionList()函数 
		choose = functionList();
	} else {								//不需要，直接启动 
		choose = getNumber();
	}
	while(choose != 0) {
		if (choose == 1) {
			add_poly();
		} else if (choose == 2) {
			sub_poly();
		} else if (choose == 3) {
			cons_poly();
		} else if (choose == 4) {
			evaluation(); 
		} else if (choose == 5) {
			show_all();
		} else if (choose == 6) {
			is_same();
		} else if (choose == 7) {
			qiudao();
		}
		keep_data_to_file();
		cout << "完成一次操作.\n";
		system("pause");
		system("cls");
		cout << "请问您是否需要查看程序功能列表?\n"
			<< "请输入yes查看，或者输入no直接启用： ";
		help_or_not = need_help_or_not();
		while (help_or_not != "yes"&&help_or_not != "no") {
			cout << "输入错误，请输入yes或no确定您是否需要查看功能列表: ";
			help_or_not = need_help_or_not();
		}
		if (help_or_not == "yes") {				//需要帮助，启用functionList()函数 
			choose = functionList();
		} else {								//不需要，直接启动 
			choose = getNumber();
		}
	}
	quit();
	return 0;
}

// 
int getNumber() {										//返回用户想要实现的功能 
	int choose;
	cout << "请输入相应的数字以启用相应功能: ";
	cin >> choose;										//输入数字 
	while (!(choose >= 0&&choose <= 7)) {				//数字不在范围内，重新输入 
		cin.clear();
		cout << "输入错误，请输入0 ~ 7中的某个数字: ";
		cin >> choose;
	}
	return choose;										//输入成功返回用户所要求的功能 
}

//
int functionList() {									//功能列表
	cout << "功能如下: \n"
		<< "	1.两个多项式相加\n"
		<< "	2.两个多项式相减\n"
		<< "	3.一个多项式与一个整数常数的乘法运算\n"
		<< "	4.求多项式中未知数带入某个整数后得到的值\n"
		<< "	5.显示所有储存的多项式\n"
		<< "	6.判断两多项式是否相等\n"
		<< "	7.对多项式求导\n"
		<< "	0.退出系统\n\n";
		int choose;
		choose = getNumber();
		return choose;
}

//
void get_data_from_file() {								//从文件中读取所有数据 
	ifstream fin("E:\\polynomial.txt");					//打开文件 
	while(!fin.is_open()) {
		ifstream fin("E:\\polynomial.txt");				//文件打开错误，重试中 
	}
	fin >> num_of_poly;									//得到数据个数 
	string temp;
	string m_name;
	string m_output;
	int lenth, i, sign, k = 0;
	while(k < num_of_poly) {
		fin >> temp;									//先将多项式字符串读取到temp中 
		lenth = temp.size();							//字符串长度 
		sign = temp.find('=');						//找到=号 
		m_name = temp.substr(0, sign);				//得到名字 
		m_output = temp.erase(0, sign + 1);			//得到储存格式 
		Polynomial get(m_name, m_output);
		Data_list[k] = get;							//将数据储存到一个对象中 
		k++;
	}
	for (i = 0; i < num_of_poly; i++) {
	}
	fin.close();
}

// 
void keep_data_to_file() {								//将改变储存到文件中 
	ofstream fout("E:\\polynomial.txt");
	while(!fout.is_open()) {
		ofstream fout("E:\\polynomial.txt");				//文件打开错误，重试中 
	}
	int i;
	fout << num_of_poly << endl;
	for (i = 0; i < num_of_poly; i++) {
		fout << Data_list[i].getName() << "=";
		fout << Data_list[i].getStore() << endl;
	}
	fout.close();
}

//
string need_help_or_not() {							//是否查看功能列表 
	string help_or_not;
	cin >> help_or_not;
	return help_or_not;
}

//
bool judge(string temp) {							//判断输入是否标准 
	int i, lenth, a = 0, b = 0, c = 0;
	lenth = temp.size();
	bool h = true;
	if (temp[0] == '('&&temp[lenth - 1] == ')') {
		for (i = 0; i < lenth; i++) {
			if (temp[i] == '(') {
				a++;
				if (!(a == (b + 1)&&a == (c + 1))) {
					h = false;
					break; 
				}
			} else if (temp[i] == ',') {
				b++;
				if (!(a == b&&a == (c + 1))) {
					h = false;
					break;
				}
			} else if (temp[i] == ')') {
				c++;
				if (!(a == b&&a == c)) {
					h = false;
					break;
				}
			}
		}
	} else {
		h = false;
	}
	return h;
}

//
int exit(string & m_name) {							//名字存在返回对应i，不存在返回-1 
	int i = 0, a = 0;
	for (i = 0; i < num_of_poly; i++) {
		if (m_name == Data_list[i].getName()) {			//名字存在 
			a = 1; break; 
		}
	}
	if (a == 1) {
		return i;
	} else {
		return -1;
	}
}

//
Polynomial get_poly() {
	string temp;
	string m_name;
	int sign;
	bool get = false;
	bool t_name;
	bool judge_right;
	while (!get) {
		t_name = false;
		cin >>  temp;
		if ((sign = temp.find('=')) != string::npos) {		//找到=号, 有名字 
			t_name = true;
			int exit_or_not;
			m_name = temp.substr(0, sign);
			exit_or_not = exit(m_name);						//判断输入的名字是否已经用过了
			if (exit_or_not >= 0) {
				cout << "错误！此名字已经用于其他多项式，请重新输入: ";
				continue;									//跳过剩余步骤 
			} else {
				temp =  temp.erase(0, sign + 1);			//将temp名字去掉 
			}
		}
		judge_right = judge(temp);					//判断输入是否符合要求 
		if (!judge_right) {
			 cout << "错误！输入格式不正确，请重新输入: ";
			 continue;
		} else {
			get = true;
		}
	}
	Polynomial te(m_name, temp);
	if (t_name) {									//有名字把多项式储存起来 
		Data_list[num_of_poly] = te;
		num_of_poly++;
	}
	return te;
}

//
void store_poly(Polynomial & temp) {
	cout << "您选择了储存结果, 现在请输入您想要给与这个结果多项式的名字: ";
	string n_name;
	cin >> n_name;
	int a;
	while ((a = exit(n_name)) >= 0) {
		cout << "不好意思, 此名称已被使用, 请重新输入: ";
		cin >> n_name;
	}
	Polynomial te(n_name, temp.getStore());
	Data_list[num_of_poly] = te;
	num_of_poly++;
	cout << "储存成功! " << te.getName() << "=";
	te.Output();
}

//
void add_poly() {
	Polynomial temp1;
	Polynomial temp2;
	Polynomial answer;
	cout << "您选择了使两个多项式相加\n" << "输入第一个多项式, ";
	temp1 = get_duoxiangshi();
	cout << "输入成功: ";
	temp1.Output();
	cout << "输入第二个多项式, ";
	temp2 = get_duoxiangshi();
	cout << "输入成功: ";
	temp2.Output();
	answer = temp1.oper_add(temp2);
	cout << "结果: ";
	answer.Output();
	cout << "是否希望系统储存此结果, 若希望则输入1, 不希望则输入0: ";
	int answer_store;
	cin >> answer_store;
	while (answer_store != 1&&answer_store != 0) {
		cout << "错误, 请输入1或0: ";
		cin >> answer_store;
	}
	if (answer_store == 1) {
		store_poly(answer);							//储存结果 
	} else {
		cout << "您选择了不储存\n";
	} 
}

//
void sub_poly() {
	Polynomial temp1;
	Polynomial temp2;
	Polynomial answer;
	cout << "您选择了使两个多项式相减\n" << "输入第一个多项式, ";
	temp1 = get_duoxiangshi();
	cout << "输入成功: ";
	temp1.Output();
	cout << "输入第二个多项式, ";
	temp2 = get_duoxiangshi();
	cout << "输入成功: ";
	temp2.Output();
	answer = temp1.oper_sub(temp2);
	cout << "结果: ";
	answer.Output();
	cout << "是否希望系统储存此结果, 若希望则输入1, 不希望则输入0: ";
	int answer_store;
	cin >> answer_store;
	while (answer_store != 1&&answer_store != 0) {
		cout << "错误, 请输入1或0: ";
		cin >> answer_store;
	}
	if (answer_store == 1) {
		store_poly(answer);								//储存结果 
	} else {
		cout << "您选择了不储存\n";
	}
}

//
void cons_poly() {							//与整数常数相乘
	Polynomial temp1;
	Polynomial answer;
	int constant; 
	cout << "您选择令一个多项式与一个整数相乘, 请输入多项式: ";
	temp1 = get_duoxiangshi();
	cout << "输入成功: ";
	temp1.Output();
	cout << "输入整数常数: ";
	cin >>  constant;
	answer = temp1.oper_constant(constant);
	cout << "结果: ";
	answer.Output();
	cout << "是否希望系统储存此结果, 若希望则输入1, 不希望则输入0: ";
	int answer_store;
	cin >> answer_store;
	while (answer_store != 1&&answer_store != 0) {
		cout << "错误, 请输入1或0: ";
		cin >> answer_store;
	}
	if (answer_store == 1) {
		store_poly(answer);								//储存结果 
	} else {
		cout << "您选择了不储存\n";
	}
}

//
void evaluation() {										//多项式求值 
	cout << "您选择了对多项式求值, 请输入您想要对其求值的多项式: ";
	Polynomial temp1;
	double answer;
	int value;
	temp1 = get_duoxiangshi();
	cout << "输入成功: ";
	temp1.Output();
	cout << "现在请输入未知变量x的值(只限整数): ";
	cin >> value;
	answer =  temp1.oper_value(value);
	cout << "结果: " << answer << endl; 
}

//
void show_all() {									//显示所有已经储存的多项式 
	int i;
	cout << "以下是所有已经储存的多项式: \n";
	for (i = 0; i < num_of_poly; i++) {
		cout << Data_list[i].getName() << "=";
		Data_list[i].Output(); 
	}
}

// 
Polynomial get_duoxiangshi() {
	Polynomial temp1;
	string te_name1;
	string aorb;
	int panduan_name;
	cout << "请选择是直接输入多项式（输入a）还是输入已经储存的多项式的名称(输入b): ";
	cin >> aorb;
	while (aorb != "a"&&aorb != "b") {
		cout << "输入错误，请选择输入a或b: ";
	 	cin >> aorb;
	}
	if (aorb == "a") {
	 	cout << "您选择了直接输入多项式，现在请输入多项式: ";
		temp1 = get_poly();
	} else {
	 	cout << "您选择了输入多项式名字，现在请输入多项式名字: ";
	 	cin >> te_name1;
	 	panduan_name = exit(te_name1);
	 	while (panduan_name < 0) {
	 		cout << "错误！为找到对应的多项式，名字错误，请重新输入: ";
	 		cin >> te_name1;
	 		panduan_name = exit(te_name1);
		}
		temp1 = Data_list[panduan_name];
	}
	return temp1;
}

//
void is_same() {
	Polynomial temp1;
	Polynomial temp2;
	string string1, string2;
	cout << "您选择了判断两个多项式是否相等\n" << "输入第一个多项式: ";
	temp1 = get_duoxiangshi();
	cout << "输入成功: ";
	temp1.Output();
	cout << "输入第二个多项式, ";
	temp2 = get_duoxiangshi();
	cout << "输入成功: ";
	temp2.Output();
	string1 = temp1.getStore();
	string2 = temp2.getStore();
	if (string1 == string2) {
		cout << "结果: 这两个多项式相等\n";
	} else {
		cout << "结果: 这两个多项式并不相等\n";
	}
}

//
void qiudao() {
	Polynomial temp1;
	Polynomial answer;
	int n;
	cout << "您选择了对多项式求导, 输入多项式: ";
	temp1 = get_duoxiangshi();
	cout << "输入成功: ";
	temp1.Output();
	cout << "输入你想求导的次数: ";
	cin >> n;
	while (n <= 0) {
		cout << "求导的次数需为正整数, 请重新输入: ";
		cin >> n;
	}
	answer = temp1.oper_qiudao(n);
	cout << "结果: ";
	answer.Output();
	cout << "是否希望系统储存此结果, 若希望则输入1, 不希望则输入0: ";
	int answer_store;
	cin >> answer_store;
	while (answer_store != 1&&answer_store != 0) {
		cout << "错误, 请输入1或0: ";
		cin >> answer_store;
	}
	if (answer_store == 1) {
		store_poly(answer);								//储存结果 
	} else {
		cout << "您选择了不储存\n";
	}
} 

//
void quit() {										//选了0，退出 
	cout << "您选择了退出系统\n欢迎下次使用\n";
}
