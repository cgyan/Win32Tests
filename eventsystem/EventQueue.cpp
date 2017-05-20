#include "EventQueue.h"
#include "CloseEvent.h"

Event EventQueue::currentEvent{Event(Event::Close)};
Object * EventQueue::currentReceiver = nullptr;
