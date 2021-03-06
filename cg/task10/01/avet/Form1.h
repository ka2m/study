#pragma once

#define forn(i, n) for(int i=0; i < (int) n; ++i)
#define max(a, b) a > b ? a : b

namespace task10 {
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

	private: System::Collections::Generic::List<polygon3D^> triangles;
	private: System::Collections::Generic::List<System::Drawing::Color> colors;
	private: point3D eye, center, up, eyeOld, centerOld, upOld;
	private: System::Drawing::Color curColor;
	private: bool isOrtho, keepZ;
	private: float near, nearOld, far, fovy, fovyOld, aspect, alpha;
	private: float left, right, top, bottom;
	private: float Wcx, Wcy, Wx, Wy;
	private: float Vcx, Vcy, Vx, Vy;

#pragma region Windows Form Designer generated code

			 void InitializeComponent(void)
			 {
				 this->openFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
				 this->btnOpen = (gcnew System::Windows::Forms::Button());
				 this->SuspendLayout();
				 this->openFileDialog->DefaultExt = L"txt";
				 this->openFileDialog->FileName = L"openFileDialog1";
				 this->openFileDialog->Filter = L"Текстовые файлы (*.txt)|*.txt|Все файлы (*.*)|*.*";
				 this->openFileDialog->Title = L"Open file";
				 this->btnOpen->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
				 this->btnOpen->Location = System::Drawing::Point(404, 12);
				 this->btnOpen->Name = L"btnOpen";
				 this->btnOpen->Size = System::Drawing::Size(131, 31);
				 this->btnOpen->TabIndex = 0;
				 this->btnOpen->Text = L"Open";
				 this->btnOpen->UseVisualStyleBackColor = true;
				 this->btnOpen->Click += gcnew System::EventHandler(this, &Form1::btnOpen_Click);
				 this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
				 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				 this->ClientSize = System::Drawing::Size(550, 500);
				 this->Controls->Add(this->btnOpen);
				 this->DoubleBuffered = true;
				 this->KeyPreview = true;
				 this->MinimumSize = System::Drawing::Size(558, 527);
				 this->Name = L"Form1";
				 this->Text = L"task9";
				 this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
				 this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::Form1_Paint);
				 this->Resize += gcnew System::EventHandler(this, &Form1::Form1_Resize);
				 this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::Form1_KeyDown);
				 this->ResumeLayout(false);

			 }
#pragma endregion

	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
				 unit(T3D);

				 left = right = top = bottom = 50;

				 Wcx = left;
				 Wcy = Form::ClientRectangle.Height - bottom;
				 Wx  = Form::ClientRectangle.Width - left - right;
				 Wy  = Form::ClientRectangle.Height - top - bottom;

				 aspect = Wx / Wy; 
			 }

	private: System::Void Form1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
				 Bitmap^ image = gcnew Bitmap(Form::ClientRectangle.Width, Form::ClientRectangle.Height);
				 Graphics^ g = Graphics::FromImage(image);
				 g->Clear(Color::White);

				 Pen^ black = gcnew Pen(Color::Black);
				 black->Width = 1;

				 Pen^ red = gcnew Pen(Color::Red);
				 red->Width = 3;

				 g->DrawRectangle(red, Wcx, top, Wx, Wy);
				 mat3D V, U, R, T1;

				 LookAt(eye, center, up, V);

				 if (isOrtho) {
					 float Vy = 2 * near * tan(fovy / 2);
					 float Vx = Vy * aspect;
					 Ortho(Vx, Vy, near, far, U);
				 } else {
					 Perspective(fovy, aspect, near, far, U);
				 }

				 times(U, V, T1);
				 times(T1, T3D, R);

				 if(keepZ) {
					 mat3D F;
					 frameKeepZ(Wcx, Wcy, Wx, Wy, F);

					 forn(i, triangles.Count) {
						 polygon3D^ p = triangles[i];
						 polygon3D^ p1 = gcnew polygon3D(0);

						 forn(j, p->Count) {
							 vec3D a, b, c;
							 point3D d;

							 point2vec(p[j], a);
							 timesMatVec(R, a, b);
							 timesMatVec(F, b, c);

							 vec2point(c, d);
							 p1->Add(d);
						 }

						 zBuffer(p1, Form::ClientRectangle.Width, Form::ClientRectangle.Height, image, colors[i], Wcx, Wcy, Wx, Wy);
					 }
				 } else {
					 mat F;
					 frame(2, 2, -1, -1, Wx, Wy, Wcx, Wcy, F);

					 forn(i, triangles.Count) {
						 polygon3D^ p = triangles[i];
						 polygon^ p1 = gcnew polygon(0);

						 point a1, a2, c;
						 vec b1, b2;

						 point3D A;
						 vec3D B1, B2;

						 forn(j, p->Count) {
							 point2vec(p[j], B1);
							 timesMatVec(R, B1, B2);
							 vec2point(B2, A);
							 set(A, a1);

							 point2vec(a1, b1);
							 timesMatVec(F, b1, b2);
							 vec2point(b2, a1);
							 p1->Add(a1);
						 }

						 point min = {left, top};
						 point max = {Form::ClientRectangle.Width - right, Form::ClientRectangle.Height - bottom};
						 p1 = Pclip(p1, min, max);

						 if (p1->Count) {
							 black->Color = colors[i];
							 c = p1[p1->Count - 1];

							 forn(j, p1->Count) {
								 g ->DrawLine(black, c.x, c.y, p1[j].x, p1[j].y);
								 c = p1[j];
							 }
						 }
					 }
				 }

				 g = e->Graphics;
				 g->DrawImage(image, 0, 0);
				 delete image;
			 }

	private: System::Void btnOpen_Click(System::Object^  sender, System::EventArgs^  e) {
				 if (this->openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
					 wchar_t fileName[1024];

					 forn(i, openFileDialog->FileName->Length) {
						 fileName[i] = openFileDialog->FileName[i];
					 }

					 fileName[openFileDialog->FileName->Length] = '\0';
					 triangles.Clear();
					 colors.Clear();

					 curColor = Color::Black;

					 std::ifstream in;
					 in.open(fileName);
					 if (in.is_open()) {
						 std::string str;
						 getline(in, str);

						 while (in) {
							 if ((str.find_first_not_of(" \t\r\n") != std::string::npos) && (str[0] != '#')) {
								 std::stringstream s(str);
								 std::string cmd;
								 s >> cmd;

								 if(cmd == "lookat") {
									 float ex, ey, ez, cx, cy, cz, ux, uy, uz;
									 s >> ex >> ey >> ez >> cx >> cy >> cz >> ux >> uy >> uz;

									 eyeOld.x = ex;
									 eyeOld.y = ey;
									 eyeOld.z = ez;

									 centerOld.x = cx;
									 centerOld.y = cy;
									 centerOld.z = cz;

									 upOld.x = ux;
									 upOld.y = uy;
									 upOld.z = uz;
								 } else if(cmd == "screen") {
									 float a, b, c;
									 s >> a >> b >> c;
									 fovyOld = a;
									 nearOld = b;
									 far = c;
								 } else if(cmd == "triangle") {				
									 polygon3D^ P = gcnew polygon3D(0);

									 forn(i, 3) {
										 point3D p;
										 s >> p.x >> p.y >> p.z;
										 P->Add(p);
									 }

									 triangles.Add(P);
									 colors.Add(curColor);
								 } else if(cmd == "color") {
									 int r, g, b;
									 s >> r >> g >> b;
									 curColor = Color::FromArgb(r, g, b);
								 }
							 }

							 getline(in, str);
						 }
					 }

					 LookAt(centerOld, eyeOld, upOld, T3D);

					 center = centerOld;
					 near = nearOld;
					 fovy = fovyOld;

					 vec3D tmpVec, tmpVec1;
					 point3D tmpP;
					 point2vec(eyeOld, tmpVec);
					 timesMatVec(T3D, tmpVec, tmpVec1);
					 vec2point(tmpVec1, tmpP);

					 eye = tmpP;

					 up.x = 0;
					 up.y = 1;
					 up.z = 0;

					 center.x = center.y = center.z = 0;
					 alpha = 0.0174532925;
					 isOrtho = true;
					 this->Refresh();
				 }
			 }

	private: System::Void Form1_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
				 mat3D R1, R2, R3, T1;

				 point3D x = {1, 0, 0};
				 point3D y = {0, 1, 0};
				 point3D z = {0, 0, 1};

				 switch(e->KeyCode) {
					 case Keys::W:
						 rotate(x, alpha, R1);
						 times(R1, T3D, T1);
						 set(T1, T3D);
						 break;
					 case Keys::S:
						 rotate(x, -alpha, R2);
						 times(R2, T3D, T1);
						 set(T1, T3D);
						 break;
					 case Keys::A:
						 rotate(y, alpha, R1);
						 times(R1, T3D, T1);
						 set(T1, T3D);
						 break;
					 case Keys::D:
						 rotate(y, -alpha, R1);
						 times(R1, T3D, T1);
						 set(T1, T3D);
						 break;
					 case Keys::Q:
						 rotate(z, alpha, R3);
						 times(R3, T3D, T1);
						 set(T1, T3D);
						 break;
					 case Keys::E:
						 rotate(z, -alpha, R3);
						 times(R3, T3D, T1);
						 set(T1, T3D);
						 break;
					 case Keys::O:
						 alpha *= 1.1;
						 break;
					 case Keys::L:
						 alpha /= 1.1;
						 break;
					 case Keys::Z:
						 near += 0.1;
						 break;
					 case Keys::X:
						 near = max(0, near - 0.1);
						 break;
					 case Keys::C:
						 fovy += 0.1;
						 break;
					 case Keys::V:
						 fovy -= 0.1;
						 break;
					 case Keys::P:
						 isOrtho = !isOrtho;
						 break;
					 case Keys::F:
						 keepZ = !keepZ;
						 break;
					 case Keys::Escape:
						 LookAt(centerOld, eyeOld, upOld, T3D);
						 near = nearOld;
						 fovy = fovyOld;
						 alpha = 0.0174532925;
						 isOrtho = true;
						 keepZ = false;
				 }

				 this->Refresh();
			 }

	private: System::Void Form1_Resize(System::Object^  sender, System::EventArgs^  e) {
				 float oldWx = Wx, oldWy = Wy;

				 Wcx = left;
				 Wcy = Form::ClientRectangle.Height - bottom;
				 Wx  = Form::ClientRectangle.Width - left - right;
				 Wy  = Form::ClientRectangle.Height - top - bottom;

				 mat R, T1;
				 move(-Wcx, -top, R);
				 times(R, T, T1);

				 scale(Wx / oldWx, Wy / oldWy, R);
				 times(R, T1, T);

				 move(Wcx, top, R);
				 times(R, T, T1);
				 set(T1, T);

				 aspect = Wx / Wy;

				 this->Refresh();
			 }
	};
}
