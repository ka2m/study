#pragma once
#define forn(i, n) for(int i=0; i < (int) n; ++i)


namespace task_2_14 {

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
			this->SuspendLayout();
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(644, 502);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::Form1_Paint);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
			 }
	private: System::Void Form1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
				 const int CELL_SIZE = 20;
				 const int PEN_WIDTH = 2;
				 const int WIDTH = 32;
				 const int HEIGHT = 26;

				 Graphics^ g = e->Graphics;
				 g->Clear(Color::White);
				 Rectangle rect = Form::ClientRectangle;

				 Pen^ pen = gcnew Pen(Color::Black);
				 pen->Width = PEN_WIDTH;

				 int x[] = { 2, 6, 8, 9, 14, 15, 19, 20, 22, 23, 24, 26, 26, 25, 27, 29, 32, 31, 29, 29, 31, 29, 28, 27, 26, 25, 24, 23, 23, 24, 24, 27, 28, 28, 27, 23, 22, 22, 23, 23, 21, 21, 20, 19, 19, 18, 18, 19, 12, 11, 9, 8, 7, 6, 6, 7, 7, 5, 5, 4, 4, 3, 4, 4, 3, 3, 2, 2, 8, 8, 9, 9, 7, 7, 6, 17, 17, 18, 18, 16, 16, 15, 15 };
				 int y[] = { 7, 3, 3, 2, 2, 3, 3, 4, 4, 5, 5, 7, 8, 9, 7, 7, 10, 11, 11, 15, 17, 19, 19, 18, 18, 17, 17, 16, 15, 14, 11, 14, 14, 15, 14, 16, 17, 22, 23, 24, 24, 23, 20, 19, 16, 15, 14, 17, 17, 16, 16, 17, 17, 18, 22, 23, 24, 24, 22, 21, 19, 18, 17, 16, 15, 13, 12, 7, 17, 20, 21, 22, 22, 20, 19, 17, 20, 21, 22, 22, 21, 20, 17 };

				 int N = sizeof(x) / sizeof(int);
				 forn(i, N - 1) {
					 if (i == 30 || i == 34 || i == 46 || i == 67 || i == 74) continue;
					 g->DrawLine(pen, x[i] * CELL_SIZE, y[i] * CELL_SIZE, x[i + 1] * CELL_SIZE, y[i + 1] * CELL_SIZE);
				 }
			 }
	};
}

