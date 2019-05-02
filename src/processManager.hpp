using namespace std;

#include <bits/stdc++.h>

class ProcessManager {
    private:

        /* data */

    public:
        PcbTableList blockedState;
        PcbTableList readyState;
        PcbTable runningState;
        int time;
        Cpu cpu;
        PcbTable pcbTable;
        Reporter reporter;

        ProcessManager (arguments);
        virtual ~ProcessManager ();

        void init(void);
        void unblock(void);
        void print(void);
        void endExecution(void);
        void execute(void);
};
