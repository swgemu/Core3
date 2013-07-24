GTEST_DIR = .

all:
	mkdir -p lib
	g++ -I${GTEST_DIR}/include -I${GTEST_DIR} -c ${GTEST_DIR}/src/gtest-all.cc -o lib/gtest-all.o
	cd lib && ar -rv libgtest.a gtest-all.o
	