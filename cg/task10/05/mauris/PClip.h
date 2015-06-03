polygon^ Pclip (polygon^ P, point Pmin, point Pmax);
void Pfill (polygon^ P, System::Drawing::Bitmap^ image, System::Drawing::Color C);
void RenderBSP(System::Collections::Generic::List<polygon3D^> ^polygons, System::Collections::Generic::List<System::Drawing::Color> ^colors, mat F, mat3D U, point r1, point r2, System::Drawing::Bitmap^ image);
