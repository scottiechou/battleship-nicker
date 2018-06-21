#include "Vessel.h"
#include "MyForm.h"
#include <math.h>


#pragma region get()


string Vessel::getName()
{
	return this->name;
}

char Vessel::getTeam()
{
	return this->team;
}
void Vessel::setTeam(char team)
{
	this->team = team;
}

double Vessel::getX()
{
	return this->x;
}

double Vessel::getY()
{
	return this->y;
}

double Vessel::getHp()
{
	return this->hp;
}

double Vessel::getSpeed()
{
	return this->currentSpeed;
}

double Vessel::getAtkRange()
{
	return this->atkRange;
}

double Vessel::getDefRange()
{
	return this->defRange;
}

double Vessel::getAtkCD()
{
	return this->atkCD;
}

double Vessel::getDefCD()
{
	return this->defCD;
}

double Vessel::getWeaponSpeed()
{
	return this->weaponSpeed;
}

double Vessel::getWeaponAtt()
{
	return this->weaponAtt;
}

string Vessel::getType()
{
	return this->type;
}

double Vessel::getMaxSpeed()
{
	return this->maxSpeed;
}

string Shell::getName()
{
	return this->name;
}
double Shell::getX()
{
	return this->x;
}
double Shell::getY()
{
	return this->y;
}

double Shell::getATK()
{
	return this->attack;
}

double Shell::getDesX()
{
	return this->destination_X;
}

double Shell::getDesY()
{
	return this->destination_Y;
}

int Vessel::getAngle()
{
	return this->angle;
}
#pragma endregion
#pragma region set()
void Vessel::setHp(double hp)
{
	this->hp = hp;
}

void Vessel::setSpeed(double speed)
{
	this->currentSpeed = speed;
}

void Vessel::setAtkRange(double atkRange)
{
	this->atkRange = atkRange;
}

void Vessel::setDefRange(double defRange)
{
	this->defRange = defRange;
}

void Vessel::setAtkCD(double atkCD)
{
	this->atkCD = atkCD;
}

void Vessel::setDefCD(double defCD)
{
	this->defCD = defCD;
}

void Vessel::setWeaponSpeed(double weaponSpeed)
{
	this->weaponSpeed = weaponSpeed;
}

void Vessel::setWeaponAtt(double weaponAtt)
{
	this->weaponSpeed = weaponAtt;
}

void Vessel::setName(string name)
{
	this->name = name;
}

void Vessel::setX(double x)
{
	this->x = x;
}

void Vessel::setY(double y)
{
	this->y = y;
}

void Vessel::setAngle(int angle)
{
	this->angle = angle;
}


void Shell::setX(double x)
{
	this->x = x;
}

void Shell::setY(double y)
{
	this->y = y;
}

#pragma endregion
#pragma region 建構子
CV::CV()
{
	hp = 5;
	maxSpeed = 1 / 60.0;
	currentSpeed = 0;
	atkRange = 25;
	atkCD = 0;
	defRange = 5;
	defCD = 0;
	weaponSpeed = (4 / 60.0);
	weaponAtt = 3;
	type = "CV";
	angle = 0;
}

BB::BB()
{
	hp = 4;
	maxSpeed = 1 / 60.0;
	currentSpeed = 0;
	atkRange = 20;
	atkCD = 0;
	defRange = 10;
	defCD = 0;
	weaponSpeed = (2 / 60.0);
	weaponAtt = 3;
	type = "BB";
	angle = 0;
}

CG::CG()
{
	hp = 3;
	maxSpeed = 2 / 60.0;
	currentSpeed = 0;
	atkRange = 15;
	atkCD = 0;
	defRange = 15;
	defCD = 0;
	weaponSpeed = (3 / 60.0);
	weaponAtt = 2;
	type = "CG";
	angle = 0;
}

DD::DD()
{
	hp = 2;
	maxSpeed = 3 / 60.0;
	currentSpeed = 0;
	atkRange = 10;
	atkCD = 0;
	defRange = 20;
	defCD = 0;
	weaponSpeed = (3 / 60.0);
	weaponAtt = 1;
	type = "DD";
	angle = 0;
}
TK::TK()//新增功能
{
	hp = 2;
	maxSpeed = 4.0 / 60.0;
	currentSpeed = 0;
	atkRange = 25;
	atkCD = 0;
	defRange = 0;
	defCD = 0;
	weaponSpeed = (6.0 / 60.0);
	weaponAtt = 2;
	type = "TK";
	angle = 0;
}
// Shell的建構子
Shell::Shell(string name, double x, double y, double destination_X, double destination_Y, double speed, double attack)
{
	this->name = name;
	this->x = x;
	this->y = y;
	this->destination_X = destination_X;
	this->destination_Y = destination_Y;
	this->speed = speed;
	this->attack = attack;
}
#pragma endregion
#pragma region 其他
void  Shell::moving()
{
	double xRange, yRange;
	xRange = destination_X - x;
	yRange = destination_Y - y;

	double range = pow(xRange, 2) + pow(yRange, 2);
	range = sqrt(range);

	x += speed * (xRange / range);
	y += speed * (yRange / range);
	//v目的地在原位置左邊，且移動後超過目的地    v目的地在原位置右邊
	if ((xRange < 0 && destination_X > x) || (xRange > 0 && destination_X < x))
	{
		x = destination_X;
	}
	//v目的地在原位置上面                     v在原位置下面
	if ((yRange < 0 && destination_Y > y) || (yRange > 0 && destination_Y < y))
	{
		y = destination_Y;
	}
}

void Vessel::moving()
{
	double newX, newY;	// x的變化量, y的變化量

	double xBound = x;
	double yBound = y;

	newX = currentSpeed * cos(angle * (PI / 180));
	newY = currentSpeed * sin(angle * (PI / 180)) * (-1);	//我不知道為甚麼要乘-1

	if (x + newX <= 0.0)
	{
		x = 0.0;
		currentSpeed = 0.0;
	}
	else if (x + newX >= 20.0)
	{
		x = 20.0;
		currentSpeed = 0.0;
	}
	else
	{
		x = x + newX;
	}

	if (y + newY <= 0.0)
	{
		yBound = 0.0;
		currentSpeed = 0.0;
	}
	else if (y + newY >= 20.0)
	{
		yBound = 20.0;
		currentSpeed = 0;
	}
	else
	{
		y = y + newY;
	}
}
#pragma endregion
