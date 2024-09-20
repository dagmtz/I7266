# set latexfile to the name of the main file without the .tex
latexfile = main

# put the names of figure files here.  include the .eps
# figures = smiley.eps logo.eps

# if no references, run "touch latexfile.bbl; touch referencefile.bib"
# or delete dependency in .dvi and tarball sections
# referencefile = refs

TEX = latex

# set the name for the PDF release 
RELEASE_NAME = Pattern_03

# support subdirectories
VPATH = Figs

pdf : $(latexfile).pdf

$(latexfile).pdf : $(latexfile).ps
	ps2pdf $(latexfile).ps $(latexfile).pdf

$(latexfile).ps : $(latexfile).dvi
	dvips $(latexfile)

# reruns latex if needed.  to get rid of this capability, delete the
# three lines after the rule.  Delete .bbl dependency if not using
# BibTeX references.
# idea from http://ctan.unsw.edu.au/help/uk-tex-faq/Makefile
$(latexfile).dvi : $(figures) $(latexfile).tex 
	while ($(TEX) $(latexfile) ; \
	grep -q "Rerun to get" $(latexfile).log ) do true ; \
	done

ps : $(latexfile).ps 

# keep .eps files in the same directory as the .fig files
%.eps : %.fig
	fig2dev -L eps $< > $(dir $< )$@

release: gif 
	cp $(latexfile).gif ../$(RELEASE_NAME).gif
	rm -f *.aux *.dvi *.log *.out *.pdf *.ps *.toc *.gif

tarball: $(latexfile).tar.gz

# make can't know all the sourcefiles.  some file may not have
# sourcefiles, e.g. eps's taken from other documents. 
$(latexfile).tar.gz : $(figures) $(latexfile).tex 
	tar -czvf $(latexfile).tar.gz $^

gif: pdf
	convert -density 300 -delay 30 -loop 0 -background white -alpha remove $(latexfile).pdf $(latexfile).gif

clean: 
	rm -f *.aux *.dvi *.log *.out *.pdf *.ps *.toc *.gif 