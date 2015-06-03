#pragma once
#include "stdafx.h"
#include "Transform.h"

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