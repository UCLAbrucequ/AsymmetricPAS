#include "arithmetic_encoding.h"
#include "MCDM.h"
#include "utility.h"
#include <assert.h>
using namespace std;

void printVect(vector <int> print)
{
    for(int i = 0; i < print.size(); i++)
        cout << print[i];
    cout << endl;
}

void testCCDM_encode(vector<vector<int>> testVect, CCDM dm1)
{
    vector<int> result;
    for(int i = 0; i < testVect.size(); i++)
    {
        (dm1.encode(testVect[i], result));
        printVect(result);
    }
}

void testCCDM_decode(vector<vector<int>> testVect, CCDM dm1)
{
    vector<int> result;
    for(int i = 0; i < testVect.size(); i++)
    {
        //assert(dm1.decode(testVect[i], result)); only works for CCDM testing, not MCDM
        printVect(result);
    }
}

int main()
{
    //Testing MCDM
    
    
    /* Initial Testing of CCDM*/
    CCDM dm1(4, .5);
    //    assert(dm1.encode("00") == "0011");
    //    assert(dm1.encode("01") == "0110");
    //    assert(dm1.encode("10") == "1001");
    //    assert(dm1.encode("11") == "1100");
    //    assert(dm1.decode("0011") == "00");
    //    assert(dm1.decode("0110") == "01");
    //    assert(dm1.decode("1001") == "10");
    //    assert(dm1.decode("1100") == "11");
    //    assert(dm1.decode("0000") == "");
    //
//    vector<vector<int>> vect1_enc{{0,0},{0,1},{1,0},{1,1}};
//    testCCDM_encode(vect1_enc, dm1);
//    vector<vector<int>> vect1_dec{{0,0,1,1},{0,1,1,0},{1,0,0,1},{1,1,0,0}};
//    testCCDM_decode(vect1_dec, dm1);
    
        CCDM dm2(4, .25);
    //    assert(dm2.encode("00") == "0001");
    //    assert(dm2.encode("01") == "0010");
    //    assert(dm2.encode("10") == "0100");
    //    assert(dm2.encode("11") == "1000");
    //    assert(dm2.decode("0001") == "00");
    //    assert(dm2.decode("0010") == "01");
    //    assert(dm2.decode("0100") == "10");
    //    assert(dm2.decode("1000") == "11");
//    vector<vector<int>> vect2_enc{{0,0},{0,1},{1,0},{1,1}};
//    testCCDM_encode(vect2_enc, dm2);
//    vector<vector<int>> vect2_dec{{0,0,0,1},{0,0,1,0},{0,1,0,0},{1,0,0,0}};
//    testCCDM_decode(vect2_dec, dm2);
    
        CCDM dm3(4, .75);
    //    assert(dm3.encode("00") == "0111");
    //    assert(dm3.encode("01") == "1011");
    //    assert(dm3.encode("10") == "1101");
    //    assert(dm3.encode("11") == "1110");
    //    assert(dm3.decode("0111") == "00");
    //    assert(dm3.decode("1011") == "01");
    //    assert(dm3.decode("1101") == "10");
    //    assert(dm3.decode("1110") == "11");
    //
//    vector<vector<int>> vect3_enc{{0,0},{0,1},{1,0},{1,1}};
//    testCCDM_encode(vect3_enc, dm3);
//    vector<vector<int>> vect3_dec{{0,1,1,1},{1,0,1,1},{1,1,0,1},{1,1,1,0}};
//    testCCDM_decode(vect3_dec, dm3);
    
        CCDM dm4(5, 3.0/5);
    //    assert(dm4.encode("000") == "00111");
    //    assert(dm4.encode("001") == "01101");
    //    assert(dm4.encode("100") == "10101");
    //    assert(dm4.encode("101") == "11001");
    //    assert(dm4.encode("110") == "11010");
    //    assert(dm4.encode("111") == "11100");
    //    assert(dm4.decode("00111") == "000");
    //    assert(dm4.decode("01101") == "001");
    //    assert(dm4.decode("10101") == "100");
    //    assert(dm4.decode("11001") == "101");
    //    assert(dm4.decode("11010") == "110");
    //    assert(dm4.decode("11100") == "111");
    //
//    vector<vector<int>> vect4_enc{{0,0,0}, {0,0,1}, {1,0,0}, {1,0,1}, {1,1,0}, {1,1,1}};
//    testCCDM_encode(vect4_enc, dm4);
//    vector<vector<int>> vect4_dec{{0,0,1,1,1},{0,1,1,0,1},{1,0,1,0,1},{1,1,0,0,1},{1,1,0,1,0},{1,1,1,0,0}};
//    testCCDM_decode(vect4_dec, dm4);
    
        CCDM dm5(5, 2.0/5);
    //    assert(dm5.encode("000") == "00011");
    //    assert(dm5.encode("001") == "00110");
    //    assert(dm5.encode("100") == "10001");
    //    assert(dm5.encode("101") == "10010");
    //    assert(dm5.encode("110") == "10100");
    //    assert(dm5.encode("111") == "11000");
    //    assert(dm5.decode("00011") == "000");
    //    assert(dm5.decode("00110") == "001");
    //    assert(dm5.decode("10001") == "100");
    //    assert(dm5.decode("10010") == "101");
    //    assert(dm5.decode("10100") == "110");
    //    assert(dm5.decode("11000") == "111");
    //
//    vector<vector<int>> vect5_enc{{0,0,0}, {0,0,1}, {1,0,0}, {1,0,1}, {1,1,0}, {1,1,1}};
//    testCCDM_encode(vect5_enc, dm5);
//    vector<vector<int>> vect5_dec{{0,0,0,1,1},{0,0,1,1,0},{1,0,0,0,1},{1,0,0,1,0},{1,0,1,0,0},{1,1,0,0,0}};
//    testCCDM_decode(vect5_dec, dm5);
    
//        CCDM dm6(8, 3.0/8);
    //    assert(dm6.encode("11100") == "11000001");
    //    assert(dm6.encode("10110") == "10001100");
    //    assert(dm6.decode("11000001") == "11100");
    //    assert(dm6.decode("10001100") == "10110");
//    vector<vector<int>> vect6_enc{{1,1,1,0,0},{1,0,1,1,0}}
//    testCCDM_encode(vect6_enc, dm6);
//    vector<vector<int>> vect6_dec{{1,1,0,0,0,0,0,1},{1,0,0,0,1,1,0,0}};
//    testCCDM_decode(vect6_dec, dm6);
    MCDM mcdm1(10, 0.476309, 0);
    vector <int> input_bits{1,1,1,1,1,1,0,0,0};
    vector <int> result;
    result = mcdm1.encode(input_bits);
    printVect(result);
    
    vector <int> output_bits{1,0,1,0,0,0,0,0,0,1};
    vector <int> result2;
    mcdm1.decode(output_bits, result2);
    printVect(result2);
    //void binary_addition(std::vector<int> input_bits, std::vector<int> thre, std::vector<int>& result, int& carry)
    //void binary_subtraction(std::vector<int> input_bits, std::vector<int> thre, std::vector<int>& result);
    
    /* Testing Binary addition and subtraction*/
    /*vector <int> v1{1, 0, 0, 0};
     vector <int> v2{0, 0, 0, 1};
     vector <int> result;
     int carry;
     binary_subtraction(v1, v2, result);
     printVect(result);*/
    
//    vector <int> v1{0,1,1,0};
//    vector <int> v2{0,1,1,0};
//    vector <int> result;
//    int carry;
//    binary_addition(v1, v2, result, carry);
//    printVect(result);
    
//    CCDM dm7(5, 1);
//    vector<vector<int>> vect7_enc{{0,0,0,0}};
//    testCCDM_encode(vect7_enc, dm7);
//
//    CCDM dm8(5, .8);
//    vector<vector<int>> vect8_enc{{0,0,0,0}, {0,0,0,1}, {0,0,1,0}, {0,0,1,1}};
//    testCCDM_encode(vect8_enc, dm8);
//
//    CCDM dm9(5, .6);
//    vector<vector<int>> vect9_enc{{0,0,0,0}, {0,0,0,1}, {0,0,1,0}, {0,0,1,1}, {0,1,0,0}, {0,1,0,1}, {0,1,1,0}, {0,1,1,1}};
//    testCCDM_encode(vect9_enc, dm9);
//
//    CCDM dm10(5, .4);
//    vector<vector<int>> vect10_enc{{0,0,0,0}, {0,0,0,1}, {0,0,1,0}};
//    testCCDM_encode(vect10_enc, dm10);

    
    
}
