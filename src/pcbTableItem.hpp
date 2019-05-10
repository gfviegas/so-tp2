#ifndef pcbTableItem_hpp
#define pcbTableItem_hpp

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

        PcbTableItem(int id, int mId, int *n, int *pc, int initTime, int *cpuTime);

        int getCpuTime(void);
        int increasePriority(void);
        int decreasePriority(void);
        int getPriority(void);
};

#endif /* pcbTable_hpp */
