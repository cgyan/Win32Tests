#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <cstdint>
class RunLoop;
class Object;
class Event;

class Application {
private:
    RunLoop * runLoop;
public:
    Application();
    ~Application();
    static void sendEvent(Object * receiver, Event * event);
    uint64_t run();
};

#endif // APPLICATION_H_
