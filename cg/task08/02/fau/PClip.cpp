#pragma once
#include "stdafx.h"
#include <vector>
#include <algorithm>
#include "Transform.h"

#define SDC System::Drawing::Color

struct statusedPx {
	float x;
	bool ok;
};


const float FMIN = float::MinValue;
const float FMAX = float::MaxValue;

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

float min(float a, float b) { return a<b?a:b; }
float max(float a, float b) { return a>b?a:b; }
void swap(float& a, float& b) { float c = b; b = a; a = c; }

point centroid(polygon^ p) {
	float x = 0.0;
	float y = 0.0;
	for (int i = 0; i < p->Count; i++) {
		x += p[i].x;
		y += p[i].y;
	}

	return point(x / p->Count, y / p->Count);
}

void PFill (polygon^ P, System::Drawing::Bitmap^ image, System::Drawing::Color C) {
	System::Collections::Generic::Stack<point> s;
	bool isOk = true;
	point mid = centroid(P);
	s.Push(mid);

	while(s.Count) {
		point cur = s.Pop();
		if (cur.x < 0 || cur.x > image->Width || cur.y < 0 || cur.y > image->Height) continue;
		SDC curColor = image->GetPixel(cur.x, cur.y);
		if (curColor.ToArgb() == C.ToArgb()) continue;
		float xmin = cur.x;
		float xmax = cur.x;
		SDC cmin; 
		do {
			xmin--;
			if(xmin < 0) break;
			else  cmin = image->GetPixel(xmin, cur.y);
		} while (cmin.ToArgb() != C.ToArgb());
		SDC cmax;
		do {
			xmax++;
			if (cur.y < 0 || cur.y > image->Height || xmax < 0 || xmax > image->Width) break;
			else cmax = image->GetPixel(xmax, cur.y);
		} while (cmax.ToArgb() != C.ToArgb());
		for (float x = xmin + 1; x <= xmax - 1; x++) {
			image->SetPixel(x, cur.y, C);
			SDC cup = image->GetPixel(x, cur.y + 1);
			if (cup.ToArgb() != C.ToArgb()) s.Push(point(x, cur.y + 1));
			SDC cdn = image->GetPixel(x, cur.y - 1);
			if (cdn.ToArgb() != C.ToArgb()) s.Push(point(x, cur.y - 1));
		}	
	}
}