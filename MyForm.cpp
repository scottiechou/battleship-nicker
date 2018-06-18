#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
void Main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Project314::MyForm form;
	Application::Run(%form);
}

void Project314::MyForm::writeLog(String^ text)
{
	battle_log->Text += (text + '\n');
	log_line++;
	if (log_line >= 25)
	{
		log_line = 0;
		battle_log->ResetText();
		battle_log->Text += (text + "\n");
		log_line++;
	}
}

void Project314::MyForm::commandOperation(string cmd, char team)
{
	String^ cmdType = "";//命令種類
	string tempS;
	int pointer = 0;//指標
	System::String ^Min, ^Sec;	// 將時間轉成String型態，用於battle_log輸出
	Min = System::Convert::ToString(minute);
	Sec = System::Convert::ToString(second);
	if (Min->Length < 2)
		Min = "0" + Min;
	if (Sec->Length < 2)
		Sec = "0" + Sec;

	while (cmd[pointer] != ' ')	//01:25更改
	{
		tempS += cmd[pointer];
		pointer++;
	}
	cmdType = gcnew String(tempS.c_str());	//01:25更改
	tempS.clear();

	if (cmd[pointer] == ' ')
		pointer++; //第一次遇到空白

	// 如果指令是SET
	if (cmdType->ToUpper() == "SET")
	{
		string vesselName = "";
		string type = "";
		String^ coordinate = "";
		double x, y;

		while (cmd[pointer] != ' ')
		{
			vesselName += cmd[pointer];
			pointer++;
		}

		if (cmd[pointer] == ' ') pointer++; //第二次遇到空白，這次處理type

		while (cmd[pointer] != ' ')
		{
			type += cmd[pointer];
			pointer++;
		}

		if (cmd[pointer] == ' ') pointer++; //第三次遇到空白，這次處理位置

		while (cmd[pointer] != ')')
		{
			if (cmd[pointer] == '(') pointer++;

			while (cmd[pointer] != ',')
			{
				tempS += cmd[pointer];
				pointer++;
			}

			if (cmd[pointer] == ',')
			{
				pointer++;
				coordinate = gcnew String(tempS.c_str());
				x = System::Convert::ToDouble(coordinate);
				coordinate = "";
				tempS.clear();
			}

			while (cmd[pointer] != ')')
			{
				tempS += cmd[pointer];
				pointer++;
			}

			coordinate = gcnew String(tempS.c_str());
			y = System::Convert::ToDouble(coordinate);
			coordinate = "";
			tempS.clear();

		}

		// 將船艦顯示到螢幕上
		System::String ^vesselName_String, ^type_String;
		vesselName_String = gcnew String(vesselName.c_str());
		type_String = gcnew String(type.c_str());
		Char team_Char = team;
		if (set(team, vesselName, type, x, y))	// 如果成功設置
		{
			System::Windows::Forms::Label^ newVesselLabel;
			newVesselLabel = (gcnew System::Windows::Forms::Label());
			if (team == 'A')
				newVesselLabel->ForeColor = System::Drawing::Color::Red;
			else if (team == 'B')
				newVesselLabel->ForeColor = System::Drawing::Color::Blue;
			//newVesselLabel->BackColor = System::Drawing::Color::Navy;
			newVesselLabel->Location = System::Drawing::Point(10 + x * distance_untiy, 10 + y * distance_untiy);
			newVesselLabel->Text = "▲" + vesselName_String;
			newVesselLabel->AutoSize = true;
			Vessel_Label->Add(newVesselLabel);
			int lastLabel = Vessel_vector.size() - 1;
			this->Controls->Add(Vessel_Label[lastLabel]);

			// Battle Log (戰鬥指令對應輸出)
			if (log_line >= 25)
			{
				log_line = 0;
				battle_log->ResetText();
			}
			battle_log->Text += "[" + Min + ":" + Sec + "] ";
			battle_log->Text += "Team" + team_Char + " SET " + vesselName_String + " with " + type_String;
			battle_log->Text += " at (" + System::Convert::ToString(x) + "," + System::Convert::ToString(y) + ")";
			battle_log->Text += " -> Success\n";
			log_line++;
		}
		else
		{
			// Battle Log (戰鬥指令對應輸出)
			if (log_line >= 25)
			{
				log_line = 0;
				battle_log->ResetText();
			}
			battle_log->Text += "[" + Min + ":" + Sec + "] ";
			battle_log->Text += "Team" + team_Char + " SET " + vesselName_String + " with " + type_String;
			battle_log->Text += " at (" + System::Convert::ToString(x) + "," + System::Convert::ToString(y) + ")";
			battle_log->Text += " -> Fail\n";
			log_line++;
		}
	}
	// 如果指令是FIRE
	else if (cmdType->ToUpper() == "FIRE")
	{
		string vesselName;
		String^ coordinate;

		double x, y;

		while (cmd[pointer] != ' ')
		{
			vesselName += cmd[pointer];
			pointer++;
		}

		if (cmd[pointer] == ' ') pointer++; //第二次遇到空白，這次處理coordinate

		tempS.clear();
		while (cmd[pointer] != ')')
		{
			if (cmd[pointer] == '(') pointer++;

			while (cmd[pointer] != ',')
			{
				tempS += cmd[pointer];
				pointer++;
			}

			if (cmd[pointer] == ',')
			{
				pointer++;
				coordinate = gcnew String(tempS.c_str());
				x = System::Convert::ToDouble(coordinate);
				coordinate = "";
				tempS.clear();
			}

			while (cmd[pointer] != ')')
			{
				tempS += cmd[pointer];
				pointer++;
			}

			coordinate = gcnew String(tempS.c_str());
			y = System::Convert::ToDouble(coordinate);
			coordinate = "";
			tempS.clear();

		}
		// 將砲彈顯示在螢幕上
		System::String ^vesselName_String, ^shellName_String;
		vesselName_String = gcnew String(vesselName.c_str());
		Char team_Char = team;
		int fireSituation = fire(team, vesselName, x, y);
		if (fireSituation >= 0)
		{
			shellName_String = gcnew String(Shell_vector[Shell_vector.size() - 1].getName().c_str());
			System::Windows::Forms::Label^ newShellLabel;
			newShellLabel = gcnew System::Windows::Forms::Label();
			//newShellLabel->BackColor = System::Drawing::Color::Yellow;
			newShellLabel->ForeColor = System::Drawing::Color::Black;
			newShellLabel->Location = System::Drawing::Point(10 + Vessel_vector[fireSituation].getX() * distance_untiy, 10 + Vessel_vector[fireSituation].getY() * distance_untiy);
			newShellLabel->Text = "●" + shellName_String;
			newShellLabel->AutoSize = true;
			Shell_Label->Add(newShellLabel);
			int lastShell = Shell_vector.size() - 1;
			this->Controls->Add(Shell_Label[lastShell]);

			// Battle Log (戰鬥指令對應輸出)
			if (log_line >= 25)
			{
				log_line = 0;
				battle_log->ResetText();
			}
			battle_log->Text += "[" + Min + ":" + Sec + "] ";
			battle_log->Text += "Team" + team_Char + " " + vesselName_String + " FIRE to ";
			battle_log->Text += "(" + System::Convert::ToString(x) + "," + System::Convert::ToString(y) + ")";
			battle_log->Text += " -> " + shellName_String + "\n";
			log_line++;
		}
		else
		{
			// Battle Log (戰鬥指令對應輸出)
			if (log_line >= 25)
			{
				log_line = 0;
				battle_log->ResetText();
			}
			battle_log->Text += "[" + Min + ":" + Sec + "] ";
			battle_log->Text += "Team" + team_Char + " " + vesselName_String + " FIRE to ";
			battle_log->Text += "(" + System::Convert::ToString(x) + "," + System::Convert::ToString(y) + ")";
			battle_log->Text += " -> Fail\n";
			log_line++;
		}
	}
	// 如果指令是DEFENSE
	else if (cmdType->ToUpper() == "DEFENSE")
	{
		string vesselName = "";
		string shellName = "";

		while (cmd[pointer] != ' ')
		{
			vesselName += cmd[pointer];
			pointer++;
		}

		if (cmd[pointer] == ' ')  pointer++;

		while (pointer < cmd.size()-1)
		{
			if(('a' <= cmd[pointer] && cmd[pointer] <= 'z') || ('A' <= cmd[pointer] && cmd[pointer] <= 'Z') || cmd[pointer] == '_' || ('0' <= cmd[pointer] && cmd[pointer] <= '9'))
				shellName += cmd[pointer];
			pointer++;
		}
		System::String ^vesselName_String, ^shellName_String;
		vesselName_String = gcnew String(vesselName.c_str());
		shellName_String = gcnew String(shellName.c_str());

		int defenseSituation = defense(team, vesselName, shellName);	//防守情形
		if (defenseSituation >= 0)
		{
			this->Controls->Remove(Shell_Label[defenseSituation]);
			Shell_Label->RemoveAt(defenseSituation);

			// Battle Log (戰鬥指令對應輸出)
			if (log_line >= 25)
			{
				log_line = 0;
				battle_log->ResetText();
			}
			battle_log->Text += "[" + Min + ":" + Sec + "] ";
			battle_log->Text += vesselName_String + " DEFENSE " + shellName_String;
			battle_log->Text += " -> Hit" + "\n";
			log_line++;
		}
		else
		{
			// Battle Log (戰鬥指令對應輸出)
			if (log_line >= 25)
			{
				log_line = 0;
				battle_log->ResetText();
			}
			//System::String ^ss = gcnew System::String(Shell_vector[0].getName().c_str());
			//System::String ^inputss = gcnew System::String(shellName.c_str());
			battle_log->Text += "[" + Min + ":" + Sec + "] ";
			battle_log->Text += vesselName_String + " DEFENSE " + shellName_String;
			battle_log->Text += " -> Fail(" + System::Convert::ToString(defenseSituation) + ")\n";
			//battle_log->Text += "Shell_vector.size() = " + System::Convert::ToString(Shell_vector.size()) + "\n";
			//battle_log->Text += "Shell_vector[0].name = " + ss + "\n";
			//battle_log->Text += "shellName = " + inputss + "\n";
			log_line++;
		}
	}
	// 如果指令是MOVE
	else if (cmdType->ToUpper() == "MOVE")
	{
		String^ speed;
		String^ angle;

		string vesselName;
		double toSpeed;
		int toAngle;

		tempS.clear();
		while (cmd[pointer] != ' ')
		{
			vesselName += cmd[pointer];
			pointer++;
		}

		if (cmd[pointer] == ' ') pointer++;

		while (cmd[pointer] != ' ')
		{
			tempS += cmd[pointer];
			pointer++;
		}
		speed = gcnew System::String(tempS.c_str());
		tempS.clear();

		if (cmd[pointer] == ' ') pointer++;

		while (pointer < cmd.size())
		{
			if('0' <= cmd[pointer] && cmd[pointer] <= '9')
				tempS += cmd[pointer];
			pointer++;
		}
		angle = gcnew System::String(tempS.c_str());
		tempS.clear();

		toSpeed = System::Convert::ToDouble(speed);
		toAngle = System::Convert::ToInt32(angle);
		System::String ^vesselName_String = gcnew System::String(vesselName.c_str());

		// Battle Log (戰鬥指令對應輸出)
		Char team_Char = team;
		if (log_line >= 25)
		{
			log_line = 0;
			battle_log->ResetText();
		}
		battle_log->Text += "[" + Min + ":" + Sec + "] ";
		battle_log->Text += "Team" + team_Char + " " + vesselName_String + " MOVE to " + angle + " as " + speed;
		if (move(team, vesselName, toSpeed, toAngle))
		{
			battle_log->Text += " -> Success\n";
			log_line++;
		}
		else
		{
			battle_log->Text += " -> Fail\n";
			log_line++;
		}
	}
	// 如果指令是TAG
	else if (cmdType->ToUpper() == "TAG")
	{
		string vesselName;
		string newName;

		while (cmd[pointer] != ' ')
		{
			vesselName += cmd[pointer];
			pointer++;
		}

		if (cmd[pointer] == ' ') pointer++; //第二次遇到空白，這次處理newName

		while (pointer < cmd.length()-1)
		{
			newName += cmd[pointer];
			pointer++;
		}

		System::String ^vesselName_String, ^newName_String;
		vesselName_String = gcnew System::String(vesselName.c_str());
		newName_String = gcnew System::String(newName.c_str());

		// Battle Log (戰鬥指令對應輸出)
		if (log_line >= 25)
		{
			log_line = 0;
			battle_log->ResetText();
		}
		Char team_Char = team;
		battle_log->Text += "[" + Min + ":" + Sec + "] ";
		battle_log->Text += "Team" + team_Char + " RENAME " + vesselName_String + " to " + newName_String;
		int tagSituation = tag(team, vesselName, newName);
		if (tagSituation != -1)
		{
			battle_log->Text += " -> Success\n";
			log_line++;
			System::String ^vesselName_String = gcnew System::String(vesselName.c_str());
			Vessel_Label[tagSituation]->Text = "▲" + newName_String;
		}
		else
		{
			battle_log->Text += " -> Fail\n";
			log_line++;
		}
	}
	// 如果指令無效
	else
	{
		String^ tempCmd = gcnew String(cmd.c_str());
		log_line++;
		if (log_line >= 25)
		{
			log_line = 0;
			battle_log->ResetText();
			battle_log->Text += ("Command : " + tempCmd + " is invalid.\n");
			log_line++;
		}
	}
}

// SET指令
bool set(char team, string name, string type, double x, double y)
{
	if (type == "CV") {
		for (int i = 0; i < Vessel_vector.size(); i++) {
			if (Vessel_vector[i].getName() == name && Vessel_vector[i].getTeam() == team) {
				return false;
			}
		}
		CV newVessel;
		newVessel.setTeam(team);
		newVessel.setName(name);
		newVessel.setX(x);
		newVessel.setY(y);
		Vessel_vector.push_back(newVessel);
		return true;

	}
	else if (type == "BB") {
		for (int i = 0; i < Vessel_vector.size(); i++) {
			if (Vessel_vector[i].getName() == name && Vessel_vector[i].getTeam() == team) {
				return false;
			}
		}
		BB newVessel;
		newVessel.setTeam(team);
		newVessel.setName(name);
		newVessel.setX(x);
		newVessel.setY(y);
		Vessel_vector.push_back(newVessel);
		return true;
	}
	else if (type == "CG") {
		for (int i = 0; i < Vessel_vector.size(); i++) {
			if (Vessel_vector[i].getName() == name && Vessel_vector[i].getTeam() == team) {
				return false;
			}
		}
		CG newVessel;
		newVessel.setTeam(team);
		newVessel.setName(name);
		newVessel.setX(x);
		newVessel.setY(y);
		Vessel_vector.push_back(newVessel);
		return true;
	}
	else if (type == "DD") {
		for (int i = 0; i < Vessel_vector.size(); i++) {
			if (Vessel_vector[i].getName() == name && Vessel_vector[i].getTeam() == team) {
				return false;
			}
		}
		DD newVessel;
		newVessel.setTeam(team);
		newVessel.setName(name);
		newVessel.setX(x);
		newVessel.setY(y);
		Vessel_vector.push_back(newVessel);
		return true;
	}
	else {
		return false;
	}
}
inline double distance(double x1, double y1, double x2, double y2) {//距離 
	if (pow(x1 - x2, 2) + pow(y1 - y2, 2) == 0)
		return 0;
	else
		return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

// FIRE指令--如果是正常發射就回傳船艦的索引值，如果找不到這艘戰艦-1, 如果CD時間還沒到回傳-2
int fire(char team, string name, double x, double y)	//攻擊艦隊伍、攻擊艦名字、攻擊座標
{
	/*
	(1)先檢查有沒有這艘船艦與，(2)在檢查可不可以發射(CD時間到了沒)，最後return發射情形
	return種類：
	如果是正常發射就回傳船艦的索引值，其他情況則回傳-1
	*/
	// (1)檢查Vessel_vector裡有沒有這個戰艦
	for (int i = 0; i < Vessel_vector.size(); i++)
	{
		// (2)如果找到了這艘船，就檢查能不能發射(CD時間到了沒)
		if (Vessel_vector[i].getName() == name && Vessel_vector[i].getTeam() == team)
		{
			if (Vessel_vector[i].getAtkCD() == 0)	// 如果CD時間到了(可以發射)
			{
				stringstream pivot;
				pivot << "Shell_" << team << Shell_vector.size() + 1;
				string shell_name;
				pivot >> shell_name;
				Shell newShell(shell_name, Vessel_vector[i].getX(), Vessel_vector[i].getY(), x, y, Vessel_vector[i].getWeaponSpeed(), Vessel_vector[i].getWeaponAtt());
				Shell_vector.push_back(newShell);
				return i;
			}
			else	// 如果CD時間還沒到(不能發射)
				return -2;
		}
	}
	return -1;	// 如果找不到這艘戰艦
}

// DEFENSE指令--如果是正常防守，就回傳被刪掉的shell的index，其他情況則回傳-1
// j = 正常防守, -1 = 沒有這艘船, -2 = 沒有這個砲彈, -3 = 防守CD時間未到or防守距離不夠
int defense(char team, string vessel_name, string shell_name)	//防守艦隊伍、防守艦名字、砲彈名字
{
	/*
		先檢查有沒有這艘船艦，在檢查有沒有這個砲彈
		return種類：
		如果是正常防守，就回傳被刪掉的shell的index，其他情況則回傳-1
		// j = 正常防守, -1 = 沒有這艘船, -2 = 沒有這個砲彈, -3 = 防守CD時間未到or防守距離不夠
	*/
	// 先查Vessel_vector裡有沒有(vessel_name)這個戰艦
	for (int i = 0; i < Vessel_vector.size(); i++)
	{
		//如果找到了這艘船
		if (Vessel_vector[i].getName() == vessel_name && Vessel_vector[i].getTeam() == team)
		{
			// 檢查有沒有(shell_name)這個砲彈
			for (int j = 0; j < Shell_vector.size(); j++)
			{
				// 如果找到這個砲彈，就檢查可不可以防禦(防禦CD到了沒)
				if (Shell_vector[j].getName() == shell_name)
				{
					if (Vessel_vector[i].getDefCD() == 0
						&& (distance(Vessel_vector[i].getX(), Vessel_vector[i].getY(), Shell_vector[j].getX(), Shell_vector[j].getY()))
						<= Vessel_vector[i].getDefRange())	//如果可以防禦
					{
						if (Vessel_vector[i].getType() == "CV")	//重設CD
							Vessel_vector[i].setDefCD(CV_DEF_CD);
						else if (Vessel_vector[i].getType() == "BB")
							Vessel_vector[i].setDefCD(BB_DEF_CD);
						else if (Vessel_vector[i].getType() == "CG")
							Vessel_vector[i].setDefCD(CG_DEF_CD);
						else if (Vessel_vector[i].getType() == "DD")
							Vessel_vector[i].setDefCD(DD_DEF_CD);
						Shell_vector.erase(Shell_vector.begin() + j);	//刪除砲彈
						return j;
					}
					else
						return (-3);
				}
			}
			// 如果沒找到砲彈
			return (-2);
		}
	}
	//如果找不到這艘戰艦
	return (-1);
}

// TAG指令--如果是正常更改就回傳船艦的索引值，其他則回傳-1
int tag(char team, string old_name, string new_name) {
	for (int i = 0; i < Vessel_vector.size(); i++) {
		if (Vessel_vector[i].getTeam() == team && Vessel_vector[i].getName() == new_name)
			return -1;
	}
	for (int i = 0; i < Vessel_vector.size(); i++) {
		if (Vessel_vector[i].getTeam() == team && Vessel_vector[i].getName() == old_name) {
			Vessel_vector[i].setName(new_name);
			return i;
		}
	}
	return -1;
}

// MOVE 指令
bool move(char team, string name, double speed, int angle) // 回傳是否找到船艦
{
	bool getVessel = false;
	unsigned int p; //記錄在Vector 中哪一個位置
	for (unsigned int i = 0; i < Vessel_vector.size(); i++)
	{
		if (Vessel_vector[i].getName() == name && Vessel_vector[i].getTeam() == team)
		{
			getVessel = true;  p = i;
		}

		if (getVessel)
		{
			if (speed > Vessel_vector[p].getMaxSpeed())//超出船艦最大速度的話
				Vessel_vector[p].setSpeed(Vessel_vector[p].getMaxSpeed());
			else
				Vessel_vector[p].setSpeed(speed);

			if (angle >= 360)//輸入超過360度就把他mod
				angle %= 360;

			Vessel_vector[p].setAngle(angle);
		}
	}
	return getVessel;
}
