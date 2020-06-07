#include "olcPixelGameEngine.h"

struct point {
	int x, y;
	bool next;
	point* nPoint;
	~point() {
		delete nPoint;
	}
};

#define PI 3.14159265358979323846
#define percentScale 0.5
#define sides 3

class project : public olc::PixelGameEngine {

public:

	point* sPoint;
	point points[sides];

	bool OnUserCreate() {
		int shbt = ScreenHeight() / 2;
		int swbt = ScreenWidth() / 2;

		for (int side = 0; side < sides; side++) {
			points[side] = { (int)(swbt + sinf(side * PI * 2 / sides) * swbt), (int)(shbt + -cosf(side * PI * 2 / sides) * shbt), false, nullptr };
		}

		sPoint = new point();
		sPoint->x = rand() % ScreenWidth();
		sPoint->y = rand() % ScreenHeight();
		sPoint->next = false;
		sPoint->nPoint = nullptr;

		return true;
	}


	bool OnUserUpdate(float fElapsedTime) {
		for (int c = 0; c < 100; c++) {
			int rn = rand() % sides;
			point* oPoint = sPoint;

			sPoint = new point();
			sPoint->x = oPoint->x * (percentScale) + points[rn].x * (1 - percentScale);
			sPoint->y = oPoint->y * (percentScale)+ points[rn].y * (1 - percentScale);
			sPoint->next = true;
			sPoint->nPoint = oPoint;
		}

		for (int x = 0; x < ScreenWidth(); x++) {
			for (int y = 0; y < ScreenHeight(); y++) {
				Draw(x, y, olc::BLACK);
			}
		}

		point* cPoint = sPoint;

		while (cPoint->next) {
			Draw(cPoint->x, cPoint->y, olc::WHITE);
			cPoint = cPoint->nPoint;
		}

		return true;
	}

	bool OnUserDestroy() {


		return true;
	}

};

int main() {

	project pWindow = project();
	if (pWindow.Construct(1600, 900, 1, 1)) pWindow.Start();
	

}