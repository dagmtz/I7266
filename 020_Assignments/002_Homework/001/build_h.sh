PROYECT=$(basename "$PWD")
set +x
pushd tex
latexmk -pdf
cp main.pdf ../H_$PROYECT.pdf
latexmk -CA
rm *converted-to.pdf
popd
set -x
