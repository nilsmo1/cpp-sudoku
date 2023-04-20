CXX=g++
CPPFILES=main.cpp Board.cpp Game.cpp
LIBFLAGS=-lsfml-graphics -lsfml-window -lsfml-system
OBJDIR=./obj
OBJFILES=$(patsubst %.cpp,$(OBJDIR)/%.o, $(CPPFILES))
BINARY=sudoku

all: $(BINARY)

$(BINARY): $(OBJFILES)
	@echo "Creating binary.."
	$(CXX) -o $@ $^ $(LIBFLAGS)

$(OBJFILES): | $(OBJDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: %.cpp
	$(CXX) -c -o $@ $^

run: $(BINARY)
	@./$(BINARY)

clean:
	@echo "Removing object files.."
	rm -rf $(OBJDIR) 
	@echo "Removing binary.."
	rm -f $(BINARY)

