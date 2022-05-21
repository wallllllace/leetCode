//
//  main.cpp
//  LeetCode
//
//  Created by wangxiaorui19 on 2022/5/19.
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <string>
#include <iterator>
#include <algorithm>

#include "json11.hpp"

//using std::vector;
//using std::unordered_multimap;
//using std::multimap;
//using std::cout;
//using std::endl;

using namespace std;
using namespace json11;

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

 struct ListNode {
     int val;
     ListNode *next;
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
 };
/// 两数相加
class Solution_leetcode_2 {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode *r_list = new ListNode();
        auto p = l1, q = l2, r = r_list;
        int shift = 0;
        while (p || q || shift) {
            int t = shift;
            if (p) {
                t += p->val;
                p = p->next;
            }
            if (q) {
                t += q->val;
                q = q->next;
            }
            shift = t / 10;
            r->next = new ListNode(t % 10);
            r = r->next;
        }
//        delete r_list;
        return r_list->next;
    }
};
  
// 无重复字符的最长子串
class Solution_leetcode_3 {
public:
     int lengthOfLongestSubstring(string s) {
         auto l = s.cbegin(), r = l;
         int length_max = 0;
         unordered_map<char, string::const_iterator> c_map;
         while (r != s.cend()) {
             auto it = c_map.find(*r);
             if (it != c_map.cend()) {
                 // map中存在,收缩左边界
                 if (it->second >= l) { // "abba"
                     l = it->second + 1; // 只针对找到的值在l右边有效
                 }
                 c_map.erase(it);
             }
             // 扩张右边界
             length_max = max<int>(length_max, r - l + 1);
             cout << "length:" << length_max << ", l:" << l - s.cbegin() << ",r:" << r - s.cbegin() << endl;
             c_map.insert({*r,r});
             ++r;
         }
         return length_max;
     }
};

// 寻找两个正序数组的中位数
class Solution_leetcode_4 {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        decltype(nums1.size() + nums2.size()) size = nums1.size() + nums2.size();
        if (size == 0) {
            return 0;
        }
        if (size == 1) {
            return nums1.empty() ? nums2[0] : nums1[0];
        }
        bool even = size % 2 == 0;
        int mid = size / 2;
        int i = 0;
        auto p = nums1.cbegin(), q = nums2.cbegin();
        vector<int>::const_iterator last, curr; // 记录上一个指针
        while (1) {
            if (i == mid) {
                return even ? (*last + *curr) / 2.0 : *curr;
            }
            if (p != nums1.cend() && q != nums2.cend()) {
                if (*p > *q) {
                    last = q;
                    ++q;
                } else {
                    last = p;
                    ++p;
                }
            }
             else if (p == nums1.cend()) {
                last = q;
                ++q;
            }
            else  {
                last = p;
                ++p;
            }
            
            ++i;
            if (p == nums1.cend()) {
                curr = q;
            } else if (q == nums2.cend()) {
                curr = p;
            } else {
                curr = *p < *q ? p : q;
            }
        }
        return 0;
    }
};



int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
//    Solution_leetcode_1 s1;
//    vector<int> nums{1,2,3,4,1};
//    auto result = s1.twoSum(nums, 6);
//    cout << result[0] << "," << result[1] << endl;
    
    
//    Solution_leetcode_3 s3;
//    int length = s3.lengthOfLongestSubstring("abba");
//    cout << length << endl;
    
//    Json my_json = Json::object {
//        { "key1", "value1" },
//        { "key2", false },
//        { "key3", Json::array { 1, 2, 3 } },
//    };
//    Json my_json = Json({
//                { "key1", "value1" },
//                { "key2", false },
//                { "key3", Json::array { 1, 2, 3 } },
//    });
//    string json_str = my_json.dump();
//
//    cout << "json:" << json_str <<endl;
    
    Solution_leetcode_4 s4;
    vector<int> nums1{};
    vector<int> nums2{1,2,3};
    double mid = s4.findMedianSortedArrays(nums1, nums2);
    cout << "mid:" << mid << endl;
    
    return 0;
}




