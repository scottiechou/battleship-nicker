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

class Vessel;
class Shell;

bool set(char team, string name, string type, double x, double y);
double distance(double x1, double y1, double x2, double y2);	//測量(x1, y1)與(x2, y2)距離
int fire(char team, string name, double x, double y);
int defense(char team, string vessel_name, string shell_name);
int tag(char team, string old_name, string new_name)
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
				if (commands_A->Text->Length > 0 && commands_A->Text[commands_A->Text->Length - 1] != '\n')	//方-6/19新增
					commands_A->Text += "\n";								//(沒有這行的話會發生"command要多加一個空行")
				if (commands_B->Text->Length > 0 && commands_B->Text[commands_B->Text->Length - 1] != '\n')	//不然會runtime error
					commands_B->Text += "\n";
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
				if (Vessel_vector[i].getAtkCD() != 0)
					Vessel_vector[i].setAtkCD(Vessel_vector[i].getAtkCD() - 1);
				if (Vessel_vector[i].getDefCD() != 0)
					Vessel_vector[i].setDefCD(Vessel_vector[i].getDefCD() - 1);
				Vessel_vector[i].moving();//船艦移動
					Vessel_Label[i]->Location = System::Drawing::Point(10 + Vessel_vector[i].getX() * distance_untiy, 10 + Vessel_vector[i].getY() * distance_untiy);
			}

			for (int i = 0; i < Shell_vector.size(); i++)
			{
				Shell_vector[i].moving();//砲彈移動
				Shell_Label[i]->Location = System::Drawing::Point(10 + Shell_vector[i].getX() * distance_untiy, 10 + Shell_vector[i].getY() * distance_untiy);
				if (Shell_vector[i].moving() >= 0) //打到了
				{
					int k = Shell_vector[i].moving();
					string success;
					if (Shell_vector[i].getATK() >= Vessel_vector[k].getHp())
					{
						success = (Vessel_vector[k].getName() + "is hit by " + Shell_vector[i].getName() + " and destroyed!");
						String^ Success = gcnew System::String(success.c_str());
						writeLog(Success);
						this->Controls->Remove(Vessel_Label[k]);
					}
					else
					{
						String^ value;
						success = (Vessel_vector[k].getName() + "is hit by " + Shell_vector[i].getName() + "!\n"
							       +Vessel_vector[k].getName() + " get " );
						String^Success = gcnew System::String(success.c_str());
						value = System::Convert::ToString(Shell_vector[i].getATK());
						Success += value + "damage!";
						writeLog(Success);
					}

					
					this->Controls->Remove(Shell_Label[i]);
				}
				else if (Shell_vector[i].moving() == -2)//沒打到
				{
					string success = (Shell_vector[i].getName() + "hit miss!");
					String^ Success = gcnew System::String(success.c_str());
					writeLog(Success);
					this->Controls->Remove(Shell_Label[i]);
				}
			}
		}
	private: System::Void commands_text_title_Click(System::Object^  sender, System::EventArgs^  e) {
	}
		 public: void writeLog(String^ text);
	};
#pragma endregion
}


