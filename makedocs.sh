grep -v 'SBINITJS0' ./src/sandboxe_initialization.js  > ./doc/docbase.js
#documentation build ./doc/*.js -f html -o doc/html
rm -rf ./doc/html
jsdoc -d=./doc/html ./doc/*.js
rm ./doc/docbase.js

