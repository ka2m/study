#pragma once
#include "stdafx.h"
#include "Transform.h"

const float FMIN = float::MinValue;
const float FMAX = float::MaxValue;

int signum(float d)
{
	if(d < -0.0001)
		return -1;
	else if(d > 0.0001)
		return 1;
	return 0;
}


value struct polygonBSP {
	polygon3D ^L;
	System::Drawing::Color C;
	float a, b, c, d;
};

value struct Node {
	Node ^left, ^right;
	polygonBSP ^nodePolygon;
};

polygon^ PClip (polygon^ P, point Pmin, point Pmax) {
	polygon^ P1 = gcnew polygon(0);

	point p1 = P[P->Count - 1];

	float xin, xout, yin, yout;
	float t1in, t1out, t2in, t2out;
	float txin, tyin, txout, tyout;
	float t1xout, t2xout, t1yout, t2yout;
	for (int i = 0; i < P->Count; i++) {
		point p2 = P[i];

		float dx = p2.x - p1.x, dy = p2.y - p1.y;

		if ((dx > 0) || ((!dx) && (p1.x > Pmax.x))) { xin = Pmin.x; xout = Pmax.x; } 
		else {xin = Pmax.x; xout = Pmin.x;}

		if ((dy > 0) || ((!dy) && (p1.y > Pmax.y))) { yin = Pmin.y; yout = Pmax.y; }
		else { yin = Pmax.y; yout = Pmin.y;	}

		if (dx) txout = (xout - p1.x) / dx;
		else if (p1.x >= Pmin.x && p1.x <= Pmax.x) txout = FMAX;
		else txout = FMIN;

		if (dy != 0) tyout = (yout - p1.y) / dy;
		else if (p1.y >= Pmin.y && p1.y <= Pmax.y) tyout = FMAX;
		else tyout = FMIN;

		if (txout < tyout) { t1out = txout;	t2out = tyout;} 
		else { t1out = tyout; t2out = txout; }

		if (t2out > 0) {

			if (dx) txin = (xin - p1.x) / dx;
			else txin = FMIN;

			if (dy) tyin = (yin - p1.y) / dy;
			else tyin = FMIN;

			if (txin < tyin) t2in = tyin;
			else t2in = txin;

			if (t1out < t2in) {
				if (t1out > 0 && t1out <= 1) {
					if (txin < tyin) P1->Add(point(xout, yin));
					else P1->Add(point(xin, yout));
				}
			} else if (t1out > 0 && t2in <= 1) {
				if (t2in >= 0) {
					if (txin > tyin) P1->Add(point(xin, p1.y + txin * dy));
					else P1->Add(point(p1.x + tyin * dx, yin));
				}

				if (t1out <= 1) {
					if (txout < tyout) P1->Add(point(xout, p1.y + txout * dy));
					else P1->Add(point(p1.x + tyout * dx, yout));
				} else P1->Add(p2);
			}

			if (t2out > 0 && t2out <= 1) P1->Add(point(xout, yout));
		}

		p1 = p2;
	}

	return P1;
}

void InitializePolygon(polygon3D ^p, polygonBSP ^nodePolygon, System::Drawing::Color color)
{
	if(p->Count < 3)
		return;
	
	nodePolygon->C = color;
	nodePolygon->L = p;
	
	nodePolygon->a = p[1].y * p[2].z + p[0].y*p[1].z + p[0].z*p[2].y - p[0].y*p[2].z - p[1].z*p[2].y - p[0].z * p[1].y;
	nodePolygon->b = p[0].x*p[2].z + p[1].z*p[2].x + p[0].z*p[1].x - p[1].x*p[2].z - p[0].x*p[1].z - p[0].z*p[2].x;
	nodePolygon->c = p[0].x*p[1].y + p[0].y*p[2].x + p[1].x*p[2].y - p[0].y*p[1].x - p[0].x*p[2].y - p[1].y*p[2].x;
	nodePolygon->d = -(p[0].x*p[1].y*p[2].z + p[0].y*p[1].z*p[2].x + p[0].z*p[1].x*p[2].y - p[0].y*p[1].x*p[2].z - p[0].x*p[1].z*p[2].y - p[0].z*p[1].y*p[2].x);
}

void draw(polygonBSP ^poly, mat F, mat3D U, point min, point max, System::Drawing::Bitmap^ image) {
	System::Drawing::Graphics^ g = System::Drawing::Graphics::FromImage(image);
	
	polygon3D^ __poly = poly->L;
	polygon^ p1 = gcnew polygon(0);
	System::Drawing::Brush^ drawBrush = gcnew System::Drawing::SolidBrush(poly->C);

	point a1, a2;
	point3D A;					
	vec b1, b2;
	vec3D B1, B2;

	for(int j = 0; j<__poly->Count; j++) {
		point2vec(__poly[j], B1);
		timesMatVec(U, B1, B2);
		vec2point(B2, A);
		set(A, a1);

		point2vec(a1, b1);
		timesMatVec(F, b1, b2);
		vec2point(b2, a1);
		p1->Add(a1);
	}
	p1 = PClip(p1, min, max);
	if(!p1->Count)
		return;
	cli::array<System::Drawing::PointF> ^arrpoly = gcnew  cli::array<System::Drawing::PointF>(p1->Count);
	point a;
	for (int j = 0; j < p1->Count; j++)
	{
			a = p1[j];
			arrpoly[j] = System::Drawing::PointF(a.x, a.y);
	}
	 
	 
	g->FillPolygon(drawBrush, arrpoly);
}


void DrawBSPTree(Node^ T, mat F, mat3D T1, point min, point max, System::Drawing::Bitmap^ image)
{
	if(T->nodePolygon == nullptr)
		return;
	if(T->nodePolygon->d < 0)
	{
		DrawBSPTree(T->right, F, T1, min, max, image);
		draw(T->nodePolygon, F, T1, min, max, image);
		DrawBSPTree(T->left, F, T1, min, max, image);
	}
	else
	{
		DrawBSPTree(T->left, F, T1, min, max, image);
		draw(T->nodePolygon, F, T1, min, max, image);
		DrawBSPTree(T->right, F, T1, min, max, image);
	}
}

void VertexCount(polygonBSP^ P, polygonBSP^ Pt, polygonBSP^ Ppos, polygonBSP^ Pneg, int& posCount, int& negCount)
{
	
	polygon3D^ Lpos = gcnew polygon3D(0);
	polygon3D^ Lneg = gcnew polygon3D(0);
	
	point3D A, B;
	A = P->L[P->L->Count-1];
	int PosCount = 0;
	int NegCount = 0;
	bool intersectionVertex = false;
	int ZeroCount = 0;
	float SpacePartA = A.x * Pt->a + A.y * Pt->b + A.z * Pt->c + Pt->d;
	float SpacePartB;
	int ActiveSign = signum(SpacePartA);
	if(ActiveSign == 0)
		intersectionVertex = true;

	for(int i =0; i<P->L->Count; i++)
	{
		B = P->L[i];
		SpacePartB = B.x * Pt->a + B.y * Pt->b + B.z * Pt->c + Pt->d;
		int NewSign = signum(SpacePartB);
		if(NewSign == 0) {
			Lpos->Add(B);
			Lneg->Add(B);
			ZeroCount++;
			intersectionVertex = true;
		}
		else
		{
			if(NewSign != ActiveSign) {
				if(!intersectionVertex) {
					float t = SpacePartA/(SpacePartA - SpacePartB);

					point3D D;
					D.x = A.x + (B.x - A.x) * t;
					D.y = A.y + (B.y - A.y) * t;
					D.z = A.z + (B.z - A.z) * t;
					
					Lpos->Add(D);
					Lneg->Add(D);
					ZeroCount++;
				}
				ActiveSign = NewSign;
				intersectionVertex = false;
			}
			if(NewSign > 0){ Lpos->Add(B); posCount++;}
			else { Lneg->Add(B); negCount++;}
		}
		A = B;
		SpacePartA = SpacePartB;
	}
	Ppos->L = Lpos;
	Ppos->C = P->C;
	Ppos->a = P->a;
	Ppos->b = P->b;
	Ppos->c = P->c;
	Ppos->d = P->d;
	
	Pneg->L = Lneg;
	Pneg->C = P->C;
	Pneg->a = P->a;
	Pneg->b = P->b;
	Pneg->c = P->c;
	Pneg->d = P->d;
	posCount = posCount + ZeroCount;
	negCount = negCount + ZeroCount;
}

void PutPolygonToBSP(polygonBSP^ poly, Node^ T) {
	if(T->nodePolygon == nullptr) {
		T->nodePolygon = poly;
		T->left = gcnew Node();
		T->right = gcnew Node();
		return;
	}
	else {
		int posCount = 0;
		int negCount = 0;
		polygonBSP^ Ppos = gcnew polygonBSP();
		polygonBSP^ Pneg = gcnew polygonBSP();
		VertexCount(poly, T->nodePolygon, Ppos, Pneg, posCount, negCount);
		if(posCount > 0) PutPolygonToBSP(Ppos, T->left);
		if((posCount == 0)|| negCount > 0) PutPolygonToBSP(Pneg, T->right);
	}
}

void Painter(System::Collections::Generic::List<polygon3D^> ^polygons, System::Collections::Generic::List<System::Drawing::Color> ^colors, mat F, mat3D U, point min, point max, System::Drawing::Bitmap^ image) {
	Node ^node = gcnew Node();
	
	for(int i =0; i<polygons->Count; i++) {
		polygon3D ^polygon = polygons[i];
		polygonBSP ^nodePolygon = gcnew polygonBSP();
		InitializePolygon(polygon, nodePolygon, colors[i]);
		PutPolygonToBSP(nodePolygon, node);
	}
	DrawBSPTree(node, F, U, min, max, image);
}


