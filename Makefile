CXX			= g++
CXXFLAGS		= -Wall --std=c++0x ${DEBUGFLAG}
OPTFLAG		= -O2
DEBUGFLAG	= -g
LINKER		= g++
LFLAGS		= -o
CURSESFLAGS	= -lncurses

SRC = \
			helperfunctions.cpp \
			Color.cpp \
			Show.cpp \
			Player.cpp \
			Playlist.cpp \
			PlaylistController.cpp \
			Window.cpp \
			PlaylistWindow.cpp \
			Settings.cpp \
			ShowsWindow.cpp \
			ncurses.cpp

OBJS = $(SRC:.cpp=.o)

ncurses: $(OBJS)
	$(CXX) $(CXXFLAGS) $(CURSESFLAGS) $(OBJS) -o $@

.h.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm $(OBJS) ncurses.o ncurses
