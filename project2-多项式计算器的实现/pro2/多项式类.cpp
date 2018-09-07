#ifndef POLY_H_
#define POLY_H_
#include<iostream>
#include<string>
#include<cmath>
using namespace std;

class Polynomial {
private:
	string name;						//多项式的名字 
	string output;						//多项式需要储存的格式
	int dataPlus[1000];					//多项式的数据中次数为正或零的部分，如data[次数] = 系数； 
	int dataMinus[1000];				//多项式的数据中次数为负的部分
	int min_cishu_fu;					//多项式最小次数 
	int max_cishu_zheng;				//多项式最大次数 
public:
	Polynomial();
	Polynomial(const string & n, const string & op);
	string getName();									//得到多项式名字 
	void Output();
	string getStore();
	Polynomial oper_add(const Polynomial & tem);		//加法 
	Polynomial oper_sub(const Polynomial & tem);		//减法 
	Polynomial oper_constant(int tem);					//与常数乘 
	double oper_value(int val);
	string num_to_char(int max, int min, int * temp_zheng, int * temp_fu);
	Polynomial oper_qiudao(int n);						//求导操作 
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
Polynomial::Polynomial(const string & n, const string & op) {		//数据整理 
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
	for(i = 0; i < lenth; i++) {						//储存符号所在的位置 
		if (output[i] == '(') {
			where_qian[k] = i;
		} else if(output[i] == ',') {
			where_dou[k] = i;
		} else if(output[i] == ')') {
			where_hou[k] = i;
			k++;
		}
	}
	for(i = 0; i < k; i++) {							//总共有k个()组 
		a = where_qian[i]; b = where_dou[i]; c = where_hou[i];
		xishu = 0; cishu = 0;
		if (output[a + 1] == '-') {						//系数为负 
			for(j = b - 1; j > (a + 1); j--) {
				int m = output[j] - '0';
				xishu += m * (int)pow(10, (b - j - 1));
			}
			xishu = 0 - xishu; 							//得到系数 
		} else {										//系数为正 
			for(j = b - 1; j > a; j--) {
				int m = output[j] - '0';
				xishu += m * (int)pow(10, (b - j - 1));
			}
		}
		if (output[b + 1] == '-') {						//次数为负 
			for(j = c - 1; j > (b + 1); j--) {
				int m = output[j] - '0';
				cishu += m * (int)pow(10, (c - j - 1));
			}
			cishu = 0 - cishu; 							//得到次数 
		} else {										//次数为正 
			for(j = c - 1; j > b; j--) {
				int m = output[j] - '0';
				cishu += m * (int)pow(10, (c - j - 1));
			}
		}
		if (cishu >= 0) {			//次数大于等于0，存在 dataPlus[1000]中 
			dataPlus[cishu] = xishu;
			if (cishu > max_cishu_zheng) {
				max_cishu_zheng = cishu;	//修改最大次数 
			}
		} else {					//次数小于0，存在 dadaMinus[1000]中 
			cishu = 0 - cishu;
			dataMinus[cishu] = xishu;
			if (cishu > min_cishu_fu) {
				min_cishu_fu = cishu;		//修改最小次数 
			}
		}
	}
}

//
string Polynomial::getName() {
	return name;
}

//
void Polynomial::Output() {				//转化为输出形式 
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
			} else if(dataPlus[i] < 0) {									//从最高次数到次数2 
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
	} else if (dataPlus[1] < 0) {										//单独判断次数为1时 
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
	} else if (dataPlus[0] < 0) {										//单独判断常数 
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
				cout << dataMinus[i] << "x^-" << i;									//从-2次数到最低次 
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
	m_name = getName();									//得到多项式的名字 
	int temp_zheng[1000] = {0};
	int temp_fu[1000] = {0};							//用两个int数组来储存结果，防止改变原来的类 
	int i;
	for (i = 0; i <= max_cishu_zheng; i++) {
		temp_zheng[i] = dataPlus[i] * tem;
	}
	for (i = 1; i <= min_cishu_fu; i++) {
		temp_fu[i] = dataMinus[i] * tem;
	}													//将结果储存了 
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
				m = m / 10;		//此系数为j位数 
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
				ans[k] = '-'; k++;						//系数为正，加负号 
				temp_fu[i] = 0 - temp_fu[i];
			}
			for (j = 0; temp_fu[i] > 0; j++) {
				ch[j] = temp_fu[i] % 10;
				temp_fu[i] = temp_fu[i] / 10;		//此系数为j位数 
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
				m = m / 10;		//此系数为j位数 
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
	int temp_fu[1000] = {0};							//用两个int数组来储存结果，防止改变原来的类 
	int i, max, min;
	if ((this->max_cishu_zheng) >= (tem.max_cishu_zheng)) {
		max = this->max_cishu_zheng;
	} else {
		max = tem.max_cishu_zheng;
	}
	if ((this->min_cishu_fu) >= (tem.min_cishu_fu)) {
		min = this->min_cishu_fu;
	} else {
		min = tem.min_cishu_fu;											//找到两个对象综合的最高和最小次数 
	}
	for (i = 0; i <= max; i++) {
		temp_zheng[i] = dataPlus[i] + tem.dataPlus[i];
	}
	for (i = 1; i <= min; i++) {
		temp_fu[i] = dataMinus[i] + tem.dataMinus[i];
	}																	//将结果储存了 
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
	int temp_fu[1000] = {0};							//用两个int数组来储存结果，防止改变原来的类 
	int i, max, min;
	if ((this->max_cishu_zheng) >= (tem.max_cishu_zheng)) {
		max = this->max_cishu_zheng;
	} else {
		max = tem.max_cishu_zheng;
	}
	if ((this->min_cishu_fu) >= (tem.min_cishu_fu)) {
		min = this->min_cishu_fu;
	} else {
		min = tem.min_cishu_fu;											//找到两个对象综合的最高和最小次数 
	}
	for (i = 0; i <= max; i++) {
		temp_zheng[i] = dataPlus[i] - tem.dataPlus[i];
	}
	for (i = 1; i <= min; i++) {
		temp_fu[i] = dataMinus[i] - tem.dataMinus[i];
	}																	//将结果储存了 
	string m_output = this->num_to_char(max, min, temp_zheng, temp_fu);
	Polynomial abc("No", m_output);
	return abc;
}

//
Polynomial Polynomial::oper_qiudao(int n) {
	int temp_zheng[1000] = {0};
	int temp_fu[1000] = {0};							//用两个int数组来储存结果，防止改变原来的类 
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
