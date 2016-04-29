class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> ret;
        int slot,target_left;
        hash_node *pTail,pTemp;

        //hash table init
        hash_node *hash_table[100];
        for(int i = 0; i < 100; i++)
            hash_table[i] = NULL;
        for(vector<int>::iterator it = nums.begin(); it != nums.end(); it++)
        {
            slot = nums[it] % 100;
            pTemp = new(hash_node);
            pTemp->data = nums[it];
            pTemp->index = it;
            pTemp->pNext = NULL;

            if(NULL == hash_table[slot])
            {
                hash_table[slot] = pTemp;
            }
            else
            {
                pTail = hash_table[slot];
                while(NULL != pTail->pNext)
                {
                    pTail = pTail->pNext;
                }
                pTail->pNext = pTemp;
            }
        }

        //search loop
        for(vector<int>::iterator it = nums.begin(); it != nums.end(); it++)
        {
            target_left = target-nums[it];
            slot = target_left%100;
            pTemp = hash_table[slot];

            if( NULL == pTemp )
                continue;

            for(;NULL != pTemp;pTemp = pTemp->pNext)
            {
                 if(pTemp->data == target_left )
                 {
                    ret.push_back(it);
                    ret.push_back(pTemp->index);
                    return ret;
                 }
            }
        }
    }
private:
    typedef struct Hash_Node {
        int data;
        int index;
        struct Hash_Node *pNext;
    } hash_node;
};
