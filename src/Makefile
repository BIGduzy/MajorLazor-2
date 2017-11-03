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
SOURCES := irSender.cpp irReceiver.cpp player.cpp irWeaponTask.cpp irDetecTask.cpp playerTask.cpp oledDisplayTask.cpp oledDisplay.cpp

# header files in this project
HEADERS := tmp.hpp irSender.hpp irReceiver.hpp player.hpp irWeaponTask.hpp irDetecTask.hpp playerTask.hpp oledDisplayTask.hpp oledDisplay.hpp due-twi.hpp

# other places to look for files for this project
SEARCH  := ./Tasks ./Boundries ./Application-Logics

# set RELATIVE to the next higher directory 
# and defer to the appropriate Makefile.* there
RELATIVE := ..
include $(RELATIVE)/Makefile.due
