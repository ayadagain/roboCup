#include <HCSR04.h>

int *lineFollowingModule();
HCSR04 ultrasonicInit(int, int, int = 20, int = 300, bool = false);
float ultrasonicSensor(HCSR04, bool = false);
void motorDriver(char, int, int, int, int, int = 255, int = 255);
void led(int, int, bool = true);
int pidLineFollower(int *);
int calcPID(int, int, int, int, int, int, int, int);