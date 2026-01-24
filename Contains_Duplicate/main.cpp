#include<iostream>
#include<vector>
#include<unordered_set>
#include<unordered_map>
#include<stdint.h>
//#include <gtest/gtest.h>
using namespace std;


class Solution {
public:
    // Solution 1: hash function
    //bool hasDuplicate(vector<int>& nums) {
    //    if(nums.size() == 0) return false;
    //    //create hash funtion 
    //    unordered_set<int> hash;
    //    for (int i = 0; i < nums.size(); i++)
    //    {
    //        if(hash.find(nums[i]) == hash.end())
    //            hash.insert(nums[i]);
    //        else
    //            return true;
    //    }
    //    return false;
    //}

        // Solution 2: brute force
    bool hasDuplicate(vector<int> nums) {
        if(nums.size() == 0) return false;
        //create hash funtion 

        for (int i = 0; i < nums.size() - 1; i++)
        {
            for (int j = 1; j < nums.size(); j++)
            {
                if(nums[i] == nums[j] )
                    return false;
            }
        }

        return true;
    }

    //Solution 3: check lenght
    bool hasDuplicate(vector<int> nums) {
        if(nums.size() == 0) return false;
        // add array và set
        // Nếu độ lớn của set khác vector thì sai vì trùng thì set bỏ phần tử đó đi
        
        unordered_set<int> v(nums.begin(), nums.end());
        if(v.size() != nums.size())
            return false;

        return true;
    }


};


// Định nghĩa bộ test
//TEST(DuplicateTest, HandlesPositiveCases) {
//    Solution so;
//    vector<int> nums = {1, 2, 3, 1};
//    EXPECT_TRUE(so.hasDuplicate(nums)); // Mong đợi kết quả là true
//}
//
//TEST(DuplicateTest, HandlesEmptyArray) {
//    Solution so;
//    vector<int> nums = {};
//    EXPECT_FALSE(so.hasDuplicate(nums)); // Mong đợi kết quả là false
//}


class dummy {
    public:

        explicit dummy() {
            cout << "Normal dummy construtor size " << endl;
        }

         dummy(dummy&& other)
         {
            cout << "Move contructor from" << " address = " << &other << " to " << this << endl;
            *this = other;
         }

        dummy(size_t size) {
            data = size;
            cout << "dummy construtor size " << size << " address = " << this << endl;
            arr = new uint8_t[size];
            for(size_t i = 0 ; i < size; i++)
            {
                arr[i] = i;
            }
        }

        ~dummy() {
            cout << "destructor caller size " << data << " address = " << this << endl;
        }

        dummy& operator()(dummy& other) {
            cout << "operator () is caller with address : " << &other << endl;
            this->data = other.data;
            this->arr = other.arr;
            other.arr = nullptr;
        }

        dummy& operator=(dummy& other) {
            cout << "operator = is caller with address : " << &other << endl;
            this->data = other.data;
            this->arr = other.arr;
            other.arr = nullptr;
        }


    private:
        int data;
        uint8_t* arr;
    

};


int main(int argc, char **argv) {
    //::testing::InitGoogleTest(&argc, argv);
    //return RUN_ALL_TESTS(); // Chạy toàn bộ các TEST trên

    //TODO: mai clear phần này
    unordered_map<uint32_t, dummy> dictory;
    //dummy intance1(8);
    dictory.insert(std::move(make_pair<uint32_t, dummy>(3, std::move(dummy(8)))));

    //dummy construtor size 8 address = 0x5ffe20 => Tạo tham số cho make_pair
    // destructor caller size 8 address => Một đối tượng tạm thời khác kiểu
    //0x5ffe08(bản sao) =(copy từ thằng này) 0x5ffe20
    //

//destructor caller size 8 address = 0x5ffe20

    Solution so;
    vector<int> nums = {1, 2, 3, 4};
    so.hasDuplicate(nums);


}//