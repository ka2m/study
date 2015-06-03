#pragma once

namespace task3 {

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
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog;
	private: System::Windows::Forms::Button^  btnOpen;
	private: System::Collections::Generic::List<polygon3D^> polygons;
	private: System::Collections::Generic::List<System::Drawing::Color> colors;

			 float top, bottom, left, right;
			 float Wcx, Wcy, Wx, Wy;
			 float Vcx, Vcy, Vx, Vy;
			 bool isOrtho;
			 float near, __near, far, fovy, __fovy, aspect, alpha;
			 point3D eye, center, up, __eye, __center, __up;

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
				 this->openFileDialog->Filter = L"Text Files (*.txt)|*.txt|All files(*.*)|*.*";
				 this->openFileDialog->Title = L"Open File";
				 // 
				 // btnOpen
				 // 
				 this->btnOpen->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
				 this->btnOpen->Location = System::Drawing::Point(711, 6);
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
				 this->ClientSize = System::Drawing::Size(792, 466);
				 this->Controls->Add(this->btnOpen);
				 this->DoubleBuffered = true;
				 this->KeyPreview = true;
				 this->MinimumSize = System::Drawing::Size(150, 50);
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
				 point min = point(left, top);
				 point max = point(Form::ClientRectangle.Width - right, Form::ClientRectangle.Height - bottom);

				 Graphics^ g = e->Graphics;
				 g->Clear(Color::White);

				 Pen^ pen = gcnew Pen(Color::Black);
				 pen->Width = 1;
				 Pen^ rectPen = gcnew Pen(Color::Aqua);
				 rectPen->Width = 3;
				 g->DrawRectangle(rectPen, Wcx, top, Wx, Wy);

				 mat3D V, U, R, T1;
				 mat F;

				 LookAt(eye, center, up, V);
				 if (!isOrtho)
					 Perspective(fovy, aspect, near, far, U);
				 else {
					 float Vy = 2 * near * tan(fovy / 2);
					 float Vx = Vy * aspect;
					 Ortho(Vx, Vy, near, far, U);
				 }
				 
				 times(U, V, T1);
				 times(T1, T3D, R);
				 frame(2, 2, -1, -1, Wx, Wy, Wcx, Wcy, F);

				 for (int i = 0; i < polygons.Count; i++) {
					 polygon3D^ p = polygons[i];
					 polygon^ p1 = gcnew polygon(0);
					 
					 point a1, a2;
					 point3D A;					
					 vec b1, b2;
					 vec3D B1, B2;


					 for(int j = 0; j < p->Count; j++) {
						 point2vec(p[j], B1);
						 timesMatVec(R, B1, B2);
						 vec2point(B2, A);
						 set(A, a1);

						 point2vec(a1, b1);
						 timesMatVec(F, b1, b2);
						 vec2point(b2, a1);
						 p1->Add(a1);
					 }

					 p1 = PClip(p1, min, max);
					 if(!p1->Count) continue;
					 Pen^ pen = gcnew Pen(colors[i]);
					 pen->Width = 2;
					 point pt = p1[p1->Count - 1];
					 for(int j = 0; j < p1->Count; j++) { g->DrawLine(pen, pt.x, pt.y, p1[j].x, p1[j].y); pt = p1[j];}

				 }
			 }
	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
				 unit(T3D);
				
				 left = 10;
				 top = 25;
				 bottom = 50;
				 right = 100;


				 Wcx = left;
				 Wcy = Form::ClientRectangle.Height - bottom;
				 Wx = Form::ClientRectangle.Width - left - right;
				 Wy = Form::ClientRectangle.Height - top - bottom;

				 aspect = Wx/Wy;

			 }
	private: System::Void btnOpen_Click(System::Object^  sender, System::EventArgs^  e) {
				 if (this->openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
					 wchar_t fileName[1024];
					 for (int i = 0; i < openFileDialog->FileName->Length; i++)
						 fileName[i] = openFileDialog->FileName[i];

					 fileName[openFileDialog->FileName->Length] = '\0';

					 std::ifstream in;
					 in.open(fileName);
					 if (in.is_open()) {
						 System::Drawing::Color currentColor = Color::FromArgb(0, 0, 0);
						 polygons.Clear();
					     unit(T3D);

						 std::string str;
						 getline(in, str);
						 bool getRanges = false;
						 while (in) {
							 if ((str.find_first_not_of(" \t\r\n") != std::string::npos) && (str[0] != '#')) {
								 std::stringstream s(str);
								 std::string cmd;
								 s >> cmd;

								 if (cmd == "lookat") {
									 float eyex, eyey, eyez, centerx, centery, centerz, upx, upy, upz;
									 s >> eyex >> eyey >> eyez >> centerx >> centery >> centerz >> upx >> upy >> upz;

									 __eye.x = eyex;
									 __eye.y = eyey;
									 __eye.z = eyez;

									 __center.x = centerx;
									 __center.y = centery;
									 __center.z = centerz;

									 __up.x = upx;
									 __up.y = upy;
									 __up.z = upz;
								 } else if (cmd == "screen") {
									 float _fovy, _near, _far;
									 s >> _fovy >> _near >> _far;
									 __fovy = _fovy;
									 __near = _near;
									 far = _far;
								 } else if (cmd == "triangle") {
									 polygon3D^ pp = gcnew polygon3D(0);

									 for (int i = 0; i < 3; i++) {
										 point3D p;
										 s >> p.x >> p.y >> p.z;
										 pp->Add(p);
									 }
									 colors.Add(currentColor);
									 polygons.Add(pp);
								 } else if (cmd == "color") {
									 int r, g, b;
									 s >> r >> g >> b;
									 currentColor = Color::FromArgb(r, g, b);
								 }

							 }
							 getline(in, str);
						 }
					 }

					 LookAt(__center, __eye, __up, T3D);
					
					 center = __center;

					 near = __near;
					 fovy = __fovy;
					 eye = __eye;
					 up = __up;

                     eye.x = 0;
					 eye.y = 0;
					 eye.z = 0;
					 
					 vec3D __eyeVec, eyeVec;
					 point3D p;
                     point2vec(__eye, __eyeVec);
                     timesMatVec(T3D, __eyeVec, eyeVec);
                     vec2point(eyeVec, p);
					
					 eye = p;
					
					 up.x = 0;
					 up.y = 1;
					 up.z = 0;

					 center.x = 0;
					 center.y = 0;
					 center.z = 0;
					 
					 alpha = 0.0872664626;
					 isOrtho = true;
					 this->Refresh();
				 }
			 }
	private: System::Void Form1_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
				 Rectangle rect = Form::ClientRectangle;
				 mat3D M1, M2, M3, T1;

				 point3D x = point3D(1, 0, 0);
				 point3D y = point3D(0, 1, 0);
				 point3D z = point3D(0, 0, 1);

				 switch(e->KeyCode) {
					case Keys::P: isOrtho = !isOrtho; break;

					case Keys::A: rotate(y, alpha, M1); 
						times(M1, T3D, T1);
						set(T1, T3D); break;
					case Keys::D: rotate(y, -alpha, M1);
						times(M1, T3D, T1);
						set(T1, T3D);break;

					case Keys::W: rotate(x, alpha, M1);
						times(M1, T3D, T1);
						set(T1, T3D);
						break;
					case Keys::S: rotate(x, -alpha, M2);
						times(M2, T3D, T1);
						set(T1, T3D); break;

					case Keys::Q: rotate(z, alpha, M3);
						times(M3, T3D, T1);
						set(T1, T3D);
						break;
					case Keys::E: rotate(z, -alpha, M3);
						times(M3, T3D, T1);
						set(T1, T3D); break;

					case Keys::Z: near += 0.1; break;
					case Keys::X: near = (near - 0.1 > 0)?near - 0.1:0; break;
					case Keys::C: fovy += 0.1; break;
					case Keys::V: fovy -= 0.1; break;

					case Keys::O: alpha *= 1.1; break;
					case Keys::L: alpha /= 1.1; break;

					case Keys::Escape:
						LookAt(__center, __eye, __up, T3D);
						near = __near;
						fovy = __fovy;
						alpha = 0.0872664626;
						break;

				 }

				 this->Refresh();
			 }
	private: System::Void Form1_Resize(System::Object^  sender, System::EventArgs^  e) {
				 float oldWx = Wx;
				 float oldWy = Wy;

				 Wcx = left;
				 Wcy = Form::ClientRectangle.Height - bottom;
				 Wx = Form::ClientRectangle.Width - left - right;
				 Wy = Form::ClientRectangle.Height - top - bottom;

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

