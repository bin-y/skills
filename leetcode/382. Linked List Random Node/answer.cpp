std::random_device rd_;
std::mt19937 mt_(rd_());

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* head_;
    /** @param head The linked list's head.
        Note that the head is guaranteed to be not null, so it contains at least one node. */
    uintptr_t count_;
    unique_ptr<uniform_int_distribution<uintptr_t>> dist__;
    uniform_int_distribution<uintptr_t>* dist_;
    Solution(ListNode* head) : head_(head) {
        count_ = 0;
        while(head) {
            count_++;
            head = head->next;
        }
        dist__.reset(new uniform_int_distribution<uintptr_t>(0, count_ - 1));
        dist_ = dist__.get();
    }
    
    /** Returns a random node's value. */
    int getRandom() {
        auto n = (*dist_)(mt_);
        auto result_node = head_;
        while(n) {
            result_node = result_node->next;
            n--;
        }
        return result_node->val;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution obj = new Solution(head);
 * int param_1 = obj.getRandom();
 */