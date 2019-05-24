#include "Schedule.h"
#include "TCB.h"
#include "MeasureSubsystem.h"
#include "ComputeSubsystem.h"
#include "WarningAlarmSubsystem.h"


int main() {
    TCB measureTCB;
    TCB computeTCB;
    TCB warningTCB;

    measureSubsystemData measureData;
    computeSubsystemData computeData;
    WarningAlarmSubsystemData warningData;
    
    void* measuredata = &measureData;
    void* computedata = &computeData;
    void* warningdata = &warningData;

    measureTCB.taskDataPtr = measuredata;
    computeTCB.taskDataPtr = computedata;
    warningTCB.taskDataPtr = warningdata;
    measureTCB.id = 1;
    computeTCB.id = 44;
    warningTCB.id = 57;

    insert(&measureTCB);

    printf("%d\n",387);

    insert(&computeTCB);

    printf("%d\n",287);

    insert(&warningTCB);


    TCB* cur = list;
    while(cur != NULL) {
        printf("%d\n", cur->id);
        cur = cur->next;
    }
    
    deleteTask(&warningTCB);
    
    TCB* cur2 = list;
    while(cur2 != NULL) {
        printf("%d\n", cur2->id);
        cur2 = cur2->next;
    }

    int age;
    std::cin>>age;

    return 1;
}
