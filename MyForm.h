#pragma once
#include "Vessel.h"
#include <ctime>
#include <cstdlib>
#include <vector>
#include <cliext/vector>
#include <sstream>
using std::vector;
using std::stringstream;

static double distance_untiy = 15;		// 遊戲距離的1單位 = 視窗中的15單位
static int acclerate = 15;			// 遊戲加速"acclerate"倍
static int minute = 0, second = 0;	// 用於紀錄遊戲時間
static int log_line = 0;			// 戰鬥日誌的行數
static vector<Vessel> Vessel_vector;// 儲存各式Vessel
static vector<Shell> Shell_vector;	// 儲存各式Shell

bool set(char team, string name, string type, double x, double y);
double distance(double x1, double y1, double x2, double y2);	//測量(x1, y1)與(x2, y2)距離
int fire(char team, string name, double x, double y);
int defense(char team, string vessel_name, string shell_name);
bool tag(char team, string old_name, string new_name);
bool move(char team, string name, double speed, int angle);

namespace Project314
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;

	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		// MyForm建構元
		MyForm(void)
		{
			// distance_untiy = 15;
			// acclerate = 10;
			InitializeComponent();
		}

	protected:
		// MyForm解構元
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
		
		void commandOperation(string cmd, char team);

	private: System::Windows::Forms::Label^  commands_text_title;	// 用於標示commands(指令輸入區)的文字方塊
	private: System::Windows::Forms::TextBox^  commands_A;	// A組的指令輸入區
	private: System::Windows::Forms::TextBox^  commands_B;	// B組的指令輸入區
	private: System::Windows::Forms::PictureBox^  pictureBox1;	// 用於在myForm.h中標記地圖大小，無意
	private: System::Windows::Forms::Label^  battle_log_title;	// 戰鬥日誌標題
	private: System::Windows::Forms::Label^  battle_log;		// 戰鬥日誌本文
	private: System::Windows::Forms::Button^  start_botton;	// 開始鍵
	private: System::Windows::Forms::Button^  pause_botton;	// 暫停鍵
	private: System::Windows::Forms::Timer^  game_timer;	// 計算時間
	private: System::Windows::Forms::Label^  time;		// 顯示時間
	private: System::ComponentModel::IContainer^  components;
	private: List<System::Windows::Forms::Label^>^ Vessel_Label;// 將船艦顯示到螢幕上所用的label
	private: List<System::Windows::Forms::Label^>^ Shell_Label;	// 將砲彈顯示到螢幕上所用的label

#pragma region 初始化各項工具(元件)(InitializeComponent)
	private:
		/*****初始化各項工具(元件)*****/
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->commands_text_title = (gcnew System::Windows::Forms::Label());
			this->commands_A = (gcnew System::Windows::Forms::TextBox());
			this->commands_B = (gcnew System::Windows::Forms::TextBox());
			this->battle_log_title = (gcnew System::Windows::Forms::Label());
			this->start_botton = (gcnew System::Windows::Forms::Button());
			this->pause_botton = (gcnew System::Windows::Forms::Button());
			this->battle_log = (gcnew System::Windows::Forms::Label());
			this->game_timer = (gcnew System::Windows::Forms::Timer(this->components));
			this->time = (gcnew System::Windows::Forms::Label());
			this->Vessel_Label = gcnew List<System::Windows::Forms::Label^>;
			this->Shell_Label = gcnew List<System::Windows::Forms::Label^>;
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(15, 15);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(450, 450);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Visible = false;
			// 
			// commands_text_title
			// 
			this->commands_text_title->AutoSize = true;
			this->commands_text_title->Font = (gcnew System::Drawing::Font(L"新細明體", 10));
			this->commands_text_title->Location = System::Drawing::Point(551, 15);
			this->commands_text_title->Name = L"commands_text_title";
			this->commands_text_title->Size = System::Drawing::Size(109, 20);
			this->commands_text_title->TabIndex = 1;
			this->commands_text_title->Text = L"指令輸入區";
			// 
			// commands_A
			// 
			this->commands_A->Location = System::Drawing::Point(472, 47);
			this->commands_A->Multiline = true;
			this->commands_A->Name = L"commands_A";
			this->commands_A->Size = System::Drawing::Size(266, 198);
			this->commands_A->TabIndex = 2;
			// 
			// commands_B
			// 
			this->commands_B->Location = System::Drawing::Point(472, 267);
			this->commands_B->Multiline = true;
			this->commands_B->Name = L"commands_B";
			this->commands_B->Size = System::Drawing::Size(266, 198);
			this->commands_B->TabIndex = 3;
			// 
			// battle_log_title
			// 
			this->battle_log_title->AutoSize = true;
			this->battle_log_title->Font = (gcnew System::Drawing::Font(L"新細明體", 10));
			this->battle_log_title->Location = System::Drawing::Point(856, 15);
			this->battle_log_title->Name = L"battle_log_title";
			this->battle_log_title->Size = System::Drawing::Size(89, 20);
			this->battle_log_title->TabIndex = 4;
			this->battle_log_title->Text = L"戰鬥日誌";
			// 
			// start_botton
			// 
			this->start_botton->Font = (gcnew System::Drawing::Font(L"新細明體", 10));
			this->start_botton->Location = System::Drawing::Point(187, 471);
			this->start_botton->Name = L"start_botton";
			this->start_botton->Size = System::Drawing::Size(104, 52);
			this->start_botton->TabIndex = 5;
			this->start_botton->Text = L"開始";
			this->start_botton->UseVisualStyleBackColor = true;
			this->start_botton->Click += gcnew System::EventHandler(this, &MyForm::start_botton_Click);
			// 
			// pause_botton
			// 
			this->pause_botton->Font = (gcnew System::Drawing::Font(L"新細明體-ExtB", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->pause_botton->Location = System::Drawing::Point(311, 471);
			this->pause_botton->Name = L"pause_botton";
			this->pause_botton->Size = System::Drawing::Size(98, 52);
			this->pause_botton->TabIndex = 6;
			this->pause_botton->Text = L"暫停";
			this->pause_botton->UseVisualStyleBackColor = true;
			this->pause_botton->Click += gcnew System::EventHandler(this, &MyForm::pause_botton_Click);
			// 
			// battle_log
			// 
			this->battle_log->AutoSize = true;
			this->battle_log->Font = (gcnew System::Drawing::Font(L"新細明體", 9));
			this->battle_log->Location = System::Drawing::Point(744, 47);
			this->battle_log->Name = L"battle_log";
			this->battle_log->Size = System::Drawing::Size(0, 18);
			this->battle_log->TabIndex = 7;
			// 
			// game_timer
			// 
			this->game_timer->Tick += gcnew System::EventHandler(this, &MyForm::game_timer_Tick);
			this->game_timer->Interval = 1000 / acclerate;
			// 
			// time
			// 
			this->time->AutoSize = true;
			this->time->Font = (gcnew System::Drawing::Font(L"Consolas", 12));
			this->time->Location = System::Drawing::Point(59, 483);
			this->time->Name = L"time";
			this->time->Size = System::Drawing::Size(77, 28);
			this->time->TabIndex = 8;
			this->time->Text = L"00:00";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 18);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1070, 535);
			this->Controls->Add(this->time);
			this->Controls->Add(this->battle_log);
			this->Controls->Add(this->start_botton);
			this->Controls->Add(this->pause_botton);
			this->Controls->Add(this->battle_log_title);
			this->Controls->Add(this->commands_B);
			this->Controls->Add(this->commands_text_title);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->commands_A);
			this->Name = L"MyForm";
			this->Text = L"即時戰略遊戲FERTIG - 第14組";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
#pragma region 遊戲初始化時，視窗上要加載的東西(MyForm_Load)
	private:
		// 遊戲初始化時，視窗上要加載的東西
		System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e)
		{
			// 建立遊戲地圖(20*20的方格)，並加載到遊戲視窗上
			array<System::Windows::Forms::Label^>^ labels;
			array<System::Windows::Forms::Label^>^ labelsV;
			labels = gcnew array<System::Windows::Forms::Label^>(21);
			labelsV = gcnew array<System::Windows::Forms::Label^>(21);
			int bias = 10;
			for (int i = 0; i < 21; i++)
			{
				labels[i] = gcnew System::Windows::Forms::Label();
				labels[i]->BackColor = System::Drawing::Color::Navy;
				labels[i]->Location = System::Drawing::Point(0 + bias, 15 * i + bias);
				labels[i]->Size = System::Drawing::Size(300, 1);
				labels[i]->AutoSize = false;
			}
			for (int i = 0; i < 21; i++)
			{
				labelsV[i] = gcnew System::Windows::Forms::Label();
				labelsV[i]->BackColor = System::Drawing::Color::Navy;
				labelsV[i]->Location = System::Drawing::Point(15 * i + bias, 0 + bias);
				labelsV[i]->Size = System::Drawing::Size(1, 300);
				labelsV[i]->AutoSize = false;
			}
			for (int i = 0; i < 21; i++)	// 將地圖添加到視窗(Controls)上
			{
				this->Controls->Add(labels[i]);
				this->Controls->Add(labelsV[i]);
			}
		}
#pragma endregion
#pragma region 開始/暫停鍵設定
	private:
		System::Void start_botton_Click(System::Object^  sender, System::EventArgs^  e)
		{
			if (this->game_timer->Enabled == false)	//避免重複按到開始鍵
			{
				this->game_timer->Enabled = true;	//時間開始
				commands_A->Enabled = false;	//停止輸入指令
				commands_B->Enabled = false;
				// 輸出開始訊號
				System::String ^Min, ^Sec;	//將時間轉成String型態後再輸出
				Min = System::Convert::ToString(minute);
				Sec = System::Convert::ToString(second);
				if (Min->Length < 2)
					Min = "0" + Min;
				if (Sec->Length < 2)
					Sec = "0" + Sec;
				battle_log->Text += "[" + Min + ":" + Sec + "] Game Start\n";
				log_line++;
				if (log_line >= 25)
				{
					log_line = 0;
					battle_log->ResetText();
					battle_log->Text += "[" + Min + ":" + Sec + "] Game Start\n";
					log_line++;
				}
				// 處理command_A和command_B
				vector<string> cmdA, cmdB;
				string tempCmd = "";
				int i = 0;
				int layer_A = 0; //第幾層command 
				int layer_B = 0;

				while (i < this->commands_A->Text->Length)
				{
					while (commands_A->Text[i] != '\n' && i < commands_A->Text->Length)
					{
						tempCmd += commands_A->Text[i];
						i++;
					}
					if (commands_A->Text[i] == '\n' || i == commands_A->Text->Length)
					{
						cmdA.push_back(tempCmd);
						tempCmd = ""; //清空 
						i++;
					}
				}
				i = 0;
				while (i < this->commands_B->Text->Length)
				{
					while (commands_B->Text[i] != '\n' && i < commands_B->Text->Length)
					{
						tempCmd += commands_B->Text[i];
						i++;
					}
					if (commands_B->Text[i] == '\n' || i == commands_B->Text->Length)
					{
						cmdB.push_back(tempCmd);
						tempCmd = "";
						i++;
					}
				}

				while (1)
				{
					if (layer_A >= cmdA.size() && layer_B >= cmdB.size())
						break;
					if (layer_A < cmdA.size())
					{
						commandOperation(cmdA[layer_A], 'A');
						layer_A++;
					}
					if (layer_B < cmdB.size())
					{
						commandOperation(cmdB[layer_B], 'B');
						layer_B++;
					}
				}
				commands_A->Text = "";
				commands_B->Text = "";
				this->game_timer->Enabled = true;	//時間開始
			}
		}
	private:
		System::Void pause_botton_Click(System::Object^  sender, System::EventArgs^  e)
		{
			if (this->game_timer->Enabled == true)
			{
				this->game_timer->Enabled = false;
				commands_A->Enabled = true;
				commands_B->Enabled = true;

				// 輸出暫停訊號
				// 將時間轉成String型態
				System::String ^Min, ^Sec;
				Min = System::Convert::ToString(minute);
				Sec = System::Convert::ToString(second);
				if (Min->Length < 2)
					Min = "0" + Min;
				if (Sec->Length < 2)
					Sec = "0" + Sec;
				battle_log->Text += "[" + Min + ":" + Sec + "] Game Pause\n";
				log_line++;
				if (log_line >= 25)
				{
					log_line = 0;
					battle_log->ResetText();
					battle_log->Text += "[" + Min + ":" + Sec + "] Game Pause\n";
					log_line++;
				}
			}
		}
#pragma endregion
#pragma region 遊戲計時器
	private:
		System::Void game_timer_Tick(System::Object^  sender, System::EventArgs^  e)
		{
			// 計算遊戲時間
			second++;
			if (second == 60)
			{
				minute++;
				second = 0;
			}
			System::String ^Min, ^Sec;	//將int(minute, second)轉成String(Min, Sec)
			Min = System::Convert::ToString(minute);
			Sec = System::Convert::ToString(second);
			if (Min->Length < 2)
				Min = "0" + Min;
			if (Sec->Length < 2)
				Sec = "0" + Sec;
			time->Text = (Min + ":" + Sec);	//輸出時間

			// 更新船艦的CD時間
			for (int i = 0; i < Vessel_vector.size(); i++)
			{
				Vessel_vector[i].setAtkCD(Vessel_vector[i].getAtkCD() - 1);
				Vessel_vector[i].setDefCD(Vessel_vector[i].getDefCD() - 1);
			}

		}
	private: System::Void commands_text_title_Click(System::Object^  sender, System::EventArgs^  e) {
	}
};
#pragma endregion
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

		while (cmd[pointer] == ')')  //(x,y)
		{
			if (cmd[pointer] == '(') pointer++;  //處理(x,

			while (cmd[pointer] != ',')
			{
				coordinate += cmd[pointer];
				pointer++;
			}

			if (cmd[pointer] == ',')
			{
				pointer++;
				x = System::Convert::ToDouble(coordinate);
				coordinate = "";
			}

			while (cmd[pointer] != ')')  //處理 y)
			{
				coordinate += cmd[pointer];
				pointer++;
			}

			y = System::Convert::ToDouble(coordinate);
			coordinate = "";
		}
		// 將砲彈顯示在螢幕上
		switch (fire(team, vesselName, x, y))
		{
			System::String ^vesselName_String, ^shellName_String;
			vesselName_String = gcnew String(vesselName.c_str());
			shellName_String = gcnew String(Shell_vector[Shell_vector.size() - 1].getName().c_str());
		case 1:
		{
			System::Windows::Forms::Label^ newShellLabel;
			newShellLabel = gcnew System::Windows::Forms::Label();
			newShellLabel->ForeColor = System::Drawing::Color::Black;
			newShellLabel->Location = System::Drawing::Point(15 + x * distance_untiy, 15 + y * distance_untiy);
			newShellLabel->Text = "·" + shellName_String;
			newShellLabel->AutoSize = false;
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
			battle_log->Text += "Team" + team + vesselName_String + " FIRE to ";
			battle_log->Text += "(" + System::Convert::ToString(x) + "," + System::Convert::ToString(y) + ")";
			battle_log->Text += " -> " + shellName_String + "\n";
			log_line++;
			break;
		}
		default:
			// Battle Log (戰鬥指令對應輸出)
			if (log_line >= 25)
			{
				log_line = 0;
				battle_log->ResetText();
			}
			battle_log->Text += "[" + Min + ":" + Sec + "] ";
			battle_log->Text += "Team" + team + vesselName_String + " FIRE to ";
			battle_log->Text += "(" + System::Convert::ToString(x) + "," + System::Convert::ToString(y) + ")";
			battle_log->Text += " -> Fail\n";
			log_line++;
			break;
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

		if (cmd[pointer] != ' ')  pointer++;

		while (cmd[pointer] != ' ' || cmd[pointer] != '\0')
		{
			shellName += cmd[pointer];
			pointer++;
		}
		System::String ^vesselName_String, ^shellName_String;
		vesselName_String = gcnew String(vesselName.c_str());
		shellName_String = gcnew String(shellName.c_str());

		int defenseSituation = defense(team, vesselName, shellName);	//防守情形
		if (defenseSituation != -1)
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
			battle_log->Text += "[" + Min + ":" + Sec + "] ";
			battle_log->Text += vesselName_String + " DEFENSE " + shellName_String;
			battle_log->Text += " -> Fail" + "\n";
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

		while (cmd[pointer] != ' ')
		{
			vesselName += cmd[pointer];
			pointer++;
		}

		if (cmd[pointer] == ' ') pointer++;

		while (cmd[pointer] != ' ')
		{
			speed += cmd[pointer];
			pointer++;
		}

		if (cmd[pointer] == ' ') pointer++;

		while (cmd[pointer] != ' ' && cmd[pointer] != '\0')
		{
			angle += cmd[pointer];
			pointer++;
		}

		toSpeed = System::Convert::ToDouble(speed);
		toAngle = System::Convert::ToInt32(angle);
		System::String ^vesselName_String = gcnew System::String(vesselName.c_str());

		// Battle Log (戰鬥指令對應輸出)
		if (log_line >= 25)
		{
			log_line = 0;
			battle_log->ResetText();
		}
		battle_log->Text += "[" + Min + ":" + Sec + "] ";
		battle_log->Text += "Team" + team + vesselName_String + " MOVE to " + toAngle + " as " + toSpeed;
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

		if (cmd[pointer] == ' ') pointer++; //第二次遇到空白，這次處理type

		while (cmd[pointer] != ' ')
		{
			newName += cmd[pointer];
			pointer;
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
		battle_log->Text += "[" + Min + ":" + Sec + "] ";
		battle_log->Text += "Team" + team + " RENAME " + vesselName_String + " to " + newName_String;
		if (tag(team, vesselName, newName))
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
	// 如果指令無效
	else
	{
		String^ tempCmd = gcnew String(cmd.c_str());
		//battle_log->Text += "cmdType = " + cmdType + "\n";	//01:25更改
		//battle_log->Text += ("Command : " + tempCmd + " is invalid.\n");	//01:25更改
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
		newVessel.setName(name);
		newVessel.setX(x);
		newVessel.setY(y);
		Vessel_vector.push_back(newVessel);
		return true;
	}
	else if (type == "DD") {
		for (int i = 0; i <Vessel_vector.size(); i++) {
			if (Vessel_vector[i].getName() == name && Vessel_vector[i].getTeam() == team) {
				return false;
			}
		}
		DD newVessel;
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
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

// FIRE指令
int fire(char team, string name, double x, double y)	//攻擊艦隊伍、攻擊艦名字、攻擊座標
{
	/*
		(1)先檢查有沒有這艘船艦與，(2)在檢查可不可以發射(CD時間到了沒)，最後return發射情形
		return種類：
		1 = 正常發射, 2 = CD時間還沒到, 3 = 沒有這艘船
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
				return 1;
			}
			else	// 如果CD時間還沒到(不能發射)
				return 2;
		}
	}
	return 3;	// 如果找不到這艘戰艦
}

// DEFENSE指令
int defense(char team, string vessel_name, string shell_name)	//防守艦隊伍、防守艦名字、砲彈名字
{
	/*
		先檢查有沒有這艘船艦，在檢查有沒有這個砲彈
		return種類：
		如果是正常防守，就回傳被刪掉的shell的index，其他情況則回傳-1
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
				if (Shell_vector[i].getName() == vessel_name)
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
						return (-1);
				}
			}
			// 如果沒找到砲彈
			return (-1);
		}
	}
	//如果找不到這艘戰艦
	return (-1);
}

//TAG 指令
bool tag(char team, string old_name, string new_name) {//一個舊名字和一個新名字
	for (int i = 0; i < Vessel_vector.size(); i++) {
		if (Vessel_vector[i].getName() == new_name)//先找新名字有沒有衝到
			return false;
	}
	for (int i = 0; i < Vessel_vector.size(); i++) {
		if (Vessel_vector[i].getName() == old_name) {//再找舊名字存不存在
			Vessel_vector[i].setName(new_name);
			return true;
		}			
	}
	return false;
}

// MOVE 指令
bool move(char team, string name, double speed, int angle) // 回傳是否找到船艦
{
	bool getVessel = false;
	unsigned int p ; //記錄在Vector 中哪一個位置
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

