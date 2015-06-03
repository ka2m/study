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
			 System::Collections::Generic::List<line> lines;
			 private: System::Collections::Generic::List<polygon^> polygons;

			 float top, bottom, left, right;
			 float Wcx, Wcy, Wx, Wy;
			 float Vcx, Vcy, Vx, Vy;


			 bool drawLineNames;

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
				 Pen^ pen = gcnew Pen(Color::Black);
				 g->Clear(Color::White);
				 pen->Width = 1;
				 //Rectangle rect = Form::ClientRectangle;

				 System::Drawing::Font^ drawFont = gcnew System::Drawing::Font("Arial", 5);
				 SolidBrush^ drawBrush = gcnew SolidBrush(Color::Black);

				 Pen^ rectPen = gcnew Pen(Color::Aqua);
				 rectPen->Width = 3;
				 g->DrawRectangle(rectPen, Wcx, top, Wx, Wy);
				 for (int i = 0; i < polygons.Count; i++) {
					 polygon^ p = polygons[i];
					 polygon^ p1 = gcnew polygon(0);

					 point a, b;
					 vec A, B, A1, B1;
					 point2vec(p[p->Count - 1], A);
					 timesMatVec(T, A, A1);
					 vec2point(A1, a);
					 p1->Add(a);
					 for (int j = 0; j < p->Count; j++){
						 point2vec(p[j], B);
						 timesMatVec(T, B, B1);
						 vec2point(B1, b);
						 p1->Add(b);
						 a = b;
					 }
					 p1 = PClip(p1, min, max);
					 if(!p1->Count) continue;

					 a = p1[p1->Count - 1];
					 b = p1[0];
					 g->DrawLine(pen, a.x, a.y, b.x, b.y);

					 for(int i = 0; i < p1->Count - 1; i++) g->DrawLine(pen, p1[i].x, p1[i].y, p1[i + 1].x, p1[i + 1].y);

				 }
				/* for (int i = 0; i < lines.Count; i++) {
					 vec A, B;
					 point2vec(lines[i].start, A);
					 point2vec(lines[i].end, B);
					 vec A1, B1;
					 timesMatVec(T, A, A1);
					 timesMatVec(T, B, B1);
					 point a, b;
					 vec2point(A1, a);
					 vec2point(B1, b);
					 if (clip(a, b, min, max)) {
						 g -> DrawLine(pen, a.x, a.y, b.x, b.y);
						 if (drawLineNames) {
							 g -> DrawString(lines[i].name, drawFont, drawBrush, a.x + (b.x - a.x) / 2, a.y + (b.y - a.y) / 2 - 8);
						 }
					 }
				 }*/
			 }
	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
				 polygons.Clear();
				 lines.Clear();

				 unit(T);
				 T[1][1] = -1;
				 T[1][M - 1] = Form::ClientRectangle.Height;

				 left = 10;
				 top = 25;
				 bottom = 50;
				 right = 100;


				 Wcx = left;
				 Wcy = Form::ClientRectangle.Height - bottom;
				 Wx = Form::ClientRectangle.Width - left - right;
				 Wy = Form::ClientRectangle.Height - top - bottom;
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
						 polygons.Clear();

						 std::string str;
						 getline(in, str);
						 bool getRanges = false;
						 while (in) {
							 if ((str.find_first_not_of(" \t\r\n") != std::string::npos) && (str[0] != '#')) {
								 std::stringstream s(str);
								 std::string cmd;
								 s >> cmd;

								 
								 if (cmd == "frame") {
									 int a, b, c, d;
									 s >> a >> b >> c >> d;

									 Vcx = a;
									 Vcy = b;
									 Vx = c;
									 Vy = d;

									 frame(Vx, Vy, Vcx, Vcy, Wx, Wy, Wcx, Wcy, T);
								 } else if (cmd == "polygon") {
									 int numpoint;
									 s >> numpoint;
									 polygon^ pn = gcnew polygon(0);
									 for (int i = 0; i < numpoint; i++) {
										 point p;
										 s >> p.x >> p.y;
										 pn->Add(p);
									 }
									 polygons.Add(pn);
								 }

							 }
							 getline(in, str);
						 }
					 } 
	
					 this->Refresh();
				 }
			 }
	private: System::Void Form1_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
				 Rectangle rect = Form::ClientRectangle;
				 mat R, T1;
				 float kscale = 1 / 1.1;
				 float centerX = rect.Width / 2;
				 float centerY = rect.Height / 2;
				 const int CELL_SIZE = 10;
				 switch(e->KeyCode) {
					case Keys::W: move(0, -1, R); break;
					case Keys::S: move(0, 1, R); break;
					case Keys::A: move(-1, 0, R); break;
					case Keys::D: move(1, 0, R);break;

					case Keys::E: rotate(0.05, 0, 0, R); break;
					case Keys::X: scale(1.1, 1.1, R); break;

					case Keys::Q: rotate(-0.05, 0, 0, R); break;
					case Keys::Z: scale(kscale, kscale, R); break;


					case Keys::T: move(0, -CELL_SIZE, R); break;
					case Keys::G: move(0, CELL_SIZE, R); break;
					case Keys::F:	move(-CELL_SIZE, 0, R); break;
					case Keys::H: move(CELL_SIZE, 0, R); break;


					case Keys::U:
						reflectVertical(R);
						times(R, T, T1);
						set(T1, T);
						move(rect.Width, 0, R);
						break;

					case Keys::J:
						reflectHorizontal(R);
						times(R, T, T1);
						set(T1, T);
						move(0, rect.Height, R);
						break;


					case Keys::R: rotate(-0.05, rect.Width / 2, rect.Height / 2, R); break;
					case Keys::Y: rotate(0.05, rect.Width / 2, rect.Height / 2, R); break;


					case Keys::C:
						move(-centerX, -centerY, R);
						times(R, T, T1);

						scale(kscale, kscale, R);
						times(R, T1, T);

						move(centerX, centerY, R);
						break;

					case Keys::V:
						move(-centerX, -centerY, R);
						times(R, T, T1);

						scale(1.1, 1.1, R);
						times(R, T1, T);


						move(centerX, centerY, R);
						break;

					case Keys::I:
						move(0, -centerY, R);
						times(R, T, T1);
						set(T1, T);

						scale(1, kscale, R);
						times(R, T1, T);


						move(0, centerY, R);
						break;

					case Keys::O:
						move(0, -centerY, R);
						times(R, T, T1);
						set(T1, T);

						scale(1, 1.1, R);
						times(R, T1, T);


						move(0, centerY, R);
						break;

					case Keys::K:
						move(-centerX, 0, R);
						times(R, T, T1);
						set(T1, T);

						scale(kscale, 1, R);
						times(R, T1, T);


						move(centerX, 0, R);
						break;

					case Keys::L:
						move(-centerX, 0, R);
						times(R, T, T1);
						set(T1, T);

						scale(1.1, 1, R);
						times(R, T1, T);


						move(centerX, 0, R);
						break;

					case Keys::Escape:
						unit(R);
						unit(T);
						frame(Vx, Vy, Vcx, Vcy, Wx, Wy, Wcx, Wcy, T);
						drawLineNames = false;
						break;
					case Keys::P:
						unit(R);
						drawLineNames = !drawLineNames;
						break;
					default: unit(R);

				 }

				 times(R, T, T1);
				 set(T1, T);
				 this->Refresh();
			 }
	private: System::Void Form1_Resize(System::Object^  sender, System::EventArgs^  e) {
				 float oldWx = Wx, oldWy = Wy;

				 Wcx = left;
				 Wcy = Form::ClientRectangle.Height - bottom;
				 Wx = Form::ClientRectangle.Width - left - right;
				 Wy = Form::ClientRectangle.Height - top - bottom;

				 mat R;
				 move(-Wcx, -top, R);
				 times(R, T, T);

				 scale(Wx / oldWx, Wy / oldWy, R);
				 times(R, T, T);

				 move(Wcx, top, R);
				 times(R, T, T);
	
				 this->Refresh();
			 }
	};
}

