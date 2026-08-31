/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        vector<int> ans = {-1, -1};

        if (!head || !head->next || !head->next->next)
            return ans;

        ListNode* prev = head;
        ListNode* curr = head->next;

        int pos = 1;
        int first = -1;
        int prevCritical = -1;

        int minDist = INT_MAX;
        int maxDist = -1;

        while (curr->next) {
            ListNode* next = curr->next;

            // Check if curr is a local maximum or minimum
            if ((curr->val > prev->val && curr->val > next->val) ||
                (curr->val < prev->val && curr->val < next->val)) {

                if (first == -1) {
                    // First critical point
                    first = pos;
                } else {
                    // Distance from previous critical point
                    minDist = min(minDist, pos - prevCritical);

                    // Distance from first critical point
                    maxDist = max(maxDist, pos - first);
                }

                prevCritical = pos;
            }

            prev = curr;
            curr = next;
            pos++;
        }

        if (maxDist == -1)
            return {-1, -1};

        return {minDist, maxDist};
    }
};

