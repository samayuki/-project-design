#ifndef POLY_H_
#define POLY_H_
#include<iostream>
#include<string>
#include<cmath>
using namespace std;

class Polynomial {
private:
	string name;						//����ʽ������ 
	string output;						//����ʽ��Ҫ����ĸ�ʽ
	int dataPlus[1000];					//����ʽ�������д���Ϊ������Ĳ��֣���data[����] = ϵ���� 
	int dataMinus[1000];				//����ʽ�������д���Ϊ���Ĳ���
	int min_cishu_fu;					//����ʽ��С���� 
	int max_cishu_zheng;				//����ʽ������ 
public:
	Polynomial();
	Polynomial(const string & n, const string & op);
	string getName();									//�õ�����ʽ���� 
	void Output();
	string getStore();
	Polynomial oper_add(const Polynomial & tem);		//�ӷ� 
	Polynomial oper_sub(const Polynomial & tem);		//���� 
	Polynomial oper_constant(int tem);					//�볣���� 
	double oper_value(int val);
	string num_to_char(int max, int min, int * temp_zheng, int * temp_fu);
	Polynomial oper_qiudao(int n);						//�󵼲��� 
};

//
Polynomial::Polynomial() {
	max_cishu_zheng = 0;
	min_cishu_fu = 0;
	name = "No Name";
	output = "0";
	int i;
	for (i = 0; i < 1000; i++) {
		dataPlus[i] = 0;
		dataMinus[i] = 0;
	}
}

//
Polynomial::Polynomial(const string & n, const string & op) {		//�������� 
	name = n;
	output = op;
	max_cishu_zheng = 0;
	min_cishu_fu = 0;
	int lenth = output.size();
	int i, j, pos = 0, k = 0, a, b, c;
	int where_qian[1000], where_dou[1000], where_hou[1000];
	int cishu = 0, xishu = 0;
	for (i = 0; i < 1000; i++) {
		dataPlus[i] = 0;
		dataMinus[i] = 0;
	}
	for(i = 0; i < lenth; i++) {						//����������ڵ�λ�� 
		if (output[i] == '(') {
			where_qian[k] = i;
		} else if(output[i] == ',') {
			where_dou[k] = i;
		} else if(output[i] == ')') {
			where_hou[k] = i;
			k++;
		}
	}
	for(i = 0; i < k; i++) {							//�ܹ���k��()�� 
		a = where_qian[i]; b = where_dou[i]; c = where_hou[i];
		xishu = 0; cishu = 0;
		if (output[a + 1] == '-') {						//ϵ��Ϊ�� 
			for(j = b - 1; j > (a + 1); j--) {
				int m = output[j] - '0';
				xishu += m * (int)pow(10, (b - j - 1));
			}
			xishu = 0 - xishu; 							//�õ�ϵ�� 
		} else {										//ϵ��Ϊ�� 
			for(j = b - 1; j > a; j--) {
				int m = output[j] - '0';
				xishu += m * (int)pow(10, (b - j - 1));
			}
		}
		if (output[b + 1] == '-') {						//����Ϊ�� 
			for(j = c - 1; j > (b + 1); j--) {
				int m = output[j] - '0';
				cishu += m * (int)pow(10, (c - j - 1));
			}
			cishu = 0 - cishu; 							//�õ����� 
		} else {										//����Ϊ�� 
			for(j = c - 1; j > b; j--) {
				int m = output[j] - '0';
				cishu += m * (int)pow(10, (c - j - 1));
			}
		}
		if (cishu >= 0) {			//�������ڵ���0������ dataPlus[1000]�� 
			dataPlus[cishu] = xishu;
			if (cishu > max_cishu_zheng) {
				max_cishu_zheng = cishu;	//�޸������� 
			}
		} else {					//����С��0������ dadaMinus[1000]�� 
			cishu = 0 - cishu;
			dataMinus[cishu] = xishu;
			if (cishu > min_cishu_fu) {
				min_cishu_fu = cishu;		//�޸���С���� 
			}
		}
	}
}

//
string Polynomial::getName() {
	return name;
}

//
void Polynomial::Output() {				//ת��Ϊ�����ʽ 
	int i;
	if (max_cishu_zheng > 1) {
		if (dataPlus[max_cishu_zheng] != 0) {
			if (dataPlus[max_cishu_zheng] == 1) {
				cout << "x^" << max_cishu_zheng;
			} else if (dataPlus[max_cishu_zheng] == -1) {
				cout << "-" << "x^" << max_cishu_zheng;
			} else {
				cout << dataPlus[max_cishu_zheng] << "x^" << max_cishu_zheng;
			}
		}
		for (i = max_cishu_zheng - 1; i > 1; i--) {
			if (dataPlus[i] > 0) {
				cout << "+";
				if (dataPlus[i] != 1) {
					cout << dataPlus[i];
				}
				cout << "x^" << i;
			} else if(dataPlus[i] < 0) {									//����ߴ���������2 
				if (dataPlus[i] != -1) {
					cout << dataPlus[i] << "x^" << i;
				} else {
					cout << "-" << "x^" << i;
				}
			}
		}
	}
	if(dataPlus[1] > 0) {
		if (max_cishu_zheng == 1) {
			if (dataPlus[1] != 1) {
				cout << dataPlus[1];
			}
			cout << "x";
		} else {
			cout << "+";
			if (dataPlus[1] != 1) {
				cout << dataPlus[1];
			}
			cout << "x";
		}
	} else if (dataPlus[1] < 0) {										//�����жϴ���Ϊ1ʱ 
		if (dataPlus[1] == -1) {
			cout << "-" << "x";
		} else {
			cout << dataPlus[1] << "x";
		}
	}
	if(dataPlus[0] > 0) {
		if (max_cishu_zheng != 0) {
			cout << "+";
		}
		cout << dataPlus[0];
	} else if (dataPlus[0] < 0) {										//�����жϳ��� 
		cout << dataPlus[0];
	}
	for (i = 1; i <= min_cishu_fu; i++) {
		if (dataMinus[i] > 0) {
			cout << "+";
			if (dataMinus[i] != 1) {
				cout << dataMinus[i];
			}
			cout << "x^-" << i;
		} else if(dataMinus[i] < 0) {
			if (dataMinus[i] == -1) {
				cout << "-" << "x^-" << i;
			} else {
				cout << dataMinus[i] << "x^-" << i;									//��-2��������ʹ� 
			}
		}
	}
	if (max_cishu_zheng == 0&&min_cishu_fu == 0&&dataPlus[0] == 0) {
		cout << "0";
	}
	cout << endl; 
}

//
string Polynomial::getStore() {
	return output;
}

//
double Polynomial::oper_value(int val) {
	int i;
	double sum = 0;
	for (i = max_cishu_zheng; i >= 0; i--) {
		sum += dataPlus[i] * pow(val, i);
	}
	for (i = 1; i <= min_cishu_fu; i++) {
		sum += dataMinus[i] * pow(val, (-i));
	}
	return sum;
}

//
Polynomial Polynomial::oper_constant(int tem) {
	string m_name;
	m_name = getName();									//�õ�����ʽ������ 
	int temp_zheng[1000] = {0};
	int temp_fu[1000] = {0};							//������int����������������ֹ�ı�ԭ������ 
	int i;
	for (i = 0; i <= max_cishu_zheng; i++) {
		temp_zheng[i] = dataPlus[i] * tem;
	}
	for (i = 1; i <= min_cishu_fu; i++) {
		temp_fu[i] = dataMinus[i] * tem;
	}													//����������� 
	string m_output = this->num_to_char(max_cishu_zheng, min_cishu_fu, temp_zheng, temp_fu);
	Polynomial abc(m_name, m_output);
	return abc;
}

//
string Polynomial::num_to_char(int max_cishu_zheng, int min_cishu_fu, int * temp_zheng, int * temp_fu) {
	char ans[2000];
	int ch[10];
	int k = 0, j, h, m, i;
	for (i = max_cishu_zheng; i > 0; i--) {
		if (temp_zheng[i] != 0) {
			ans[k] = '('; k++;
			if (temp_zheng[i] < 0) {
				ans[k] = '-'; k++;
				temp_zheng[i] = 0 - temp_zheng[i];
			}
			for (j = 0; temp_zheng[i] > 0; j++) {
				ch[j] = temp_zheng[i] % 10;
				temp_zheng[i] = temp_zheng[i] / 10;
			}
			j--;
			for (h = j; h >= 0; h--) {
				ans[k] = '0' + ch[h];
				k++;
			}
			ans[k] = ','; k++;
			m = i;
			for (j = 0; m > 0; j++) {
				ch[j] = m % 10;
				m = m / 10;		//��ϵ��Ϊjλ�� 
			}
			j--;
			for (h = j; h >= 0; h--) {
				ans[k] = '0' + ch[h];
				k++;
			}
			ans[k] = ')'; k++;
		}
	}
	if (temp_zheng[0] != 0) {
		ans[k] = '('; k++;
			if (temp_zheng[0] < 0) {
				ans[k] = '-'; k++;
				temp_zheng[0] = 0 - temp_zheng[0];
			}
			for (j = 0; temp_zheng[0] > 0; j++) {
				ch[j] = temp_zheng[0] % 10;
				temp_zheng[0] = temp_zheng[0] / 10;
			}
			j--;
			for (h = j; h >= 0; h--) {
				ans[k] = 48 + ch[h];
				k++;
			}
			ans[k] = ','; k++;
			ans[k] = '0'; k++;
			ans[k] = ')'; k++;
	}
	for (i = 1; i <= min_cishu_fu; i++) {
		if (temp_fu[i] != 0) {
			ans[k] = '('; k++;
			if (temp_fu[i] < 0) {
				ans[k] = '-'; k++;						//ϵ��Ϊ�����Ӹ��� 
				temp_fu[i] = 0 - temp_fu[i];
			}
			for (j = 0; temp_fu[i] > 0; j++) {
				ch[j] = temp_fu[i] % 10;
				temp_fu[i] = temp_fu[i] / 10;		//��ϵ��Ϊjλ�� 
			}
			j--;
			for (h = j; h >= 0; h--) {
				ans[k] = '0' + ch[h];
				k++;
			}
			ans[k] = ','; k++;
			ans[k] = '-'; k++;
			m = i;
			for (j = 0; m > 0; j++) {
				ch[j] = m % 10;
				m = m / 10;		//��ϵ��Ϊjλ�� 
			}
			j--;
			for (h = j; h >= 0; h--) {
				ans[k] = '0' + ch[h];
				k++;
			}
			ans[k] = ')'; k++;
		}
	}
	ans[k] = '\0';
	string m_output(ans);
	if (m_output.size() == 0) {
		m_output = "(0,0)";
	}
	return m_output;
}
//
Polynomial Polynomial::oper_add(const Polynomial & tem) {
	char ans[2000];
	int ch[10];
	int k, j, h, m;
	int temp_zheng[1000] = {0};
	int temp_fu[1000] = {0};							//������int����������������ֹ�ı�ԭ������ 
	int i, max, min;
	if ((this->max_cishu_zheng) >= (tem.max_cishu_zheng)) {
		max = this->max_cishu_zheng;
	} else {
		max = tem.max_cishu_zheng;
	}
	if ((this->min_cishu_fu) >= (tem.min_cishu_fu)) {
		min = this->min_cishu_fu;
	} else {
		min = tem.min_cishu_fu;											//�ҵ����������ۺϵ���ߺ���С���� 
	}
	for (i = 0; i <= max; i++) {
		temp_zheng[i] = dataPlus[i] + tem.dataPlus[i];
	}
	for (i = 1; i <= min; i++) {
		temp_fu[i] = dataMinus[i] + tem.dataMinus[i];
	}																	//����������� 
	string m_output = this->num_to_char(max, min, temp_zheng, temp_fu);
	Polynomial abc("No", m_output);
	return abc;
}

//
Polynomial Polynomial::oper_sub(const Polynomial & tem) {
	char ans[2000];
	int ch[10];
	int k, j, h, m;
	int temp_zheng[1000] = {0};
	int temp_fu[1000] = {0};							//������int����������������ֹ�ı�ԭ������ 
	int i, max, min;
	if ((this->max_cishu_zheng) >= (tem.max_cishu_zheng)) {
		max = this->max_cishu_zheng;
	} else {
		max = tem.max_cishu_zheng;
	}
	if ((this->min_cishu_fu) >= (tem.min_cishu_fu)) {
		min = this->min_cishu_fu;
	} else {
		min = tem.min_cishu_fu;											//�ҵ����������ۺϵ���ߺ���С���� 
	}
	for (i = 0; i <= max; i++) {
		temp_zheng[i] = dataPlus[i] - tem.dataPlus[i];
	}
	for (i = 1; i <= min; i++) {
		temp_fu[i] = dataMinus[i] - tem.dataMinus[i];
	}																	//����������� 
	string m_output = this->num_to_char(max, min, temp_zheng, temp_fu);
	Polynomial abc("No", m_output);
	return abc;
}

//
Polynomial Polynomial::oper_qiudao(int n) {
	int temp_zheng[1000] = {0};
	int temp_fu[1000] = {0};							//������int����������������ֹ�ı�ԭ������ 
	int i, j, max, min;
	for (i = 0; i <= max_cishu_zheng; i++) {
		if (i == n) {
			temp_zheng[0] = dataPlus[i];
			for (j = 1; j <= n; j++) {
				temp_zheng[0] *= j;
			}
		} else if (i > n) {
			int m = i - n;
			temp_zheng[m] = dataPlus[i];
			for (j = i; j > m; j--) {
				temp_zheng[m] *= j;
			}
		}
	}
	if (max_cishu_zheng >= n) {
		max = max_cishu_zheng - n;
	} else {
		max = 0;
	}
	for (i = 1; i <= min_cishu_fu; i++) {
		int m = i + n;
		temp_fu[m] = dataMinus[i];
		for (j = i; j < m; j++) {
			temp_fu[m] *= (-1 * j);
		}
	}
	if (min_cishu_fu > 0) {
		min = min_cishu_fu + n;
	} else {
		min = 0;
	}
	string m_output = this->num_to_char(max, min, temp_zheng, temp_fu);
	Polynomial abc("No", m_output);
	return abc;
}
#endif
