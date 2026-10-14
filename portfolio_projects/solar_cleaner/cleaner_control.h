#pragma once
#include <cstdint>
enum class CleanerState { IDLE,CLEANING,DONE,FAULT };
struct CleanerOutput {CleanerState state;bool drive;bool brush;};
class CleanerControl {
    CleanerState state_=CleanerState::IDLE;uint32_t started_=0;
public:
    bool start(uint32_t now,bool front_edge,bool rear_edge,bool emergency){
        if(state_==CleanerState::FAULT||front_edge||rear_edge||emergency)return false;
        state_=CleanerState::CLEANING;started_=now;return true;
    }
    bool reset(bool front_edge,bool rear_edge,bool emergency){
        if(front_edge||rear_edge||emergency)return false;
        state_=CleanerState::IDLE;return true;
    }
    void stop(){if(state_!=CleanerState::FAULT)state_=CleanerState::IDLE;}
    CleanerOutput tick(uint32_t now,bool front_edge,bool rear_edge,bool emergency){
        if(emergency||rear_edge)state_=CleanerState::FAULT;
        else if(state_==CleanerState::CLEANING&&front_edge)state_=CleanerState::DONE;
        else if(state_==CleanerState::CLEANING&&uint32_t(now-started_)>=25000)state_=CleanerState::FAULT;
        bool on=state_==CleanerState::CLEANING;return {state_,on,on};
    }
};
