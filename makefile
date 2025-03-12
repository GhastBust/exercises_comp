GTAGS = -fdiagnostics-color=always -Wall -g -Wextra 
file ?= unnamed

all: final

main.o: src/main.c src/intt/trap/trap.h src/intt/simpson/simpson.h src/output/output.h 
	@echo "Compiling main..."
	@gcc $(GTAGS) -c src/main.c -o bin/main.o -lm

vec.o: src/vec/vec.c
	@echo "Compiling vec..."
	@gcc $(GTAGS) -c src/vec/vec.c -o bin/vec.o -lm

trap.o: src/intt/trap/trap.c src/vec/vec.c
	@echo "Compiling trap..."
	@gcc $(GTAGS) -c src/intt/trap/trap.c -o bin/trap.o -lm

simpson.o: src/intt/simpson/simpson.c src/vec/vec.c
	@echo "Compiling simpson..."
	@gcc $(GTAGS) -c src/intt/simpson/simpson.c -o bin/simpson.o -lm

output.o: src/output/output.c 
	@echo "Compiling output..."
	@gcc $(GTAGS) -c src/output/output.c -o bin/output.o -lm

final: output.o trap.o simpson.o vec.o main.o
	@echo "Compiling final executable..."
	@gcc $(GTAGS) bin/output.o bin/simpson.o bin/trap.o bin/vec.o bin/main.o -o bin/final -lm
	@echo "Done!"

file: 
#* per usare scrivere: "make file name=(nome)"
#* e sostituire al posto di (nome) il nome della cartella
#* make creerà una cartella con quel nome con due file dentro,
#* un .c e un .h già con le cose essenziali scritte all'interno
	@cd src; \
	[[ -d $(name) ]] || mkdir $(name); \
	cd $(name); \
	~/Workspace/C/header-writer/bin/final $(name); 

clear:
	@echo "Removing binaries..."
	rm bin/*