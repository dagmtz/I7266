PROYECT=$(basename "$PWD")
set +x
pushd tex
latexmk -pdf
cp main.pdf ../$PROYECT.pdf
latexmk -CA
rm *.bbl *.nav *.snm
set -x
popd