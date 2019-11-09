#!/bin/sh
rm -rdf ./build
rm -rdf ./dist
rm -rdf ./.vs-code
rm -rdf ./.vs
rm *.zip

git add .


commit=`git commit -m "$1"`