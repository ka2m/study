#pragma once
#include "stdafx.h"
#include <algorithm>
#include "Transform.h"
#include "Pclip.h"

#define forn(i, n) for(int i=0; int(i) < int(n); ++i)

using namespace std;
using namespace System::Collections::Generic;

int extCode(point a, point min, point max) {
	int C = 0;
	if(a.x < min.x) {
		C++;
		
		if(a.y < min.y) {
			C += 20;
		}

		if(a.y > max.y) {
			C += 24;
		}

		return C;
	}
	
	if(a.x > max.x) {
		C += 2;

		if(a.y < min.y) {
			C += 20;
		}

		if(a.y > max.y) {
			C += 24;
		}

		return C;
	}

	if(a.y < min.y) {
		C += 4;
	}

	if(a.y > max.y) {
		C += 8;
	}

	return C;
}

point Angle(int C, point min, point max) {
	point ans;

	if(C & 1) ans.x = min.x;
	if(C & 2) ans.x = max.x;
	if(C & 4) ans.y = min.y;
	if(C & 8) ans.y = max.y;

	return ans;
}

int Tcc(int C) {
	int corr;

	if(C & 1) corr = -1;
	if(C & 2) corr = 1;
	if(C & 4) corr = -4;
	if(C & 8) corr = 4;

	return corr;
}

polygon^ Pclip (polygon^ P, point min, point max) {
	int n = P->Count;
	point A = P[n - 1];
	int Cstart = extCode(A, min, max);
	polygon^ P1 = gcnew polygon(0);
	
	for(int k = 0; k < n; k++) {
		point B = P[k];
		int Cend = extCode(B, min, max);
		
		int C1 = Cstart;
		int C2 = Cend;

		float x1 = A.x;
		float y1 = A.y;
		float x2 = B.x;
		float y2 = B.y;

		bool clip = false;
		bool flip = false;
		bool segm = false;

		while(true) {
			if(((C1 | C2) & 15) == 0) {
				if(flip) {
					swap(x1, x2);
					swap(y1, y2);
				}
				segm = true;
				break;
			} else {
				if(C1 & C2 & 15) {
					segm = false;
					break;
				} else {
					if((C1 & 15) == 0) {
						swap(x1, x2);
						swap(y1, y2);
						swap(C1, C2);
						flip = !flip;
					}

					if((C1 & 15) != 0 && !flip) {
						clip = true;	
					}

					float dx = x2 - x1;
					float dy = y2 - y1;

					if(C1 & 1) {
						y1 = y2 - (x2 - min.x) * dy / dx;
						x1 = min.x;
					}

					else if(C1 & 2) {
						y1 = y2 - (x2 - max.x) * dy / dx;
						x1 = max.x;
					}

					else if(C1 & 4) {
						x1 = x2 - (y2 - min.y) * dx / dy;
						y1 = min.y;
					}

					else if(C1 & 8) {
						x1 = x2 - (y2 - max.y) * dx / dy;
						y1 = max.y;
					}

					point tmp = {x1, y1};
					C1 = extCode(tmp, min, max);

				}
			}
		}

		C2 = Cend;
		point A1 = {x1, y1};
		point B1 = {x2, y2};

		if(segm) {
			if(clip) {
				P1->Add(A1);
			}
			P1->Add(B1);
		} else {
			if(Cend & 0x10) {
				if((Cstart & Cend & 0x0F) == 0) {
					if((Cstart & 0x10) == 0) {
						C1 = Cend + Tcc(Cstart);
					} else {
						x1 = A.x;
						y1 = A.y;
						x2 = B.x;
						y2 = B.y;

						int C11 = Cstart;
						int C12 = Cend;
						
						step17aib:
						point mid = {(x1 + x2) / 2, (y1 + y2) / 2};
						C1 = extCode(mid, min, max);
						
						if(C1 & 16) {
							if(C1 == C12) {
								x2 = mid.x;
								y2 = mid.y;
								C12 = C1;
								goto step17aib;
							}
							
							if(C1 == C11) {
								x1 = mid.x;
								y1 = mid.y;
								C11 = C1;
								goto step17aib;
							}
						} else {
							if(C1 & C12) {
								C1 = C11 + Tcc(C1);
							} else {
								C1 = C12 + Tcc(C1);
							}
						}
					}

					point tmp = Angle(C1, min, max);
					P1->Add(tmp);
				}
			} else {
				if((Cstart & Cend & 0x0F) == 0) {
					if(Cstart & 0x10) {
						C2 = Cstart + Tcc(Cend);
					} else {
						C2 = Cstart + Cend + 16;
					}
				}
			}
		}

		if(C2 & 0x10) {
			point tmp = Angle(C2, min, max);
			P1->Add(tmp);
		}

		A = B;
		Cstart = Cend;
	}
	
	return P1;
}

public ref class EdgeComparer: IComparer<line3D> {
public:
    virtual int Compare(line3D x, line3D y) {
		return x.start.y.CompareTo(y.start.y);
    }
};

value struct AEL {
	float x1, x2, x3, x4, x5;
};

public ref class AELComparer: IComparer<AEL> {
public:
    virtual int Compare(AEL x, AEL y) {
		if(x.x1 != y.x1) {
			return x.x1.CompareTo(y.x1);
		}
		return x.x4.CompareTo(y.x4);
    }
};
void showLine(float y0, float x1, float z1, float x2, float z2, System::Drawing::Color c, System::Drawing::Bitmap^ image, vector<vector<float> > &zBuf, float Wcx, float Wcy, float Wx, float Wy) {
	if(y0 < Wcy || y0 > Wcy + Wy) {
		return;
	}

	if(x2 < Wcx || x1 > Wcx + Wx) {
		return;
	}

	float x = x1;
	float z = z1;
	float dz = (z2 - z1) / (x2 - x1);

	if(x < Wcx) {
		z += (Wcx - x) * dz;
		x = Wcx;
	}

	while(x <= x2 && x <= Wcx + Wx) {
		int i = int(x);
		int j = int(y0);

		if(zBuf[i][j] <= z && z <= 1) {
			zBuf[i][j] = z;
			image->SetPixel(i, j, c);
		}

		x++;
		z += dz;
	}
}

void zBuffer(polygon3D^ p, int w, int h, System::Drawing::Bitmap^ image, System::Drawing::Color c, float Wcx, float Wcy, float Wx, float Wy) {
	vector<vector<float> > zBuf(w, vector<float>(h, -1));

	List<line3D>^ S = gcnew List<line3D>();
	point3D start = p[p->Count - 1];
	forn(i, p->Count) {
		line3D line;

		if(start.x <= p[i].x && start.y <= p[i].y) {
			line.start = start;
			line.end = p[i];
		} else {
			line.start = p[i];
			line.end = start;
		}
		
		S->Add(line);
		start = p[i];
	}

	EdgeComparer^ cmp = gcnew EdgeComparer();
	S->Sort(cmp);

	float yMin = float::MaxValue;
	float yMax = float::MinValue;

	forn(i, S->Count) {
		yMin = min(yMin, S[i].start.y);
		yMin = min(yMin, S[i].end.y);

		yMax = max(yMax, S[i].start.y);
		yMax = max(yMax, S[i].end.y);
	}

	List<AEL>^ ael = gcnew List<AEL>();
	float yt = yMin;
	float ysNext = yMin;
	float aelNext = float::MaxValue;

	while(yt <= yMax) {
		if(int(yt) == int(ysNext)) {
			forn(i, S->Count) {
				if(int(S[i].start.y) == int(yt)) {
					if(int(S[i].start.y) != int(S[i].end.y)) {
					   AEL cur = {S[i].start.x,
								  S[i].start.z,
								  S[i].end.y,
								 (S[i].end.x - S[i].start.x) / (S[i].end.y - S[i].start.y),
								 (S[i].end.z - S[i].start.z) / (S[i].end.y - S[i].start.y)};
					   ael->Add(cur);
					} else {
						showLine(yt, S[i].start.x, S[i].start.z, S[i].end.x, S[i].end.z, c, image, zBuf, Wcx, Wcy, Wx, Wy);
					}
				}
			}

			forn(i, S->Count) {
				if(int(S[i].start.y) == int(yt)) {
					S->RemoveAt(i);
				}
			}

			forn(i, S->Count) {
				ysNext = min(ysNext, S[i].start.y);
				ysNext = min(ysNext, S[i].end.y);
			}

			AELComparer^ aelCmp = gcnew AELComparer();
			ael->Sort(aelCmp);
			
			aelNext = float::MaxValue;
			forn(i, ael->Count) {
				aelNext = min(aelNext, ael[i].x3);
			}
		}

		for(int i=0; i + 1 < ael->Count; i += 2) {
			showLine(yt, ael[i].x1, ael[i].x2, ael[i + 1].x1, ael[i + 1].x2, c, image, zBuf, Wcx, Wcy, Wx, Wy);
		}

		yt++;
		if(yt >= aelNext) {
			forn(i, ael->Count) {
				if(ael[i].x3 <= yt) {
					ael->RemoveAt(i);
				}
			}
		}

		forn(i, ael->Count) {
			ael[i].x1 += ael[i].x4;
			ael[i].x2 += ael[i].x5;
		}
	}
}