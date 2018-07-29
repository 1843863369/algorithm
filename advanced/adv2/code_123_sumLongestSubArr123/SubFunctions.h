#pragma once
#ifndef SUBFUNCTION_H
#define SUBFUNCTION_H

#include <vector>
#include <iostream>
#include <algorithm>
#include <tuple>
#include <random>


typedef std::tuple<int, int, int> Results;

std::vector<int> generatePosVector();

void printVector(std::vector<int> &v);

std::vector<int> generateVector();

Results PositiveLongestArr(std::vector<int> &arr, int aim);

Results LongestSubArr(std::vector<int> &v, int aim);
Results LessEquLongestSubArr(std::vector<int> &v, int aim);

#endif