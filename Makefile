CC=g++
CFLAGS=-Iinclude

SRCDIR=src
OBJDIR=obj

SOURCES=$(wildcard $(SRCDIR)/*.cpp)
OBJECTS=$(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))
EXECUTABLE=bin/app

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $^ -lsqlite3 -o $@

all: $(EXECUTABLE)

run:
	./$(EXECUTABLE)

clean:
	rm -f $(OBJDIR)/*.o $(EXECUTABLE)

test:
	$(CC) tests/main.cpp tests/test_console_manager.cpp src/console_manager.cpp src/auth.cpp src/services.cpp tests/test_auth.cpp src/database.cpp tests/test_database.cpp -l gtest -l sqlite3 -o ./bin/tests $(CFLAGS)
	./bin/tests
