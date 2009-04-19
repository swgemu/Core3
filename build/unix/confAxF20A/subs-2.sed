/@[a-zA-Z_][a-zA-Z_0-9]*@/!b end
s,@USER_LIBS_PATH@,|#_!!_#|/usr/local/lib,g
s,@LIBOBJS@,|#_!!_#|,g
s,@LTLIBOBJS@,|#_!!_#|,g
:end
s/|#_!!_#|//g
