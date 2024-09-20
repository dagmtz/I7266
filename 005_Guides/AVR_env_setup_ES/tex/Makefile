# set latexfile to the name of the main file without the .tex
latexfile = main

# set the directory where the files are
RELEASE_NAME = AVR_env_setup_ES

# put the names of figure files here.  include the .eps
# figures = smiley.eps logo.eps

# if no references, run "touch latexfile.bbl; touch referencefile.bib"
# or delete dependency in .dvi and tarball sections
# referencefile = refs

TEX = latex

# support subdirectories
VPATH = Figs

# reruns latex if needed.  to get rid of this capability, delete the
# three lines after the rule.  Delete .bbl dependency if not using
# BibTeX references.
# idea from http://ctan.unsw.edu.au/help/uk-tex-faq/Makefile
$(latexfile).dvi : $(figures) $(latexfile).tex 
	while ($(TEX) $(latexfile) ; \
	grep -q "Rerun to get" $(latexfile).log ) do true ; \
	done

# keep .eps files in the same directory as the .fig files
%.eps : %.fig
	fig2dev -L eps $< > $(dir $< )$@

$(latexfile).pdf : $(latexfile).ps
	ps2pdf $(latexfile).ps $(latexfile).pdf

pdf : $(latexfile).pdf

$(latexfile).ps : $(latexfile).dvi
	dvips $(latexfile)

ps : $(latexfile).ps 

# make can't know all the sourcefiles.  some file may not have
# sourcefiles, e.g. eps's taken from other documents. 
$(latexfile).tar.gz : $(figures) $(latexfile).tex 
	tar -czvf $(latexfile).tar.gz $^

tarball: $(latexfile).tar.gz

release: pdf 
	cp $(latexfile).pdf ../$(RELEASE_NAME).pdf
	rm -f *.aux *.dvi *.log *.out *.pdf *.ps *.toc

clean: 
	rm -f *.aux *.dvi *.log *.out *.pdf *.ps *.toc