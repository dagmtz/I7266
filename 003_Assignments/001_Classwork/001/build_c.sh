PROYECT=$(basename "$PWD")
set +x
pushd tex
latexmk -pdf
cp main.pdf ../C_$PROYECT.pdf
latexmk -CA
set -x
popd