#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <algorithm>
#include <functional>
#include "Kanmusu_List.h"
#include "Fighter.h"
#define GET_ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))
using namespace std;

int wepons[6][4] = {}; //�������鑕��
string weponsName[6][4] = {}; //�������鑕���̖��O
string names[6] = {}; //�o������͖��̃��X�g
int sally; //�o������͖��̐�(sally...�o���̈�)
int mode = 0; //���[�h�I���̕ϐ�
int seiku = 0; //�ڕW����l�̕ϐ�
bool roop = true; //���[�v����̕ϐ�
int aircommand = 0; //�v�Z���̐���l
int inwepon = 0; //����̑�����
Fighter fi[8] = {}; //�͍ڋ@�̃N���X
ifstream ifs("Fighters.txt", ios::in);
int fsize = GET_ARRAY_SIZE(fi); //�͍ڋ@�̎�ސ�

void ga(string*, int); //�v���g�^�C�v�錾(������v�Z)
void hu(string*, int); //�v���g�^�C�v�錾(2,3�X���b�g�ɓ����v�Z)
void my(string*, int); //�v���g�^�C�v�錾(�蓮�v�Z)
void sh();			   //�v���g�^�C�v�錾(�\��)
void Fsetting(){ //�͍ڋ@�̃Z�b�g
	string name, kanji;
	int taiku, shoji, i = 0;
	bool kansen;
	while (ifs >> name){
		ifs >> kansen >> taiku >> shoji >> kanji;
		fi[i].setting(name, kansen, taiku, shoji, kanji);
		i++;
	}
}

int main(){
	KMS();
	Fsetting();
	bool endCheck = true;
	/* �o�^��HAJIMARI */
	cout << "���͖̊��͉��l�o�����܂����H ";
	cin >> sally;
	if (sally < 1 || 6 < sally) return 0;
	for (int i = 0; i < sally; i++){
		cout << "���O�̓o�^�����܂��B���O����͂��Ă��������B" << endl;
		cin >> names[i];
		if (kms.find(names[i]) == kms.end()){
			cout << "�s���ȓ��͂ł��B���͂��Ȃ����Ă��������B" << endl;
			i -= 1;
		}
	}
	/* �o�^��OWARI */
MODE:
	/* ���[�h�ƖڕW����l��NYURYOKU */
	cout << "�g�p���������[�h��I�����Ă�������" << endl;
	cout << "1: ��������(������), 2: ��������(�U������), 3: �蓮����: ";
	cin >> mode;

	/* ���[�h�I����HAJIMARI */
	switch (mode){
	case 1:
		ga(names, sally); //������v�Z
		sh();
		break;
	case 2:
		hu(names, sally);
		sh();
		break;
	case 3:
		my(names, sally); //�蓮�v�Z
		break;
	default:
		cout << "�s���ȓ��͂ł��B" << endl;
		goto MODE;
		break;
	}
	roop = true; //�C���̎��ɂ����Ǝg����悤��
	/* ���[�h�I����OWARI */

	/* �蓮�C�����[�h��SENTAKU */
	string fix;
	cout << "�C�����܂���?(yes/no): ";
	cin >> fix;
	if (fix == "yes") my(names, sally);
	/* �蓮�C�����[�h��OWARI */

	/* �I���̊m�F */
	while (endCheck){
		cout << "OK?" << endl;
		string ok;
		cin >> ok;
		if (ok == "ok") endCheck = false;
	}
} //main��OWARI

void ga(string* n, int sa){
	KMS();
	Fsetting();
	string na[6]; //���O�i�[�p
	for (int i = 0; i < sa; i++){
		na[i] = *n;
		++n;
	}
	cout << "�ڕW�̐���l����͂��Ē���: ";
	cin >> seiku;
	while (roop){
		int i = 0, j = 0;
		int max = 0;
		int mi = 0, mj = 0;
		aircommand = 0;
		/* ���ڂ��ĂȂ��ő�X���b�g�̌��� */
		for (i = 0; i < sa; i++){
			for (j = 0; j < 4; j++){
				if (kms[na[i]][j] > max && wepons[i][j] == 0){
					max = kms[na[i]][j];
					mi = i; //�������ĂȂ��ő�X���b�g(�͖��̈ʒu)
					mj = j; //�������ĂȂ��ő�X���b�g(�X���b�g�̈ʒu)
				}
			}
		}
		/* �X���b�g�̑��� */
		for (i = 0; i < fsize; i++){
			if (fi[i].get_shojisu() > 0){
				wepons[mi][mj] = fi[i].equip();
				weponsName[mi][mj] = fi[i].show_name();
				inwepon += 1;
				break;
			}
		}
		/* �v�Z���� */
		for (i = 0; i < sa; i++){
			for (j = 0; j < 4; j++){
				aircommand += int(wepons[i][j] * sqrt(kms[na[i]][j]));
			}
		}
		/* ����l�Ƃ̔�r */
		if (seiku < aircommand) roop = false;
		else if (inwepon == sa * 4) roop = false; //�S�ς݂������甲����
	}
}

void hu(string* n, int sa){
	KMS();
	Fsetting();
	string na[6]; //���O�i�[
	vector<pair<int, pair<int, int>>> Daughters(sa * 2); //�͖��̖��O�ƃX���b�g�����o����
	vector<pair<int, int>> temp(4); //first�ɂ͓��ڐ� second�ɂ͏ꏊ���o����

	for (int i = 0; i < sa; i++){
		na[i] = *n;
		++n;
	}
//	cout << "�ڕW�̐���l����͂��Ă�: ";
//	cin >> seiku;
	for (int i = 0; i < sa; i++) {
		for (int j = 0; j < 4; j++){
			temp[j].first = kms[na[i]][j];
			temp[j].second = j;
		}
		sort(temp.begin(), temp.end(), greater<pair<int, int> >());
		/* 2�Ԗڂ̃X���b�g��o�^ */
		Daughters[i * 2].first = temp[1].first; //�X���b�g��
		Daughters[i * 2].second.first = i; //���O(���Ԗڂɓo�^����Ă���͖���)
		Daughters[i * 2].second.second = temp[1].second; //�����̏ꏊ
		/* 3�Ԗڂ̃X���b�g��o�^ */
		Daughters[i * 2 + 1].first = temp[2].first; //�X���b�g��
		Daughters[i * 2 + 1].second.first = i; //���O(���Ԗڂɓo�^����Ă���͖���)
		Daughters[i * 2 + 1].second.second = temp[2].second; //�����̏ꏊ
	}
	/* �X���b�g�̑傫�����Ƀ\�[�g */
	sort(Daughters.begin(), Daughters.end(), greater<pair<int, pair<int, int>> >());

	for (int i = 0; i < sa*2; i++) { //����̑���
		for (int j = 0; j < fsize; j++) {
			if (fi[j].get_shojisu() > 0){
				wepons[Daughters[i].second.first][Daughters[i].second.second] = fi[j].equip();
				weponsName[Daughters[i].second.first][Daughters[i].second.second] = fi[j].show_name();
				break;
			}
		}
	}

	for (int i = 0; i < sa; i++){ //����l�̌v�Z
		for (int j = 0; j < 4; j++){
			aircommand += int(wepons[i][j] * sqrt(kms[na[i]][j]));
		}
	}
}

void my(string* n, int sa){
	KMS();
	sh();
	Fsetting();
	string na[6]; //���O�i�[
	string inName; //���͂��ꂽ�͖��A�͍ڋ@�̖��O
	int inslot; //���͂��ꂽ�X���b�g
	for (int i = 0; i < sa; i++){
		na[i] = *n;
		++n;
	}
	while (roop){
		int kanmusui; //���͂��ꂽ�͖������Ԗڂɂ��邩��ۗL
		int kansaikii; //���͂��ꂽ�͍ڋ@�����Ԗڂɂ��邩��ۗL
		int sloti; //���͂��ꂽ�X���b�g�̏ꏊ��ۗL
		aircommand = 0;
		/* ���O���� */
	NAMING:
		cout << "�N�̑�����ҏW����?" << endl;
		cin >> inName; //�͖��̖��O����
		for (int i = 0; i < sa; i++){
			if (inName == na[i]){
				kanmusui = i;
				break;
			}
			else kanmusui = 99;
		}
		if (kanmusui == 99){
			cout << "�s���ȓ��͂ł��B" << endl;
			goto NAMING;
		}

		/* �͍ڋ@���� */
		while (roop){
			cout << "�ǂ͍̊ڋ@�𑕔�����?" << endl;
			cin >> inName; //�͍ڋ@�̖��O����
			for (int i = 0; i < fsize; i++){
				if (inName == fi[i].get_name()){
					kansaikii = i;
					roop = false;
					break;
				}
				else kansaikii = 99;
			}
			if (inName == "out") {
				roop = false;
				kansaikii = 90;
			}
			if (kansaikii == 99 || fi[kansaikii].get_shojisu() <= 0){
				cout << "�s���ȓ��͂ł��B" << endl;
			}
		}
		roop = true;

		/* �X���b�g���� */
		while (roop){
			cout << "�ǂ̃X���b�g�ɑ�������?" << endl;
			if (cin >> inslot)
				if (1 <= inslot && inslot <= 4){
					roop = false; //�X���b�g�̓���
				}
				else cout << "�s���ȓ��͂ł�" << endl;
			else {
				cin.clear();
				cin.ignore();
				cout << "�s���ȓ��͂ł�" << endl;
			}

			sloti = inslot - 1;
			for (int i = 0; i < fsize; i++) {
				if (fi[i].re_name(inName))
					weponsName[kanmusui][sloti] = fi[i].show_name();
			}
		}
		roop = true;
		/* �X���b�g���͏I��� */

		/* ���������Ă��邩�ǂ����̃`�F�b�N */
		if (inName == "out"){ //�����O��
			for (int i = 0; i < fsize; i++){
				if (wepons[kanmusui][sloti] == fi[i].get_taiku()){
					fi[i].push_shojisu();
					wepons[kanmusui][sloti] = 0;
				}
			}
			goto CALC;
		}
		if (wepons[kanmusui][sloti] == 0){
			wepons[kanmusui][sloti] = fi[kansaikii].equip();
		}
		else{
			for (int i = 0; i < fsize; i++){
				if (wepons[kanmusui][sloti] == fi[i].get_taiku()){
					fi[i].push_shojisu();
					wepons[kanmusui][sloti] = fi[kansaikii].equip();
				}
			}
		}

		/* �v�Z��HAJIMARI */
	CALC:
		for (int i = 0; i < sa; i++){
			for (int j = 0; j < 4; j++){
				aircommand += int(wepons[i][j] * sqrt(kms[na[i]][j]));
			}
		}
		/* �v�Z��OWARI */
		/* �o�͂�HAJIMARI */
		sh();
		/* �o�͂�OWARI */
		/* �I������ */
		cout << "����?(yes/no)" << endl;
		string ok;
		cin >> ok;
		if (ok == "yes") roop = false;
	}
}

void sh(){
	Fsetting();
	/* �o�͂�HAJIMARI */
	for (int i = 0; i < sally; i++){
		cout << names[i] << " �̑���" << endl;
		for (int j = 0; j < 4; j++){
			cout << kms[names[i]][j] << ": ";
			if (weponsName[i][j] == "" || wepons[i][j] == 0)weponsName[i][j] = "�Ȃ�";
			cout << weponsName[i][j] << endl;
		}
	}
	if (inwepon == sally * 4 && aircommand < seiku) cout << "���̕Ґ��ł͖����ł�" << endl;
	cout << "����l�� " << aircommand << " �ł��B" << endl;
	cout << "�c��͍̊ڋ@��" << endl;
	for (int i = 0; i < fsize; i++) fi[i].showAll();
	int bonus_check = 0;
	for (int i = 0; i < sally; i++){
		for (int j = 0; j < 4; j++){
			if (wepons[i][j] == 0) bonus_check += 1;
		}
	}
	if (bonus_check != sally * 4){
		cout << "�n���x�{�[�i�X���܂߂�H(yes/no) ";
		string bonus;
		cin >> bonus;
		if (bonus == "yes"){
			for (int i = 0; i < sally; i++) {
				for (int j = 0; j < 4; j++) {
					for (int k = 0; k < fsize; k++){
						if (weponsName[i][j] == fi[k].show_name() && fi[k].get_kind())
							aircommand += 25;
					}
				}
			}
			cout << "�{�[�i�X���܂߂�����l�� " << aircommand << " �ł��B" << endl;
		}
	}
	/* �o�͂�OWARI */
}
