#include <cassert>
#include <cmath>
#include <iostream>
#include "../smart_dustbin/bin_control.h"
#include "../solar_cleaner/cleaner_control.h"
int main(){
    BinControl bin;auto a=bin.tick(0,false,30);assert(!a.lid_open&&a.fill_percent==0);
    a=bin.tick(100,true,3);assert(a.lid_open&&a.full&&a.fill_percent==100);
    assert(bin.tick(1000,false,15).lid_open);assert(!bin.tick(1600,false,15).lid_open);
    assert(bin.tick(1700,false,NAN).fill_percent==-1);assert(bin.tick(1800,false,60).fill_percent==-1);
    BinControl rollover;rollover.tick(0xffffff00u,true,10);assert(rollover.tick(100,false,10).lid_open);assert(!rollover.tick(2000,false,10).lid_open);
    CleanerControl c;assert(c.start(0,false,false,false));assert(c.tick(100,false,false,false).drive);
    auto o=c.tick(200,true,false,false);assert(o.state==CleanerState::DONE&&!o.drive&&!o.brush);
    assert(c.start(300,false,false,false));o=c.tick(400,false,true,false);assert(o.state==CleanerState::FAULT&&!o.drive);
    assert(!c.start(500,false,false,false));assert(!c.reset(false,true,false));assert(c.reset(false,false,false));
    assert(c.start(600,false,false,false));o=c.tick(26000,false,false,false);assert(o.state==CleanerState::FAULT&&!o.brush);
    assert(c.reset(false,false,false));assert(c.start(27000,false,false,false));o=c.tick(27001,false,false,true);assert(o.state==CleanerState::FAULT);
    std::cout<<"Passed: bin presence/hold/fill/invalid-sensor/rollover and cleaner edge/emergency/watchdog/fault-reset cases.\n";
}
