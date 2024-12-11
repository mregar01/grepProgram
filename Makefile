###
### Makefile for Zap Project
###
### Author: Max Regardie and Nikola Muromcew


MAKEFLAGS += -L 
CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow


indexTree.o: indexTree.cpp indexTree.h FSTree.h DirNode.h
	$(CXX) $(CXXFLAGS) -c indexTree.cpp

fileHash.o: fileHash.cpp fileHash.h indexTree.h indexTree.cpp FSTree.h DirNode.h
	$(CXX) $(CXXFLAGS) -c fileHash.cpp

gerp.o: gerp.cpp gerp.h fileHash.cpp fileHash.h indexTree.h indexTree.cpp \
FSTree.h DirNode.h
	$(CXX) $(CXXFLAGS) -c gerp.cpp

main.o: main.cpp gerp.cpp gerp.h fileHash.cpp fileHash.h indexTree.h \
indexTree.cpp FSTree.h DirNode.h
	$(CXX) $(CXXFLAGS) -c main.cpp

gerp: indexTree.o fileHash.o gerp.o main.o FSTree.o DirNode.o
	$(CXX) $(CXXFLAGS) -o gerp $^

