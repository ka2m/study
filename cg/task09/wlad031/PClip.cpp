#pragma once
#include "stdafx.h"

#include "Transform.h"

using namespace std;

polygon^ Pclip (polygon^ P, point min, point max) {
	polygon^ P1 = gcnew polygon(0);

	int k = 0;

	point p1 = P[P->Count - 1];
	point p2;

	point in, out, tin, tout;
	float t1in, t1out, t2in, t2out;

	while (k < P->Count) {
		p2 = P[k];

		float dx = p2.x - p1.x,
			  dy = p2.y - p1.y;

		if (dx > 0 || dx == 0 && p1.x > max.x) {
			in.x = min.x;
			out.x = max.x;
		} else {
			in.x = max.x;
			out.x = min.x;
		}

		if (dy > 0 || dy == 0 && p1.y > max.y) {
			in.y = min.y;
			out.y = max.y;
		} else {
			in.y = max.y;
			out.y = min.y;
		}

		if (dx != 0) {
			tout.x = (out.x - p1.x) / dx;
		} else if (p1.x >= min.x && p1.x <= max.x) {
			tout.x = float::MaxValue;
		} else {
			tout.x = float::MinValue;
		}

		if (dy != 0) {
			tout.y = (out.y - p1.y) / dy;
		} else if (p1.y >= min.y && p1.y <= max.y) {
			tout.y = float::MaxValue;
		} else {
			tout.y = float::MinValue;
		}
		

		if (tout.x < tout.y) {
			t1out = tout.x;
			t2out = tout.y;
		} else {
			t1out = tout.y;
			t2out = tout.x;
		}

		if (t2out > 0) {

			if (dx != 0) {
				tin.x = (in.x - p1.x) / dx;
			} else {
				tin.x = float::MinValue;
			}

			if (dy != 0) {
				tin.y = (in.y - p1.y) / dy;
			} else {
				tin.y = float::MinValue;
			}

			if (tin.x < tin.y) {
				t2in = tin.y;
			} else {
				t2in = tin.x;
			}

			if (t1out < t2in) {

				if (t1out > 0 && t1out <= 1) {
					if (tin.x < tin.y) {
						P1->Add(point(out.x, in.y));
					} else {
						P1->Add(point(in.x, out.y));
					}
				}

			} else if (t1out > 0 && t2in <= 1) {

				if (t2in >= 0) {
					if (tin.x > tin.y) {
						P1->Add(point(in.x, p1.y + tin.x * dy));
					} else {
						P1->Add(point(p1.x + tin.y * dx, in.y));
					}
				}

				if (t1out <= 1) {
					if (tout.x < tout.y) {
						P1->Add(point(out.x, p1.y + tout.x * dy));
					} else {
						P1->Add(point(p1.x + tout.y * dx, out.y));
					}
				} else {
					P1->Add(p2);
				}
			}

			if (t2out > 0 && t2out <= 1) {
				P1->Add(out);
			}
		}

		k = k + 1;
		p1 = p2;
	}

	return P1;
}