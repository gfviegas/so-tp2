#ifndef pcbTableItem_hpp
#define pcbTableItem_hpp

#define MIN_PRIORITY 0
#define MAX_PRIORITY 3

class PcbTableItem {
    private:
        int masterId;
        int *pc;
        int *n;
        int initTime;
        int *cpuTime;
    public:
        int pid;
        int priority;

        PcbTableItem(int id, int mId, int *pc, int *n, int initTime, int *cpuTime);

        int getCpuTime(void);
        int increasePriority(void);
        int decreasePriority(void);
        int getPriority(void);
        int getMasterId(void);
        int getValue(void);
        int getInitTime(void);
};

#endif /* pcbTable_hpp */
