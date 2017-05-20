#include "RunLoop.h"

bool RunLoop::m_isRunning = false;

RunLoop::~RunLoop() {
    //
}

void
RunLoop::start() {
    m_isRunning = true;
}

void
RunLoop::stop() {
    m_isRunning = false;
}

const bool
RunLoop::isRunning() {
    return m_isRunning;
}
