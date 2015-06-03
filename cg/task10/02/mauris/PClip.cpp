#pragma once
#include "stdafx.h"
#include "Transform.h"
#include <math.h>
#include <cfloat>
#include <algorithm>
#include <vector>

polygon ^Pclip(polygon^ P, point Pmin, point Pmax)
{
	polygon^ poly = gcnew polygon(0);
	
	point p1 = P[P->Count-1], p2;
	for(int k = 0; k<P->Count; k++)
	{
		p2 = P[k];
		point delta;
		point in, out, tout, tin;
		delta.x = p2.x - p1.x; //определяем направление отрезка
		delta.y = p2.y - p1.y;
		if(delta.x > 0 || delta.x == 0 && p1.x > Pmax.x)//какая из границ по Ox будет входящей и выходящей
		{
			in.x = Pmin.x;
			out.x = Pmax.x;
		}
		else
		{
			in.x = Pmax.x;
			out.x = Pmin.x;
		}
		if(delta.y >0 || delta.y == 0 && p1.y > Pmax.y)//какая из границ по Oy будет входящей и выходящей
		{
			in.y = Pmin.y;
			out.y = Pmax.y;
		}
		else
		{
			in.y = Pmax.y;
			out.y = Pmin.y;
		}

		if(delta.x != 0)
		{
			tout.x = (out.x - p1.x)/delta.x;
		}
		else
		{
			if(Pmin.x <= p1.x && p1.x <= Pmax.x)
				tout.x = FLT_MAX;
			else
				tout.x = -FLT_MAX;
		}
		
		if(delta.y != 0)
		{
			tout.y = (out.y - p1.y)/delta.y;
		}
		else
		{
			if(Pmin.y <= p1.y && p1.y <= Pmax.y)
				tout.y = FLT_MAX;
			else
				tout.y = -FLT_MAX;
		}
		float t1out, t2out;
		if(tout.x < tout.y)
		{
			t1out = tout.x;
			t2out = tout.y;
		}
		else
		{
			t1out = tout.y;
			t2out = tout.x;
		}
		float t2in;
		if(t2out > 0)
		{
			if(delta.x != 0)
				tin.x = (in.x - p1.x)/delta.x;
			else
				tin.x = -FLT_MAX;

			if(delta.y != 0)
				tin.y = (in.y - p1.y)/delta.y;
			else
				tin.y = -FLT_MAX;

			if(tin.x < tin.y)
				t2in = tin.y;
			else
				t2in = tin.x;
			if(t1out < t2in)
			{
				//i
				if(0 < t1out && t1out <= 1) //отрезок заходит в угловую область
				{
					point a;
					if(tin.x < tin.y)
					{
						a.x = out.x;
						a.y = in.y;
						poly->Add(a);
					}
					else
					{
						a.x = in.x;
						a.y = out.y;
						poly->Add(a);
					}
					
				}
			}
			else if(t1out > 0 && t2in <= 1)
			{
				//отрезок имеет видимую часть
				point a;
				if(t2in >= 0)
				{
					if(tin.x > tin.y)
					{
						a.x = in.x;
						a.y = p1.y + tin.x * delta.y;
					}
					else
					{
						a.x = p1.x + tin.y * delta.x;
						a.y = in.y;
					}
					poly->Add(a);
				}
				
				if(t1out <= 1)
				{
					if(tout.x < tout.y)
					{
						a.x = out.x;
						a.y = p1.y + tout.x * delta.y;
					}
					else
					{
						a.x = p1.x + tout.y * delta.x;
						a.y = out.y;
					}
					poly->Add(a);
				}
				else
				{
					poly->Add(p2);
				}
			}
			if(0 < t2out && t2out <= 1)
				poly->Add(out);
		}

		p1 = p2;
	}
	
	return poly;
}

struct L
{
	point start, end;
};

bool c(L x, L y)
{	
	return x.start.y < y.start.y;
}

struct Ael
{
	float x1, y2, dxy;
};

bool cA(Ael x, Ael y)
{
	if(x.x1 < y.x1)
		return 0;
	
	if(x.x1 > y.x1)
		return 1;
		
	if(x.dxy < y.dxy)
		return 0;
	
	if(x.dxy > y.dxy)
		return 1;
	
	return 0;
}

void Pgill(polygon^ P, System::Drawing::Bitmap^ image, System::Drawing::Color C)
{
	System::Drawing::Graphics^ g = System::Drawing::Graphics::FromImage(image);
	System::Drawing::Pen^ pen = gcnew System::Drawing::Pen(C);
	
	std::vector<L> S;
	point a, b;
	a = P[P->Count - 1];
	for (int j = 0; j < P->Count; j++)
	{
		b = P[j];
		L l;
		if(a.y <= b.y)
		{
			l.start = a;
			l.end = b;
		}
		else
		{
			l.start = b;
			l.end = a;
		}
		S.push_back(l);
		a = b;
	}
	std::sort(S.begin(), S.end(), c);
	point Pmin = S[0].start, Pmax = S[0].start;
	for(int i =0; i<S.size(); i++)
	{
		if(S[i].start.y < Pmin.y)
			Pmin = S[i].start;
		if(S[i].end.y < Pmin.y)
			Pmin = S[i].end;

		if(S[i].start.y > Pmax.y)
			Pmax = S[i].start;
		if(S[i].end.y > Pmax.y)
			Pmax = S[i].end;
	}
	//3
	int yt = Pmin.y;
	std::vector<Ael> AEL;

	//4
	while(true)
	{
		for(int i = 0; i<S.size(); i++)
		{
			if(int(S[i].start.y) == yt && int(S[i].start.y) != int(S[i].end.y))
			{
				Ael t;
				t.x1 = S[i].start.x;
				t.y2 = S[i].end.y;
				t.dxy = (S[i].end.x - S[i].start.x)/(S[i].end.y - S[i].start.y);
				AEL.push_back(t);
			}
			if(int(S[i].start.y) == yt && int(S[i].start.y) == int(S[i].end.y))
				g ->DrawLine(pen, int(S[i].start.x), int(S[i].start.y), int(S[i].end.x), int(S[i].end.y));
		}

		for(int i = 0; i<S.size(); i++)
		{
			if(int(S[i].start.y) == yt)
			{
				S.erase(S.begin() + i);
				i--;
			}
		}

		//7
		int ysnext = INT_MAX;
		for(int i =0; i<S.size(); i++)
		{
			if(int(S[i].start.y) < ysnext)
				ysnext = int(S[i].start.y);
		}
		//8
		float yaelnext = INT_MAX;
		int size = AEL.size();
		std::sort(AEL.begin(), AEL.end(), cA);
		for(int i =0; i<AEL.size(); i++)
		{
			if(AEL[i].y2 < yaelnext && int(AEL[i].y2) != yt)
				yaelnext = int(AEL[i].y2);
		}
		//9
		
		while(yt != ysnext)
		{
			//10
			if(AEL.size() != 0)
			{
				for(int i = 0; i < AEL.size()-1; i+=2)
				{
					g ->DrawLine(pen, int(AEL[i].x1), yt, int(AEL[i+1].x1), yt);
				}
			}
			//14
			
			for(int i =0; i < AEL.size(); i++)
			{
				AEL[i].x1 = AEL[i].x1 + AEL[i].dxy;
			}
			yt+=1;
			if( yt >= yaelnext)
			{
				std::vector<Ael>::iterator it;
				for(it = AEL.begin(); it!= AEL.end();)
				{
					if(int((*it).y2) <= yt)
						it = AEL.erase(it);
					else
						++it;
				}
				yaelnext = INT_MAX;
				
				for(int i =0; i<AEL.size(); i++)
				{
					if(AEL[i].y2 < yaelnext && int(AEL[i].y2) != yt)
						yaelnext = int(AEL[i].y2);
				}
			}
			if(yt > Pmax.y)
				return;
		}
	}
	return;
}


void showline(System::Drawing::Bitmap^ image, float Z[], int y0, float x1, float z1, float x2, float z2, System::Drawing::Color C, int Wx, int Wy, int Wcx, int Wcy)
{	
	if(y0 < Wcy || y0 > Wcy + Wy)
		return;
	if(x2 < Wcx || x1 > Wcx + Wx)
		return;
	float x = x1;
	float z = z1;
	float dz = (z2 - z1)/(x2 - x1);
	if(x < Wcx)
	{
		z = z + (Wcx - x) * dz;
		x = Wcx;
	}
	while(x <= x2 && x<= Wcx + Wx)
	{
		if(Z[int(x)] >= z && z >= -1)
		{
			Z[int(x)] = z;
			image->SetPixel(int(x), y0, C);
		}
		x = x+1;
		z = z + dz;
	}
}

struct L3D
{
	point3D start, end;
};

struct Ael3D
{
	int P;
	int r, g, b;
	float x1, z1, y2, dxy, dzy;
};


bool cA3D(Ael3D x, Ael3D y)
{
	if(x.P < y.P)
		return 0;
	
	if(x.P > y.P)
		return 1;

	if(x.x1 < y.x1)
		return 0;
	
	if(x.x1 > y.x1)
		return 1;
		
	if(x.dxy < y.dxy)
		return 0;
	
	if(x.dxy > y.dxy)
		return 1;
	
	return 0;
}

void Sbufer(System::Collections::Generic::List<polygon3D^> ^polygons, System::Drawing::Bitmap^ image, System::Collections::Generic::List<System::Drawing::Color> ^colors, int Wx, int Wy, int Wcx, int Wcy)
{
	System::Drawing::Graphics^ g = System::Drawing::Graphics::FromImage(image);
	System::Drawing::Pen^ bgpen = gcnew System::Drawing::Pen(System::Drawing::Color::Black);
	System::Collections::Generic::List<System::Drawing::Color> fcolors;
	for(int i =0; i<colors->Count; i++)
	{
		fcolors.Add(colors[i]);
	}
	
	int ypnext = Wcy + Wy + 1;
	for(int i =0; i<polygons->Count; i++)
	{
		int ypmin = Wcy + Wy + 1, ypmax = Wcy - 1;
		polygon3D^ P = polygons[i];
		
		for (int j = 0; j < P->Count; j++)
		{
			if(ypmin > P[j].y)
				ypmin = P[j].y;
			if(ypmax < P[j].y)
				ypmax = P[j].y;	
		}

		if(ypmin > Wcy + Wy || ypmax < Wcy)
		{
			polygons->Remove(polygons[i]);
			fcolors.Remove(fcolors[i]);
			i--;
		}
		else
		{
			if(ypnext > ypmin)
				ypnext = ypmin;
		}
	}
	
	int yt = ypnext;
	int yaplnext = 0;
	int yaelnext = 0;
	
	float *Z = new float[image->Width];
	for(int iz = 0; iz < image->Width; iz++)
		Z[iz] = FLT_MAX;

	System::Collections::Generic::List<polygon3D^> APL;
	System::Collections::Generic::List<System::Drawing::Color> APLcolors;
	std::vector<Ael3D> AEL;
	AEL.clear();

	while(yt <= Wcy + Wy)
	{
		//1
		if(yt == ypnext)
		{
			int ypnextn = Wcy + Wy + 1;
			for(int i =0; i<polygons->Count; i++)
			{
				int ypmin = Wcy + Wy + 1, ypmax = Wcy - 1;
				polygon3D^ P = polygons[i];
				
				for (int j = 0; j < P->Count; j++)
				{
					if(ypmin > P[j].y)
						ypmin = P[j].y;
					if(ypmax < P[j].y)
						ypmax = P[j].y;	
				}

				if(ypmin == yt)
				{
					APL.Add(polygons[i]);
					APLcolors.Add(fcolors[i]);
					fcolors.Remove(fcolors[i]);
					polygons->Remove(polygons[i]);
					i--;
				}
				else 
					if(ypnextn > ypmin)
						ypnextn = ypmin;

				
			}
			yaplnext = yt;
			if(polygons->Count == 0)
				ypnext = INT_MAX;
			else
				ypnext = ypnextn;
		}
		
		//2
		if(yt >= Wcy)
		{
			//g->DrawLine(bgpen, Wcx, yt, Wcx + Wx, yt);
			for(int iz = 0; iz < image->Width; iz++)
				Z[iz] = FLT_MAX;
		}
		
		if(yt == yaplnext)
		{
			int yaplnextn = INT_MAX;
			int yaelnextn = INT_MAX;
			for(int i =0; i<APL.Count; i++)
			{
				std::vector<L3D> S;
				polygon3D^ P = APL[i];
				point3D a, b;
				a = P[P->Count - 1];
				for (int j = 0; j < P->Count; j++)
				{
					b = P[j];
					L3D l;
					if(a.y < b.y)
					{
						l.start = a;
						l.end = b;
					}
					
					if(a.y == b.y)
					{
						if(a.x <= b.x)
						{
							l.start = b;
							l.end = a;
						}
						else
						{
							l.start = b;
							l.end = a;
						}
					}
					if(a.y > b.y)
					{
						l.start = b;
						l.end = a;
					}
					S.push_back(l);
					if(int(l.start.y) == yt && int(l.start.y) != int(l.end.y))
					{
						Ael3D t;
						t.P = i;
						int color = APLcolors[i].ToArgb();
						t.r = color >> 16 & 0xff;
						t.g = color >> 8 & 0xff;
						t.b = color & 0xff;

						t.x1 = l.start.x;
						t.z1 = l.start.z;
						t.y2 = l.end.y;
						t.dxy = (l.end.x - l.start.x)/(l.end.y - l.start.y);
						t.dzy = (l.end.z - l.start.z)/(l.end.y - l.start.y);
						AEL.push_back(t);						
					}
					if(yt >= Wcy && int(l.start.y) == yt && int(l.start.y) == int(l.end.y))
					{
						showline(image, Z, yt, l.start.x, l.start.z, l.end.x, l.end.z, APLcolors[i], Wx, Wy, Wcx, Wcy);
					}
					if(int(l.start.y) > yt && yaplnextn > (int)l.start.y)
					{
						int y = l.start.y;
						yaplnextn = l.start.y;
					}
					a = b;
				}

			}
			yaplnext = yaplnextn;
			std::sort(AEL.begin(), AEL.end(), cA3D);
			for(int i =0; i<AEL.size(); i++)
			{
				if(int(AEL[i].y2) < yaelnext && int(AEL[i].y2) != yt)
					yaelnext = int(AEL[i].y2);
			}
		}
		if(yt >= Wcy)
		{
			if(AEL.size() != 0)
			{
				for(int i = 0; i < AEL.size()-1; i+=2)
				{
					showline(image, Z, yt, AEL[i+1].x1, AEL[i+1].z1, AEL[i].x1, AEL[i].z1, System::Drawing::Color::FromArgb(AEL[i].r, AEL[i].g, AEL[i].b), Wx, Wy, Wcx, Wcy);
				}
			}
		}
		for(int i =0; i < AEL.size(); i++)
		{
			AEL[i].x1 = AEL[i].x1 + AEL[i].dxy;
			AEL[i].z1 = AEL[i].z1 + AEL[i].dzy;
		}
		yt = yt + 1;
		if(yt >= yaelnext)
		{
			std::vector<Ael3D>::iterator it;
			for(it = AEL.begin(); it!= AEL.end();)
			{
				if(int((*it).y2) <= yt)
					it = AEL.erase(it);
				else
					++it;
			}
			yaelnext = INT_MAX;
			for(int i =0; i<AEL.size(); i++)
			{
				if(AEL[i].y2 < yaelnext && int(AEL[i].y2) != yt)
					yaelnext = int(AEL[i].y2);
			}
		}
		
	}
		
	delete Z;
}

