CXX=gcc
CPPFILES=main.c
CXXFLAGS=-Wall -Wextra
OBJDIR=./obj
OBJFILES=$(patsubst %.c,$(OBJDIR)/%.o, $(CPPFILES))
BINARY=brainfuck

all: $(BINARY)

$(BINARY): $(OBJFILES)
	@echo "Creating binary.."
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJFILES): | $(OBJDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: %.c
	$(CXX) $(CXXFLAGS) -c -o $@ $^

run: $(BINARY)
	@./$(BINARY)

clean:
	@echo "Removing object files.."
	rm -rf $(OBJDIR) 
	@echo "Removing binary.."
	rm -f $(BINARY)
