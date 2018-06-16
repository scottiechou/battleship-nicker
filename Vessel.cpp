#include "Vessel.h"

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
	maxSpeed = 1;
	currentSpeed = 0;
	atkRange = 25;
	atkCD = 0;
	defRange = 5;
	defCD = 0;
	weaponSpeed = (4 / 60);
	weaponAtt = 3;
	type = "CV";
	angle = 0;
}

BB::BB()
{
	hp = 4;
	maxSpeed = 1;
	currentSpeed = 0;
	atkRange = 20;
	atkCD = 0;
	defRange = 10;
	defCD = 0;
	weaponSpeed = (2 / 60);
	weaponAtt = 3;
	type = "BB";
	angle = 0;
}
}

CG::CG()
{
	hp = 3;
	maxSpeed = 2;
	currentSpeed = 0;
	atkRange = 15;
	atkCD = 0;
	defRange = 15;
	defCD = 0;
	weaponSpeed = (3 / 60);
	weaponAtt = 2;
	type = "CG";
	angle = 0;
}
}

DD::DD()
{
	hp = 2;
	maxSpeed = 3;
	currentSpeed = 0;
	atkRange = 10;
	atkCD = 0;
	defRange = 20;
	defCD = 0;
	weaponSpeed = (3 / 60);
	weaponAtt = 1;
	type = "DD";
	angle = 0;
}
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
