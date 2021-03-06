#pragma once

#define TEXT_SIZE 7
#define BORDER 2

namespace CG_task6 {

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

			 float frameWidthMiddle, frameHeightMiddle;
			 float clientRectangleHeight, clientRectangleWidth;


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
				 this->btnOpen->Location = System::Drawing::Point(825, 12);
				 this->btnOpen->Name = L"btnOpen";
				 this->btnOpen->Size = System::Drawing::Size(75, 25);
				 this->btnOpen->TabIndex = 0;
				 this->btnOpen->Text = L"Open";
				 this->btnOpen->UseVisualStyleBackColor = true;
				 this->btnOpen->Click += gcnew System::EventHandler(this, &Form1::btnOpen_Click);
				 // 
				 // Form1
				 // 
				 this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
				 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				 this->ClientSize = System::Drawing::Size(912, 473);
				 this->Controls->Add(this->btnOpen);
				 this->DoubleBuffered = true;
				 this->KeyPreview = true;
				 this->MinimumSize = System::Drawing::Size(368, 200);
				 this->Name = L"Form1";
				 this->Text = L"CG_task6";
				 this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
				 this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::Form1_Paint);
				 this->Resize += gcnew System::EventHandler(this, &Form1::Form1_Resize);
				 this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::Form1_KeyDown);
				 this->ResumeLayout(false);

			 }
#pragma endregion

		private: void drawLines(Graphics^ g, Pen^ pen, int x, int y, int mas[][2], int massize) { 

			for (int i = 0; i < massize; i++) {
				g->DrawLine(pen, x, y, x + mas[i][0] / (10 / 2.37), y + mas[i][1] / (10 / 2.37));
				x += (mas[i][0] / (10 / 2.37));
				y += (mas[i][1] / (10 / 2.37));
			}
		}

		private: void DrawFigure(Graphics^ g, Pen^ pen) {
			// Points inc/dec -rements
					 g->DrawRectangle(pen, -20,-30,40,60);


					 int arr[123][4] = {
						{90  ,210 ,90,  220},
						{90  ,220 ,70,  240},
						{70  ,240 ,70,  260},
						{70  ,260 ,90,  280},
						{90  ,280 ,110, 280},
						{110 ,280 ,130, 260},
						{130 ,260 ,130, 240},
						{130 ,240 ,110, 220},
						{110 ,220 ,110, 210},
						{80  ,210 ,140, 210 },
						{140 ,210 ,160, 230 },
						{160 ,230 ,160, 240 },
						{160 ,240 ,180, 260 },
						{180 ,260 ,180, 230 },
						{180 ,230 ,140, 190 },
						{140 ,190 ,140, 160 },
						{140 ,160 ,120, 140 },
						{120 ,140 ,80 , 140 },
						{80  ,140 ,60 , 160 },
						{60  ,160 ,60 , 190 },
						{60  ,190 ,40 , 170 },
						{40  ,170 ,40 , 160 },
						{40  ,160 ,20 , 140 },
						{20  ,140 ,20 , 170 },
						{20  ,170 ,60 , 210 },
						{60  ,210 ,80 , 210 },
						{80  ,210 ,100, 190 },
						{100 ,190 ,120, 210 },
						{80  ,260 ,90 , 260 },
						{90  ,260 ,90 , 250 },
						{90  ,250 ,80 , 250 },
						{80  ,250 ,80 , 260 },
						{110 ,260 ,120, 260 },
						{120 ,260 ,120, 250 },
						{120 ,250 ,110, 250 },
						{110 ,250 ,110, 260 },
						{90  ,240 ,110, 240 },
						{110 ,240 ,110, 230 },
						{110 ,230 ,90 , 230 },
						{90  ,230 ,90 , 240 },
						{120 ,140 ,140, 120 },
						{140 ,120 ,140, 50  },
						{140 ,50  ,130, 50  },
						{130 ,50  ,130, 40  },
						{130 ,40  ,140, 40  },
						{140 ,40  ,140, 20  },
						{140 ,20  ,120, 40  },
						{120 ,40  ,120, 50  },
						{120 ,50  ,110, 50  },
						{110 ,50  ,110, 110 },
						{110 ,110 ,90 , 110 },
						{90  ,110 ,90 , 50  },
						{90  ,50  ,80 , 50  },
						{80  ,50  ,80 , 40  },
						{80  ,40  ,60 , 20  },
						{60  ,20  ,60 , 40  },
						{60  ,40  ,70 , 40  },
						{70  ,40  ,70 , 50  },
						{70  ,50  ,60 , 50  },
						{60  ,50  ,60 , 120 },
						{60  ,120 ,80 , 140 },
						{90  ,210 ,90 , 220 },
						{90  ,220 ,70 , 240 },
						{70  ,240 ,70 , 260 },
						{70  ,260 ,90 , 280 },
						{90  ,280 ,110, 280 },
						{110 ,280 ,130, 260 },
						{130 ,260 ,130, 240 },
						{130 ,240 ,110, 220 },
						{110 ,220 ,110, 210 },
						{80  ,210 ,140, 210 },
						{140 ,210 ,160, 230 },
						{160 ,230 ,160, 240 },
						{160 ,240 ,180, 260 },
						{180 ,260 ,180, 230 },
						{180 ,230 ,140, 190 },
						{140 ,190 ,140, 160 },
						{140 ,160 ,120, 140 },
						{120 ,140 ,80 , 140 },
						{80  ,140 ,60 , 160 },
						{60  ,160 ,60 , 190 },
						{60  ,190 ,40 , 170 },
						{40  ,170 ,40 , 160 },
						{40  ,160 ,20 , 140 },
						{20  ,140 ,20 , 170 },
						{20  ,170 ,60 , 210 },
						{60  ,210 ,80 , 210 },
						{80  ,210 ,100, 190 },
						{100 ,190 ,120, 210 },
						{80  ,260 ,90 , 260 },
						{90  ,260 ,90 , 250 },
						{90  ,250 ,80 , 250 },
						{80  ,250 ,80 , 260 },
						{110 ,260 ,120, 260 },
						{120 ,260 ,120, 250 },
						{120 ,250 ,110, 250 },
						{110 ,250 ,110, 260 },
						{90  ,240 ,110, 240 },
						{110 ,240 ,110, 230 },
						{110 ,230 ,90 , 230 },
						{90  ,230 ,90 , 240 },
						{120 ,140 ,140, 120 },
						{140 ,120 ,140, 50  },
						{140 ,50  ,130, 50  },
						{130 ,50  ,130, 40  },
						{130 ,40  ,140, 40  },
						{140 ,40  ,140, 20  },
						{140 ,20  ,120, 40  },
						{120 ,40  ,120, 50  },
						{120 ,50  ,110, 50  },
						{110 ,50  ,110, 110 },
						{110 ,110 ,90 , 110 },
						{90  ,110 ,90 , 50  },
						{90  ,50  ,80 , 50  },
						{80  ,50  ,80 , 40  },
						{80 ,40  ,60 , 20  },
						{60 ,20  ,60 , 40  },
						{60 ,40  ,70 , 40  },
						{70 ,40  ,70 , 50  },
						{70 ,50  ,60 , 50  },
						{60 ,50  ,60 , 120 },
						{60 ,120 ,80 , 140 },
						{60 ,120 ,80 , 140 }};

				for (int i = 0; i < 123; i++) {
					g->DrawLine(pen, 
						(float)((arr[i][0] / 5 - 20) * 2.307 / 2), 
						(float)((arr[i][1] / 5 - 30) * 2.307 / 2), 
						(float)((arr[i][2] / 5 - 20) * 2.307 / 2), 
						(float)((arr[i][3] / 5 - 30) * 2.307 / 2));
				}
		}

		private: System::Void Form1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
			Graphics^ g = e->Graphics;
			g->Clear(Color::White);

			Pen^ pen = gcnew Pen(Color::Black);
			pen->Width = 0.1;

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

			Rectangle rect = System::Drawing::Rectangle(Wcx, top, Wx, Wy);
			g->DrawRectangle(rectPen, rect);
			g->Clip = gcnew System::Drawing::Region(rect);

			g->DrawLine(axesPen, left, 
								 (clientRectangleHeight - bottom - top) / 2 + top, 
								 clientRectangleWidth - right, 
								 (clientRectangleHeight - bottom - top) / 2 + top);
			g->DrawLine(axesPen, (clientRectangleWidth - left - right) / 2 + left, 
								 top, 
								 (clientRectangleWidth - left - right) / 2 + left, 
								 clientRectangleHeight - bottom);

			g->DrawRectangle(rectPen, Wcx, top, Wx, Wy);

			for (int i = 0; i < matrices.size(); i++) {
				mat С;
				times(T, matrices[i], С);
				g->Transform = gcnew System::Drawing::Drawing2D::Matrix(
					С[0][0], С[1][0],
					С[0][1], С[1][1],
					С[0][2], С[1][2]);

				DrawFigure(g, pen);
			}
		}

		private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
			lines.Clear();
			unit(T);

			clientRectangleHeight = Form::ClientRectangle.Height;
			clientRectangleWidth  = Form::ClientRectangle.Width;

			left   = 15;
			right  = 110;
			top    = 15;
			bottom = 15;

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
					matrices.clear();
					std::stack<mat> matStack;

					mat K; 
					unit(K);
					unit(T);

					std::string str;
					getline(in, str);

					while (in) {
						if ((str.find_first_not_of(" \t\r\n") != std::string::npos)
							&& (str[0] != '#')) {

							std::stringstream s(str);
							std::string cmd;
							s >> cmd;

							if ( cmd == "frame" ) {
								int VcxInt, VcyInt, VxInt, VyInt;
								s >> VcxInt >> VcyInt >> VxInt >> VyInt;
								Vcx = VcxInt; Vx = VxInt;
								Vcy = VcyInt; Vy = VyInt;
								frame(Vx, Vy, Vcx, Vcy, Wx, Wy, Wcx, Wcy, T);
							} 
							else if ( cmd == "figure" ) {
								matrices.push_back(K);
							} 
							else if ( cmd == "pushTransform" ) {
								matStack.push(K);
							} 
							else if ( cmd == "popTransform" ) {
								K = matStack.top();
								matStack.pop();
							} 
							else if ( cmd == "translate" ) {
								int x, y;
								s >> x >> y;
								mat C, C1;
								move(x, y, C);
								times(K, C, C1);
								K = C1;
							} 
							else if ( cmd == "scale" ) {
								int x, y;
								s >> x >> y;
								mat C, C1;
								scale(x, y, C);
								times(K, C, C1);
								K = C1;
							} 
							else if ( cmd == "rotate" ) {
								float Phi;
								s >> Phi;
								float pi = 3.1415926535;
								float PhiR = Phi * (pi / 180);
								mat C, C1;
								rotate(PhiR, 0, 0, C);
								times(K, C, C1);
								K = C1;
							}
						}

						getline(in, str);
					}
				}

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
				case Keys::Escape :
					frame(Vx, Vy, Vcx, Vcy, Wx, Wy, Wcx, Wcy, T);
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
