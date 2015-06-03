#pragma once

namespace CG_task218 {

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
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}

	protected: 

	protected: 

	private:
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code

		void InitializeComponent(void)
		{
			this->SuspendLayout();
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(242, 293);
			this->Name = L"Form1";
			this->Text = L"CG_task2-18";
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::Form1_Paint);
			this->ResumeLayout(false);

		}
#pragma endregion
		
		void drawLines(Graphics^ g, Pen^ pen, int x, int y, int mas[][2], int massize) { 
			
            for (int i = 0; i < massize; i++) {
				g->DrawLine(pen, x, y, x + mas[i][0], y + mas[i][1]);
				x += mas[i][0];
                y += mas[i][1];
            }
        }

		private: System::Void Form1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
                 
			Graphics^ g = e->Graphics;
			g->Clear(Color::White);

			Rectangle rect = Form::ClientRectangle;
			Pen^ pen = gcnew Pen(Color::Black);
			pen->Width = 2;

			// Points inc/dec -rements
			int head[9][2]  = {{  0, -10}, 
							   {-20, -20}, 
							   {  0, -20}, 
							   { 20, -20}, 
							   { 20,   0},
							   { 20,  20},
							   {  0,  20},
							   {-20,  20},
							   {  0,  10}};

			int body[19][2] = {{ 60,   0}, 
							   { 20, -20}, 
							   {  0, -10}, 
							   { 20, -20}, 
							   {  0,  30}, 
							   {-40,  40}, 
							   {  0,  30}, 
							   {-20,  20}, 
							   {-40,   0}, 
							   {-20, -20}, 
							   {  0, -30}, 
							   {-20,  20}, 
							   {  0,  10}, 
							   {-20,  20}, 
							   {  0, -30}, 
							   { 40, -40}, 
							   { 20,   0}, 
							   { 20,  20}, 
							   { 20, -20}};

			int eye[4][2]   = {{ 10,   0}, 
							   {  0,  10}, 
							   {-10,   0}, 
							   {  0, -10}};

			int mouth[4][2] = {{ 20,   0}, 
							   {  0,  10}, 
							   {-20,   0}, 
							   {  0, -10}};

			int legs[21][2] = {{ 20,  20}, 
							   {  0,  70}, 
							   {-10,   0}, 
							   {  0,  10}, 
							   { 10,   0}, 
							   {  0,  20}, 
							   {-20, -20}, 
							   {  0, -10}, 
							   {-10,   0}, 
							   {  0, -60}, 
							   {-20,   0}, 
							   {  0,  60}, 
							   {-10,   0}, 
							   {  0,  10}, 
							   {-20,  20}, 
							   {  0, -20}, 
							   { 10,   0}, 
							   {  0, -10}, 
							   {-10,   0}, 
							   {  0, -70}, 
							   { 20, -20}};

			drawLines(g, pen, 90,  90,  head,  9);
			drawLines(g, pen, 80,  90,  body, 19);
			drawLines(g, pen, 80,  40,  eye,   4);
			drawLines(g, pen, 110, 40,  eye,   4);
			drawLines(g, pen, 90,  60,  mouth, 4);
			drawLines(g, pen, 120, 160, legs, 21);
                 
		}
	};
}

