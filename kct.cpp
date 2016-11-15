#include "tool.h"
#include <iostream>
#include <map>
#include <math.h>
#include <algorithm>
using namespace std;

map<string, KM> kms;
vector<AC> ac;
void read() {
	ifstream ifs("KMS_List");
	string inpn = ""; //inputName
	string outn = ""; //outputName
	int s; //slot
	while (ifs >> inpn) {
		ifs >> outn;
		kms[inpn].name = outn;
		for (int i = 0; i < 4; i++) {
			ifs >> s;
			kms[inpn].slot.push_back(s);
		}
	}
	ifstream ifs2("AC_List");
	while (ifs2 >> inpn) {
		AC temp;
		ifs2 >> outn;
		temp.inputName = inpn;
		temp.outputName = outn;
		for (int i = 0; i < 3; i++) {
			ifs2 >> s;
			temp.all.push_back(s);
		}
		ac.push_back(temp);
	}
}

/* vectorにsと一致する名前の艦載機があるかを調べ，艦載機を返す */
AC* vfind(vector<AC> a, string s) {
	for (int i = 0; i < a.size(); i++) {
		if (ac[i].inputName == s) return &ac[i];
	}
	return NULL;
}

/* vectorに一致するsがあるかを調べ，boolを返す */
bool infind(vector<string> v, string s) {
	for (int i = 0; i < v.size(); i++) {
		if (v[i] == s) return true;
	}
	return false;
}

/* スロットの小さい順番で名前とそのスロットの場所を持つpairを作って返す */
vector<pair<int, string>> mysort(vector<string> n, map<string, KM> km) {
	map<string, KM> k = km;
	vector<pair<int, string>> vp;
	for (int i = 0; i < n.size(); i++) {
		for (int j = 0; j < 4; j++) {
			vp.push_back(pair<int, string>(k[n[i]].slot[j], n[i]));
		}
	}
	sort(vp.begin(), vp.end());
	for (int i = 0; i < vp.size(); i++) {
		for (int j = 0; j < 4; j++) {
			if (vp[i].first == k[vp[i].second].slot[j]) {
				vp[i].first = j;
				k[vp[i].second].slot[j] = 0;
				break;
			}
		}
	}
	return vp;
}

/* 手動装備の関数 */
void handing(vector<string> input) {
START:
	string tempn; //一時的な名前
	printf("\033[41m");
	cout << "誰に? ";
	printf("\033[0m");
	cin >> tempn;
	if (!infind(input, tempn)) goto START;

	string tempe; //一時的な装備
	printf("\033[41m");
	cout << "何を? ";
	printf("\033[0m");
	cin >> tempe;
	AC tempac = (*vfind(ac, tempe));
	if (tempac.inputName == "" || tempac.all[2] <= 0) goto START;

	int temps; //一時的な場所
	printf("\033[41m");
	cout << "どこに? ";
	printf("\033[0m");
	cin >> temps;
	if (temps >= 5 || temps <= 0) goto START;
	printf("\n");

	//間違いがないっぽいので装備
	if (tempe == "out") (*vfind(ac, kms[tempn].eq[temps - 1].inputName)).all[2]++; //装備したものの所持数を減らす
	kms[tempn].eq[temps - 1] = (*vfind(ac, tempe));
	(*vfind(ac, tempe)).all[2]--; //装備したものの所持数を減らす
}

/* 自動装備の関数 */
bool autoset(vector<pair<int, string>> vp, int target, vector<string> input) {
	for (int i = 0; i < vp.size(); i++) {
		vector<int> rm;
		int j = i;
		int k = 0;
		while (j >= 0 && k < ac.size()) {
			if (ac[k].all[2] >= 1) {
				kms[vp[j].second].eq[vp[j].first] = ac[k];
				ac[k].all[2]--;
				rm.push_back(k);
				j--;
			} else {
				k++;
			}
		}
		int air = 0;
		for (int a = 0; a < input.size(); a++) {
			for (int b = 0; b < 4; b++) {
				air += (int)kms[input[a]].eq[b].all[0] * sqrt(kms[input[a]].slot[b]);
				air += jukuren(kms[input[a]].eq[b].all[1]);
			}
		}
		if (target <= air) return true;
		for(int kk : rm){
			ac[kk].all[2]++;
		}
	}
	return false;
}

int main() {
	//	make();
	read();
	vector<string> input;
	int air = 0;
	//入力部分
	while (true) {
		string temp;
		cout << "艦娘の入力(終了はf): ";
		cin >> temp;
		if (temp == "f") break;
		else if (kms.find(temp) != kms.end()) {
			input.push_back(temp);
		} else cout << "該当の艦娘はいません" << endl;
	}
	if (input.size() < 1) return 0;
	vector<pair<int, string>> vp = mysort(input, kms); //スロットの小さい順とその艦娘
	//最初の表示
	for (int i = 0; i < input.size(); i++) {
		printf("\033[36m");
		cout << kms[input[i]].name << endl; //名前の表示
		printf("\033[0m");
		for (int j = 0; j < 4; j++) {
			kms[input[i]].eq.push_back((*vfind(ac, "out"))); //初期値の挿入
			cout << kms[input[i]].slot[j] << ": " << kms[input[i]].eq[j].outputName << endl;
		}
	}
	//所持艦載機の最初の表示
	for (int i = 0; i < ac.size() - 1; i++) {
		cout << ac[i].outputName << "(" << ac[i].inputName << ") 所持数: " << ac[i].all[2] << endl;
	}
	//装備だ！
	int mode;
	cout << "どうする?" << endl;
	cout << "[0: 手動装備 / 1:自動装備] ";
	cin >> mode;
	if (mode == 1) {
		int target;
		cout << "目標制空値は? ";
		cin >> target;
		if(!autoset(vp, target, input)) cout << "無理でした" << endl;
		goto SHOW;
	}
	while (true) {
		handing(input);
		//計算部分
	SHOW:
		air = 0;
		for (int i = 0; i < input.size(); i++) {
			for (int j = 0; j < 4; j++) {
				air += (int)kms[input[i]].eq[j].all[0] * sqrt(kms[input[i]].slot[j]);
				air += jukuren(kms[input[i]].eq[j].all[1]);
			}
		}
		//艦娘表示部分
		for (int i = 0; i < input.size(); i++) {
			printf("\033[36m");
			cout << kms[input[i]].name << endl;
			printf("\033[0m");
			for (int j = 0; j < kms[input[i]].slot.size(); j++) {
				cout << kms[input[i]].slot[j] << ": " << kms[input[i]].eq[j].outputName << endl;
			}
		}
		//艦載機表示部分
		for (int i = 0; i < ac.size() - 1; i++) {
			cout << ac[i].outputName << "(" << ac[i].inputName << ") 所持数: " << ac[i].all[2] << endl;
		}
		printf("\033[33m");
		cout << "現在制空値: " << air << endl;
		printf("\033[0m");
		string y;
		cout << "終わる?(y/n) ";
		cin >> y;
		if (y == "y") break;
	}
	//結果の出力 実行ファイルと同じところに出力する
	ofstream outputList("Wepons_List.txt");
	for (int i = 0; i < input.size(); i++) {
		outputList << "・" << kms[input[i]].name << endl;
		for (int j = 0; j < kms[input[i]].slot.size(); j++) {
			outputList << kms[input[i]].slot[j] << ": " << kms[input[i]].eq[j].outputName << endl;
		}
	}
	outputList << "現在制空値: " << air << endl;
}

/*
制空値 = [(艦載機の対空値) × √(搭載数) ＋ 熟練度補正]　の総計　（[]は端数切り捨て）
熟練度補正は練度MAX(>>)で艦戦 / 水戦は + 25、水爆は + 9、艦攻 / 艦爆は + 3。
*/