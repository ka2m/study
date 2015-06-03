#pragma once
#include <cstdio>
#include <string.h>

namespace mauris_task03_15 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private:
			System::Collections::Generic::List<line> lines;
			float left, right, top, bottom;
			float Wcx, Wcy, Wx, Wy;
			float Vcx, Vcy, Vx, Vy;
			bool drawNames;


	private: System::Windows::Forms::OpenFileDialog^  openFileDialog;
	protected: 
	private: System::Windows::Forms::Button^  btnOpen;
	private:

	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->openFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->btnOpen = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// openFileDialog
			// 
			this->openFileDialog->DefaultExt = L"txt";
			this->openFileDialog->FileName = L"openFileDialog";
			this->openFileDialog->Filter = L"Текстовые файлы (*.txt)|*.txt|Все файлы (*.*)|*.*";
			this->openFileDialog->Title = L"Открыть файл";
			// 
			// btnOpen
			// 
			this->btnOpen->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->btnOpen->Location = System::Drawing::Point(0, 419);
			this->btnOpen->Name = L"btnOpen";
			this->btnOpen->Size = System::Drawing::Size(624, 23);
			this->btnOpen->TabIndex = 0;
			this->btnOpen->Text = L"Открыть";
			this->btnOpen->UseVisualStyleBackColor = true;
			this->btnOpen->Click += gcnew System::EventHandler(this, &Form1::btnOpen_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(624, 442);
			this->Controls->Add(this->btnOpen);
			this->KeyPreview = true;
			this->MinimumSize = System::Drawing::Size(320, 240);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::Form1_Paint);
			this->Resize += gcnew System::EventHandler(this, &Form1::Form1_Resize);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::Form1_KeyDown);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void Form1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
				 Graphics^ g = e->Graphics;
				 System::Drawing::Font^ drawFont = gcnew System::Drawing::Font("Arial", 5);
				 SolidBrush^ drawBrush = gcnew SolidBrush(Color::Black);
				 Pen^ blackPen = gcnew Pen(Color::Black);
				 Pen^ rectPen = gcnew Pen(Color::Purple);
				 g->Clear(Color::White);
				 blackPen->Width = 0.1;
				 rectPen->Width = 2;
				 Rectangle rect = System::Drawing::Rectangle(Wcx, top, Wx, Wy);
				 g->DrawRectangle(rectPen, rect);
				 g->Clip = gcnew System::Drawing::Region(rect);
				 g->Transform = gcnew System::Drawing::Drawing2D::Matrix(T[0][0], T[1][0], T[0][1], T[1][1], T[0][2], T[1][2]);


				 for(int i = 0; i < matrices.size(); i++){
					 mat С;
					 times(T, matrices[i], С);
					 g->Transform = gcnew System::Drawing::Drawing2D::Matrix(С[0][0], С[1][0], С[0][1], С[1][1], С[0][2], С[1][2]);
					 this->DrawFigure(g, blackPen);
				 }
			 }
	private: System::Void Form1_Resize(System::Object^  sender, System::EventArgs^  e) {
				 float oldWx = Wx, oldWy = Wy;
				 Wcy = Form::ClientRectangle.Height - bottom;
				 Wx = Form::ClientRectangle.Width - left - right;
				 Wy = Form::ClientRectangle.Height - top - bottom;
				 mat Mov, nMov, Scale;
				 scale(this->Wx/oldWx, this->Wy/oldWy, Scale);
				 move(-this->Wcx, -this->top, Mov);
				 move(this->Wcx, this->top, nMov);
				 mat MS, R, T1;
				 times(nMov, Scale, MS);
				 times(MS, Mov, R);
				 times(R, T, T1);
				 set(T1, T);
				 this->Refresh();
			 }
	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
				 this->drawNames = false;
				 lines.Clear();
				 unit(T);
				 this->top = 60.f;
				 this->left = 60.f;
				 this->right = 60.f;
				 this->bottom = 60.f;

				 Wcx = left;
				 Wcy = Form::ClientRectangle.Height - bottom;
				 Wx = Form::ClientRectangle.Width - left - right;
				 Wy = Form::ClientRectangle.Height - top - bottom;
			 }
	private: System::Void btnOpen_Click(System::Object^  sender, System::EventArgs^  e) {
				 if(this->openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK){
					 wchar_t fileName[1024];
					 for (int i = 0; i < openFileDialog->FileName->Length; i++)
						 fileName[i] = openFileDialog->FileName[i];

					 fileName[openFileDialog->FileName->Length] = '\0';

					 std::ifstream in;
					 in.open(fileName);
					 if (in.is_open()) {
						 matrices.clear();
						 std::stack<mat> matStack;
						 mat K; unit(K);
						 unit(T);
						 std::string str;
						 getline(in, str);
						 while (in) {
							 if ((str.find_first_not_of(" \t\r\n") != std::string::npos) && (str[0] != '#')) {
								 std::stringstream s(str);
								 std::string cmd;								 s >> cmd;								 if ( cmd == "frame" ) {									 float vcx, vcy, vx, vy;									 s >> vcx >> vcy >> vx >> vy;									 this->Vx = vx;									 this->Vy = vy;									 this->Vcx = vcx;									 this->Vcy = vcy;									 frame(this->Vx, this->Vy, this->Vcx, this->Vcy, this->Wx, this->Wy, this->Wcx, this->Wcy, T);								 }								 else if( cmd == "figure" ) {									 matrices.push_back(K);								 }								 else if ( cmd == "pushTransform" ) {									 matStack.push(K);								 }								 else if ( cmd == "popTransform" ) {									 K = matStack.top();									 matStack.pop();								 }								 else if ( cmd == "rotate" ) {									 float Phi;
									 s >> Phi;
									 float pi = 3.1415926535;
									 float PhiR = Phi * (pi / 180);
									 mat C, C1;
									 rotate(PhiR, C);
									 times(K, C, C1);
									 K = C1;								 }								 else if ( cmd == "translate" ) {									 float tx, ty;									 s >> tx >> ty;									 mat C, C1;									 move(tx, ty, C);									 times(K, C, C1);									 K = C1;								 }								 else if ( cmd == "scale" ) {									 float Scale;									 s >> Scale;									 mat C, C1;									 scale(Scale, Scale, C);									 times(K, C, C1);									 K = C1;								 }							 }
							 getline(in, str);
						 }
					 }
					 
					 this->Refresh();					
				 }
			 }
	private: void DrawFigure(Graphics^ g, Pen^ pen) {
				 //g->DrawRectangle(pen, -30,-20, 60,40);
				 float size = 2 * 20.f/18.f;
				 int x1[] = {-9, -11, -13, 10, 10, 13, -9, -8, -7, -7, -7, -7, -7, -6, -6, -6, -6, -5, -5, -5, -7, -7, -7, -4, -4, -4, -8, -3, 1, 1, 3, 5, 7, 7, 8, 9, 7, 8, 6, 9, 6, 6, 7, 6, 6, 5, 5, 5, 5, 5, 7};
				 int y1[] = {-8, -6, -4, -4, -5, -5, -8, -3, -2, 0, 2, 7, 8, 10, 10, 7, 0, 10, 7, 0, 8, 2, -2, 8, 2, -2, -3, -3, -2, -2, -2, 2, 1, 7, 7, 1, 10, 10, 8, 8, 1, -1, 10, 8, 7, 2, 1, 0, -1, -2, 1};
				 int x2[] = {13, 13, 10, 10, 13, 13, -13, -3, -4, -4, -4, -4, -4, -5, -6, -6, -6, -5, -5, -5, -7, -7, -7, -4, -4, -4, -8, -3, 3, 1, 3, 5, 7, 7, 8, 9, 7, 8, 6, 9, 6, 6, 8, 9, 9, 7, 6, 6, 6, 6, 9};
				 int y2[] = {-8, -6, -4, -5, -5, -8, -4, -3, -2, 0, 2, 7, 8, 10, 8, 2, -2, 8, 2, -2, 7, 0, -3, 7, 0, -3, -4, -4, -2, -4, -4, -4, -4, 2, 1, -4, 8, 8, 7, 7, 0, -2, 10, 8, 7, 2, 1, 0, -1, -2, 1};

				 for(int i = 0; i<sizeof(x1)/sizeof(int); i++)
				 	g->DrawLine(pen, x1[i] * size, (y1[i]-1) * size, x2[i] * size, (y2[i]-1) * size);
			 }
	private: System::Void Form1_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
				 mat R, T1;
				 mat Center, nCenter, Trans, Trm;

				 switch(e->KeyCode) {
					case Keys::W: 
						move(0.f, -1.f, R);
						break;
					case Keys::S:
						move(0.f, 1.f, R);
						break;
					case Keys::A:
						move(-1.f, 0.f, R);
						break;
					case Keys::D:
						move(1.f, 0.f, R);
						break;

					case Keys::E :
						rotate(0.05f, R);
						break;
					case Keys::Q :
						rotate(-0.05f, R);
						break;

					case Keys::Z :
						scale(1.f/1.1f, 1.f/1.1f, R);
						break;
					case Keys::X :
						scale(1.1f/1.f, 1.1f/1.f, R);
						break;

					case Keys::T: 
						move(0.f, -10.f, R);
						break;
					case Keys::G:
						move(0.f, 10.f, R);
						break;
					case Keys::F:
						move(-10.f, 0.f, R);
						break;
					case Keys::H:
						move(10.f, 0.f, R);
						break;

					case Keys::U:
						move(-float(Form::ClientRectangle.Width/2), 0.f, Center);
						move(float(Form::ClientRectangle.Width/2), 0.f, nCenter);
						unit(R);
						reflectHorizontal(Trans);
						times(Trans, Center, Trm);
						times(nCenter, Trm, R);
						break;
					case Keys::J:
						move(0.f, -float(Form::ClientRectangle.Height/2), Center);
						move(0.f, float(Form::ClientRectangle.Height/2), nCenter);
						unit(R);
						reflectVertical(Trans);
						times(Trans, Center, Trm);
						times(nCenter, Trm, R);
						break;

					case Keys::R:
						move(-float(Form::ClientRectangle.Width/2), -float(Form::ClientRectangle.Height/2), Center);
						move(float(Form::ClientRectangle.Width/2), float(Form::ClientRectangle.Height/2), nCenter);
						unit(R);
						rotate(-0.05f, Trans);
						times(Trans, Center, Trm);
						times(nCenter, Trm, R);
						break;
					case Keys::Y:
						move(-float(Form::ClientRectangle.Width/2), -float(Form::ClientRectangle.Height/2), Center);
						move(float(Form::ClientRectangle.Width/2), float(Form::ClientRectangle.Height/2), nCenter);
						unit(R);
						rotate(0.05f, Trans);
						times(Trans, Center, Trm);
						times(nCenter, Trm, R);
						break;

					case Keys::C:
						move(-float(Form::ClientRectangle.Width/2), -float(Form::ClientRectangle.Height/2), Center);
						move(float(Form::ClientRectangle.Width/2), float(Form::ClientRectangle.Height/2), nCenter);
						unit(R);
						scale(1.f/1.1f, 1.f/1.1f, Trans);
						times(Trans, Center, Trm);
						times(nCenter, Trm, R);
						break;
					case Keys::V:
						move(-float(Form::ClientRectangle.Width/2), -float(Form::ClientRectangle.Height/2), Center);
						move(float(Form::ClientRectangle.Width/2), float(Form::ClientRectangle.Height/2), nCenter);
						unit(R);
						scale(1.1f/1.f, 1.1f/1.f, Trans);
						times(Trans, Center, Trm);
						times(nCenter, Trm, R);
						break;

					case Keys::I:
						move(-float(Form::ClientRectangle.Width/2), 0.f, Center);
						move(float(Form::ClientRectangle.Width/2), 0.f, nCenter);
						unit(R);
						scale(1.f/1.1f, 1.f, Trans);
						times(Trans, Center, Trm);
						times(nCenter, Trm, R);
						break;
					case Keys::O:
						move(-float(Form::ClientRectangle.Width/2), 0.f, Center);
						move(float(Form::ClientRectangle.Width/2), 0.f, nCenter);
						unit(R);
						scale(1.1f/1.f, 1.f, Trans);
						times(Trans, Center, Trm);
						times(nCenter, Trm, R);
						break;

					case Keys::K:
						move(0.f, -float(Form::ClientRectangle.Height/2), Center);
						move(0.f, float(Form::ClientRectangle.Height/2), nCenter);
						unit(R);
						scale(1.f, 1.f/1.1f, Trans);
						times(Trans, Center, Trm);
						times(nCenter, Trm, R);
						break;
					case Keys::L:
						move(0.f, -float(Form::ClientRectangle.Height/2), Center);
						move(0.f, float(Form::ClientRectangle.Height/2), nCenter);
						unit(R);
						scale(1.f, 1.1f/1.f, Trans);
						times(Trans, Center, Trm);
						times(nCenter, Trm, R);
						break;

					case Keys::Escape:
						frame(this->Vx, this->Vy, this->Vcx, this->Vcy, this->Wx, this->Wy, this->Wcx, this->Wcy, T);
						unit(R);
						break;
					case Keys::P:
						this->drawNames = !this->drawNames;
						unit(R);
						break;

					default: 
						unit(R);
				  }
				 times(R, T, T1);
				 set(T1, T);
				 this->Refresh();

			 }
	};
}

