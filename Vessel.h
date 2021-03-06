#pragma once
#include <iostream>
#include <vector>
#include <string>

class Vessel;
class Shell;

// 船艦攻擊CD
#define CV_ATT_CD 60
#define BB_ATT_CD 30
#define CG_ATT_CD 30
#define DD_ATT_CD 15
// 船艦防禦CD
#define CV_DEF_CD 15
#define BB_DEF_CD 30
#define CG_DEF_CD 30
#define DD_DEF_CD 60

#define PI 3.1415926

using std::string;



#pragma 
class Vessel 
{
protected:
	string type;
	string name;
	char team;
	double x, y;
	double hp, atkRange, defRange, atkCD, defCD, maxSpeed, currentSpeed;
	double weaponSpeed, weaponAtt;
	int angle;
public:
	// get()
	string getName();
	char getTeam();
	double getX();
	double getY();
	double getHp();
	double getSpeed();
	double getAtkRange();
	double getDefRange();
	double getAtkCD();
	double getDefCD();
	double getWeaponSpeed();
	double getWeaponAtt();
	string getType();
	double getMaxSpeed();

	// set()
	void setTeam(char team);
	void setHp(double hp);
	void setSpeed(double speed);
	void setAtkRange(double atkRange);
	void setDefRange(double defRange);
	void setAtkCD(double atkCD);
	void setDefCD(double defCD);
	void setWeaponSpeed(double weaponSpeed);
	void setWeaponAtt(double weaponAtt);
	void setName(string name);
	void setX(double x);
	void setY(double y);
	void setAngle(int angle);
	void moving();
	

};
class CV : public Vessel 
{
public:
	CV();
};
class BB : public Vessel 
{
public:
	BB();
};
class CG : public Vessel 
{
public:
	CG();
};
class DD : public Vessel 
{
public:
	DD();
};
class TK : public Vessel {
public:
	TK();
};
class HERO : public Vessel
{
public:
	HERO();
};

class Shell
{
private:
	string name;	//砲彈名字
	double x, y;	//砲彈目前位置
	double destination_X, destination_Y;	//砲彈目的地
	double speed, attack;	//砲彈速度、攻擊
public:
	Shell(string name, double x, double y, double destination_X, double destination_Y, double speed, double attack);
	string getName();
	double getX();
	double getY();
	double getDesX();
	double getDesY();
	double getATK();
	void setX(double x);
	void setY(double y);
	void moving();
};


