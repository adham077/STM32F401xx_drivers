#include "scheduler.h"

 
static uint32_t SCHED_arrCurrentVals[MAX_NO_OF_TASKS] = {0};
//make it an array of pointers instead
static volatile SCHED_stTaskCfg_t SCHED_arrTasks[MAX_NO_OF_TASKS] = {0};

void SCHED_vInit(void){

    Systick_enuInit1Ms(SYSTICK_enu_PRESCALER_1);

    Systick_enuSetCyclicFnMs(SHED_vRun,1);

}

SCHED_enuErrorStatus_t SCHED_enuAddRunnable(SCHED_stTaskCfg_t* Add_stTask){

    SCHED_enuErrorStatus_t Loc_enuStatus = SCHED_enu_OK;

    if(Add_stTask->CallBack==NULL){
        Loc_enuStatus = SCHED_enu_NULL_POINTER;
    }
    else if(SCHED_arrTasks[Add_stTask->Priority].CallBack != NULL){
        Loc_enuStatus = SCHED_enu_PRIORITY_OCCUPIED;
    }
    else{
        SCHED_arrTasks[Add_stTask->Priority].CallBack = Add_stTask->CallBack;
        SCHED_arrTasks[Add_stTask->Priority].CycleTime = Add_stTask->CycleTime;
        SCHED_arrTasks[Add_stTask->Priority].Priority = Add_stTask->Priority;        
    }

    return Loc_enuStatus;
}

void SHED_vRun(void){
    
    uint32_t i = 0;

    for(;i<MAX_NO_OF_TASKS;i++){
        SCHED_arrCurrentVals[i]++;
        if(SCHED_arrTasks[i].CallBack!=NULL){
            if(SCHED_arrCurrentVals[i] == SCHED_arrTasks[i].CycleTime){
                SCHED_arrTasks[i].CallBack();
                SCHED_arrCurrentVals[i] = 0;
            }
        }
    }
}

void SCHED_vStart(void){
    Systick_vStart();
    while(1){
        //idle task
    }
}

void SHED_vStop(void){
    Systick_vStop();
}
