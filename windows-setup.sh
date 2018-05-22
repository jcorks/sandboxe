#/bin/sh
dynacoe-add sandboxe
echo '-I../include -I../v8-import/include/' > INCLUDES
echo '-L../v8-import/ -lv8 -lv8preparser -lpthread -lwinmm -lws2_32' > LIBRARIES


