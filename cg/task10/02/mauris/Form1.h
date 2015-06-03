#pragma once


namespace tasks3 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для Form1
	///
	/// Внимание! При изменении имени этого класса необходимо также изменить
	///          свойство имени файла ресурсов ("Resource File Name") для средства компиляции управляемого ресурса,
	///          связанного со всеми файлами с расширением .resx, от которых зависит данный класс. В противном случае,
	///          конструкторы не смогут правильно работать с локализованными
	///          ресурсами, сопоставленными данной форме.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}


	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog;
	private: System::Windows::Forms::Button^  btnOpen;
			 System::Collections::Generic::List<line> lines; //список lines с элементами типа line
			 float left, right, top, bottom;
			 float Wcx, Wcy, Wx, Wy;
			 float Vcx, Vcy, Vx, Vy;

			 point3D eye, center, up, eye_, center_, up_;
			 float near, far, fovy, aspect, near_,fovy_, alpha;
			 bool prOrtho;
			 bool usesbuf;

	private: System::Collections::Generic::List<polygon3D^> polygons; //список указателей на многоугольники 
	private: System::Collections::Generic::List<Color> ^colors; //список цветов многоугольников



	private:
		/// <summary>
		/// Требуется переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Обязательный метод для поддержки конструктора - не изменяйте
		/// содержимое данного метода при помощи редактора кода.
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
			this->openFileDialog->FileName = L"openFileDialog2";
			this->openFileDialog->Filter = L"Текстовые файлы (*.txt)|*.txt|Все файлы (*.*)|*.*";
			this->openFileDialog->Title = L"Открыть файл";
			// 
			// btnOpen
			// 
			this->btnOpen->Location = System::Drawing::Point(12, 12);
			this->btnOpen->Name = L"btnOpen";
			this->btnOpen->Size = System::Drawing::Size(75, 23);
			this->btnOpen->TabIndex = 0;
			this->btnOpen->Text = L"Открыть";
			this->btnOpen->UseVisualStyleBackColor = true;
			this->btnOpen->Click += gcnew System::EventHandler(this, &Form1::btnOpen_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 262);
			this->Controls->Add(this->btnOpen);
			this->KeyPreview = true;
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
				 if(this->ClientRectangle.Height == 0)
					return;
				 Bitmap^ image1 = gcnew Bitmap( this->ClientRectangle.Width
					, this->ClientRectangle.Height
					);
				 Graphics^ g = Graphics::FromImage(image1);
				g->Clear(Color::White);
				Pen^ bPen = gcnew Pen(Color::Black);
				Pen^ rectPen = gcnew Pen(Color::Red);
				bPen->Width = 4;
				rectPen->Width = 2;
				g->DrawRectangle(rectPen, Wcx, top, Wx, Wy);
				
				mat3D V, U, UV, R, F3D;
				mat F;

				LookAt(eye_, center_, up_, V);
				if(prOrtho)
				{
					float vy = 2 * near_ * tan(fovy * 3.1415 / 180 / 2);
					float vx = vy * aspect;
					Ortho(vx, vy, near_, far, U);
				}
				else
				{
					Perspective(fovy_, aspect, near_, far, U);
				}
				
				point LT, RB;//левая верхняя и правая нижняя точки 
				LT.x = this->left;
				LT.y = this->top;
				RB.x = Form::ClientRectangle.Width - right;
				RB.y = Form::ClientRectangle.Height - bottom;
				
				times(U, V, UV);
				times(UV, T3d, R);
				polygon ^poly = gcnew polygon(0);
				
				System::Collections::Generic::List<polygon3D^> ^buferpolygons = gcnew System::Collections::Generic::List<polygon3D^>(0);
				buferpolygons->Clear();

				frame(2, 2, -1, -1, Wx, Wy, Wcx, Wcy, F);
				frame3D(2, 2, -1, -1, Wx, Wy, Wcx, Wcy, F3D);

				for (int i = 0; i < polygons.Count; i++) 
				{
					poly->Clear(); //для отделения многоугольников друг от друга
					polygon3D ^poly3D = gcnew polygon3D(0);
					polygon3D ^p = polygons[i];
					Pen^ pen = gcnew Pen(colors[i]);
					if(usesbuf)
					{
						for(int j = 0; j < p->Count; j++)
						{
							 vec3D a, res, fin;
							 point2vec(p[j], a);
							 timesMatVec(R, a, res);
							 timesMatVec(F3D, res, fin);
							 point3D fp;
							 vec2point(fin, fp);
							 poly3D->Add(fp);
						}
						buferpolygons->Add(poly3D);
					}
					else
					{
						for(int j = 0; j < p->Count; j++)
						 {
							 vec3D a, res, fin;
							 point2vec(p[j], a);
							 timesMatVec(R, a, res);
							

							 vec b, fb;
							 point3D fp;
							 vec2point(res, fp);
							 point pb;
							 set(fp, pb);
							 point2vec(pb, b);
							 timesMatVec(F, b, fb);
							 point p;
							 vec2point(fb, p);
							 poly->Add(p);
						 }
						 poly = Pclip(poly, LT, RB);
						 if(poly->Count != 0)
						 {
							 point a, b;
							 a = poly[poly->Count - 1];
							 for (int j = 0; j < poly->Count; j++){
									b = poly[j];
									g ->DrawLine(pen, a.x, a.y, b.x, b.y);
									a = b;
							 }
						 }
					 }
					
				}
				if(usesbuf)
					Sbufer(buferpolygons, image1, colors, Wx, Wy, left, top);

				g = e->Graphics;
				g->DrawImage(image1,0,0);
				delete image1;
			 }

	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
				unit(T);
				unit(T3d);

				top = 50;
				left = 60;
				right = 60;
				bottom = 50;

			    Wcx = left;
				Wcy = Form::ClientRectangle.Height - bottom;
				Wx = Form::ClientRectangle.Width - left - right;
				Wy = Form::ClientRectangle.Height - top - bottom;

				prOrtho = false;
				alpha = 5 * 3.1415 / 180;
				aspect = Wx/Wy;
				colors = gcnew System::Collections::Generic::List<Color>(0);
				usesbuf = false;
			 }
	private: System::Void btnOpen_Click(System::Object^  sender, System::EventArgs^  e) {
				 if ( this->openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
				{
					wchar_t fileName[1024];
					for (int i = 0; i < openFileDialog->FileName->Length; i++)
						fileName[i] = openFileDialog->FileName[i];
					fileName[openFileDialog->FileName->Length] = '\0';
					
					std::ifstream in;
					in.open(fileName);
					if ( in.is_open() ) 
					{
						lines.Clear();
						polygons.Clear();
						colors->Clear();
						std::string str;
						getline (in, str);
						Color cc = Color::FromArgb(0, 0, 0);
						while (in) 
						{
							if ((str.find_first_not_of(" \t\r\n") != std::string::npos)&& (str[0] != '#')) 
							{
								std::stringstream s(str);
								line l;
								std::string linename;
								std::string cmd;
								s >> cmd;
								if (cmd == "screen")
									{
										 float fo, n, f;
										 s >> fo >> n >>f;
										 fovy = fo;
										 near = n;
										 far = f;
									}
								if (cmd == "triangle")
								{
									 point3D a, b, c;
									 polygon3D^ p = gcnew polygon3D(0);
									 p->Clear();
									 s >> a.x >> a.y >> a.z >> b.x >> b.y >> b.z >> c.x >> c.y >> c.z;
									 p->Add(a); p->Add(b); p->Add(c);
									 
									 polygons.Add(p);
									 colors->Add(cc);
									
								}

								if (cmd == "color")
								{
									int r;
									int g;
									int b;
									s >> r >> g >> b;
									cc = Color::FromArgb(r, g, b);
								}

								if( cmd == "lookat" ) {
								    point3D e, c, u;
									s >> e.x >> e.y >> e.z >> c.x >> c.y >> c.z >> u.x >> u.y >> u.z;
									up.x = u.x; 
									up.y = u.y; 
									up.z = u.z;
									eye.x = e.x;
									eye.y = e.y;
									eye.z = e.z;

									center.x = c.x;
									center.y = c.y;
									center.z = c.z;
									LookAt(center, eye, up, T3d);
																	
									vec3D neye, a;
									point2vec(eye, neye);
									timesMatVec(T3d, neye, a);
									point3D neyep;
									vec2point(a, neyep);

									eye_.x = neyep.x;
									eye_.y = neyep.y;
									eye_.z = neyep.z;
									up_.x = 0;
									up_.z = 0;
									up_.y = 1;
									center_.x = 0;
									center_.y = 0;
									center_.z = 0;
								 }
				
							}
						getline (in, str);
						}
					}
					frame(Vx, Vy, Vcx, Vcy, Wx, Wy, Wcx, Wcy, T);
					
					near_ = near;
					fovy_ = fovy;

					this->Refresh();
					}
				}
	private: System::Void Form1_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
				Rectangle rec = Form::ClientRectangle;
				mat3D R, T1;
				unit(R);
				point3D x, z;
				x.x = 1;
				x.y = 0;
				x.z = 0;

				z.x = 0;
				z.y = 0;
				z.z = 1;

				switch(e->KeyCode) {
				
				case Keys::W:
						rotate(x, alpha, R);
						break;
					case Keys::S:
						rotate(x, -alpha, R);
						break;
					case Keys::A:
						rotate(up_, alpha, R);
						break;
					case Keys::D:
						rotate(up_, -alpha, R);
						break;
					
					case Keys::E :
						rotate(z, -alpha, R);
						break;
					case Keys::Q :
						rotate(z, alpha, R);
						break;
					
					case Keys::P :
						if(this->prOrtho == true)
							prOrtho = false;
						else
							prOrtho = true;
						break;
					case Keys::F :
						if(this->usesbuf == true)
							usesbuf = false;
						else
							usesbuf = true;
						break;
					case Keys::Escape:
						near_ = near;
						fovy_ = fovy;
						alpha = 5 * 3.1415 / 180;;

						LookAt(center, eye, up, T3d);
									
						vec3D neye, a;
						point2vec(eye, neye);
						timesMatVec(T3d, neye, a);
						point3D neyep;
						vec2point(a, neyep);

						eye_.x = neyep.x;
						eye_.y = neyep.y;
						eye_.z = neyep.z;
						up_.x = 0;
						up_.z = 0;
						up_.y = 1;
						center_.x = 0;
						center_.y = 0;
						center_.z = 0;
						prOrtho = false;
						break;
					
					case Keys::Z :
						near_ = near_ + 0.1;
						break;
					case Keys::X :
						near_ = near_ - 0.1;
						if(near_ <= 0.1)
							near_ = 0.1;
						break;
					case Keys::C :
						fovy_ = fovy_ + 1;
						break;
					case Keys::V :
						fovy_ = fovy_ - 1;
						break;
					case Keys::O :
						alpha = alpha * 1.1;
						break;
					case Keys::L :
						alpha = alpha / 1.1;
						break;	
				default:
					unit(R);
					}

				 times(R, T3d, T1);
				 set(T1, T3d);//домножим матрицу T слева на R
				 this->Refresh();

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

			 aspect = Wx/Wy;
			 
			 this->Refresh();

		 }
};
}

