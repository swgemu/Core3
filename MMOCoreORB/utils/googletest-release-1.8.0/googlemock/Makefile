GTEST_DIR = ../googletest
GMOCK_DIR = .

gtest-all.o: ${GTEST_DIR}/src/gtest-all.cc
		$(CXX) $(CPPFLAGS) $(CXXFLAGS) -pthread -std=c++11 -I${GTEST_DIR}/include -I${GTEST_DIR} -I${GMOCK_DIR}/include -I${GMOCK_DIR} -c ${GTEST_DIR}/src/gtest-all.cc -o lib/gtest-all.o

gmock-all.o: ${GMOCK_DIR}/src/gmock-all.cc
		$(CXX) $(CPPFLAGS) $(CXXFLAGS) -pthread -std=c++11 -I${GTEST_DIR}/include -I${GTEST_DIR} -I${GMOCK_DIR}/include -I${GMOCK_DIR} -c ${GMOCK_DIR}/src/gmock-all.cc -o lib/gmock-all.o

compile: gtest-all.o gmock-all.o

clean:
		rm -f lib/*.o

all:	
		mkdir -p lib
		${MAKE} compile
		cd lib && ar -rv libgtest.a gtest-all.o gmock-all.o