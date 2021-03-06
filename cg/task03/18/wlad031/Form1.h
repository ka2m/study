#pragma once


namespace CG_task318 {

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

	private:
		System::ComponentModel::Container ^components;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog;
	private: System::Windows::Forms::Button^  btnOpen;

		// List of the lines
		System::Collections::Generic::List<line> lines;

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
			this->btnOpen->Location = System::Drawing::Point(12, 12);
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
			this->ClientSize = System::Drawing::Size(592, 323);
			this->Controls->Add(this->btnOpen);
			this->DoubleBuffered = true;
			this->KeyPreview = true;
			this->Name = L"Form1";
			this->Text = L"CG_task3-18";
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

			Rectangle rect = Form::ClientRectangle;

			Pen^ pen = gcnew Pen(Color::Black);
			pen->Width = 2;

			Pen^ axesPen = gcnew Pen(Color::Gray);
			axesPen->Width = 1;

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

				g->DrawLine(pen, a.x, a.y, b.x, b.y);
			}

			g->DrawLine(axesPen, rect.Width / 2, 0, rect.Width / 2, rect.Height);
			g->DrawLine(axesPen, 0, rect.Height / 2, rect.Width, rect.Height / 2);
		}

		private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
			lines.Clear();
			unit(T);			
		}

		private: System::Void btnOpen_Click(System::Object^  sender, System::EventArgs^  e) {

			if (this->openFileDialog->ShowDialog() ==
				System::Windows::Forms::DialogResult::OK) {

				wchar_t fileName[1024];
				Rectangle rect = Form::ClientRectangle;

				for (int i = 0; i < openFileDialog->FileName->Length; i++)
					fileName[i] = openFileDialog->FileName[i];

				fileName[openFileDialog->FileName->Length] = '\0';
				
				std::ifstream in;
				in.open(fileName);
				if (in.is_open()) {
					lines.Clear();

					std::string str;
					getline(in, str);
					while (in) {
						if ((str.find_first_not_of(" \t\r\n") != std::string::npos)
								&& (str[0] != '#')) {

							std::stringstream s(str);
							line l;
							s >> l.start.x >> l.start.y >> l.end.x >> l.end.y;
							std::string linename;
							s >> linename;
							l.name = gcnew String(linename.c_str());
							lines.Add(l);
						}

						getline(in, str);
					}
				}

				unit(T);
				mat R, T1;

				reflect(1, 0, R);
				times(R, T, T1);

				move(0, rect.Height, R);
				times(R, T1, T);

				this->Refresh();
			}

		}

		private: System::Void Form1_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
			mat R, T1;
			unit(T1);
			Rectangle rect = Form::ClientRectangle;

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
					rotate(0.05, 0, 0, R);
					break;
				case Keys::Q :		// Left rotate
					rotate(-0.05, 0, 0, R);
					break;
				case Keys::Y :		// Right rotate about center
					rotate(0.05, rect.Width / 2, rect.Height / 2, R);
					break;
				case Keys::R :		// Left rotate about center
					rotate(-0.05, rect.Width / 2, rect.Height / 2, R);
					break;
				case Keys::Z :		// Decrease
					scale(1 / 1.1, 1 / 1.1, R);
					break;
				case Keys::X :		// Increase
					scale(1.1, 1.1, R);
					break;
				case Keys::C :		// Decrease about center
					move(-rect.Width / 2, -rect.Height / 2, R);
					times(R, T, T1);

					scale(1 / 1.1, 1 / 1.1, R);
					times(R, T1, T);

					move(rect.Width / 2, rect.Height / 2, R);
					break;
				case Keys::V :		// Increase about center
					move(-rect.Width / 2, -rect.Height / 2, R);
					times(R, T, T1);

					scale(1.1, 1.1, R);
					times(R, T1, T);

					move(rect.Width / 2, rect.Height / 2, R);
					break;
				case Keys::L :		// Increase about vertical middle
					move(-rect.Width / 2, 0, R);
					times(R, T, T1);

					scale(1.1, 1, R);
					times(R, T1, T);

					move(rect.Width / 2, 0, R);
					break;
				case Keys::K :		// Decrease about vertical middle
					move(-rect.Width / 2, 0, R);
					times(R, T, T1);

					scale(1 / 1.1, 1, R);
					times(R, T1, T);

					move(rect.Width / 2, 0, R);
					break;
				case Keys::O :		// Increase about horizontal middle
					move(0, -rect.Height / 2, R);
					times(R, T, T1);

					scale(1, 1.1, R);
					times(R, T1, T);

					move(0, rect.Height / 2, R);
					break;
				case Keys::I :		// Decrease about horizontal middle
					move(0, -rect.Height / 2, R);
					times(R, T, T1);

					scale(1, 1 / 1.1, R);
					times(R, T1, T);

					move(0, rect.Height / 2, R);
					break;
				case Keys::U :		// Reflection about vertical middle
					reflect(0, 1, R);
					times(R, T, T1);
					set(T1, T);

					move(rect.Width, 0, R);				
					break;
				case Keys::J :		// Reflection about horizontal middle
					reflect(1, 0, R);
					times(R, T, T1);
					set(T1, T);

					move(0, rect.Height, R);	
					break;
				case Keys::Escape :
					unit(T);
					reflect(1, 0, R);
					times(R, T, T1);

					move(0, rect.Height, R);
					times(R, T1, T);
				default :
					unit(R);
			}

			unit(T1);
			times(R, T, T1);
			set(T1, T);
			this->Refresh();
		}

		private: System::Void Form1_Resize(System::Object^  sender, System::EventArgs^  e) {
			this->Refresh();
		}
	};
}

