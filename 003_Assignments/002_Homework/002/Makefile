LATEX = pdflatex
mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
current_dir := $(notdir $(patsubst %/,%,$(dir $(mkfile_path))))

all: main.pdf clean 
	mv main.pdf $(current_dir).pdf 


main.pdf: main.tex
	$(LATEX) main.tex

clean:
	rm -f *.aux *.log 
