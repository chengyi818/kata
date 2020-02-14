#include <uthash.h>
#include <stdio.h>
/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    struct ListNode *next;
};

typedef struct prefix {
    int sum;
    struct ListNode* pNode;
    UT_hash_handle hh;
} Prefix;


struct ListNode* removeZeroSumSublists(struct ListNode* head){
    struct ListNode* dummpy = (struct ListNode*)malloc(sizeof(struct ListNode));
    memset(dummpy, 0, sizeof(struct ListNode));
    dummpy->next = head;
    Prefix* prefixes = NULL;

    Prefix* p = NULL;
    int prefixSum = 0;
    struct ListNode* cur = dummpy;

    while(cur) {
        prefixSum += cur->val;
        HASH_FIND_INT(prefixes, &prefixSum, p);
        // 前缀和未出现过
        if(p == NULL) {
            p = (Prefix*)malloc(sizeof(Prefix));
            p->sum = prefixSum;
            p->pNode = cur;
            HASH_ADD_INT(prefixes, sum, p);
            printf("ADD_INT: %d\n", p->sum);
        } else {
            // 0, 1, 2, -3, 3, 1
            // 将1,2,-3去除
            int curSum = p->sum;
            printf("curSum: %d\n", curSum);
            Prefix* tmpPrefix;
            struct ListNode* tmpHead = p->pNode;
            struct ListNode* tmpEnd = cur->next;
            struct ListNode* tmpIter = tmpHead;
            while(tmpIter->next != tmpEnd) {
                // 清理hash表
                curSum += tmpIter->next->val;
                printf("Iter curSum: %d\n", curSum);

                HASH_FIND_INT(prefixes, &curSum, tmpPrefix);
                HASH_DEL(prefixes, tmpPrefix);
                free(tmpPrefix);

                // 移除节点
                tmpIter->next = tmpIter->next->next;
            }
        }
        printf("Iter end\n");
        cur = cur->next;
    }

    // free hash map
    printf("free hash map\n");
    Prefix *current, *tmp;
    HASH_ITER(hh, prefixes, current, tmp) {
        HASH_DEL(prefixes, current);
        free(current);
    }

    head = dummpy->next;
    free(dummpy);
    return head;
}

int main() {
    struct ListNode p[5] = {
        {1, &p[1]},
        {2, &p[2]},
        {-3, &p[3]},
        {3, &p[4]},
        {1, &p[5]}
    };
    removeZeroSumSublists(&p[0]);
}
