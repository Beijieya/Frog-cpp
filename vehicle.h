#pragma once
#include "GameObject.h"

class Vehicle : public GameObject {
protected:
    int d;                          // 每幀位移量 ±
public:
    Vehicle(int x,int y,char c,int d);
};

class Car  : public Vehicle {
public:
    Car (int x,int y,char c,int d);
    bool move() override;
};

class Moto : public Vehicle {
public:
    Moto(int x,int y,char c,int d);
    bool move() override;
};
