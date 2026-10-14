#pragma once
#include <algorithm>
#include <cmath>
#include <cstdint>
struct BinOutput {bool lid_open;int fill_percent;bool full;};
class BinControl {
    uint32_t last_seen_=0;bool open_=false;
public:
    BinOutput tick(uint32_t now,bool person,float distance_cm){
        if(person){open_=true;last_seen_=now;}
        else if(open_ && uint32_t(now-last_seen_)>=1500)open_=false;
        int fill=-1;
        if(std::isfinite(distance_cm)&&distance_cm>=2&&distance_cm<=35)
            fill=std::clamp(int(std::lround((30.0f-distance_cm)/27.0f*100.0f)),0,100);
        return {open_,fill,fill>=90};
    }
};
