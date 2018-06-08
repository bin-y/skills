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
    ListNode* deleteDuplicates(ListNode* head) {
        if (head == nullptr)
            return nullptr;
        auto node_ptr = &head;
        while ((*node_ptr)->next) {
            if ((*node_ptr)->next->val == (*node_ptr)->val) {
                (*node_ptr)->next = (*node_ptr)->next->next;
            }
            else {
                node_ptr = &(*node_ptr)->next;
            }
        }
        return head;
    }
};