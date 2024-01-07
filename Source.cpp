//From: Nguyen Le Khanh Duy
//Facebook: Nguyễn Duy || Link: https://www.facebook.com/profile.php?id=100011007699795
//Github: DragonCoderVN || Link: https://github.com/dragoncodervn
#include <iostream>
#include <ctime>
#include <algorithm>
#include "GameLibrary.h"
using namespace std;
//Thân rắn
#define DOT_RAN 254
#define MAX 100
//Di chuyển
#define LEN 1 //Mã hướng lên 
#define XUONG 2 //Mã hướng xuống
#define TRAI 3 //Mã hướng qua trái
#define PHAI 4 //Mã hướng qua phải
//Tường
#define TUONG_TREN 0 //Vị trí tường trên
#define TUONG_DUOI 14 //Vị trí tường dưới
#define TUONG_TRAI 0  //Vị trí tường trái
#define TUONG_PHAI 52 //Vị trí tường phải
//Thức ăn
#define CHERRY 235
//Toạ độ console
struct Position{
	int x; 
	int y;
};
typedef Position Pos;
//Khởi tạo rắn
Pos Ran[MAX]; //Toạ độ các đốt rắn
int SoDot = 3; //Độ dài của rắn
void khoitaoRan();
void hienthiRan(Pos LastOldDot);
Pos Moving(int huong); //Di chuyển
void Events(int& huong); //Bắt nút
//Tường
void Walls(); 
//Kiểm tra thua
bool CheckLoseGame();
void Loser();
//Thức ăn
Pos food();
bool AteFood(Pos obj);
//Thêm đốt mới
void AddDot();

//Điểm số ban đầu
int score = 0;

int main(void) {
	system("cls");
	noCursorType();
	setTextColor(11);
	khoitaoRan();
	int x = 0, y = 0;
	int huong = PHAI;
	int sec = 250;
	Walls();
	Pos obj = food();
	//Hiện điểm số ban đầu
	gotoXY(TUONG_PHAI + 3, TUONG_TREN + 1);
	cout << "Score: " << score << endl;
	//Mẹo & cách chơi
	gotoXY(TUONG_PHAI + 3, TUONG_TREN + 3);
	cout << "*Meo:Neu khong an nut thi click chuot vao man hinh game vai cai!\n";
	gotoXY(TUONG_PHAI + 3, TUONG_TREN + 5);
	cout << "Nhiem vu: Dieu khien ran an moi dat 100 diem de thang";
	gotoXY(TUONG_PHAI + 3, TUONG_TREN + 7);
	cout << "W hoac Pg Up - Di chuyen len\n";
	gotoXY(TUONG_PHAI + 3, TUONG_TREN + 9);
	cout << "A hoac Pg Left - Di chuyen qua trai\n";
	gotoXY(TUONG_PHAI + 3, TUONG_TREN + 11);
	cout << "S hoac Pg Down- Di chuyen xuong\n";
	gotoXY(TUONG_PHAI + 3, TUONG_TREN + 13);
	cout << "D hoac Pg Right- Di chuyen qua phai\n";
	gotoXY(TUONG_PHAI + 3, TUONG_TREN + 15);
	cout << "**Luu y:tat Bo Go Tieng Viet khi choi game!!!";
	while (true) {
		//clrscr();
		Pos LastOldDot = Moving(huong);
		Events(huong);
		hienthiRan(LastOldDot);
		if (AteFood(obj)) {
			obj = food();
			AddDot();
			score++;
			gotoXY(TUONG_PHAI + 3, TUONG_TREN + 1);
			cout << "Score: " << score;
			if (sec > 20) sec -= 20;
		};
		if (CheckLoseGame()) break;
		Sleep(sec);
	}
	Loser();
	return NULL;
}
//Tạo rắn & hiển thị rắn
void khoitaoRan() {
	Ran[0].x = TUONG_PHAI - 27;
	Ran[1].x = TUONG_PHAI - 26;
	Ran[2].x = TUONG_PHAI - 25;
	Ran[0].y = Ran[1].y = Ran[2].y = TUONG_TREN + 7;
}
void hienthiRan(Pos LastOldDot) {
	for (int i = 0; i < SoDot; ++i) {
		gotoXY(Ran[i].x, Ran[i].y);
		cout << (char)DOT_RAN;
	}
	gotoXY(LastOldDot.x, LastOldDot.y);
	cout << ' ';
}
//Di chuyển
Pos Moving(int huong) {
	Pos LastOldDot = Ran[SoDot - 1];
	for (int i = SoDot - 1; i >= 1; --i) {
		Ran[i] = Ran[i - 1];
	}
	switch (huong) {
	case LEN:
		Ran[0].y--;
		break;
	case XUONG:
		Ran[0].y++;
		break;
	case TRAI:
		Ran[0].x--;
		break;
	case PHAI:
		Ran[0].x++;
		break;
	}
	return LastOldDot;
}
//Bắt nút
void Events(int& huong){
	int key = inputKey();
	if (key == 'w' || key == 'W' || key == KEY_UP) {
		huong = LEN;
	}
	else if (key == 's' || key == 'S' || key == KEY_DOWN) {
		huong = XUONG;
	}
	else if (key == 'a' || key == 'A' || key == KEY_LEFT) {
		huong = TRAI;
	}
	else if (key == 'd' || key == 'D' || key == KEY_RIGHT) {
		huong = PHAI;
	}
}
//Tường
void Walls() {
	for (int x = TUONG_TRAI; x <= TUONG_PHAI; ++x) {
		gotoXY(x, TUONG_TREN);
		cout << (char)220; 
	}
	for (int y = TUONG_TREN + 1; y <= TUONG_DUOI; ++y) {
		gotoXY(TUONG_TRAI, y);
		cout << (char)221;
		gotoXY(TUONG_PHAI, y);
		cout << (char)222;
	}
	for (int x = TUONG_TRAI; x <= TUONG_PHAI; ++x) {
		gotoXY(x, TUONG_DUOI + 1);
		cout << (char)223;
	}
}
//Kiểm tra thua
bool CheckLoseGame() {
	//Thua do rắn chạm tường
	if (Ran[0].y == TUONG_TREN || Ran[0].y == TUONG_DUOI ) {
		return true;
	}
	if (Ran[0].x == TUONG_TRAI || Ran[0].x == TUONG_PHAI) {
		return true;
	}
}
void Loser() {
		Sleep(500);
		clrscr();
		gotoXY(46, 14);
		cout << "GAME OVER !!!"<<"(Score:"<<score<<")";//Hiển thị khi thua
}
//Thức ăn
Pos food() {
	srand(time(NULL));
	int x = TUONG_TRAI + 1 + rand() % (TUONG_PHAI - TUONG_TRAI - 1);
	int y = TUONG_TREN + 1 + rand() % (TUONG_DUOI - TUONG_TREN - 1);
	gotoXY(x,y);
	cout <<(char)CHERRY;
	return Pos{ x,y };
}
bool AteFood(Pos obj) {
	if (Ran[0].x == obj.x && Ran[0].y == obj.y)
		return true;
	return false;
}
//Thêm đốt
void AddDot() {
	Ran[SoDot] = Ran[SoDot - 1];
	SoDot++;
}