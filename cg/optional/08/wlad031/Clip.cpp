#pragma once
#include "stdafx.h"
#include <algorithm>

#include "Transform.h"

using namespace std;

bool clip(float& x1, float& y1, float& x2, float& y2, polygon^ fw) {
	float tmin = 0;
	float tmax = 1;

	int n = fw->Count;
	bool visible = true;

	point A = fw[n - 1];
	point B;

	point tmpP1, tmpP;
	vec tmpV;

	for (int i = 0; i < n; i++) {
		B = fw[i];

		float Pi, Qi0;
		vec Fi, Ni;
		vec p, p1;

		point2vec(A, Fi);
		normal(A, B, Ni);

		point2vec(point(x2 - x1, y2 - y1), p);
		point2vec(point(x1, y1), p1);
		
		Pi = multSkalar(p, Ni);

		sub(p1, Fi, tmpV);
		Qi0 = multSkalar(tmpV, Ni);

		if (Pi == 0) {
			if (Qi0 < 0) {
				visible = false;
				break;
			}
		} else {
			if (Pi > 0) {
				tmin = max(tmin, -Qi0 / Pi);
			} else {
				tmax = min(tmax, -Qi0 / Pi);
			}

			if (tmin > tmax) {
				visible = false;
				break;
			}
		}

		A = B;
	}


	if (visible) {
		point p1s, p2s;
		point p1 = point(x1, y1), p2 = point(x2, y2);
		
		sub(p2, p1, tmpP);
		mult(tmpP, tmin, tmpP1);
		sum(p1, tmpP1, p1s);
		mult(tmpP, tmax, tmpP1);
		sum(p1, tmpP1, p2s);

		x1 = p1s.x;
		y1 = p1s.y;
		x2 = p2s.x;
		y2 = p2s.y;

		return true;
	}

	return false;
}