#pragma once

#define TEXT_SIZE 7
#define BORDER 2

namespace CG_task418 {

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

			 // List of the lines
			 System::Collections::Generic::List<line> lines;

			 float left, right, top, bottom;
			 float Wcx, Wcy, Wx, Wy;
			 float Vcx, Vcy, Vx, Vy;

			 bool flTitlesVisible;
			 float frameWidthMiddle, frameHeightMiddle;
			 float clientRectangleHeight, clientRectangleWidth;

	private: System::Windows::Forms::RichTextBox^  richTextBox1;


#pragma region Windows Form Designer generated code

			 void InitializeComponent(void)
			 {
				 this->openFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
				 this->btnOpen = (gcnew System::Windows::Forms::Button());
				 this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
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
				 // richTextBox1
				 // 
				 this->richTextBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
				 this->richTextBox1->Location = System::Drawing::Point(430, 512);
				 this->richTextBox1->Name = L"richTextBox1";
				 this->richTextBox1->ReadOnly = true;
				 this->richTextBox1->Size = System::Drawing::Size(75, 129);
				 this->richTextBox1->TabIndex = 1;
				 this->richTextBox1->Text = L"";
				 // 
				 // Form1
				 // 
				 this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
				 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				 this->ClientSize = System::Drawing::Size(517, 653);
				 this->Controls->Add(this->richTextBox1);
				 this->Controls->Add(this->btnOpen);
				 this->DoubleBuffered = true;
				 this->KeyPreview = true;
				 this->MinimumSize = System::Drawing::Size(280, 220);
				 this->Name = L"Form1";
				 this->Text = L"CG_task4-18";
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

			Pen^ pen = gcnew Pen(Color::Black);
			pen->Width = 2;

			Pen^ rectPen = gcnew Pen(Color::Red);
			rectPen->Width = BORDER;

			Pen^ axesPen = gcnew Pen(Color::Gray);
			axesPen->Width = 1;

			System::Drawing::Font^ font = gcnew System::Drawing::Font("Arial", TEXT_SIZE);
			SolidBrush^ brush = gcnew SolidBrush(Color::Black);

			point Pmax, Pmin;
			Pmax.x = clientRectangleWidth  - right;	
			Pmin.x = left;
			Pmax.y = clientRectangleHeight - bottom;	
			Pmin.y = top;

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
				
				if (clip(a.x, a.y, b.x, b.y, Pmin, Pmax)) {
					g->DrawLine(pen, a.x, a.y, b.x, b.y);

					float txtPosX = (a.x + b.x) / 2, txtPosY = (a.y + b.y) / 2;
					if (flTitlesVisible && 
						txtPosX < (Wx + Wcx - TEXT_SIZE - BORDER) && 
						txtPosY < (Wcy - TEXT_SIZE - BORDER)) {
							
						g->DrawString(lines[i].name, font, brush, txtPosX, txtPosY);
					}
				}
			}

			g->DrawLine(axesPen, left, 
								 (clientRectangleHeight - bottom - top) / 2 + top, 
								 clientRectangleWidth - right, 
								 (clientRectangleHeight - bottom - top) / 2 + top);
			g->DrawLine(axesPen, (clientRectangleWidth - left - right) / 2 + left, 
								 top, 
								 (clientRectangleWidth - left - right) / 2 + left, 
								 clientRectangleHeight - bottom);

			g->DrawRectangle(rectPen, Wcx, top, Wx, Wy);

			this->richTextBox1->Text  = "Wcx = " + Wcx + "\n";
			this->richTextBox1->Text += "Wcy = " + Wcy + "\n";
			this->richTextBox1->Text += "Wx  = " + Wx  + "\n";
			this->richTextBox1->Text += "Wy  = " + Wy  + "\n";
			this->richTextBox1->Text += "Vcx = " + Vcx + "\n";
			this->richTextBox1->Text += "Vcy = " + Vcy + "\n";
			this->richTextBox1->Text += "Vx  = " + Vx  + "\n";
			this->richTextBox1->Text += "Vy  = " + Vy  + "\n";
		}

		private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
			lines.Clear();
			unit(T);

			clientRectangleHeight = Form::ClientRectangle.Height;
			clientRectangleWidth  = Form::ClientRectangle.Width;

			left   = 15;
			right  = 110;
			top    = 35;
			bottom = 50;

			flTitlesVisible = 0;

			Wcx = left;
			Wcy = clientRectangleHeight - bottom;
			Wx  = clientRectangleWidth - left - right;
			Wy  = clientRectangleHeight - top - bottom;

			frameWidthMiddle = (clientRectangleWidth - left - right) / 2 + left;
			frameHeightMiddle = (clientRectangleHeight - bottom - top) / 2 + top;
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

					std::string str;
					getline(in, str);
					bool fl = 0;
					int vcx, vcy, vx, vy;
					while (in) {
						if ((str.find_first_not_of(" \t\r\n") != std::string::npos)
							&& (str[0] != '#')) {

							std::stringstream s(str);
							line l;
							if (fl == 0)  { 
								s >> vcx >> vcy >> vx >> vy; 
								fl = 1; 
							} else {
								s >> l.start.x >> l.start.y >> l.end.x >> l.end.y;
								std::string linename;
								s >> linename;
								l.name = gcnew String(linename.c_str());
								lines.Add(l);
							}
						}

						getline(in, str);
					}

					Vcx = vcx; 
					Vcy = vcy; 
					Vx  = vx; 
					Vy  = vy;
				}

				frame(Vx, Vy, Vcx, Vcy, Wx, Wy, Wcx, Wcy, T);
				flTitlesVisible = 0;
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
					rotate(0.05, frameWidthMiddle, frameHeightMiddle, R);
					break;
				case Keys::R :		// Left rotate about center
					rotate(-0.05, frameWidthMiddle, frameHeightMiddle, R);
					break;
				case Keys::Z :		// Decrease
					scale(1 / 1.1, 1 / 1.1, R);
					break;
				case Keys::X :		// Increase
					scale(1.1, 1.1, R);
					break;
				case Keys::C :		// Decrease about center
					move(-frameWidthMiddle, -frameHeightMiddle, R);
					times(R, T, T1);

					scale(1 / 1.1, 1 / 1.1, R);
					times(R, T1, T);

					move(frameWidthMiddle, frameHeightMiddle, R);
					break;
				case Keys::V :		// Increase about center
					move(-frameWidthMiddle, -frameHeightMiddle, R);
					times(R, T, T1);

					scale(1.1, 1.1, R);
					times(R, T1, T);

					move(frameWidthMiddle, frameHeightMiddle, R);
					break;
				case Keys::L :		// Increase about vertical middle
					move(-frameWidthMiddle, 0, R);
					times(R, T, T1);

					scale(1.1, 1, R);
					times(R, T1, T);

					move(frameWidthMiddle, 0, R);
					break;
				case Keys::K :		// Decrease about vertical middle
					move(-frameWidthMiddle, 0, R);
					times(R, T, T1);

					scale(1 / 1.1, 1, R);
					times(R, T1, T);

					move(frameWidthMiddle, 0, R);
					break;
				case Keys::O :		// Increase about horizontal middle
					move(0, -frameHeightMiddle, R);
					times(R, T, T1);

					scale(1, 1.1, R);
					times(R, T1, T);

					move(0, frameHeightMiddle, R);
					break;
				case Keys::I :		// Decrease about horizontal middle
					move(0, -frameHeightMiddle, R);
					times(R, T, T1);

					scale(1, 1 / 1.1, R);
					times(R, T1, T);

					move(0, frameHeightMiddle, R);
					break;
				case Keys::U :		// Reflection about vertical middle
					reflect(0, 1, R);
					times(R, T, T1);
					set(T1, T);

					move(frameWidthMiddle * 2, 0, R);				
					break;
				case Keys::J :		// Reflection about horizontal middle
					reflect(1, 0, R);
					times(R, T, T1);
					set(T1, T);

					move(0, frameHeightMiddle * 2, R);	
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

			clientRectangleHeight = Form::ClientRectangle.Height;
			clientRectangleWidth  = Form::ClientRectangle.Width;
			
			Wcx = left;
			Wcy = clientRectangleHeight - bottom;
			Wx  = clientRectangleWidth - left - right;
			Wy  = clientRectangleHeight - top - bottom;
			
			mat R, T1;
			move(-Wcx, -top, R);
			times(R, T, T1);

			scale(Wx / oldWx, Wy / oldWy, R);
			times(R, T1, T);

			move(Wcx, top, R);
			times(R, T, T1);
			set(T1, T);

			frameWidthMiddle  = 
				(clientRectangleWidth - left - right) / 2 + left;
			frameHeightMiddle = 
				(clientRectangleHeight - bottom - top) / 2 + top;

			this->Refresh();
		}
	};
}
