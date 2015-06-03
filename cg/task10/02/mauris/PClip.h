polygon ^Pclip(polygon^ P, point Pmin, point Pmax);
void Pgill(polygon^ P, System::Drawing::Bitmap^ image, System::Drawing::Color C);
void Sbufer(System::Collections::Generic::List<polygon3D^> ^polygons, System::Drawing::Bitmap^ image, System::Collections::Generic::List<System::Drawing::Color> ^colors, int Wx, int Wy, int Wcx, int Wcy);