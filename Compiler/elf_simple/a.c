/* a.c */
extern int shared;
void swap(int*, int*);

int main()
{
    int a = 100;
    swap(&a, &shared);
}
