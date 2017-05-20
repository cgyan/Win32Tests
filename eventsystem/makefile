CC = g++

CFLAGS = -Wall -std=c++11 -mwindows -mconsole

OBJS = \
	main.o \
	Application.o \
	Button.o \
	Object.o \
	RunLoop.o \
	Widget.o \
	Win32RunLoop.o

EXE = main

default : $(EXE)

$(EXE) : $(OBJS)
	@echo Building target: $@
	$(CC) $(CFLAGS) -o $(EXE) $(OBJS)
	@echo Finished building target: $@
	@echo ''

main.o : main.cpp Application.h Widget.h DerivedWidget.h Button.h
	@echo Building file: main.cpp
	$(CC) $(CFLAGS) -c main.cpp
	@echo Finished building file: main.cpp
	@echo ''

Application.o : Application.cpp Application.h Win32RunLoop.h Object.h Event.h
	@echo Building file: Application.cpp
	$(CC) $(CFLAGS) -c Application.cpp
	@echo Finished building file: Application.cpp
	@echo ''

Button.o : Button.cpp Button.h ButtonImpl.h
	@echo Building file: Button.cpp
	$(CC) $(CFLAGS) -c Button.cpp
	@echo Finished building file: Button.cpp
	@echo ''

Object.o : Object.cpp Object.h
	@echo Building file: Object.cpp
	$(CC) $(CFLAGS) -c Object.cpp
	@echo Finished building file: Object.cpp
	@echo ''

RunLoop.o : RunLoop.cpp RunLoop.h
	@echo Building file: RunLoop.cpp
	$(CC) $(CFLAGS) -c RunLoop.cpp
	@echo Finished building file: RunLoop.cpp
	@echo ''

Widget.o : Widget.cpp Widget.h WidgetImpl.h Event.h CloseEvent.h ResizeEvent.h MouseEvent.h
	@echo Building file: Widget.cpp
	$(CC) $(CFLAGS) -c Widget.cpp
	@echo Finished building file: Widget.cpp
	@echo ''

Win32RunLoop.o : Win32RunLoop.cpp Win32RunLoop.h Application.h CloseEvent.h
	@echo Building file: Win32RunLoop.cpp
	$(CC) $(CFLAGS) -c Win32RunLoop.cpp
	@echo Finished building file: Win32RunLoop.cpp
	@echo ''

clean :
	rm -rf $(OBJS) $(EXE)
