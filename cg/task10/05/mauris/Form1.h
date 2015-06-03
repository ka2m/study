#pragma once
#include <cstdio>
#include <string.h>
#include <cmath>

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
			System::Collections::Generic::List<polygon3D^> polygons;
			System::Collections::Generic::List<System::Drawing::Color> ^colors;

			float left, right, top, bottom;
			float Wcx, Wcy, Wx, Wy;
			float Vcx, Vcy, Vx, Vy;
			bool drawNames;
			point3D eye, center, up, deye, dcenter, dup;
			float near, far, fovy, aspect, dnear, dfar, dfovy, alpha, dalpha;
			bool prOrtho;
			bool cull3d;


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
			this->DoubleBuffered = true;
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
				 Bitmap^ image1 = gcnew Bitmap( this->ClientRectangle.Width
					, this->ClientRectangle.Height
					);
				 Graphics^ g = Graphics::FromImage(image1);

				 System::Drawing::Font^ drawFont = gcnew System::Drawing::Font("Arial", 5);
				 SolidBrush^ drawBrush = gcnew SolidBrush(Color::Black);
				 Pen^ blackPen = gcnew Pen(Color::Black);
				 Pen^ rectPen = gcnew Pen(Color::Purple);
				 Pen^ polyPen = gcnew Pen(Color::Black);
				 polyPen->Width = 2;
				 g->Clear(Color::White);
				 blackPen->Width = 4;
				 rectPen->Width = 2;
				 g->DrawRectangle(rectPen, Wcx, top, Wx, Wy);
				 
				 
				 
				 mat3D V, U, VT, R;
				 mat F;
				 
				 point r1, r2;
				 r1.x = this->left;
				 r1.y = this->top;
				 r2.x = Form::ClientRectangle.Width - right;
				 r2.y = Form::ClientRectangle.Height - bottom;
				 unit(V);
				 LookAt(eye, center, up, V);
				 if(prOrtho)
				 {
					float ymax = 8 * near * tan(fovy * M_PI / 360);
					float xmax = ymax * aspect;
					Ortho(xmax, ymax, near, far, U);
				 }
				 else
				 {
					Perspective(fovy, aspect, near, far, U);
				 }

				 times(V, T, VT);
				 times(U, VT, R);
				 
				 frame(2, 2, -1, -1, Wx, Wy, Wcx, Wcy, F);

				 System::Collections::Generic::List<polygon3D^> ^bsppolygons = gcnew System::Collections::Generic::List<polygon3D^>(0);

				 for (int i = 0; i < polygons.Count; i++)
				 {
					 polygon3D^ p = polygons[i];
					 polygon^ p1 = gcnew polygon(0);
					 Pen^ polyPen = gcnew Pen(colors[i]);
					 drawBrush = gcnew SolidBrush(colors[i]);
					 polyPen->Width = 2;
					 if(this->cull3d)
					 {
						 polygon3D^ bsppoly = gcnew polygon3D(0);
						 for(int j = 0; j < p->Count; j++)
						 {
							 vec3D v3d, res;
							 point2vec(p[j], v3d);
							 timesMatVec(VT, v3d, res);
							 point3D fp;
							 vec2point(res, fp);
							 bsppoly->Add(fp);
						 }
						 bsppolygons->Add(bsppoly);
					 }
					 else
					 {
						 for(int j = 0; j < p->Count; j++)
						 {
							 vec3D v3d, res;
							 point2vec(p[j], v3d);
							 timesMatVec(R, v3d, res);
							
							 vec v, fv;
							 point3D fp;
							 vec2point(res, fp);
							 point pv;
							 set(fp, pv);
							 point2vec(pv, v);
							 
							 timesMatVec(F, v, fv);
							 point p;
							 vec2point(fv, p);
							 p1->Add(p);
						 }
						 p1 = Pclip(p1, r1, r2);
						 if(!p1->Count)
							continue;
						 cli::array<System::Drawing::PointF> ^arrpoly = gcnew  cli::array<System::Drawing::PointF>(p1->Count);
						 point a, b;
						 a = p1[p1->Count - 1];
						 for (int j = 0; j < p1->Count; j++){
								b = p1[j];
								arrpoly[j] = System::Drawing::PointF(b.x, b.y);
								g ->DrawLine(polyPen, a.x, a.y, b.x, b.y);
								a = b;
						 }
						 
						 
						 //g->FillPolygon(drawBrush, arrpoly);
					 }
				 }

				 if(this->cull3d)
					 RenderBSP(bsppolygons, colors, F, U, r1, r2, image1);
				 g = e->Graphics;
				 g->DrawImage(image1,0,0);
				 delete image1;

			 }
	private: System::Void Form1_Resize(System::Object^  sender, System::EventArgs^  e) {
				 float oldWx = Wx, oldWy = Wy;
				 Wcy = Form::ClientRectangle.Height - bottom;
				 Wx = Form::ClientRectangle.Width - left - right;
				 Wy = Form::ClientRectangle.Height - top - bottom;
				 
				 aspect = Wx/Wy;
				 if(Wy == 0)
					 aspect = 1;
				 /*
				 mat Mov, nMov, Scale;
				 scale(this->Wx/oldWx, this->Wy/oldWy, Scale);
				 move(-this->Wcx, -this->top, Mov);
				 move(this->Wcx, this->top, nMov);
				 mat MS, R, T1;
				 times(nMov, Scale, MS);
				 times(MS, Mov, R);
				 times(R, T, T1);
				 set(T1, T);
				 */
				 this->Refresh();
			 }
	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
				 this->drawNames = false;
				 lines.Clear();
				 polygons.Clear();
				 unit(T);
				 this->top = 60.f;
				 this->left = 60.f;
				 this->right = 60.f;
				 this->bottom = 60.f;
				 prOrtho = 0;

				 Wcx = left;
				 Wcy = Form::ClientRectangle.Height - bottom;
				 Wx = Form::ClientRectangle.Width - left - right;
				 Wy = Form::ClientRectangle.Height - top - bottom;
				 dalpha = alpha = 0.0872664626;	//5 deg
				 aspect = Wx/Wy;
				 cull3d = false;
				 colors = gcnew System::Collections::Generic::List<System::Drawing::Color>(0);
				 if(Wy == 0)
					aspect = 1;
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
						 lines.Clear();
						 polygons.Clear();
						 colors->Clear();
						 unit(T);
						 std::string str;
						 getline(in, str);
						 System::Drawing::Color currentColor = Color::FromArgb(0, 0, 0);
						 while (in) {
							 if ((str.find_first_not_of(" \t\r\n") != std::string::npos) && (str[0] != '#')) {
								 std::stringstream s(str);
								 std::string cmd;
								 s >> cmd;
								 
								 if ( cmd == "screen" ) {
									 float df, dn, dfr;

									 s >> df >> dn >> dfr;
									 dfovy = df;
									 dnear = dn;
									 dfar = dfr;
								 } else if( cmd == "triangle" ) {
									 point3D x, y, z;
									 polygon3D^ pn = gcnew polygon3D(0);
									 pn->Clear();
									 s >> x.x >> x.y >> x.z >> y.x >> y.y >> y.z >> z.x >> z.y >> z.z;
									 pn->Add(x);
									 pn->Add(y);
									 pn->Add(z);
									 
									 polygons.Add(pn);
									 colors->Add(currentColor);

								 } else if( cmd == "color" ) {
									int r, g, b;
									s >> r >> g >> b;
									currentColor = Color::FromArgb(255, r, g, b);
								 } else if( cmd == "lookat" ) {
								    point3D de, dc, du;
									s >> de.x >> de.y >> de.z >> dc.x >> dc.y >> dc.z >> du.x >> du.y >> du.z;
									dup.x = du.x; dup.y = du.y; dup.z = du.z;
									deye.x = de.x; deye.y = de.y; deye.z = de.z;
									dcenter.x = dc.x; dcenter.y = dc.y; dcenter.z = dc.z;
									unit(T);
									LookAt(dcenter, deye, dup, T);
									
									vec3D neweye, r;
									point2vec(deye, neweye);
									timesMatVec(T, neweye, r);
									point3D neweyep;
									vec2point(r, neweyep);
									eye.x = neweyep.x;
									eye.y = neweyep.y;
									eye.z = neweyep.z;
									//printf("%.2f %.2f %.2f\n", eye.x, eye.y, eye.z);
									up.x = up.z = 0;
									up.y = 1;
									center.x = center.y = center.z = 0;
								 }

								 
							 
							 }
							 getline(in, str);
						 }
					 }
					 near = dnear;
					 far = dfar;
					 fovy = dfovy;

					 this->Refresh();					
				 }
			 }
	private: System::Void Form1_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
				 mat3D R, T1;
				 unit(R);
				 point3D Ox, Oz;
				 Ox.x = 1;
				 Ox.y = Ox.z = 0;
				 Oz.z = 1;
				 Oz.x = Oz.y = 0;
				 switch(e->KeyCode) {
					case Keys::W:
						rotate(Ox, alpha, R);
						break;
					case Keys::S:
						rotate(Ox, -alpha, R);
						break;
					case Keys::A:
						rotate(up, alpha, R);
						break;
					case Keys::D:
						rotate(up, -alpha, R);
						break;
					
					case Keys::E :
						rotate(Oz, -alpha, R);
						break;
					case Keys::Q :
						rotate(Oz, alpha, R);
						break;
					
					case Keys::P :
						this->prOrtho = !this->prOrtho;
						break;
					case Keys::F :
						this->cull3d = !this->cull3d;
						break;
					case Keys::Escape:
						near = dnear;
						fovy = dfovy;
						alpha = dalpha;

						LookAt(dcenter, deye, dup, T);
						vec3D neweye, r;
						point2vec(deye, neweye);
						timesMatVec(T, neweye, r);
						point3D neweyep;
						vec2point(r, neweyep);
						eye.x = neweyep.x;
						eye.y = neweyep.y;
						eye.z = neweyep.z;
						up.x = up.z = 0;
						up.y = 1;
						center.x = center.y = center.z = 0;
						prOrtho = 0;
						break;
					
					case Keys::Z :
						near += 0.1;
						break;
					case Keys::X :
						near -= 0.1;
						if(near <= 0.1)
							near = 0.1;
						break;
					case Keys::T :
						for(int i =0; i<4; i++)
						{
							for(int j = 0; j < 4; j++)
								printf("%.2f ", T[i][j]);
							printf("\n");
						}
						break;
					case Keys::C :
						fovy += 1;
						break;
					case Keys::V :
						fovy -= 1;
						break;
					case Keys::O :
						alpha *= 1.1;
						break;
					case Keys::L :
						alpha /= 1.1;
						break;
					/*
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

					
					case Keys::P:
						this->drawNames = !this->drawNames;
						unit(R);
						break;
					*/
					default: 
						unit(R);
				  }

				 times(R, T, T1);
				 set(T1, T);
				 this->Refresh();

			 }
	};
}

