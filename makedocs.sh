grep -v 'SBINITJS0' ./src/sandboxe_initialization.js  > ./docbase.js
documentation build ./docbase.js -f html -o doc
rm ./docbase.js

