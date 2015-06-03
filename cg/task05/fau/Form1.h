#pragma once

#define BSIZE 4

namespace task5 {

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
		float top, bottom, left, right;
		float Wcx, Wcy, Wx, Wy;
		float Vcx, Vcy, Vx, Vy;
		float bVcx, bVcy, bVx, bVy;
		int K, L;

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
			this->ClientSize = System::Drawing::Size(692, 673);
			this->DoubleBuffered = true;
			this->KeyPreview = true;
			this->MinimumSize = System::Drawing::Size(150, 150);
			this->Name = L"Form1";
			this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Show;
			this->Text = L"Form1";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::Form1_Paint);
			this->Resize += gcnew System::EventHandler(this, &Form1::Form1_Resize);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::Form1_KeyDown);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void Form1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
				 float fancyLimit = BSIZE / 2; 

				 point min = {left + fancyLimit, top + fancyLimit};
				 point max = {Form::ClientRectangle.Width - right - fancyLimit , Form::ClientRectangle.Height - bottom - fancyLimit};

				 Graphics^ g = e->Graphics;
				 Pen^ pen = gcnew Pen(Color::Black);
				 g->Clear(Color::White);
				 pen->Width = 1;

				 Pen^ coordsPen = gcnew Pen(Color::DarkBlue);
				 coordsPen->Width = 1;

				 System::Drawing::Font^ drawFont = gcnew System::Drawing::Font("Arial", 8);
				 SolidBrush^ drawBrush = gcnew SolidBrush(Color::Black);

				 Pen^ rectPen = gcnew Pen(Color::Aqua);
				 rectPen->Width = BSIZE;
				 g->DrawRectangle(rectPen, Wcx, top, Wx, Wy);

				 float dx = Wcx;
				 float x = Vcx;
				 float y = 0;
				 float dy = 0;
				 float ddy = 0;
				 bool visible1 = false, visible2 = false;

				 // Coord lines stuff
				 float wdK = Wx / (K + 1);
				 float  wdL = Wy / (L + 1); 

				 float dK = Wcx + wdK;
				 float dL = Wcy - Wy + wdL;
				 int countK = 0, countL = 0;

				 if (fexists(x)) {
					 visible1 = true;
					 y = f(x);
					 dy = Wcy - ((y - Vcy) / Vy) * Wy;
				 } else visible1 = false;

				 while (dx < Wcx + Wx) {
					 x = ((dx + 1 - Wcx) / Wx) * Vx + Vcx;
					 if (fexists(x)) {
						 visible2 = true;
						 y = f(x);
						 ddy = Wcy - ((y - Vcy) / Vy) * Wy; 
					 } else visible2 = false;

					 if (visible1 && visible2) {
						 point a, b;
						 a.x = dx;
						 a.y = dy;
						 b.x = dx + 1;
						 b.y = ddy;
						 if (clip(a, b, min, max)) {
							 g->DrawLine(pen, a.x, a.y, b.x, b.y);
						 }
					 }

					 if ((int)dx == (int)dK && countK < K) {
						 float value = ((dx - Wcx) / Wx) * Vx + Vcx;
						 value = (float)(((int)(value * 100))) / 100;

						 g->DrawLine(coordsPen, dx, Wcy - Wy + fancyLimit, dx, Wcy - fancyLimit);
						 g->DrawString(Convert::ToString(value), drawFont, drawBrush, dx, Wcy + fancyLimit);

						 dK += wdK;
						 countK++;
					 }

					 dx++;
					 dy = ddy;
					 visible1 = visible2;
				 }
				
				 float coordy = Wcy - Wy;

				 while (countL < L) {
					 if ((int)coordy == (int)dL) {
						 float value = Vcy - ((coordy - Wcy) / Wy) * Vy;

						 value = (float)(((int)(value * 100))) / 100;

						 g->DrawLine(coordsPen, Wcx + fancyLimit, coordy, Wcx + Wx - fancyLimit, coordy);
						 g->DrawString(Convert::ToString(value), drawFont, drawBrush, Wx + Wcx + fancyLimit, coordy);

						 dL += wdL;
						 countL++;
					 }
					 coordy++;
				 }

			 }
	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
				 left = right = top = bottom = 30;

				 Vx = bVx = 10;
				 Vy = bVy = 30;
				 Vcx = bVcx = -Vx / 2;
				 Vcy = bVcy = -Vy / 2;

				 K = L = 5;

				 Wcx = left;
				 Wcy = Form::ClientRectangle.Height - bottom;
				 Wx = Form::ClientRectangle.Width - left - right;
				 Wy = Form::ClientRectangle.Height - top - bottom;
			 }
	private: System::Void Form1_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
				 float old;
				 switch(e->KeyCode) {
					case Keys::W: Vcy -= (Vy / Wy); break;
					case Keys::S: Vcy += (Vy / Wy); break;
					case Keys::A: Vcx += (Vx / Wx); break;
					case Keys::D: Vcx -= (Vx / Wx); break;

					case Keys::T: Vcy -= 10 * (Vy / Wy); break;
					case Keys::G: Vcy += 10 * (Vy / Wy); break;
					case Keys::F: Vcx += 10 * (Vx / Wx); break;
					case Keys::H: Vcx -= 10 * (Vx / Wx); break;

					case Keys::Q: K++; break;
					case Keys::E: K = std::max(K-1, 2); break;
					case Keys::Z: L++; break;
					case Keys::C: L = std::max(L-1, 2); break;

					case Keys::I:
						old = Vy;
						Vy *= 1 / 1.1;
						Vcy += (old - Vy) / 2;
						break;

					case Keys::O :
						old = Vy;
						Vy *= 1.1;
						Vcy += (old - Vy) / 2;
						break;
					case Keys::K :
						old = Vx;
						Vx *= 1 / 1.1;
						Vcx += (old - Vx) / 2;
						break;
					case Keys::L :
						old = Vx;
						Vx *= 1.1;
						Vcx += (old - Vx) / 2;
						break;

					case Keys::Escape:
						Vx = bVx;
						Vy = bVy;
						Vcx = bVcx;
						Vcy = bVcy;
						break;

				 }
				 this->Refresh();
			 }
	private: System::Void Form1_Resize(System::Object^  sender, System::EventArgs^  e) {
				 float oldWx = Wx, oldWy = Wy;

				 Wcx = left;
				 Wcy = Form::ClientRectangle.Height - bottom;
				 Wx = Form::ClientRectangle.Width - left - right;
				 Wy = Form::ClientRectangle.Height - top - bottom;


				 this->Refresh();
			 }
	};
}

