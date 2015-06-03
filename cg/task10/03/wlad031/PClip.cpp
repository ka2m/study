#include "stdafx.h"

#include "Transform.h"

#define BACKGROUND_COLOR Color::White

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

/**
 * Watkins algorithm
 */

using namespace System::Collections::Generic;
using namespace System::Drawing;
using namespace std;

bool HasIntersection(float xleft, float xright, int& xint, float yt, List<APLelem>^ APL) {
	for (int j = 0; j < APL->Count; j++) {
		APLelem curJ = APL[j];

		float zjleft, zjright;

		if (curJ.active) {
			zjleft  = - (curJ.a * xleft  + curJ.b * yt + curJ.d) / curJ.c;
			zjright = - (curJ.a * xright + curJ.b * yt + curJ.d) / curJ.c;
		}

		for (int k = 0; k < APL->Count; k++) {
			APLelem curK = APL[k];

			float zkleft, zkright;

			if (curK.active) {
				zkleft  = - (curK.a * xleft  + curK.b * yt + curK.d) / curK.c;
				zkright = - (curK.a * xright + curK.b * yt + curK.d) / curK.c;
			}

			float dzleft  = zjleft  - zkleft,
				  dzright = zjright - zkright;

			if (dzleft * dzright < 0) {
				xint = (xright * dzleft - xleft * dzright) / (dzleft - dzright);
				return true;
			}
		}
	}

	return false;
}

void InitializePolygon(polygon3D^ polygon, float& a, float& b, float& c, float& d) {
	a = b = c = d;

	if (polygon->Count >= 3) {
		point3D p1 = polygon[0],
			p2 = polygon[1],
			p3 = polygon[2];

		a = p2.y * p3.z - p3.y * p2.z - p1.y * (p3.z - p2.z) + p1.z * (p3.y - p2.y);
		b = p1.x * (p3.z - p2.z) - (p2.x * p3.z - p3.x * p2.z) + p1.z * (p2.x - p3.x);
		c = p1.x * (p2.y - p3.y) - p1.y * (p2.x - p3.x) + (p2.x * p3.y - p3.x * p2.y);
		d = - (p1.x * (p2.y * p3.z - p3.y * p2.z) - p1.y * (p2.x * p3.z - p3.x * p2.z) + p1.z * (p2.x * p3.y - p3.x * p2.y));
	}
}

APLelem^ Active(List<APLelem>^ APL, polygon3D^ p) {
	for (int i = 0; i < APL->Count; i++) {
		if (APL[i].P->P == p) {
			return APL[i];
		}
	}

	return gcnew APLelem();
}

void ProcessLine(int Wcx, int Wx, float y0, float yt, List<AELelem>^ AEL, List<APLelem>^ APL, Graphics^ g) {
	float xleft  = float::MinValue,
		  xright = Wcx;

	int polygonCount = 0,
		i = 0;

	Color C = BACKGROUND_COLOR;

	while (i < AEL->Count && xleft < Wcx + Wx) {

		Pen^ pen = gcnew Pen(C, 1);
		
		AELelem curAEL = AEL[i];
		xright = curAEL.x;

		if (xright > Wcx) {
			
			if ((int) xleft  < Wcx)	   xleft  = Wcx;
			if ((int) xright > Wcx + Wx) xright = Wcx + Wx;

			if (polygonCount == 0) C = BACKGROUND_COLOR;
			else if (polygonCount == 1) C = curAEL.P->color;
			else {
				stack<float> intersectionStack;

				do {
					if (!intersectionStack.empty()) {
						pen->Color = C;
						g->DrawLine(pen, xleft, y0, xright, y0);

						xleft = xright;
						xright = intersectionStack.top();
						intersectionStack.pop();
					}

					int xint;
					while (HasIntersection(xleft, xright, xint, yt, APL)) {
						intersectionStack.push(xright);
						xright = xint;
					}

					clrPolygon^ tmpP;
					float zmidmax = float::MinValue;
					for (int j = 0; j < APL->Count; j++) {
						APLelem curAPL = APL[j];

						if (curAPL.active) {
							float t = - (curAPL.a * (xleft + xright) + 2 * curAPL.b * yt + 2 * curAPL.d) / 2 * curAPL.c;
							if (t < zmidmax) {
								zmidmax = t;
								tmpP = curAPL.P;
							}
						}
					}

					C = tmpP->color;
					
				} while (!intersectionStack.empty());
			}

			Active(APL, curAEL.P->P)->active ^ 1;
			if (Active(APL, curAEL.P->P)->active) polygonCount += 1;
			else polygonCount -= 1;

			g->DrawLine(pen, xleft, y0, xright, y0);

			xleft = xright;
		} 

		i++;
	}

	if ((int) xleft < Wcx + Wx) {
		if ((int) xleft < Wcx) xleft = Wcx;

		xright = Wcx + Wx;

		g->DrawLine(gcnew Pen(BACKGROUND_COLOR, 1), xleft, y0, xright, y0);
	}
}

void Watkins(List<clrPolygon>^ clrPolygons, Graphics^ g, int Wcx, int Wx, int Wcy, int Wy) {

	List<Pelem>^ R = gcnew List<Pelem>(0);

	for (int i = 0; i < clrPolygons->Count; i++) {
		R->Add(Pelem(clrPolygons[i], float::MaxValue, float::MinValue));
	}

	for (int i = 0; i < R->Count; i++) {
		for (int j = 0; j < R[i].P->P->Count; j++) {
			float yc = R[i].P->P[j].y;

			if (R[i].yPmin > yc) {
				R[i] = Pelem(R[i].P, yc, R[i].yPmax);
			}

			if (R[i].yPmax < yc) {
				R[i] = Pelem(R[i].P, R[i].yPmin, yc);
			}
			
		}
	}

	float yPnext = float::MaxValue;
	for (int i = 0; i < R->Count; i++) {
		if (R[i].yPmin > Wcy + Wy || R[i].yPmax < Wcy) {
			R->RemoveAt(i);
			i--;
		}
	}

	R;

	for (int i = 0; i < R->Count; i++) {
		if (yPnext > R[i].yPmin) {
			yPnext = R[i].yPmin;
		}
	}

	float yt = yPnext;
	float yAPLnext;

	List<APLelem>^ APL = gcnew List<APLelem>(0);

	while ((int) yt <= Wcy + Wy) { 

		if ((int) yt == (int) yPnext) {

			for (int i = 0; i < R->Count; i++) {
				if ((int) R[i].yPmin == (int) yt) {
					float a, b, c, d;
					InitializePolygon(R[i].P->P, a, b, c, d);

					if (c != 0) {
						APL->Add(APLelem(R[i].P, false, a, b, c, d));
						R->RemoveAt(i);
						i--;
					}
				}
			}

			yAPLnext = yt;

			if (R->Count == 0) {
				yPnext == float::MaxValue;
			} else {
				yPnext = float::MaxValue;
				for (int i = 0; i < R->Count; i++) {
					if (yPnext > R[i].yPmin) {
						yPnext = R[i].yPmin;
					}
				}
			}
		}

		List<AELelem>^ AEL = gcnew List<AELelem>(0);
		float yAELnext;

		if ((int) yt == (int) yAPLnext) {

			for (int i = 0; i < APL->Count; i++) {
				point3D A = APL[i].P->P[APL[i].P->P->Count - 1];
				point3D B;

				for (int j = 0; j < APL[i].P->P->Count; j++) {
					B = APL[i].P->P[j];

					if ((int) A.y == (int) yt && (int) A.y != (int) B.y) {
						AEL->Add(AELelem(APL[i].P, A.x, B.y, (B.x - A.x) / (B.y - B.y)));
					}

					A = B;
				}
			}

			for (int i = 0; i < APL->Count; i++) {
				point3D A = APL[i].P->P[APL[i].P->P->Count - 1];
				point3D B;

				for (int j = 0; j < APL[i].P->P->Count; j++) {
					B = APL[i].P->P[j];

					if ((int) A.y == (int) yt && (int) A.y == (int) B.y) {
						AEL->Add(AELelem(APL[i].P, A.x, B.y, 0));
					}

					A = B;
				}
			}
			
			yAPLnext = float::MaxValue;
			for (int i = 0; i < APL->Count; i++) {
				point3D A = APL[i].P->P[APL[i].P->P->Count - 1];
				point3D B;

				for (int j = 0; j < APL[i].P->P->Count; j++) {
					B = APL[i].P->P[j];

					if ((int) A.y > (int) yt && (int) yAPLnext > (int) A.y) {
						yAPLnext = A.y;
					}

					A = B;
				}
			}

			for (int i = 0; i < AEL->Count; i++) {
				for (int j = 0; j < AEL->Count - i - 1; j++) {
					if (AEL[j].y > AEL[j + 1].y || AEL[j].y == AEL[j + 1].y && AEL[j].x >= AEL[j + 1].x) {
						AELelem temp = AEL[j];
						AEL[j] = AEL[j + 1];
						AEL[j + 1] = temp;
					}
				}
			}

			yAELnext = float::MaxValue;
			for (int i = 0; i < AEL->Count; i++) {
				if (yAELnext > AEL[i].y) {
					yAELnext = AEL[i].y;
				}
			}
		}

		AEL;
		APL;
		yt;
		Wcx;
		Wcy;
		Wx;
		Wy;

		ProcessLine(Wcx, Wx, yt, yt, AEL, APL, g);

		/*if ((int) yt >= Wcy) { 
			ProcessLine(Wcx, Wx, 0, yt, AEL, APL, g);
		}*/

		yt += 1;

		if ((int) yt >= yAELnext) {

			for (int i = 0; i < AEL->Count; i++) {
				if ((int) yt >= AEL[i].y) {
					AEL->RemoveAt(i);
					i--;
				}
			}

			yAELnext = float::MaxValue;

			for (int i = 0; i < AEL->Count; i++) {
				if (yAELnext > AEL[i].y) {
					yAELnext = AEL[i].y;
				}
			}
		}

		for (int i = 0; i < AEL->Count; i++) {
			AEL[i].x += AEL[i].dx;
		}
	}
}