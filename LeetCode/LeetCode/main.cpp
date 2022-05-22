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
#include <tuple>

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


/// 最长回文子串
/**
 class Solution_leetcode_5 {
 public:
     string longestPalindrome(string s) {
         if (s.empty()) {
             return "";
         }
         vector<pair<int, bool>> dp; // 保存的是以i结尾的最大回文字符串，然后找出dp中最大的一个即可
         // vector 不能通过下标添加元素
         dp.push_back({0, true});
         string longestStr = s.substr(0,1);
         for (int i = 1; i < s.size(); ++i) {
             if (dp[i-1].first != 0 && s[dp[i-1].first-1] == s[i]) {
                 dp.push_back({dp[i-1].first-1,false});
             }else if (i > 1 && s[i-2] == s[i]){
                 if (dp[i-1].second) {
                     dp.push_back({dp[i-1].first, true});
                 } else {
                     dp.push_back({i-2, false});
                 }
             }else if (s[i-1] == s[i]) {
                 if (dp[i-1].second) {
                     dp.push_back({dp[i-1].first, true});
                 } else {
                     dp.push_back({i-1, true});
                 }
             } else {
                 dp.push_back({i,true});
             }
             cout << "dp[i]:" << dp[i].first << endl;
             string s_i = s.substr(dp[i].first, i - dp[i].first + 1);
             longestStr = longestStr.size() > s_i.size() ? longestStr : s_i;
         }
         return longestStr;
     }
 };
 */

class Solution_leetcode_5 {
public:
    
    /// 思路就是：
    /// 1、 一维dp到二维dp（i和j分别是左右边界）
    /// 2、先确定子串长度为1，然后从2开始到n遍历
    string longestPalindrome(string s) {
        if (s.empty()) {
            return "";
        }
        int n = s.size();
        if (n == 1) {
            return s;
        }
        // 不要定义一个字符串保存，这样每次都要执行subStr方法，开销（时间开销、空间开销）都会增加
        // 只需保存起始位置和长度，最后返回时只用截取一次支付穿
        int maxLen = 1;
        int begin = 0;
        // 二维数组，vector这样定义
        vector<vector<int>> dp(n, vector<int>(n));
        for (int i = 0; i < n; ++i)  {
            dp[i][i] = 1;
        }
        // vector 不能通过下标添加元素
        // 枚举长度，从2开始
        for (int L = 2; L <= n; ++L) {
            // 枚举左边界
            for (int i = 0; i < n; ++i) {
               // 右边界 j - i + 1 = L
                int j = L + i - 1;
                if (j >= n) {
                    break;
                }
                if (s[i] != s[j]) {
                    dp[i][j] = 0;
                } else {
                    // 如果两个边界相等
                    if (L < 4) { // 只要是长度为3/2/1的都是回文字符串，不用特殊处理长度为1的子串了
                        dp[i][j] = 1;
                    } else {
                        dp[i][j] = dp[i+1][j-1];
                    }
                }
                if (dp[i][j] && L > maxLen) {
                    maxLen = L;
                    begin = i;
                }
            }
        }
        return s.substr(begin,maxLen);
    }
};

// "aacabdkaaaa"


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
    
//    Solution_leetcode_4 s4;
//    vector<int> nums1{};
//    vector<int> nums2{1,2,3};
//    double mid = s4.findMedianSortedArrays(nums1, nums2);
//    cout << "mid:" << mid << endl;
    
    Solution_leetcode_5 s5;
    string subs = s5.longestPalindrome("aca");
    cout << "最长回文子串是：" << subs << endl;
    
    return 0;
}




