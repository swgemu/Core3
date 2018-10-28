FIND_LIBRARY(GCCLIBATOMIC_LIBRARY NAMES atomic atomic.so.1 libatomic.so.1
  HINTS
  $ENV{HOME}/local/lib64
  $ENV{HOME}/local/lib
  /usr/local/lib64
  /usr/local/lib
  /opt/local/lib64
  /opt/local/lib
  /usr/lib64
  /usr/lib
  /lib64
  /lib
)

IF (GCCLIBATOMIC_LIBRARY)
    SET(GCCLIBATOMIC_FOUND TRUE)
    MESSAGE(STATUS "Found GCC's libatomic.so: lib=${GCCLIBATOMIC_LIBRARY}")
ELSE ()
    SET(GCCLIBATOMIC_FOUND FALSE)
    MESSAGE(STATUS "GCC's libatomic.so not found.")
    MESSAGE(STATUS "Try: 'sudo yum install libatomic' or 'sudo apt-get install libatomic1')")
ENDIF ()

MARK_AS_ADVANCED (GCCLIBATOMIC_LIBRARY)
