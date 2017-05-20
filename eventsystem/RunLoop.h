#ifndef RUNLOOP_H_
#define RUNLOOP_H_

class RunLoop {
protected:
    static bool m_isRunning;
public:
    virtual ~RunLoop();
    virtual void processNextEvent() = 0;

    static void         start();
    static void         stop();
    static const bool   isRunning();
};

#endif // RUNLOOP_H_
