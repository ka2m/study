#pragma once


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
			this->btnOpen->Location = System::Drawing::Point(283, 407);
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
			this->ClientSize = System::Drawing::Size(624, 442);
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
				 Graphics^ g = e->Graphics;
				 Pen^ blackPen = gcnew Pen(Color::Black);
				 g->Clear(Color::White);
				 blackPen->Width = 4;
				 for(int i = 0; i < lines.Count; i++){
					 vec A, B;
					 point2vec(lines[i].start, A);
					 point2vec(lines[i].end, B);
					 vec A1, B1;
					 timesMatVec(T, A, A1);
					 timesMatVec(T, B, B1);
					 point a, b;
					 vec2point(A1, a);
					 vec2point(B1, b);
					 g->DrawLine(blackPen, a.x, a.y, b.x, b.y);
				 }
			 }
	private: System::Void Form1_Resize(System::Object^  sender, System::EventArgs^  e) {
				 this->Refresh();
			 }
	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
				 lines.Clear();
				 unit(T);

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
						 unit(T);
						 unit(LoadMat);
						 mat S, L, Mov, LS;
						 
						 move(0.f, float(Form::ClientRectangle.Height), Mov);
						 scale(15, 15, S);
						 reflectVertical(L);

						 times(S, L, LS);
						 times(Mov, LS, LoadMat);
						
						 std::string str;
						 getline(in, str);
						 while (in) {
							 if ((str.find_first_not_of(" \t\r\n") != std::string::npos) && (str[0] != '#')) {
								 std::stringstream s(str);
								 line l;
								 std::string linename;

								 s >> l.start.x >> l.start.y >> l.end.x >> l.end.y >> linename;
								 l.name = gcnew String(linename.c_str());
								 vec A, B;
								 point2vec(l.start, A);
								 point2vec(l.end, B);
								 vec A1, B1;
								 timesMatVec(LoadMat, A, A1);
								 timesMatVec(LoadMat, B, B1);
								 point a, b;
								 vec2point(A1, a);
								 vec2point(B1, b);
								 l.start = a;
								 l.end = b;
									
								 lines.Add(l);
							 }
							 getline(in, str);
						 }
					 }
					 this->Refresh();					
				 }
			 }
	private: System::Void Form1_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
				 mat R, T1;
				 mat Center, nCenter, Trans, Trm;

				 switch(e->KeyCode) {
					case Keys::W: 
						move(0.f, -1.f, R);
						break;
					case Keys::S:
						move(0.f, 1.f, R);
						break;
					case Keys::A:
						move(-1.f, 0.f, R);
						break;
					case Keys::D:
						move(1.f, 0.f, R);
						break;

					case Keys::E :
						rotate(0.05f, R);
						break;
					case Keys::Q :
						rotate(-0.05f, R);
						break;

					case Keys::Z :
						scale(1.f/1.1f, 1.f/1.1f, R);
						break;					case Keys::X :
						scale(1.1f/1.f, 1.1f/1.f, R);
						break;					case Keys::T: 
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
						break;					case Keys::U:						move(-float(Form::ClientRectangle.Width/2), 0.f, Center);						move(float(Form::ClientRectangle.Width/2), 0.f, nCenter);						unit(R);						reflectHorizontal(Trans);						times(Trans, Center, Trm);						times(nCenter, Trm, R);						break;					case Keys::J:						move(0.f, -float(Form::ClientRectangle.Height/2), Center);						move(0.f, float(Form::ClientRectangle.Height/2), nCenter);						unit(R);						reflectVertical(Trans);						times(Trans, Center, Trm);						times(nCenter, Trm, R);						break;					case Keys::R:						move(-float(Form::ClientRectangle.Width/2), -float(Form::ClientRectangle.Height/2), Center);						move(float(Form::ClientRectangle.Width/2), float(Form::ClientRectangle.Height/2), nCenter);						unit(R);						rotate(-0.05f, Trans);						times(Trans, Center, Trm);						times(nCenter, Trm, R);						break;					case Keys::Y:						move(-float(Form::ClientRectangle.Width/2), -float(Form::ClientRectangle.Height/2), Center);						move(float(Form::ClientRectangle.Width/2), float(Form::ClientRectangle.Height/2), nCenter);						unit(R);						rotate(0.05f, Trans);						times(Trans, Center, Trm);						times(nCenter, Trm, R);						break;					case Keys::C:						move(-float(Form::ClientRectangle.Width/2), -float(Form::ClientRectangle.Height/2), Center);						move(float(Form::ClientRectangle.Width/2), float(Form::ClientRectangle.Height/2), nCenter);						unit(R);						scale(1.f/1.1f, 1.f/1.1f, Trans);						times(Trans, Center, Trm);						times(nCenter, Trm, R);						break;					case Keys::V:						move(-float(Form::ClientRectangle.Width/2), -float(Form::ClientRectangle.Height/2), Center);						move(float(Form::ClientRectangle.Width/2), float(Form::ClientRectangle.Height/2), nCenter);						unit(R);						scale(1.1f/1.f, 1.1f/1.f, Trans);						times(Trans, Center, Trm);						times(nCenter, Trm, R);						break;					case Keys::I:						move(-float(Form::ClientRectangle.Width/2), 0.f, Center);						move(float(Form::ClientRectangle.Width/2), 0.f, nCenter);						unit(R);						scale(1.f/1.1f, 1.f, Trans);						times(Trans, Center, Trm);						times(nCenter, Trm, R);						break;					case Keys::O:						move(-float(Form::ClientRectangle.Width/2), 0.f, Center);						move(float(Form::ClientRectangle.Width/2), 0.f, nCenter);						unit(R);						scale(1.1f/1.f, 1.f, Trans);						times(Trans, Center, Trm);						times(nCenter, Trm, R);						break;					case Keys::K:						move(0.f, -float(Form::ClientRectangle.Height/2), Center);						move(0.f, float(Form::ClientRectangle.Height/2), nCenter);						unit(R);						scale(1.f, 1.f/1.1f, Trans);						times(Trans, Center, Trm);						times(nCenter, Trm, R);						break;					case Keys::L:						move(0.f, -float(Form::ClientRectangle.Height/2), Center);						move(0.f, float(Form::ClientRectangle.Height/2), nCenter);						unit(R);						scale(1.f, 1.1f/1.f, Trans);						times(Trans, Center, Trm);						times(nCenter, Trm, R);						break;					case Keys::Escape:						unit(T);						unit(R);						break;
					default: 
						unit(R);
				  }
				 times(R, T, T1);
				 set(T1, T);
				 this->Refresh();

			 }
};
}

