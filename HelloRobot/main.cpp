#include <iostream>
#include <libplayerc++/playerc++.h>

using namespace std;
using namespace PlayerCc;

#define LASER_SAMPLES 666
#define MIN_ANGLE_FOR_AVOIDANCE -45
#define MAX_ANGLE_FOR_AVOIDANCE 45
#define MAX_DIST_TO_OBSTACLE 0.5


int deg_to_index(double deg)
{
	return (deg + 120) / 0.36;
}

int main(int argc, char** argv)
{
	PlayerClient pc("localhost",6665);
	Position2dProxy pp(&pc,0);
	LaserProxy lp(&pc, 0);

	while (true)
	{
		pc.Read();
		bool isObstacleInFront = false;
		int minIndex = deg_to_index(MIN_ANGLE_FOR_AVOIDANCE);
		int maxIndex = deg_to_index(MAX_ANGLE_FOR_AVOIDANCE);

		for (int i = minIndex; i <= maxIndex; i++)
		{
			if (lp[i] < MAX_DIST_TO_OBSTACLE)
			{
				isObstacleInFront = true;
				break;
			}
		}

		if (isObstacleInFront)
			pp.SetSpeed(0, 0.5);
		else
			pp.SetSpeed(0.5, 0);
	}

	return 0;
}
