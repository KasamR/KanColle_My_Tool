#include <fstream>
#include <vector>
#include <string>

struct AC {
	std::string inputName = "";
	std::string outputName = ""; //艦載機の出力する名前
	std::vector<int> all; //{対空値, 種類, 所持数}
};
struct KM {
	std::string name = ""; //艦娘の名前(漢字)
	std::vector<int> slot; //艦娘のスロット数
	std::vector<AC> eq; //equipment 装備
};

void make() {
	std::ofstream ofs("KMS_List");
	/* 正規空母 */
	ofs << "Akagi 赤城改 20 20 32 10" << std::endl;
	ofs << "Kaga 加賀改 20 20 46 12" << std::endl;
	ofs << "Hiryu2 飛龍改二 18 36 22 3" << std::endl;
	ofs << "Soryu2 蒼龍改二 18 35 20 6" << std::endl;
	ofs << "Shokaku2 翔鶴改二 27 27 27 12" << std::endl;
	ofs << "Zuikaku2 瑞鶴改二 27 27 27 12" << std::endl;
	ofs << "Unryu 雲龍改 18 21 27 3" << std::endl;
	ofs << "Amagi 天城改 18 21 27 3" << std::endl;
	ofs << "Katsuragi 葛城改 18 21 27 3" << std::endl;
	ofs << "Graf Graf_Zeppelin改 30 13 10 3" << std::endl;
	/* 装甲空母 */
	ofs << "Taiho 大鳳改 30 24 24 8" << std::endl;
	ofs << "Shokaku2kou 翔鶴改二甲 34 21 12 9" << std::endl;
	ofs << "Zuikaku2kou 瑞鶴改二甲 34 24 12 6" << std::endl;
	/* 軽空母 */
	ofs << "Hosho 鳳翔改 14 16 12 0" << std::endl;
	ofs << "Ryujo2 龍驤改二 18 28 6 3" << std::endl;
	ofs << "Ryuho 龍鳳改 21 9 9 6" << std::endl;
	ofs << "Shoho 祥鳳改 18 12 12 6" << std::endl;
	ofs << "Zuiho 瑞鳳改 18 12 12 6" << std::endl;
	ofs << "Hiyo 飛鷹改 18 18 18 12" << std::endl;
	ofs << "Junyo2 隼鷹改二 24 18 20 4" << std::endl;
	ofs << "Chitose2 千歳改二 24 16 11 8" << std::endl;
	ofs << "Chiyoda2 千代田改二 24 16 11 8" << std::endl;
	/* その他 */
	ofs << "Akitsumaru あきつ丸改 8 8 8 0" << std::endl;
	/* 航空戦艦 */
	ofs << "Fuso2 扶桑改二 4 4 9 23" << std::endl;
	ofs << "Yamashiro2 山城改二 4 4 9 23" << std::endl;
	ofs << "Ise 伊勢改 11 11 11 14" << std::endl;
	ofs << "Hyuga 日向改 11 11 11 14" << std::endl;
	/* 航空巡洋艦 */
	ofs << "Mogami 最上改 5 6 5 11" << std::endl;
	ofs << "Mikuma 三隈改 5 6 5 8" << std::endl;
	ofs << "Suzuya 鈴谷改 5 6 5 6" << std::endl;
	ofs << "Kumano 熊野改 5 6 5 6" << std::endl;
	ofs << "Tone2 利根改二 2 2 9 5" << std::endl;
	ofs << "Chikuma2 筑摩改二 2 2 9 5 " << std::endl;
	/* パスタ艦 */
	ofs << "Italia Italia 3 3 3 3" << std::endl;
	ofs << "Roma Roma改 3 3 3 3" << std::endl;
	ofs << "Zara Zara改 2 2 2 2" << std::endl;
	ofs << "Pola Pola改 2 2 2 2" << std::endl;
	/* 大和型 */
	ofs << "Yamato 大和改 7 7 7 7" << std::endl;
	ofs << "Musashi 武蔵改 7 7 7 7" << std::endl;

	std::ofstream ofs2("AC_List"); //{ 対空値, 種類, 所持数 }
	//種類... 0(艦戦/水戦) 1(水爆) 2(艦攻/艦爆)
	//熟練度補正は練度MAX(>>)で 艦戦/水戦は+25, 水爆は+9, 艦攻/艦爆は+3
	ofs2 << "Reppu601 烈風(六〇一空) 10 0 1" << std::endl;
	ofs2 << "Fw190 Fw190T改 10 0 1" << std::endl;
	ofs2 << "Iwai 零戦52型丙(付岩井小隊) 10 0 1" << std::endl;
	ofs2 << "Bf109 Bf109T改 8 0 2" << std::endl;
	ofs2 << "Shiden2 紫電改二 9 0 9" << std::endl;
	ofs2 << "Reppu 烈風 10 0 9" << std::endl;
	ofs2 << "Zerosen601 零戦52型丙(六〇一空) 9 0 1" << std::endl;
	ofs2 << "Jukuren 零式艦戦21型(熟練) 8 0 2" << std::endl;
	ofs2 << "Zuiun 瑞雲 2 1 21" << std::endl;
	ofs2 << "Zuiun12 瑞雲12型 3 1 1" << std::endl;
	ofs2 << "Named (江草/友永/村田) 1 2 4" << std::endl;
	ofs2 << "Ro44 Ro.44水上戦闘機 2 0 1" << std::endl;
	ofs2 << "out なし 0 -1 999" << std::endl;
}
int jukuren(int a) {
	if (a == 0) return 25; //艦戦 水戦
	else if (a == 1) return 9; //水爆
	else if (a == 2) return 3; //艦攻 艦爆
	else return 0;
}