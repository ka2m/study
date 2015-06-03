#pragma once

namespace mauris_task02_15 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
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
			this->ClientSize = System::Drawing::Size(640, 480);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::Form1_Paint);
			this->Resize += gcnew System::EventHandler(this, &Form1::Form1_Resize);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void Form1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
				 Graphics^ g = e->Graphics;
				 g->Clear(Color::White);

				 Pen^ blackPen = gcnew Pen(Color::Black);
				 blackPen->Width = 2;

				 Rectangle rect = Form::ClientRectangle;

				 int sizex = 20, sizey = 20;
				 //==----------------------------------||--------------------------|-------------------------------------------------------------------||------------------------------------------==----------------------------------
				 int x1[] = { 6,  4,  2, 25, 25, 28,  6,  7,  8,  8,  8,  8,  8,  9,  9,  9,  9, 10, 10, 10,  8,  8,  8, 11, 11, 11,  7, 12, 16, 16, 18, 20, 22, 22, 23, 24, 22, 23, 21, 24, 21, 21, 22, 21, 21, 20, 20, 20, 20, 20, 22};
				 int y1[] = {20, 18, 16, 16, 17, 17, 20, 15, 14, 12, 10,  5,  4,  2,  2,  5, 12,  2,  5, 12,  4, 10, 14,  4, 10, 14, 15, 15, 14, 14, 14, 10, 11,  5,  5, 11,  2,  2,  4,  4, 11, 13,  2,  4,  5, 10, 11, 12, 13, 14, 11};
				 int x2[] = {28, 28, 25, 25, 28, 28,  2, 12, 11, 11, 11, 11, 11, 10,  9,  9,  9, 10, 10, 10,  8,  8,  8, 11, 11, 11,  7, 12, 18, 16, 18, 20, 22, 22, 23, 24, 22, 23, 21, 24, 21, 21, 23, 24, 24, 22, 21, 21, 21, 21, 24};
				 int y2[] = {20, 18, 16, 17, 17, 20, 16, 15, 14, 12, 10,  5,  4,  2,  4, 10, 14,  4, 10, 14,  5, 12, 15,  5, 12, 15, 16, 16, 14, 16, 16, 16, 16, 10, 11, 16,  4,  4,  5,  5, 12, 14,  2,  4,  5, 10, 11, 12, 13, 14, 11};

				 for(int i = 0; i<sizeof(x1)/sizeof(int); i++)
				 	g->DrawLine(blackPen, x1[i]*sizex, y1[i]*sizey, x2[i]*sizex, y2[i]*sizey);
			 }
	private: System::Void Form1_Resize(System::Object^  sender, System::EventArgs^  e) {
				 this->Refresh();
			 }
	};
}