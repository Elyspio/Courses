# !/bin/sh
rm -rdf ./build
rm -rdf ./dist
rm -rdf ./.vs-code
rm -rdf ./.vs
rm *.zip

rm `find . -name "*.o"`     

git add .


# commit=`git commit -m "$1"`