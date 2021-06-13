#include <Arduino.h>
#include <HCSR04.h>
#include <Wire.h>

int *lineFollowingModule()
{
    int raw_result[10];
    int analog_result[5];
    int high_byte;
    int low_byte;
    static int result[5];
    int count = 0;

    Wire.requestFrom(0x11, 10); // request 6 bytes from slave device #8
    while (Wire.available())
    {
        int c = Wire.read();
        raw_result[count] = c;
        count++;
    }

    // Serial.println(' ');
    count = 0;

    for (int i = 0; i < 5; i++)
    {
        high_byte = raw_result[i * 2] << 8;
        low_byte = raw_result[i * 2 + 1];
        analog_result[i] = high_byte + low_byte;
        result[i] = analog_result[i];
    }

    // for (int i = 0; i < 5; i++)
    // {
    //     Serial.print(result[i]);
    //     Serial.print(" ");
    // }

    return result;
}

HCSR04 ultrasonicInit(int trig, int echo, int temperature = 20, int distance = 300, bool raw = false)
{
    HCSR04 ultrasonic(trig, echo, temperature, distance);
    return ultrasonic;
}

// void lineFollower(int *ltStatus)
// {

// }
int pidLineFollower(int *lf)
{
    int th = 5;
    int error;
    if ((lf[0] > th) && (lf[1] > th) && (lf[2] > th) && (lf[3] > th) && (lf[4] < th))
    {
        error = 4;
    }
    else if ((lf[0] > th) && (lf[1] > th) && (lf[2] > th) && (lf[3] < th) && (lf[4] < th))
    {
        error = 3;
    }
    else if ((lf[0] > th) && (lf[1] > th) && (lf[2] > th) && (lf[3] < th) && (lf[4] > th))
    {
        error = 2;
    }
    else if ((lf[0] > th) && (lf[1] > th) && (lf[2] < th) && (lf[3] < th) && (lf[4] > th))
    {
        error = 1;
    }
    else if ((lf[0] > th) && (lf[1] > th) && (lf[2] < th) && (lf[3] > th) && (lf[4] > th))
    {
        error = 0;
    }
    else if ((lf[0] > th) && (lf[1] < th) && (lf[2] < th) && (lf[3] > th) && (lf[4] > th))
    {
        error = -1;
    }
    else if ((lf[0] > th) && (lf[1] < th) && (lf[2] > th) && (lf[3] > th) && (lf[4] > th))
    {
        error = -2;
    }
    else if ((lf[0] < th) && (lf[1] < th) && (lf[2] > th) && (lf[3] > th) && (lf[4] > th))
    {
        error = -3;
    }
    else if ((lf[0] < th) && (lf[1] > th) && (lf[2] > th) && (lf[3] > th) && (lf[4] > th))
    {
        error = -4;
    }

    return error;
}

float ultrasonicSensor(HCSR04 obj, bool raw = false)
{
    float uDistance = 0;
    if (!raw)
    {
        uDistance = obj.getMedianFilterDistance();
    }
    else
    {
        uDistance = obj.getDistance();
    }

    if (uDistance != HCSR04_OUT_OF_RANGE)
    {
        return uDistance;
    }
    else
    {
        return -1;
    }
}

void motorDriver(char direction, int m1p1, int m1p2, int m2p1, int m2p2, int m1speed = 255, int m2speed = 255)
{
    // TODO: Remove after testing
    int m1s = 255;
    int m2s = 255;

    analogWrite(9, m1speed);
    analogWrite(10, m2speed);
    if (direction == 'f')
    {
        digitalWrite(m1p1, HIGH);
        digitalWrite(m1p2, LOW);
        digitalWrite(m2p1, HIGH);
        digitalWrite(m2p2, LOW);
    }
    else if (direction == 'b')
    {
        digitalWrite(m1p1, LOW);
        digitalWrite(m1p2, HIGH);
        digitalWrite(m2p1, LOW);
        digitalWrite(m2p2, HIGH);
    }
    else if (direction == 'l')
    {
        digitalWrite(m1p1, HIGH);
        digitalWrite(m1p2, LOW);
        digitalWrite(m2p1, LOW);
        digitalWrite(m2p2, HIGH);
    }
    else if (direction == 'r')
    {
        digitalWrite(m1p1, LOW);
        digitalWrite(m1p2, HIGH);
        digitalWrite(m2p1, HIGH);
        digitalWrite(m2p2, LOW);
    }
}

void led(int ledpin, int time, bool state = true)
{
    if (state)
    {
        digitalWrite(ledpin, HIGH);
        delay(time);
        digitalWrite(ledpin, LOW);
    }
    else
    {
        digitalWrite(ledpin, LOW);
    }
}

int calcPID(int &kp, int &ki, int &kd, int &p, int &i, int &d, int &e, int &pe);
{
    int pid;
    p = e;
    i = i + e;
    d = e - pe;
    pid = ((kp * p) + (ki * i) + (kd + d));
    pe = e;
    return 0;
}
