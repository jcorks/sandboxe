grep -v 'SBINITJS0' ./src/sandboxe_initialization.js  > ./doc/docbase.js
documentation build ./doc/*.js -f html -o doc/html
rm ./doc/docbase.js

