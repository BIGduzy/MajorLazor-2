#############################################################################
#
# Project Makefile
#
# (c) Wouter van Ooijen (www.voti.nl) 2016
#
# This file is in the public domain.
# 
#############################################################################

# source files in this project (main.cpp is automatically assumed)
SOURCES := gameLeaderTask.cpp irSender.cpp playerTask.cpp irDetecTask.cpp oledDisplayTask.cpp oledDisplay.cpp irWeaponTask.cpp keypad.cpp keypadTask.cpp buttonTask.cpp speakerTask.cpp

# header files in this project
HEADERS := gameLeaderTask.hpp tmp.hpp irSender.hpp irReceiver.hpp irWeaponTask.hpp irDetecTask.hpp playerTask.hpp irSignal.hpp message.hpp oledDisplayTask.hpp oledDisplay.hpp due-twi.hpp keypad.hpp keypadTask.hpp button.hpp buttonTask.hpp speaker.hpp speakerTask.hpp

# other places to look for files for this project
SEARCH  := ./Tasks ./Boundries ./Application-Logics ./Entities

# set RELATIVE to the next higher directory 
# and defer to the appropriate Makefile.* there
RELATIVE := ..
include $(RELATIVE)/Makefile.due
