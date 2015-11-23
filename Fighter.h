#include <iostream>
#include <string>
#include <fstream>

class Fighter{
private:
	std::string name; //�͍ڋ@�̖��O
	bool kansen; //�͍ڋ@�̎��
	int taiku; //�͍ڋ@�̑΋�l
	int shojisu; //�͍ڋ@�̎c�菊����
	std::string kanji_name; //�\���p�̊����̖��O
public:
	void setting(std::string n, bool k, int t, int s, std::string kn); //�������I�ȓz
	void showAll();//���͍̊ڋ@�̏�Ԃ�����
	bool get_kind() { return kansen; } //�͐킩��bool�ŕԂ�
	std::string get_name() { return name; } //�͍ڋ@�̖��O��Ԃ�
	int get_taiku() { return taiku; } //�΋�l��Ԃ�
	int get_shojisu() { return shojisu; } //��������Ԃ�
	std::string show_name() { return kanji_name; } //�\���p�̖��O��Ԃ�
	int equip(); //�͍ڋ@�̑����A���O��Ԃ��ď����������炷
	bool re_name(std::string na);
	void push_shojisu() { shojisu += 1; } //�������𑝂₷
};

void Fighter::setting(std::string n, bool k, int t, int s, std::string kn){
	name = n;
	kansen = k;
	taiku = t;
	shojisu = s;
	kanji_name = kn;
}
void Fighter::showAll(){
	std::cout << "���O: " << kanji_name;
	std::cout << " (" << name << ")" << std::endl;
	if (kansen) std::cout << "�͐�";
	else std::cout << "�͍U/�͔�";
	std::cout << ", �΋�: " << taiku;
	std::cout << ", ������: " << shojisu << std::endl;
}
int Fighter::equip(){
	if (shojisu >0)shojisu -= 1;
	else return 0;
	return taiku;
}
bool Fighter::re_name(std::string na){
	if (na == name) return true;
	else return false;
}
/* �A�E�g�v�b�g�p�̃\�[�X�R�[�h */
/*
	ofstream ofs("Fighters.txt", std::ios::out);
	ofs << "Reppu601 1 11 1 ��(601��)" << endl;
	ofs << "Reppu 1 10 7 ��" << endl;
	ofs << "Shiden2 1 9 4 ���d����" << endl;
	ofs << "Jukuren21 1 8 2 �뎮�͐�21�^(�n��)" << endl;
	ofs << "Zerosen601 1 9 1 ���52�^��(601��)" << endl;
	ofs << "Named 0 1 3 �]���E�F�i�E���c��" << endl;
	ofs << "Zuiun 0 2 17 ���_" << endl;
	ofs << "Zuiun12 0 3 1 ���_12�^" << endl;
*/

