polygon^ PClip (polygon^ P, point Pmin, point Pmax);


void Painter(System::Collections::Generic::List<polygon3D^> ^polygons, 
			 System::Collections::Generic::List<System::Drawing::Color> ^colors, 
			 mat F, 
			 mat3D U, 
			 point min, 
			 point max, 
			 System::Drawing::Bitmap^ image);