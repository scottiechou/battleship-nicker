#pragma once
#include "Vessel.h"
#include <ctime>
#include <cstdlib>
#include <vector>
using std::vector;

static int distance_untiy = 15;		// �C���Z����1��� = ��������15���
static int acclerate = 15;			// �C���[�t"acclerate"��
static int minute = 0, second = 0;	// �Ω�����C���ɶ�
static int log_line = 0;			// �԰���x�����
static vector<Vessel> Vessel_vector;// �x�s�U��Vessel
static vector<Shell> Shell_vector;	// �x�s�U��Shell

bool set(char team, string name, string type, double x, double y);
int fire(char team, string name, double x, double y);

namespace Project314
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		// MyForm�غc��
		MyForm(void)
		{
			// distance_untiy = 15;
			// acclerate = 10;
			InitializeComponent();
		}

	protected:
		// MyForm�Ѻc��
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  commands_text_title;	// �Ω�Х�commands(���O��J��)����r���
	private: System::Windows::Forms::TextBox^  commands_A;	// A�ժ����O��J��
	private: System::Windows::Forms::TextBox^  commands_B;	// B�ժ����O��J��
	private: System::Windows::Forms::PictureBox^  pictureBox1;	// �Ω�bmyForm.h���аO�a�Ϥj�p�A�L�N
	private: System::Windows::Forms::Label^  battle_log_title;	// �԰���x���D
	private: System::Windows::Forms::Label^  battle_log;		// �԰���x����
	private: System::Windows::Forms::Button^  start_botton;	// �}�l��
	private: System::Windows::Forms::Button^  pause_botton;	// �Ȱ���
	private: System::Windows::Forms::Timer^  game_timer;	// �p��ɶ�
	private: System::Windows::Forms::Label^  time;		// ��ܮɶ�
	private: System::ComponentModel::IContainer^  components;

#pragma region ��l�ƦU���u��(����)(InitializeComponent)
	private:
		/*****��l�ƦU���u��(����)*****/
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
			this->commands_text_title->Font = (gcnew System::Drawing::Font(L"�s�ө���", 10));
			this->commands_text_title->Location = System::Drawing::Point(551, 15);
			this->commands_text_title->Name = L"commands_text_title";
			this->commands_text_title->Size = System::Drawing::Size(109, 20);
			this->commands_text_title->TabIndex = 1;
			this->commands_text_title->Text = L"���O��J��";
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
			this->battle_log_title->Font = (gcnew System::Drawing::Font(L"�s�ө���", 10));
			this->battle_log_title->Location = System::Drawing::Point(856, 15);
			this->battle_log_title->Name = L"battle_log_title";
			this->battle_log_title->Size = System::Drawing::Size(89, 20);
			this->battle_log_title->TabIndex = 4;
			this->battle_log_title->Text = L"�԰���x";
			// 
			// start_botton
			// 
			this->start_botton->Font = (gcnew System::Drawing::Font(L"�s�ө���", 10));
			this->start_botton->Location = System::Drawing::Point(187, 471);
			this->start_botton->Name = L"start_botton";
			this->start_botton->Size = System::Drawing::Size(104, 52);
			this->start_botton->TabIndex = 5;
			this->start_botton->Text = L"�}�l";
			this->start_botton->UseVisualStyleBackColor = true;
			this->start_botton->Click += gcnew System::EventHandler(this, &MyForm::start_botton_Click);
			// 
			// pause_botton
			// 
			this->pause_botton->Font = (gcnew System::Drawing::Font(L"�s�ө���-ExtB", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->pause_botton->Location = System::Drawing::Point(311, 471);
			this->pause_botton->Name = L"pause_botton";
			this->pause_botton->Size = System::Drawing::Size(98, 52);
			this->pause_botton->TabIndex = 6;
			this->pause_botton->Text = L"�Ȱ�";
			this->pause_botton->UseVisualStyleBackColor = true;
			this->pause_botton->Click += gcnew System::EventHandler(this, &MyForm::pause_botton_Click);
			// 
			// battle_log
			// 
			this->battle_log->AutoSize = true;
			this->battle_log->Font = (gcnew System::Drawing::Font(L"�s�ө���", 9));
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
			this->Text = L"�Y�ɾԲ��C��FERTIG - ��14��";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
#pragma region �C����l�ƮɡA�����W�n�[�����F��(MyForm_Load)
	private:
		// �C����l�ƮɡA�����W�n�[�����F��
		System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e)
		{
			// �إ߹C���a��(20*20�����)�A�å[����C�������W
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
			for (int i = 0; i < 21; i++)	// �N�a�ϲK�[�����(Controls)�W
			{
				this->Controls->Add(labels[i]);
				this->Controls->Add(labelsV[i]);
			}
		}
#pragma endregion
#pragma region �}�l/�Ȱ���]�w
	private:
		System::Void start_botton_Click(System::Object^  sender, System::EventArgs^  e)
		{
			if (this->game_timer->Enabled == false)	//�קK���ƫ���}�l��
			{
				this->game_timer->Enabled = true;	//�ɶ��}�l
				commands_A->Enabled = false;	//�����J���O
				commands_B->Enabled = false;
				// ��X�}�l�T��
				System::String ^Min, ^Sec;	//�N�ɶ��নString���A��A��X
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
				// �B�zcommand_A�Mcommand_B

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

				// ��X�Ȱ��T��
				// �N�ɶ��নString���A
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
#pragma region �C���p�ɾ�
	private:
		System::Void game_timer_Tick(System::Object^  sender, System::EventArgs^  e)
		{
			second++;
			if (second == 60)
			{
				minute++;
				second = 0;
			}
			// �Nint�নString
			System::String ^Min, ^Sec;
			Min = System::Convert::ToString(minute);
			Sec = System::Convert::ToString(second);
			if (Min->Length < 2)
				Min = "0" + Min;
			if (Sec->Length < 2)
				Sec = "0" + Sec;
			// ��X�ɶ�
			time->Text = (Min + ":" + Sec);

		}
	};
#pragma endregion
}

// Find_Name
bool findName(char team, string name)
{
	for (int i = 0; i < CV_vector.size(); i++) {
		if (CV_vector[i].getName() == name && CV_vector[i].getTeam == team) {
			return false;
		}
	}
	for (int i = 0; i < BB_vector.size(); i++) {
		if (BB_vector[i].getName() == name && BB_vector[i].getTeam == team) {
			return false;
		}
	}
	for (int i = 0; i < CG_vector.size(); i++) {
		if (CG_vector[i].getName() == name && CG_vector[i].getTeam == team) {
			return false;
		}
	}
	for (int i = 0; i < CV_vector.size(); i++) {
		if (DD_vector[i].getName() == name && DD_vector[i].getTeam == team) {
			return false;
		}
	}
	return true;
}
// SET���O
bool set(char team, string name, string type, double x, double y) 
{

	if (type == "CV") {
		for (int i = 0; i < CV_vector.size(); i++) {
			if (CV_vector[i].getName() == name && CV_vector[i].getTeam == team) {
				return false;
			}
		}
		CV newVessel;
		newVessel.setName(name);
		newVessel.setX(x);
		newVessel.setY(y);
		CV_vector.push_back(newVessel);
		return true;

	}
	else if (type == "BB") {
		for (int i = 0; i < BB_vector.size(); i++) {
			if (BB_vector[i].getName() == name && BB_vector[i].getTeam == team) {
				return false;
			}
		}
		BB newVessel;
		newVessel.setName(name);
		newVessel.setX(x);
		newVessel.setY(y);
		BB_vector.push_back(newVessel);
		return true;
	}
	else if (type == "CG") {
		for (int i = 0; i < CG_vector.size(); i++) {
			if (CG_vector[i].getName() == name && CG_vector[i].getTeam == team) {
				return false;
			}
		}
		CG newVessel;
		newVessel.setName(name);
		newVessel.setX(x);
		newVessel.setY(y);
		CG_vector.push_back(newVessel);
		return true;
	}
	else if (type == "DD") {
		for (int i = 0; i < CV_vector.size(); i++) {
			if (DD_vector[i].getName() == name && DD_vector[i].getTeam == team) {
				return false;
			}
		}
		DD newVessel;
		newVessel.setName(name);
		newVessel.setX(x);
		newVessel.setY(y);
		DD_vector.push_back(newVessel);
		return true;
	}
	else {
		return false;
	}
}

// FIRE���O
int fire(char team, string name, double x, double y)	//����ĥ����B����ĥ�W�r�B�����y��
{
	/*
		���ˬd���S���o����ĥ�A�b�ˬd�i���i�H�o�g(CD�ɶ���F�S)�A�̫�return�o�g����
		return�����G
		1 = ���`�o�g, 2 = CD�ɶ��٨S��, 3 = �S���o����
	*/
	//�dCV_vector�̦��S���o�Ӿ�ĥ
	for (int i = 0; i < CV_vector.size(); i++)	
	{
		if (CV_vector[i].getName() == name && CV_vector[i].getTeam() == team)	//�p�G���F�o����
		{
			if (CV_vector[i].getAtkCD() == 0)	//�p�G�i�H�o�g
			{
				CV_vector[i].setAtkCD(CV_ATT_CD);	//�NCD�ɶ����]
				Shell newShell(name, x, y, CV_vector[i].getWeaponSpeed(), CV_vector[i].getWeaponAtt());	//�s�W���u
				Shell_vector.push_back(newShell);
				return 1;
			}
			else	//�p�GCD�ɶ��٨S��A�N�^�Ǳ���2
				return 2;
		}
	}
	//�dBB_vector�̦��S���o�Ӿ�ĥ
	for (int i = 0; i < BB_vector.size(); i++)	
	{
		if (BB_vector[i].getAtkCD() == 0)	//�p�G�i�H�o�g
		{
			BB_vector[i].setAtkCD(BB_ATT_CD);	//�NCD�ɶ����]
			Shell newShell(name, x, y, BB_vector[i].getWeaponSpeed(), BB_vector[i].getWeaponAtt());	//�s�W���u
			Shell_vector.push_back(newShell);
			return 1;
		}
		else	//�p�GCD�ɶ��٨S��A�N�^�Ǳ���2
			return 2;
	}
	//�dCG_vector�̦��S���o�Ӿ�ĥ
	for (int i = 0; i < CG_vector.size(); i++)	
	{
		if (CG_vector[i].getName() == name && CG_vector[i].getTeam() == team)	//�p�G���F�o����
		{
			CG_vector[i].setAtkCD(CG_ATT_CD);	//�NCD�ɶ����]
			Shell newShell(name, x, y, CG_vector[i].getWeaponSpeed(), CG_vector[i].getWeaponAtt());	//�s�W���u
			Shell_vector.push_back(newShell);
			return 1;
		}
		else	//�p�GCD�ɶ��٨S��A�N�^�Ǳ���2
			return 2;
	}
	//�dDD_vector�̦��S���o�Ӿ�ĥ
	for (int i = 0; i < DD_vector.size(); i++)	
	{
		if (DD_vector[i].getName() == name && DD_vector[i].getTeam() == team)	//�p�G���F�o����
		{
			DD_vector[i].setAtkCD(DD_ATT_CD);	//�NCD�ɶ����]
			Shell newShell(name, x, y, DD_vector[i].getWeaponSpeed(), DD_vector[i].getWeaponAtt());	//�s�W���u
			Shell_vector.push_back(newShell);
			return 1;
		}
		else	//�p�GCD�ɶ��٨S��A�N�^�Ǳ���2
			return 2;
	}

	return 3;	//�p�G�䤣��o����ĥ�A�N�^�Ǳ���3
}

// DEFENSE���O
int defense(char team, string vessel_name, string shell_name)	//���uĥ����B���uĥ�W�r�B���u�W�r
{
	/*
		���ˬd���S���o����ĥ�A�b�ˬd���S���o�ӯ��u
		return�����G
		1 = ���`���u, 2 = �S���o����, 3 = �S���o�ӯ��u, 4 = ���uCD�ɶ�����, 5 = ���u�Z������
	*/

}
