//
//  MCDM.hpp
//  arithmetic_encoding_c++
//
//  Created by Eugene Min on 7/13/22.
//

#ifndef MCDM_h
#define MCDM_h

#include <stdio.h>
#include <vector>
#include "arithmetic_encoding.h"
class MCDM{
public:
    MCDM(float cwd_length, float p, int selector);
    void define_CCDMs_TS();
    void define_CCDMs_HP();
    void initialize_CCDMs(std::vector<float> p, int numCCDMs);
    void define_thresholds();
    
    //Encoding
    int find_group_with_threshold(std::vector<int> input_bits);
    std::vector<int> encode(std::vector<int> input_bits);
    
    //Decoding
    int find_group_with_type(std::vector<int> input_bits);
    bool decode(std::vector<int> output_bits, std::vector<int>& original_binary);
private:
    std::vector<CCDM*> CCDMcollection;
    int m_cwd_length;
    float m_p;
    int m_input_length; 
    std::vector<std::vector<int>> thresholds;
};
#endif /* MCDM_hpp */
