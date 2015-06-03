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
			float defVcx, defVcy, defVx, defVy;
			bool drawNames;
			int K,L;



	protected: 

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
			this->SuspendLayout();
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(624, 442);
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
				 Pen^ linePen = gcnew Pen(Color::Gray);
				 g->Clear(Color::White);
				 blackPen->Width = 4;
				 rectPen->Width = 2;
				 linePen->Width = 1;
				 g->DrawRectangle(rectPen, Wcx, top, Wx, Wy);
				 
				 
				 bool visible1, visible2 = false;
				 float x = Vcx;
				 int xd = this->Wcx;
				 float y, yd, ydd;
				 if(fexists(x))
				 {
				 	 visible1 = true;
					 y = f(x);
					 yd = this->Wcy - ((y - this->Vcy)*this->Wy)/this->Vy;
				 }
				 else
					 visible1 = false;
				 
				 for(xd = this->Wcx + 1; xd < this->Wcx + this->Wx; xd++){
					
					 x = (((xd + 1) - this->Wcx)*this->Vx)/this->Wx + this->Vcx;
					if(fexists(x))
					{
						visible2 = true;
						y = f(x);
						ydd = this->Wcy - (y - this->Vcy)/this->Vy*this->Wy;
					}
					else
					{
						visible2 = false;
					}
					
					
					if(visible1 && visible2)
					{
						point a, b;
						a.x = xd;
						a.y = yd;
						b.x = xd + 1;
						b.y = ydd;
						point r1, r2;
						r1.x = this->left;
						r1.y = this->top;
						r2.x = Form::ClientRectangle.Width - right;
						r2.y = Form::ClientRectangle.Height - bottom;
						if(clip(a, b, r1, r2)){
							g->DrawLine(blackPen, a.x, a.y, b.x, b.y);
						}
					}
					yd = ydd;
					visible1 = visible2;
					
				 }

				 for(int xl = this->Wcx + this->Wx/(this->L + 1); xl < this->Wcx + this->Wx; xl += this->Wx/(this->L + 1))
				 {
					point t, b;
					b.x = t.x = xl;
					t.y = this->top;
					b.y = this->Form::ClientRectangle.Height - bottom;
					float x = ((xl - Wcx) / Wx) * Vx + Vcx;
					g->DrawLine(linePen, t.x, t.y, b.x, b.y);
					g->DrawString(Convert::ToString(x), drawFont, drawBrush, xl, this->top - 24);
				 }

				 for(int yl = this->top + this->Wy/(this->K + 1); yl < this->top + this->Wy; yl += this->Wy/(this->K + 1))
				 {
					point l, r;
					l.y = r.y = yl;
					l.x = this->left;
					r.x = Form::ClientRectangle.Width - right;
					float y = Vcy - ((yl - Wcy) / Wy) * Vy;
					g->DrawLine(linePen, l.x, l.y, r.x, r.y);
					g->DrawString(Convert::ToString(y), drawFont, drawBrush, this->left - 48, yl);

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

				 this->defVcx = this->Vcx = -5;
				 this->defVcy = this->Vcy = -3;
				 this->defVx = this->Vx = 10;
				 this->defVy = this->Vy = 6;
				 
				 this->K = 7;
				 this->L = 7;
			 }
	
	private: System::Void Form1_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
				 float past;
				 switch(e->KeyCode) {
					case Keys::W: 
						Vcy -= (Vy / Wy);
						break;
					case Keys::S:
						Vcy += (Vy / Wy);
						break;
					case Keys::A:
						Vcx += (Vx / Wx);
						break;
					case Keys::D:
						Vcx -= (Vx / Wx);
						break;

					case Keys::T:
						Vcy -= 10 * (Vy / Wy);
						break;
					case Keys::G:
						Vcy += 10 * (Vy / Wy);
						break;
					case Keys::F:
						Vcx += 10 * (Vx / Wx);
						break;
					case Keys::H:
						Vcx -= 10 * (Vx / Wx);
						break;
					
					case Keys::Q:
						K++;
						break;
					case Keys::E:
						if (K > 1)
							K--;
						break;
					case Keys::Z:
						L++;
						break;
					case Keys::C:
						if (L > 1)
							L--;
						break;

					case Keys::I:
						past = Vy;
						Vy *= 1 / 1.1;
						Vcy += (past - Vy) / 2;
						break;

					case Keys::O :
						past = Vy;
						Vy *= 1.1;
						Vcy += (past - Vy) / 2;
						break;
					case Keys::K :
						past = Vx;
						Vx *= 1 / 1.1;
						Vcx += (past - Vx) / 2;
						break;
					case Keys::L :
						past = Vx;
						Vx *= 1.1;
						Vcx += (past - Vx) / 2;
						break;
					
					case Keys::Escape:
						this->Vx = this->defVx;
						this->Vy = this->defVy;
						this->Vcx = this->defVcx;
						this->Vcy = this->defVcy;
						break;

				 }
				 this->Refresh();

			 }
	};
}

