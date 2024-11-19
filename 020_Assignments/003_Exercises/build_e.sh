PROYECT=$(basename "$PWD")
set +x
pushd tex
latexmk -pdf
cp main.pdf ../P_$PROYECT.pdf
latexmk -CA
set -x
popd