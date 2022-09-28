//
//  utility.hpp
//  arithmetic_encoding_c++
//
//  Created by Eugene Min on 7/14/22.
//

#ifndef utility_h
#define utility_h

#include <stdio.h>
#include <cmath>
#include <vector>
#include <iostream>
double factorial(double a);
double comb(double n, double r);
double nchoosek_log2(int n, int k);
void binary_subtraction(std::vector<int> input_bits, std::vector<int> thre, std::vector<int>& result);
void binary_addition(std::vector<int> input_bits, std::vector<int> thre, std::vector<int>& result, int& carry);
#endif /* utility_hpp */
