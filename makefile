SHELL := /bin/bash
GTAGS 	= -fdiagnostics-color=always -Wall -g -Wextra 
# -I lib/**
LTAGS 	= -fdiagnostics-color=always -Wall -Wextra
libs 	= lib/libout.a
file 	?= unnamed

cc = gcc

all: clean final

final: test

	@cd bin; \
	oo=`find -type f -name '*.o'`; \
	gcc $(GTAGS) $$oo -o final -lm

update_libs:

# /home/saturn/Workspace/C/putils/dist/putils-1.0.5.tar.gz


# LIB_FILES 	:= ${wildcard lib/*/*.c}
# LIB_OBJ		:= ${LIB_FILES:.c=.o}

# LIB_SUBS	:= ${wildcard lib/*/.}

# lib/%.o: lib/%.c
# 	gcc -c $(LTAGS) $< -o $@

# libs:  $(LIB_OBJ)
# 	ar rcs lib/libout.a $(LIB_OBJ)

test: 

	@for i in $$(find ./src  -type f -name '*.c' ); do \
    	str=$${i/#"./src"/bin}; \
		oo=$${str/.c/.o}; \
		if ! [[ -d `dirname $$oo` ]]; then \
			mkdir -p `dirname $$oo`; \
		fi; \
		gcc $(GTAGS) -c $$i -o $$oo -lm; \
		done


header: 
#* per usare scrivere: "make header name=(nome)"
#* e sostituire al posto di (nome) il nome della cartella
#* make creerà una cartella con quel nome con due file dentro,
#* un .c e un .h già con le cose essenziali scritte all'interno
	@cd src; \
	[[ -d $(name) ]] || mkdir $(name); \
	cd $(name); \
	~/Workspace/C/header-writer/bin/final $(name) 

clean:
	@echo "Removing binaries..."
	rm -r -f bin/*