SHELL := /bin/bash
GTAGS 	= -fdiagnostics-color=always -Wall -g -Wextra 
# `gsl-config --cflags --libs`
LTAGS 	= -fdiagnostics-color=always -Wall -Wextra
LINKS = -lgsl -lgslcblas -lm

libs 	= lib/libout.a
file 	?= unnamed
ver     ?= NaN

token2 = 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
token = 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

cc = gcc

all: clean final

final: test

	@cd bin; \
	oo=`find -type f -name '*.o'`; \
	gcc $(GTAGS) $$oo -o final $(LINKS)

ulibs:

	.venv/bin/pip install git+https://username:$(token2)@github.com/GhastBust/putils.git

test: 

	@for i in $$(find ./src  -type f -name '*.c' ); do \
    	str=$${i/#"./src"/bin}; \
		oo=$${str/.c/.o}; \
		if ! [[ -d `dirname $$oo` ]]; then \
			mkdir -p `dirname $$oo`; \
		fi; \
		gcc $(GTAGS) -c $$i -o $$oo $(LINKS);  \
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