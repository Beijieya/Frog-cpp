#include "Vehicle.h"
#include "Config.h"

Vehicle::Vehicle(int x,int y,char c,int d):GameObject(x,y,c),d(d){}

Car::Car (int x,int y,char c,int d):Vehicle(x,y,c,d){}
bool Car::move(){
    x += d; if(x<0)x=MAP_WIDTH-1; if(x>=MAP_WIDTH)x=0;
    return setXY(x,y);
}

Moto::Moto(int x,int y,char c,int d):Vehicle(x,y,c,d){}
bool Moto::move(){
    x += d; if(x<0)x=MAP_WIDTH-1; if(x>=MAP_WIDTH)x=0;
    return setXY(x,y);
}
