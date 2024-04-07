# FLAGS = -Werror -std=c++11
# main.o: main.cpp # 목적파일: 필요한 파일
# 	g++ ${FLAGS} -o main.o # 재료

# sub.o: sub.cpp

# sum.o: sump.cpp
# 	g++ -c sum.cpp

# main.exe: main.o sub.o sum.o
# 	g++ -o main.exe main.o sub.o sum.o

# # window는 mingw32-make 사용

all:
	g++ -Werror -o main *.cpp

run:
	./main
	