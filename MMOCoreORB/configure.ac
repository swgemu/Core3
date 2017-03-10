AC_INIT([core3],[1.0])
AC_CANONICAL_TARGET

AC_CONFIG_AUX_DIR(build/unix/config)
AC_CONFIG_HEADER(config.h)

AM_INIT_AUTOMAKE
AM_INIT_AUTOMAKE([subdir-objects])

CXXFLAGS="$CXXFLAGS $C_EXTRA_FLAGS "

#AM_PROG_CC
AM_PROG_CC_C_O
AC_PROG_CXX
AC_PROG_RANLIB
AC_PROG_MAKE_SET

# checking for library dependencies.
AC_CHECK_HEADER(lua.h, [], [AC_MSG_ERROR([*** lua.h is required, install lua header files])])	 AC_CHECK_HEADER([mysql/mysql.h], [], [AC_MSG_ERROR([*** mysql.h is required, install mysql header files])])
AC_CHECK_HEADER(mysql/mysql.h, [], [AC_MSG_ERROR([*** mysql.h is required, install mysql header files])])	 AC_CHECK_HEADER([mysql/mysql.h], [], [AC_MSG_ERROR([*** mysql.h is required, install mysql header files])])
#AC_CHECK_HEADER(db_cxx.h, [], [AC_MSG_ERROR([*** db_cxx.h is required, install berkleydb header files])])	 AC_CHECK_HEADER([mysql/mysql.h], [], [AC_MSG_ERROR([*** mysql.h is required, install mysql header files])])
AC_CHECK_PROG([USING_HOMEBREW],[brew],[yes])
#AC_CHECK_LIB(liblua, lua_open, [], [AC_MSG_ERROR([*** libblua.a is required, install lua library files])])
#AC_CHECK_LIB(libmysqlclient, mysql_init, [], [AC_MSG_ERROR([*** libmysqlclient.a is required, install mysql library files])])
#AC_CHECK_LIB(db_cxx.a, db_env_create, [], [AC_MSG_ERROR([*** libdb_cxx.a is required, install berkleydb library files])])

case "$host_cpu-$host_os" in
    *freebsd*)
      SYSTEM_INCLUDES="-I/usr/local/include"
      SYSTEM_LIBS="-lpthread -lexecinfo"
      USER_INCLUDES_PATH="/usr/local/include"
      USER_LIBS_PATH="/usr/local/lib"
      ;;
     *darwin*)
	  if test x"${USING_HOMEBREW}" == x"yes" ; then
	  	AC_DEFINE([HAS_HOMEBREW],[],["Using Homebrew"])
		AC_MSG_RESULT("configuring for homebrew paths")
      	SYSTEM_INCLUDES="-I/usr/local/include"
      	SYSTEM_LIBS="-lpthread"
      	USER_INCLUDES_PATH="/usr/local/include"
      	USER_LIBS_PATH="/usr/local/lib"
	  else
	  	AC_DEFINE([HAS_MACPORTS],[],["Using Macports"])
		AC_MSG_RESULT("configuring for macports paths")
      	SYSTEM_INCLUDES="-I/opt/local/include"
      	SYSTEM_LIBS="-lpthread"
      	USER_INCLUDES_PATH="/opt/local/include"
      	USER_LIBS_PATH="/opt/local/lib"
	  fi
      ;;
    *cygwin*)
      SYSTEM_INCLUDES=""
      SYSTEM_LIBS="-lpthread -lwsock32"
      USER_INCLUDES_PATH="/usr/local/include"
      USER_LIBS_PATH="/usr/local/lib"
      USER_BIN_PATH="/usr/local/bin"
      ;;
    *)
      SYSTEM_INCLUDES=""
      SYSTEM_LIBS="-lrt -ldl -pthread"
      if [[ -f "/etc/redhat-release" ]]; then
          USER_INCLUDES_PATH="/usr/include"
          USER_LIBS_PATH="/usr/lib64"
      else
          USER_INCLUDES_PATH="/usr/local/include"
          USER_LIBS_PATH="/usr/local/lib"
      fi
      ;;
esac

AC_SUBST(CFLAGS)
AC_SUBST(CXXFLAGS)

AC_SUBST(SYSTEM_INCLUDES)
AC_SUBST(SYSTEM_LIBS)

AC_SUBST(USER_INCLUDES_PATH)
AC_SUBST(USER_LIBS_PATH)

AC_CONFIG_FILES([Makefile src/Makefile])
#AC_CONFIG_SUBDIRS([src/odb])

AC_OUTPUT

