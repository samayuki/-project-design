#include<iostream>
#include<string>
#include<fstream> 
#include"����ʽ��.cpp"
using namespace std;

Polynomial Data_list[1000];								//������ļ��ж�ȡ������ 
int num_of_poly = 0;									//Data_list���Ѿ�����Ķ���ʽ��Ŀ 

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
	get_data_from_file();						//��ȡ�ļ������� 
	cout << "��ӭʹ�ô����\n"; 
	cout << "����ʽ����Ҫ��: ����ʽ��ʾΪ���Ե���ʽ���룬��x^2+3,����Ӧ��Ϊp=(1,2)(3,0).��һ������Ϊϵ�����ڶ�������Ϊ������"
		<< "��������������ʱ��p=,��˶���ʽ���������ĵ��У�����Ϊp; ���򲻴��档"
		<< "��Ȼ����������Ѿ������˵Ķ���ʽ������������\n\n";
	cout << "�������Ƿ���Ҫ�鿴�������б�?\n"
		<< "������yes�鿴����������noֱ�����ã� ";
	string help_or_not;
	int choose;
	help_or_not = need_help_or_not();
	while (help_or_not != "yes"&&help_or_not != "no") {
		cout << "�������������yes��noȷ�����Ƿ���Ҫ�鿴�����б�: ";
		help_or_not = need_help_or_not();
	}
	if (help_or_not == "yes") {				//��Ҫ����������functionList()���� 
		choose = functionList();
	} else {								//����Ҫ��ֱ������ 
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
		cout << "���һ�β���.\n";
		system("pause");
		system("cls");
		cout << "�������Ƿ���Ҫ�鿴�������б�?\n"
			<< "������yes�鿴����������noֱ�����ã� ";
		help_or_not = need_help_or_not();
		while (help_or_not != "yes"&&help_or_not != "no") {
			cout << "�������������yes��noȷ�����Ƿ���Ҫ�鿴�����б�: ";
			help_or_not = need_help_or_not();
		}
		if (help_or_not == "yes") {				//��Ҫ����������functionList()���� 
			choose = functionList();
		} else {								//����Ҫ��ֱ������ 
			choose = getNumber();
		}
	}
	quit();
	return 0;
}

// 
int getNumber() {										//�����û���Ҫʵ�ֵĹ��� 
	int choose;
	cout << "��������Ӧ��������������Ӧ����: ";
	cin >> choose;										//�������� 
	while (!(choose >= 0&&choose <= 7)) {				//���ֲ��ڷ�Χ�ڣ��������� 
		cin.clear();
		cout << "�������������0 ~ 7�е�ĳ������: ";
		cin >> choose;
	}
	return choose;										//����ɹ������û���Ҫ��Ĺ��� 
}

//
int functionList() {									//�����б�
	cout << "��������: \n"
		<< "	1.��������ʽ���\n"
		<< "	2.��������ʽ���\n"
		<< "	3.һ������ʽ��һ�����������ĳ˷�����\n"
		<< "	4.�����ʽ��δ֪������ĳ��������õ���ֵ\n"
		<< "	5.��ʾ���д���Ķ���ʽ\n"
		<< "	6.�ж�������ʽ�Ƿ����\n"
		<< "	7.�Զ���ʽ��\n"
		<< "	0.�˳�ϵͳ\n\n";
		int choose;
		choose = getNumber();
		return choose;
}

//
void get_data_from_file() {								//���ļ��ж�ȡ�������� 
	ifstream fin("E:\\polynomial.txt");					//���ļ� 
	while(!fin.is_open()) {
		ifstream fin("E:\\polynomial.txt");				//�ļ��򿪴��������� 
	}
	fin >> num_of_poly;									//�õ����ݸ��� 
	string temp;
	string m_name;
	string m_output;
	int lenth, i, sign, k = 0;
	while(k < num_of_poly) {
		fin >> temp;									//�Ƚ�����ʽ�ַ�����ȡ��temp�� 
		lenth = temp.size();							//�ַ������� 
		sign = temp.find('=');						//�ҵ�=�� 
		m_name = temp.substr(0, sign);				//�õ����� 
		m_output = temp.erase(0, sign + 1);			//�õ������ʽ 
		Polynomial get(m_name, m_output);
		Data_list[k] = get;							//�����ݴ��浽һ�������� 
		k++;
	}
	for (i = 0; i < num_of_poly; i++) {
	}
	fin.close();
}

// 
void keep_data_to_file() {								//���ı䴢�浽�ļ��� 
	ofstream fout("E:\\polynomial.txt");
	while(!fout.is_open()) {
		ofstream fout("E:\\polynomial.txt");				//�ļ��򿪴��������� 
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
string need_help_or_not() {							//�Ƿ�鿴�����б� 
	string help_or_not;
	cin >> help_or_not;
	return help_or_not;
}

//
bool judge(string temp) {							//�ж������Ƿ��׼ 
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
int exit(string & m_name) {							//���ִ��ڷ��ض�Ӧi�������ڷ���-1 
	int i = 0, a = 0;
	for (i = 0; i < num_of_poly; i++) {
		if (m_name == Data_list[i].getName()) {			//���ִ��� 
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
		if ((sign = temp.find('=')) != string::npos) {		//�ҵ�=��, ������ 
			t_name = true;
			int exit_or_not;
			m_name = temp.substr(0, sign);
			exit_or_not = exit(m_name);						//�ж�����������Ƿ��Ѿ��ù���
			if (exit_or_not >= 0) {
				cout << "���󣡴������Ѿ�������������ʽ������������: ";
				continue;									//����ʣ�ಽ�� 
			} else {
				temp =  temp.erase(0, sign + 1);			//��temp����ȥ�� 
			}
		}
		judge_right = judge(temp);					//�ж������Ƿ����Ҫ�� 
		if (!judge_right) {
			 cout << "���������ʽ����ȷ������������: ";
			 continue;
		} else {
			get = true;
		}
	}
	Polynomial te(m_name, temp);
	if (t_name) {									//�����ְѶ���ʽ�������� 
		Data_list[num_of_poly] = te;
		num_of_poly++;
	}
	return te;
}

//
void store_poly(Polynomial & temp) {
	cout << "��ѡ���˴�����, ��������������Ҫ��������������ʽ������: ";
	string n_name;
	cin >> n_name;
	int a;
	while ((a = exit(n_name)) >= 0) {
		cout << "������˼, �������ѱ�ʹ��, ����������: ";
		cin >> n_name;
	}
	Polynomial te(n_name, temp.getStore());
	Data_list[num_of_poly] = te;
	num_of_poly++;
	cout << "����ɹ�! " << te.getName() << "=";
	te.Output();
}

//
void add_poly() {
	Polynomial temp1;
	Polynomial temp2;
	Polynomial answer;
	cout << "��ѡ����ʹ��������ʽ���\n" << "�����һ������ʽ, ";
	temp1 = get_duoxiangshi();
	cout << "����ɹ�: ";
	temp1.Output();
	cout << "����ڶ�������ʽ, ";
	temp2 = get_duoxiangshi();
	cout << "����ɹ�: ";
	temp2.Output();
	answer = temp1.oper_add(temp2);
	cout << "���: ";
	answer.Output();
	cout << "�Ƿ�ϣ��ϵͳ����˽��, ��ϣ��������1, ��ϣ��������0: ";
	int answer_store;
	cin >> answer_store;
	while (answer_store != 1&&answer_store != 0) {
		cout << "����, ������1��0: ";
		cin >> answer_store;
	}
	if (answer_store == 1) {
		store_poly(answer);							//������ 
	} else {
		cout << "��ѡ���˲�����\n";
	} 
}

//
void sub_poly() {
	Polynomial temp1;
	Polynomial temp2;
	Polynomial answer;
	cout << "��ѡ����ʹ��������ʽ���\n" << "�����һ������ʽ, ";
	temp1 = get_duoxiangshi();
	cout << "����ɹ�: ";
	temp1.Output();
	cout << "����ڶ�������ʽ, ";
	temp2 = get_duoxiangshi();
	cout << "����ɹ�: ";
	temp2.Output();
	answer = temp1.oper_sub(temp2);
	cout << "���: ";
	answer.Output();
	cout << "�Ƿ�ϣ��ϵͳ����˽��, ��ϣ��������1, ��ϣ��������0: ";
	int answer_store;
	cin >> answer_store;
	while (answer_store != 1&&answer_store != 0) {
		cout << "����, ������1��0: ";
		cin >> answer_store;
	}
	if (answer_store == 1) {
		store_poly(answer);								//������ 
	} else {
		cout << "��ѡ���˲�����\n";
	}
}

//
void cons_poly() {							//�������������
	Polynomial temp1;
	Polynomial answer;
	int constant; 
	cout << "��ѡ����һ������ʽ��һ���������, ���������ʽ: ";
	temp1 = get_duoxiangshi();
	cout << "����ɹ�: ";
	temp1.Output();
	cout << "������������: ";
	cin >>  constant;
	answer = temp1.oper_constant(constant);
	cout << "���: ";
	answer.Output();
	cout << "�Ƿ�ϣ��ϵͳ����˽��, ��ϣ��������1, ��ϣ��������0: ";
	int answer_store;
	cin >> answer_store;
	while (answer_store != 1&&answer_store != 0) {
		cout << "����, ������1��0: ";
		cin >> answer_store;
	}
	if (answer_store == 1) {
		store_poly(answer);								//������ 
	} else {
		cout << "��ѡ���˲�����\n";
	}
}

//
void evaluation() {										//����ʽ��ֵ 
	cout << "��ѡ���˶Զ���ʽ��ֵ, ����������Ҫ������ֵ�Ķ���ʽ: ";
	Polynomial temp1;
	double answer;
	int value;
	temp1 = get_duoxiangshi();
	cout << "����ɹ�: ";
	temp1.Output();
	cout << "����������δ֪����x��ֵ(ֻ������): ";
	cin >> value;
	answer =  temp1.oper_value(value);
	cout << "���: " << answer << endl; 
}

//
void show_all() {									//��ʾ�����Ѿ�����Ķ���ʽ 
	int i;
	cout << "�����������Ѿ�����Ķ���ʽ: \n";
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
	cout << "��ѡ����ֱ���������ʽ������a�����������Ѿ�����Ķ���ʽ������(����b): ";
	cin >> aorb;
	while (aorb != "a"&&aorb != "b") {
		cout << "���������ѡ������a��b: ";
	 	cin >> aorb;
	}
	if (aorb == "a") {
	 	cout << "��ѡ����ֱ���������ʽ���������������ʽ: ";
		temp1 = get_poly();
	} else {
	 	cout << "��ѡ�����������ʽ���֣��������������ʽ����: ";
	 	cin >> te_name1;
	 	panduan_name = exit(te_name1);
	 	while (panduan_name < 0) {
	 		cout << "����Ϊ�ҵ���Ӧ�Ķ���ʽ�����ִ�������������: ";
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
	cout << "��ѡ�����ж���������ʽ�Ƿ����\n" << "�����һ������ʽ: ";
	temp1 = get_duoxiangshi();
	cout << "����ɹ�: ";
	temp1.Output();
	cout << "����ڶ�������ʽ, ";
	temp2 = get_duoxiangshi();
	cout << "����ɹ�: ";
	temp2.Output();
	string1 = temp1.getStore();
	string2 = temp2.getStore();
	if (string1 == string2) {
		cout << "���: ����������ʽ���\n";
	} else {
		cout << "���: ����������ʽ�������\n";
	}
}

//
void qiudao() {
	Polynomial temp1;
	Polynomial answer;
	int n;
	cout << "��ѡ���˶Զ���ʽ��, �������ʽ: ";
	temp1 = get_duoxiangshi();
	cout << "����ɹ�: ";
	temp1.Output();
	cout << "���������󵼵Ĵ���: ";
	cin >> n;
	while (n <= 0) {
		cout << "�󵼵Ĵ�����Ϊ������, ����������: ";
		cin >> n;
	}
	answer = temp1.oper_qiudao(n);
	cout << "���: ";
	answer.Output();
	cout << "�Ƿ�ϣ��ϵͳ����˽��, ��ϣ��������1, ��ϣ��������0: ";
	int answer_store;
	cin >> answer_store;
	while (answer_store != 1&&answer_store != 0) {
		cout << "����, ������1��0: ";
		cin >> answer_store;
	}
	if (answer_store == 1) {
		store_poly(answer);								//������ 
	} else {
		cout << "��ѡ���˲�����\n";
	}
} 

//
void quit() {										//ѡ��0���˳� 
	cout << "��ѡ�����˳�ϵͳ\n��ӭ�´�ʹ��\n";
}
