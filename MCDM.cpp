//
//  MCDM.cpp
//  arithmetic_encoding_c++
//
//  Created by Eugene Min on 7/13/22.
//

#include "MCDM.h"
#include "utility.h"
#include <numeric>
MCDM::MCDM(float cwd_length, float p, int selector) // selector: 0 means TS and 1 means HP
{
    m_p = p; //percentage of 1's
    m_cwd_length = cwd_length;
    if(selector == 0)
    {
        define_CCDMs_TS();
    }
    else
    {
        define_CCDMs_HP();
    }
    define_thresholds();
}

float Normalized_KL(float output_length, float cb_length, float empirical_ones, float desired_ones)
{
    /*
     INPUT:
     output_length: number of bits in the ouptut of a MCDM
     cb_length: codebook length
     empirical_ones
     
     */
    float ft = -log2(abs(cb_length))/output_length;
    float st;
    float tt;
    if(empirical_ones == 0)
    {
        st = 0;
        tt = log2(1.0/(1.0 - desired_ones));
    }
    else if(empirical_ones == 1)
    {
        st = 0;
        tt = log2(empirical_ones/desired_ones);
    }
    else
    {
        st = (1.0 - empirical_ones) * log2(1.0/(1.0 - empirical_ones)) + empirical_ones * log2(1.0/empirical_ones);
        tt = (1.0 - empirical_ones) * log2((1.0 - empirical_ones)/(1.0 - desired_ones)) + empirical_ones * log2(empirical_ones/desired_ones);
    }
    return ft + st + tt;
}

void MCDM::define_CCDMs_TS()
{
    std::vector<float> KL_vect;
    std::vector<float> ordered_vect;
    std::vector<float> descend_num1;
    float target_num1_float = round(m_cwd_length * m_p); // The best-fit distribution
    for(int i = 0; i <= m_cwd_length; i++) //Initialize array of ascending numerical order
        ordered_vect.push_back(i);
    int i = 1;
    descend_num1.push_back(target_num1_float);
    if(m_p < 0.5)
    {
        while(descend_num1.size() < ordered_vect.size())
        {
            if(target_num1_float + i < ordered_vect.size())
                descend_num1.push_back(ordered_vect[target_num1_float + i]);
            if(target_num1_float- i > -1)
                descend_num1.push_back(ordered_vect[target_num1_float - i]);
                i++;
        }
    }
    else
    {
        while(descend_num1.size() < ordered_vect.size())
        {
            if(target_num1_float- i > -1)
                descend_num1.push_back(ordered_vect[target_num1_float - i]);
            if(target_num1_float + i < ordered_vect.size())
                descend_num1.push_back(ordered_vect[target_num1_float + i]);
                i++;
        }
    }
    
    int numCCDMs = 1;
    float num1;
    int cb_length = 0;
    double available_cwds = 0;
    std::vector<int> single_cb_length;
    std::vector<float> CCDMs;
    while(numCCDMs <= (m_cwd_length + 1))
    {
        num1 = 0;
        // Keep track of num1, cb_length, and available_cwds
        
        available_cwds += std::pow(2, (floor(log2(comb(m_cwd_length, descend_num1[numCCDMs-1])))));
        single_cb_length.push_back(std::pow(2,(floor(log2((comb(m_cwd_length, descend_num1[numCCDMs-1])))))));
        
        // Update only if MCDM codebook expands
        if(floor(log2(available_cwds)) > log2(cb_length))
        {
            cb_length = std::pow(2, floor(log2(available_cwds))); // Update codebook length
            int temp_cb_length = cb_length;
            for(int mini_cb = 0; mini_cb < single_cb_length.size(); mini_cb++)
            {
                if(single_cb_length[mini_cb] <= temp_cb_length)
                {
                    num1 += single_cb_length[mini_cb] * descend_num1[mini_cb];
                    temp_cb_length -= single_cb_length[mini_cb];
                }
                else
                {
                    num1 += temp_cb_length * descend_num1[mini_cb];
                    break;
                }
            }
            float empirical_ones_prob = num1 / (m_cwd_length * cb_length);
            // Calculate Normalized KL
            float temp_KL = Normalized_KL(m_cwd_length, cb_length, empirical_ones_prob, m_p);
            KL_vect.push_back(temp_KL); // Append results to a list
        }
        else //// If not update
        {
            KL_vect.push_back(KL_vect[numCCDMs - 2]);
        }
        
        if((KL_vect[KL_vect.size()-2] < KL_vect[KL_vect.size()-1]  && KL_vect.size() > 1) || KL_vect.size() == m_cwd_length+1)
        {
            m_input_length = log2(cb_length);
            for(int i = 0; i < descend_num1.size(); i++)
                descend_num1[i] /= m_cwd_length;
            initialize_CCDMs(descend_num1, numCCDMs - 1);
            break;
        }
        
        numCCDMs ++;  // Update iterator
    }
}

void MCDM::define_CCDMs_HP()
{
    std::vector<float> KL_vect;
    int numCCDMs = 1;
    float num1;
    int cb_length = 0;
    double available_cwds = 0;
    std::vector<int> single_cb_length;
    std::vector<float> CCDMs;
    while(numCCDMs <= (m_cwd_length + 1))
    {
        num1 = 0;
        // Keep track of num1, cb_length, and available_cwds
        
        available_cwds += std::pow(2, (floor(log2(comb(m_cwd_length, numCCDMs-1)))));
        single_cb_length.push_back(std::pow(2,(floor(log2((comb(m_cwd_length, numCCDMs-1)))))));
        
        // Update only if MCDM codebook expands
        if(floor(log2(available_cwds)) > log2(cb_length))
        {
            cb_length = std::pow(2, floor(log2(available_cwds))); // Update
            int temp_cb_length = cb_length;
            for(int mini_cb = 0; mini_cb < single_cb_length.size(); mini_cb++)
            {
                if(single_cb_length[mini_cb] <= temp_cb_length)
                {
                    if(m_p > 0.5) //// Start from all 1's
                    {
                        for(int i = m_cwd_length; i >= 0; i--)
                            CCDMs.push_back(float(i)/m_cwd_length);
                        num1 += single_cb_length[mini_cb] * (m_cwd_length - mini_cb);
                    }
                    else
                    {
                        for(int i = 0; i <= m_cwd_length; i++)
                            CCDMs.push_back(float(i)/m_cwd_length);
                        num1 += single_cb_length[mini_cb] * mini_cb;
                    }
                    temp_cb_length -= single_cb_length[mini_cb];
                }
                else
                {
                    if(m_p > 0.5)
                    {
                        num1 += temp_cb_length * (m_cwd_length - mini_cb);
                    }
                    else
                    {
                        num1 += temp_cb_length * mini_cb;
                        break;
                    }
                }
            }
            
            float empirical_ones_prob = num1 / (m_cwd_length * cb_length);
            // Calculate Normalized KL
            float temp_KL = Normalized_KL(m_cwd_length, cb_length, empirical_ones_prob, m_p);
            KL_vect.push_back(temp_KL); // Append results to a list
        }
        else //// If not update
        {
            KL_vect.push_back(KL_vect[numCCDMs - 2]);
        }
        
        if((KL_vect[KL_vect.size()-2] < KL_vect[KL_vect.size()-1]  && KL_vect.size() > 1) || KL_vect.size() == m_cwd_length)
        {
            m_input_length = log2(cb_length);
            initialize_CCDMs(CCDMs, numCCDMs - 1);
            break;
        }
        
        numCCDMs ++;  // Update iterator
    }
    
}

void MCDM::initialize_CCDMs(std::vector<float> p, int numCCDMs)
{
    for(int i = 0; i < numCCDMs; i++)
        CCDMcollection.push_back(new CCDM(m_cwd_length, p[i]));
}

void MCDM::define_thresholds()
{
    std::vector <int> zero;
    zero.assign(m_input_length, 0); //define first threshold
    thresholds.push_back(zero); //push back zeroth threshold
    for(int i = 0; i < CCDMcollection.size()-1; i++)
    {
        std::vector <int> thresh;
        int carry;
        thresh.assign(m_input_length, 0);
        thresh[m_input_length - CCDMcollection[i]->getInputSize() - 1] = 1; //figure out which position to put a 1 in
        std::vector <int> result;
        binary_addition(thresh, thresholds[i], result, carry);
        if(carry)
            break; 
        thresholds.push_back(result);
    }
    std::vector<int> ones;
    ones.assign(m_input_length + 1, 0);
    ones[0] = 1;
    thresholds.push_back(ones);
}

//Encoding//

int MCDM::find_group_with_threshold(std::vector<int> input_bits)
{
    int high = thresholds.size() - 2;
    int low = 0;
    while(low <= high)
    {
        int mid = (high + low)/2;
        std::vector<int> threshold = thresholds[mid];
        if(threshold < input_bits)
            low = mid + 1;
        else if(threshold > input_bits)
            high = mid - 1;
        else
            return mid;
    }
    return low - 1;
}

std::vector<int> MCDM::encode(std::vector<int> MCDM_input_bits)
{
    //determine CCDM
    int CCDM_num = find_group_with_threshold(MCDM_input_bits);
    //Compute CCDM input
    std::vector<int> CCDM_input;
    binary_subtraction(MCDM_input_bits, thresholds[CCDM_num], CCDM_input);
    //Run CCDM encoding
    std::vector<int> CCDM_output;
    CCDMcollection[CCDM_num]->encode(CCDM_input, CCDM_output);
    return CCDM_output;
}

//Decoding//

int MCDM::find_group_with_type(std::vector<int> input_bits)
{
    int num0 = 0;
    int num1 = 0;
    for(int n = 0; n < input_bits.size(); n++)
        if(input_bits[n] == 0)
            num0++;
        else
            num1++;
    float p = float(num1) / (num1 + num0);
    int i;
    for(i = 0; i < CCDMcollection.size(); i++)
    {
        if(CCDMcollection[i]->getP() == p)
            return i;
    }
    return -1;
}

bool MCDM::decode(std::vector<int> CCDM_output_bits, std::vector<int>& original_binary)
{
    //Determine validity of input
    int CCDM_num = find_group_with_type(CCDM_output_bits);
    if(CCDM_num == -1)
        return false;
    //CCDM decode
    std::vector<int> CCDM_input;
    CCDMcollection[CCDM_num]->decode(CCDM_output_bits, CCDM_input, m_input_length);
    //Add back threshold
    std::vector<int> padded_CCDM_input;
    for(int i = CCDM_input.size(); i < m_input_length; i++)
        padded_CCDM_input.push_back(0);
    for(int i = 0; i < CCDM_input.size(); i++)
        padded_CCDM_input.push_back(CCDM_input[i]);
    int carry;
    binary_addition(padded_CCDM_input, thresholds[CCDM_num], original_binary, carry);
    return true;
}
