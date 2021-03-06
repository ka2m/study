#pragma once

#define TEXT_SIZE 7
#define BORDER 2

#define CLIENT_HEIGHT Form::ClientRectangle.Height
#define CLIENT_WIDTH Form::ClientRectangle.Width

#define FRAME_WIDTH_MIDDLE (CLIENT_WIDTH - left - right) / 2 + left
#define FRAME_HEIGHT_MIDDLE (CLIENT_HEIGHT - bottom - top) / 2 + top


namespace CG_opttask12 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
		}

	protected:
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::ComponentModel::Container ^components;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog;
	private: System::Windows::Forms::Button^  btnOpen;

	private: System::Collections::Generic::List<line> lines;

	private: float left, right, top, bottom;
	private: float Wcx, Wcy, Wx, Wy;
	private: float Vcx, Vcy, Vx, Vy;
	private: polygon^ frameWindow;

	private: bool flTitlesVisible;

#pragma region Windows Form Designer generated code

			 void InitializeComponent(void)
			 {
				 this->openFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
				 this->btnOpen = (gcnew System::Windows::Forms::Button());
				 this->SuspendLayout();
				 // 
				 // openFileDialog
				 // 
				 this->openFileDialog->DefaultExt = L"txt";
				 this->openFileDialog->FileName = L"openFileDialog1";
				 this->openFileDialog->Filter = L"Текстовые файлы (*.txt)|*.txt|Все файлы (*.*)|*.*";
				 this->openFileDialog->Title = L"Open file";
				 // 
				 // btnOpen
				 // 
				 this->btnOpen->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
				 this->btnOpen->Location = System::Drawing::Point(430, 12);
				 this->btnOpen->Name = L"btnOpen";
				 this->btnOpen->Size = System::Drawing::Size(75, 23);
				 this->btnOpen->TabIndex = 0;
				 this->btnOpen->Text = L"Open";
				 this->btnOpen->UseVisualStyleBackColor = true;
				 this->btnOpen->Click += gcnew System::EventHandler(this, &Form1::btnOpen_Click);
				 // 
				 // Form1
				 // 
				 this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
				 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				 this->ClientSize = System::Drawing::Size(517, 653);
				 this->Controls->Add(this->btnOpen);
				 this->DoubleBuffered = true;
				 this->KeyPreview = true;
				 this->MinimumSize = System::Drawing::Size(280, 220);
				 this->Name = L"Form1";
				 this->Text = L"CG_opt-task1-2";
				 this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
				 this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::Form1_Paint);
				 this->Resize += gcnew System::EventHandler(this, &Form1::Form1_Resize);
				 this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::Form1_KeyDown);
				 this->ResumeLayout(false);

			 }
#pragma endregion

	private: System::Void Form1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
				 Graphics^ g = e->Graphics;
				 g->Clear(Color::White);

				 Pen^ pen = gcnew Pen(Color::Black, 2);
				 Pen^ rectPen = gcnew Pen(Color::Red, BORDER);
				 Pen^ axesPen = gcnew Pen(Color::Gray, 1);

				 System::Drawing::Font^ font = gcnew System::Drawing::Font("Arial", TEXT_SIZE);
				 SolidBrush^ brush = gcnew SolidBrush(Color::Black);

				 point Pmax = point(CLIENT_WIDTH - right, CLIENT_HEIGHT - bottom);
				 point Pmin = point(left, top);

				 mat F;
				 vec A, B, C;
				 point a, b;
				 polygon^ p1 = gcnew polygon(0);

				 frame(Vx, Vy, Vcx, Vcy, Wx, Wy, Wcx, Wcy, F);

				 for (int j = 0; j < frameWindow->Count; j++) {
					 point2vec(frameWindow[j], A);
					 timesMatVec(F, A, B);
					 vec2point(B, a);
					 p1->Add(a);
				 }

				 p1->Reverse();

				 for (int i = 0; i < lines.Count; i++) {
					 vec A, B;
					 point2vec(lines[i].start, A);
					 point2vec(lines[i].end, B);

					 vec A1, B1;
					 timesMatVec(T, A, A1);
					 timesMatVec(T, B, B1);

					 point a, b;
					 vec2point(A1, a);
					 vec2point(B1, b);

					 if (clip(a.x, a.y, b.x, b.y, p1)) {

						 g->DrawLine(pen, a.x, a.y, b.x, b.y);

						 if (flTitlesVisible) {
							 float txtPosX = (a.x + b.x) / 2, txtPosY = (a.y + b.y) / 2;
							 g->DrawString(lines[i].name, font, brush, txtPosX, txtPosY);
						 }
					 }
				 }

				 if (p1->Count != 0) {
					 b = p1[p1->Count - 1];

					 for (int j = 0; j < p1->Count; j++) {
						 g->DrawLine(rectPen, b.x, b.y, p1[j].x, p1[j].y);
						 b = p1[j];
					 }
				 }
			 }

	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
				 lines.Clear();
				 unit(T);

				 left   = 15;
				 right  = 105;
				 top    = 15;
				 bottom = 15;

				 flTitlesVisible = false;

				 point Pmax = point(CLIENT_WIDTH - right, CLIENT_HEIGHT - bottom);
				 point Pmin = point(left, top);

				 frameWindow = gcnew polygon(0);
				 frameWindow->Add(point(0, 0));
				 frameWindow->Add(point(0, 300));
				 frameWindow->Add(point(200, 300));
				 frameWindow->Add(point(200, 0));

				 Wcx = left;
				 Wcy = CLIENT_HEIGHT - bottom;
				 Wx  = CLIENT_WIDTH - left - right;
				 Wy  = CLIENT_HEIGHT - top - bottom;
			 }

	private: System::Void btnOpen_Click(System::Object^  sender, System::EventArgs^  e) {

				 if (this->openFileDialog->ShowDialog() ==
					 System::Windows::Forms::DialogResult::OK) {

						 wchar_t fileName[1024];
						 for (int i = 0; i < openFileDialog->FileName->Length; i++)
							 fileName[i] = openFileDialog->FileName[i];

						 fileName[openFileDialog->FileName->Length] = '\0';

						 std::ifstream in;
						 in.open(fileName);
						 if (in.is_open()) {
							 lines.Clear();
							 unit(T);

							 std::string str;
							 getline(in, str);
							 bool fl = 0;
							 int vcx, vcy, vx, vy;
							 while (in) {
								 if ((str.find_first_not_of(" \t\r\n") != std::string::npos)
									 && (str[0] != '#')) {

										 std::stringstream s(str);
										 std::string cmd;
										 s >> cmd;

										 if ( cmd == "frame" ) {
											 float a, b, c, d;
											 s >> a >> b >> c >> d;
											 Vcx = a;
											 Vcy = b;
											 Vx = c;
											 Vy = d;
											 frame(Vx, Vy, Vcx, Vcy, Wx, Wy, Wcx, Wcy, T);
										 } else if ( cmd == "line" ) {
											 point p1, p2;
											 std::string name;
											 s >> p1.x >> p1.y >> p2.x >> p2.y >> name;
											 lines.Add(line(p1, p2, gcnew String(name.c_str())));
										 } else if ( cmd == "clip" ) {
											 int n;
											 s >> n;
											 frameWindow->Clear();
											 point p;
											 for (int i = 0; i < n; i++) {
												s >> p.x >> p.y;
												frameWindow->Add(p);
											 }
										 }
								 }

								 getline(in, str);
							 }
						 }

						 flTitlesVisible = false;
						 this->Refresh();
				 }
			 }

	private: System::Void Form1_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
				 mat R, T1;

				 switch(e->KeyCode) {
				case Keys::W :		// Move up
					move(0, -1, R);
					break;
				case Keys::S :		// Move down
					move(0, 1, R);
					break;
				case Keys::A :		// Move left
					move(-1, 0, R);
					break;
				case Keys::D :		// Move right
					move(1, 0, R);
					break;
				case Keys::T :		// Fast move up
					move(0, -10, R);
					break;
				case Keys::G :		// Fast move down
					move(0, 10, R);
					break;
				case Keys::F :		// Fast move left
					move(-10, 0, R);
					break;
				case Keys::H :		// Fast move right
					move(10, 0, R);
					break;
				case Keys::E :		// Right rotate
					rotate(0.05, left, top, R);
					break;
				case Keys::Q :		// Left rotate
					rotate(-0.05, left, top, R);
					break;
				case Keys::Y :		// Right rotate about center
					rotate(0.05, FRAME_WIDTH_MIDDLE, FRAME_HEIGHT_MIDDLE, R);
					break;
				case Keys::R :		// Left rotate about center
					rotate(-0.05, FRAME_WIDTH_MIDDLE, FRAME_HEIGHT_MIDDLE, R);
					break;
				case Keys::Z :		// Decrease
					scale(1 / 1.1, 1 / 1.1, R);
					break;
				case Keys::X :		// Increase
					scale(1.1, 1.1, R);
					break;
				case Keys::C :		// Decrease about center
					move(-FRAME_WIDTH_MIDDLE, -FRAME_HEIGHT_MIDDLE, R);
					times(R, T, T1);

					scale(1 / 1.1, 1 / 1.1, R);
					times(R, T1, T);

					move(FRAME_WIDTH_MIDDLE, FRAME_HEIGHT_MIDDLE, R);
					break;
				case Keys::V :		// Increase about center
					move(-FRAME_WIDTH_MIDDLE, -FRAME_HEIGHT_MIDDLE, R);
					times(R, T, T1);

					scale(1.1, 1.1, R);
					times(R, T1, T);

					move(FRAME_WIDTH_MIDDLE, FRAME_HEIGHT_MIDDLE, R);
					break;
				case Keys::L :		// Increase about vertical middle
					move(-FRAME_WIDTH_MIDDLE, 0, R);
					times(R, T, T1);

					scale(1.1, 1, R);
					times(R, T1, T);

					move(FRAME_WIDTH_MIDDLE, 0, R);
					break;
				case Keys::K :		// Decrease about vertical middle
					move(-FRAME_WIDTH_MIDDLE, 0, R);
					times(R, T, T1);

					scale(1 / 1.1, 1, R);
					times(R, T1, T);

					move(FRAME_WIDTH_MIDDLE, 0, R);
					break;
				case Keys::O :		// Increase about horizontal middle
					move(0, -FRAME_HEIGHT_MIDDLE, R);
					times(R, T, T1);

					scale(1, 1.1, R);
					times(R, T1, T);

					move(0, FRAME_HEIGHT_MIDDLE, R);
					break;
				case Keys::I :		// Decrease about horizontal middle
					move(0, -FRAME_HEIGHT_MIDDLE, R);
					times(R, T, T1);

					scale(1, 1 / 1.1, R);
					times(R, T1, T);

					move(0, FRAME_HEIGHT_MIDDLE, R);
					break;
				case Keys::U :		// Reflection about vertical middle
					reflect(0, 1, R);
					times(R, T, T1);
					set(T1, T);

					move(FRAME_WIDTH_MIDDLE * 2, 0, R);				
					break;
				case Keys::J :		// Reflection about horizontal middle
					reflect(1, 0, R);
					times(R, T, T1);
					set(T1, T);

					move(0, FRAME_HEIGHT_MIDDLE * 2, R);	
					break;
				case Keys::P :
					unit(R);
					flTitlesVisible = !flTitlesVisible;
					break;
				case Keys::Escape :
					frame(Vx, Vy, Vcx, Vcy, Wx, Wy, Wcx, Wcy, T);
					flTitlesVisible = 0;
				default :
					unit(R);
				 }

				 times(R, T, T1);
				 set(T1, T);
				 this->Refresh();
			 }

	private: System::Void Form1_Resize(System::Object^  sender, System::EventArgs^  e) {
				 float oldWx = Wx, oldWy = Wy;

				 Wcx = left;
				 Wcy = CLIENT_HEIGHT - bottom;
				 Wx  = CLIENT_WIDTH - left - right;
				 Wy  = CLIENT_HEIGHT - top - bottom;

				 mat R, T1;
				 move(-Wcx, -top, R);
				 times(R, T, T1);

				 scale(Wx / oldWx, Wy / oldWy, R);
				 times(R, T1, T);

				 move(Wcx, top, R);
				 times(R, T, T1);
				 set(T1, T);

				 this->Refresh();
			 }
	};
}
