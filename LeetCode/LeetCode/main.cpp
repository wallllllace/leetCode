//
//  main.cpp
//  LeetCode
//
//  Created by wangxiaorui19 on 2022/5/19.
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>

//using std::vector;
//using std::unordered_multimap;
//using std::multimap;
//using std::cout;
//using std::endl;

using namespace std;

// 两数之和
class Solution_leetcode_1 {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> mm;
        for (int i = 0; i < nums.size(); ++i) {
            auto it = mm.find(target - nums[i]);
            if (it != mm.cend()) {
                return {it->second, i};
            }
            mm.insert({nums[i], i});
        }
        return {};
        
        /*
         // 迭代器写
         unordered_map<int, int> mm;
         auto begin = nums.cbegin();
         int i = 0;
         while (begin != nums.cend()) {
             auto it = mm.find(target - *begin);
             if (it != mm.cend()) {
                 return {(*it).second, i};
             }
             mm.insert({*begin, i});
             ++i;
             ++begin;
         }
         return {};
         */
        
    }
};


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    Solution_leetcode_1 s1;
    vector<int> nums{1,2,3,4,1};
    auto result = s1.twoSum(nums, 6);
    cout << result[0] << "," << result[1] << endl;
    return 0;
}




