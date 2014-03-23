AC_INIT([odb3],[1.0])
AC_CANONICAL_TARGET

AC_CONFIG_AUX_DIR(build/unix/config)
AC_CONFIG_HEADER(config.h)

AM_INIT_AUTOMAKE
AM_INIT_AUTOMAKE([subdir-objects])

CXXFLAGS="$CXXFLAGS $C_EXTRA_FLAGS "

AC_PROG_CC
AC_PROG_CXX
AC_PROG_RANLIB

case "$host_cpu-$host_os" in
    *freebsd*)
      SYSTEM_INCLUDES="-I/usr/local/include"
      SYSTEM_LIBS="-lpthread -lexecinfo"
      USER_INCLUDES_PATH="/usr/local/include"
      USER_LIBS_PATH="/usr/local/lib"
      ;;
     *darwin*)
      SYSTEM_INCLUDES="-I/opt/local/include"
      SYSTEM_LIBS="-lpthread"
      USER_INCLUDES_PATH="/opt/local/include"
      USER_LIBS_PATH="/opt/local/lib"
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
      SYSTEM_LIBS="-lrt -ldl -lpthread"
      USER_INCLUDES_PATH="/usr/local/include"
      USER_LIBS_PATH="/usr/local/lib"
esac

AC_SUBST(CFLAGS)
AC_SUBST(CXXFLAGS)

AC_SUBST(SYSTEM_INCLUDES)
AC_SUBST(SYSTEM_LIBS)

AC_SUBST(USER_INCLUDES_PATH)
AC_SUBST(USER_LIBS_PATH)

AC_CONFIG_FILES([Makefile])
AC_OUTPUT

