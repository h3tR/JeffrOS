#include <stdint-gcc.h>

int abs(int val){
    if(val<0){
        val*=-1;
    }
    return val;
}

float abs(float val){
    if(val<0){
        val*=-1;
    }
    return val;
}




int pow(int base,int power){
    //lazy implementation
    int originalbase = base;
    if(power == 0){
        return power;
    }else if(power == 1){
        return base;
    }else{
        if(power>1){
            power-=1;
        }
        for(int i =0;i<abs(power);i++){
            if(power<0){
                base/=originalbase;
            }else{
                base*=originalbase;
            }
        }
        return base;
    }
    
}

//TODO 
//requires general float based functions
float pow(float base,/*float?*/int power);

float sin(float value, int accuracy);
float sin(float value);
float cos(float value, int accuracy);
float cos(float value);
float tan(float value, int accuracy);
float tan(float value);

/*float asin(float value, int accuracy);?*/
float asin(float value);
/*float acos(float value, int accuracy);?*/
float acos(float value);
/*float atan(float value, int accuracy);?*/
float atan(float value);

int log();
int logab();

/*float log();?*/

int floor(float value);
int ceiling(float value);
int round(float value);