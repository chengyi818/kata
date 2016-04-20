class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> ret;
        int slot;
        class hash_node *pTail;

        //hash table init
        class hash_node *hash_table[100];
        for(int i = 0; i < 100; i++)
            hash_table[i] = NULL;
        for(vector<int>::iterator it = nums.begin(); it != nums.end(); it++)
        {
            slot = nums[it] % 100;
            class hash_node *pTemp = new(class hash_node);
            pTemp->data = nums[it];
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

        //search




        return ret;
    }
private:
    class hash_node {
        int data;
        class hash_node *pNext;
    };
};
