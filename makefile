SHELL := /bin/bash
DBGTAGS 	= -std=gnu2x -fdiagnostics-color=always -Wall -g -Wextra 
RLSTAGS 	= -std=gnu2x -fdiagnostics-color=always -Wall -O3 -Wextra 
# `gsl-config --cflags --libs`
LTAGS 	= -fdiagnostics-color=always -Wall -Wextra
LINKS = -lgsl -lgslcblas -lm

libs 	= lib/libout.a
file 	?= unnamed
ver     ?= NaN

token2 = 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
token = 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

cc = gcc


OSFLAG :=
ifeq ($(OS),Windows_NT) 
	OSFLAG += -G"MSYS Makefiles"
else 	
	OSFLAG += -G"Unix Makefiles"
endif



build: .FORCE
	@mkdir -p build; \
	cd build; \
	cmake $(OSFLAG) -DCMAKE_BUILD_TYPE=Release ..; \
	$(MAKE) -s

.FORCE:


test: .FORCE build
	@cd build;\
	ctest --output-on-failure
# $(MAKE) -s test 

all: clean final

final: release

	@cd bin; \
	oo=`find -type f -name '*.o'`; \
	gcc $(RLSTAGS) $$oo -o final $(LINKS)

ulibs:

	@.venv/bin/pip install git+https://username:$(token2)@github.com/GhastBust/putils.git

dbg: 
	@for i in $$(find ./src  -type f -name '*.c' ); do \
    	str=$${i/#"./src"/bin}; \
		oo=$${str/.c/.o}; \
		if ! [[ -d `dirname $$oo` ]]; then \
			mkdir -p `dirname $$oo`; \
		fi; \
		gcc $(DBGTAGS) -c $$i -o $$oo $(LINKS);  \
		done
	@cd bin; \
	oo=`find -type f -name '*.o'`; \
	gcc $(DBGTAGS) $$oo -o final $(LINKS)


release: 

	@for i in $$(find ./src  -type f -name '*.c' ); do \
    	str=$${i/#"./src"/bin}; \
		oo=$${str/.c/.o}; \
		if ! [[ -d `dirname $$oo` ]]; then \
			mkdir -p `dirname $$oo`; \
		fi; \
		gcc $(RLSTAGS) -c $$i -o $$oo $(LINKS);  \
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