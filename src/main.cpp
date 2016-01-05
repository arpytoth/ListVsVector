/*
 *  Precise Timer by Arpad Toth ( High Precision Timer Library )
 *  Copyright (C) 2015  Arpad Toth
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 *  Arpad Toth <arpytoth@live.com>
 */
#include "precise_timer.h"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <list>
#include <vector>

// Utility macros used to simplify the benchmark code.
#define BENCHMARK_START \
{\
  toth::PreciseTimer timer;\
  timer.start();

#define BENCHMARK_END(FunctionName) \
  timer.stop();\
  std::cout << "  * " << FunctionName <<" took: " << timer.milliseconds() << "msecs" << std::endl;\
}

int findInsertPosition(std::vector<int>& aVector, int elem) {
  int i = 0;
  for (; i < aVector.size(); ++i) {
    if (aVector[i] >= elem) {
      return i;
    }
  }
  return i;
}

std::list<int>::iterator findInsertPosition(std::list<int>& aList,  int elem) {
  std::list<int>::iterator it;
  for (it = aList.begin(); it != aList.end(); it++) {
    if (*it >= elem) {
      return it;
    }
  }
  return it;
}

void insertInVector(std::vector<int>& aVector, std::vector<int>& elems) {
  BENCHMARK_START;
  for (int i = 0; i < elems.size(); ++i) {
    int position = findInsertPosition(aVector, elems[i]);
    aVector.insert(aVector.begin() + position, elems[i]);
  }
  BENCHMARK_END("Insert in vector");
}

void insertInList(std::list<int>& aList, std::vector<int>& elems) {
  BENCHMARK_START;
  for (int i = 0; i < elems.size(); ++i) {
    std::list<int>::iterator position = findInsertPosition(aList, elems[i]);
    aList.insert(position, elems[i]);
  }
  BENCHMARK_END("Insert in list");
}

void removeFromVector(std::vector<int>& aVector, std::vector<int>& removePositions) {
  BENCHMARK_START;
  for (int i = 0; i < removePositions.size(); ++i) {
    int position = removePositions[i];
    aVector.erase(aVector.begin() + position);
  }
  BENCHMARK_END("Remove in vector");
}

void removeFromList(std::list<int>& aList, std::vector<int>& removePositions) {
  BENCHMARK_START;
  for (int i = 0; i < removePositions.size(); ++i) {
    std::list<int>::iterator position = aList.begin();
    for (int k = 0; k < removePositions[i]; k++) {
      position++;
    }
    aList.erase(position);
  }
  BENCHMARK_END("Remove from list");
}

int main() 
{
  srand (time(NULL));

  int testSize = 1000;
  std::vector<int> elems;
  std::vector<int> removePositions;
  for (int i = 0; i < testSize; ++i)
  {
    int value = rand();
    int removePos = value % (testSize - i);
    elems.push_back(value);
    removePositions.push_back(removePos);
  }

  std::vector<int> intVector;
  std::list<int> intList;

  std::cout << "INSERT BENCHMARK" << std::endl;
  insertInVector(intVector, elems);
  insertInList(intList, elems);

  std::cout << "REMOVE BENCHMARK" << std::endl;
  removeFromVector(intVector, removePositions);
  removeFromList(intList, removePositions);

  return 0;
}
