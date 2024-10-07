PROYECT=$(basename "$PWD")
set +x
pushd tex
latexmk -pdf
cp main.pdf ../$PROYECT.pdf
latexmk -CA
set -x
popd