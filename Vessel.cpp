#include "Vessel.h"
#include "MyForm.h"


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

void Vessel::moving()
{
	double newX, newY;

	double xBound = x;
	double yBound = y;

	newX = currentSpeed * cos(angle / 180 * PI);
	newY = currentSpeed * sin(angle / 180 * PI);

	if (x + newX <= 0.0)
	{
		xBound = 0.0;
		newY *= ((x - 0.0) / newX);
		currentSpeed = 0.0;
	}
	else if (x + newX >= 20.0)
	{
		xBound = 20.0;
		newY *= ((20.0 - x) / newX);
		currentSpeed = 0.0;
	}

	if (y + newY <= 0.0)
	{
		yBound = 0.0;
		newX *= ((y - 0.0) / newY);
		currentSpeed = 0.0;
	}

	else if (y + newY >= 20.0)
	{
		yBound = 20.0;
		newX *= ((20.0 - y) / newY);
		currentSpeed = 0;
	}

	if (x != xBound)
		x = xBound;
	else
		x += newX;

	if (y != yBound)
		y = yBound;
	else
		y += newY;
	

}

void Vessel::setAngle(int angle)
{
	this->angle = angle;
}

int getHit(Vessel& it, Shell* weapon)
{

	if (pow(it.getX() - weapon->getX(), 2) + pow(it.getY() - weapon->getY(), 2) <= 2.25)//範圍內表擊中
	{
		int hitValue = weapon ->getATK();
		
		double tempHP = it.getHp();//先得到船艦的HP
		tempHP -= weapon->getATK();//減去武器的攻擊力
		
		if (tempHP <= 0)//小於0表擊沉
		{
			for (int i = 0; i < Vessel_vector.size(); i++)//從vector裡刪除
			{
				if (Vessel_vector[i].getName() == it.getName() && Vessel_vector[i].getTeam() == it.getTeam())
				{
					Vessel_vector.erase(Vessel_vector.begin() + i);
					break;
				}
			}
			it.vanish();//本身刪除

			for (int i = 0; i < Shell_vector.size(); i++)//刪除Shell
			{
				if (Shell_vector[i].getName() == weapon->getName())
				{
					Shell_vector.erase(Shell_vector.begin() + i);
					break;
				}
			}
			
		}
		else
		{
			it.setHp(tempHP);//反之扣血
			for (int i = 0; i < Shell_vector.size(); i++)//刪除Shell
			{
				if (Shell_vector[i].getName() == weapon->getName())
				{
					Shell_vector.erase(Shell_vector.begin() + i);
					break;
				}
			}
			
		}
		return 1;//回傳1表擊中
	}


	else
		weapon->vanish();
		return -1; //回傳-1表沒打中
}

void Shell::setX(double x)
{
	this->x = x;
}

void Shell::setY(double y)
{
	this->y = y;
}

double Shell::getATK()
{
	return this->attack;
}

int  Shell::moving()
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

	if (x == destination_X && y == destination_Y)
	{
		for (int i = 0; i < Vessel_vector.size(); i++)
		{
			if (getHit(Vessel_vector[i], this) == 1)//如果砲彈打到了
			return i;  //回傳是vector中第幾個 要刪掉label
			else if (getHit(Vessel_vector[i], this) == 2)
			return -1; //打到扣血
		}
		return -2; //沒打到回傳-1
	}
	return -3;//還沒到目標回傳-2
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
