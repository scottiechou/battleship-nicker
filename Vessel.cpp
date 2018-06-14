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
	return this->speed;
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
#pragma endregion
#pragma region set()
void Vessel::setHp(double hp)
{
	this->hp = hp;
}

void Vessel::setSpeed(double speed)
{
	this->speed = speed;
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
#pragma endregion
#pragma region �غc�l
CV::CV()
{
	hp = 5;
	speed = 1;
	atkRange = 25;
	atkCD = 0;
	defRange = 5;
	defCD = 0;
	weaponSpeed = (4 / 60);
	weaponAtt = 3;
}

BB::BB()
{
	hp = 4;
	speed = 1;
	atkRange = 20;
	atkCD = 0;
	defRange = 10;
	defCD = 0;
	weaponSpeed = (2 / 60);
	weaponAtt = 3;
}

CG::CG()
{
	hp = 3;
	speed = 2;
	atkRange = 15;
	atkCD = 0;
	defRange = 15;
	defCD = 0;
	weaponSpeed = (3 / 60);
	weaponAtt = 2;
}

DD::DD()
{
	hp = 2;
	speed = 3;
	atkRange = 10;
	atkCD = 0;
	defRange = 20;
	defCD = 0;
	weaponSpeed = (3 / 60);
	weaponAtt = 1;
}
// Shell���غc�l
Shell::Shell(string name, double x, double y, double speed, double attack)
{
	this->name = name;
	this->x = x;
	this->y = y;
	this->speed = speed;
	this->attack = attack;
}
#pragma endregion