ENGINE3_PATH=../../../../MMOEngine
LUA_INCLUDE=/usr/include/lua5.1
MYSQL_INCLUDE=/usr/include/mysql
BERKELEY_INCLUDE=/usr/local/BerkeleyDB.5.0/include

engine.h.gch: $(ENGINE3_PATH)/include/engine/engine.h
	g++ -I/opt/local/include -I/usr/include -I$(ENGINE3_PATH)/include -I$(LUA_INCLUDE) -I$(MYSQL_INCLUDE) -I$(BERKELEY_INCLUDE)  $(ENGINE3_PATH)/include/engine/engine.h

all: engine.h.gch
	#done 
	