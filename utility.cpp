//
//  utility.cpp
//  arithmetic_encoding_c++
//
//  Created by Eugene Min on 7/14/22.
//

#include "utility.h"

double factorial(double a)
{
    if(a == 0 || a == 1)
    {
        return 1;
    }
    return a * factorial(a-1);
}

double comb(double n, double r)
{
    if(r > n)
        return 0;
    
    return factorial(n)/factorial(r)/factorial(n-r);
}

double nchoosek_log2(int n, int k)
{
    if (k > n - k)
        k = n - k;
    double sum_1 = 0;
    double sum_2 = 0;
    for(int i = 0; i < k; i++)
    {
        sum_1 += log2(n - i);
        sum_2 += log2(i+1);
    }
    return sum_1 - sum_2;
}

void binary_subtraction(std::vector<int> input_bits, std::vector<int> thre, std::vector<int>& result)
{
    //-----declaration-------
    bool carry_bit;
    //------------------------
    
    carry_bit = false;
    result.assign(input_bits.size(), 0);
    for (int ii = (int)thre.size() - 1; ii >= 0; ii--)
    {
        
        if (carry_bit)
        {
            if (input_bits[ii] == 0)
            {
                if (ii == 0) // MSB
                {
                    std::cout << "Wrong Info: value is less than threshold! " << std::endl;
                    return;
                }
                result[ii] = 1 - thre[ii];
            }
            else
            {
                if (thre[ii] == 0)
                {
                    carry_bit = false;
                }
                else
                {
                    result[ii] = 1;
                    carry_bit = true;
                }
            }
        }
        else
        {
            if (input_bits[ii] == 1)
            {
                result[ii] = 1 - thre[ii];
                // carry_bit = false;
            }
            else
            {
                if (thre[ii] == 1)
                {
                    result[ii] = 1;
                    carry_bit = true;
                }
            }
        }
    }
    
    if (carry_bit) // MSB
    {
        std::cout << "Last line Wrong Info: value is less than threshold! " << std::endl;
        return;
    }
}

//void binary_addition(std::vector<int> input_bits, std::vector<int> thre, std::vector<int>& result, int& carry)
//{
//    result.assign(thre.size(), 0);
//    carry = 0;
//    int ii = (int)input_bits.size()-1, jj=(int)thre.size()-1;
//
//    for (; ii >= 0; ii--,jj--)
//    {
//        result[jj] = thre[jj] + input_bits[ii] + carry;
//        carry = result[jj] >> 2;
//        result[jj] = result[jj]%2;
//    }
//
//    for (; jj>=0; jj--)
//    {
//        result[jj] = thre[jj] + carry;
//        carry = result[jj] >> 2;
//        result[jj] = result[jj]%2;
//    }
//}

void binary_addition(std::vector<int> input_bits, std::vector<int> thre, std::vector<int>& result, int& carry)
{
    result.assign(thre.size(), 0);
    carry = 0;
    int ii = (int)input_bits.size()-1, jj=(int)thre.size()-1;

    for (; ii >= 0; ii--,jj--)
    {
        result[jj] = thre[jj] + input_bits[ii] + carry;
        carry = result[jj] >> 1;
        result[jj] = result[jj]%2;
    }
}
