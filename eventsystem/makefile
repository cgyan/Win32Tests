CC = g++

CPPFLAGS = -Wall -std=c++11 -mwindows -mconsole -g

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
	$(CC) $(CPPFLAGS) -o $(EXE) $(OBJS)
	@echo Finished building target: $@
	@echo ''

%.o : %.cpp
	@echo Building file: $<
	$(CC) $(CPPFLAGS) -MD -c $<
	@cp $*.d $*.P; \
		sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
			-e '/^$$/ d' -e 's/$$/ :/' < $*.d >> $*.P; \
		rm -f $*.d
	@echo Finished building file: $<
	@echo ''


clean :
	rm -rf $(EXE) $(OBJS) *.P

-include *.P
