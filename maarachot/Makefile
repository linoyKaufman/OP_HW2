# מגדירים את המהדר והדגלים
CXX = g++
CXXFLAGS = -Wall -Wextra -g

# מטרות ברירת מחדל לייצור שני קבצי ההפעלה
all: tictactow mync

# יצירת קובץ ההפעלה tictactow
tictactow: tictactow.o
	$(CXX) $(CXXFLAGS) -o tictactow tictactow.o

# יצירת קובץ ההפעלה mync
mync: mync.o
	$(CXX) $(CXXFLAGS) -o mync mync.o

# קבצי אובייקט
tictactow.o: tictactow.cpp
	$(CXX) $(CXXFLAGS) -c tictactow.cpp

mync.o: mync.cpp
	$(CXX) $(CXXFLAGS) -c mync.cpp

# ניקוי קבצים
clean:
	rm -f *.o tictactow mync
