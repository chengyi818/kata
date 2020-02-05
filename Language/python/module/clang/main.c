//#include <stdio.h>
//#include <stdlib.h>
//#include <dlfcn.h>

typedef void(*add_t)(int , int);

int main(void)
{

    void *handle;
    add_t add;
    char *error;


    handle = dlopen("./func.so", RTLD_LAZY);
    if(!handle)
        {
            printf("%s\n",dlerror());
            exit(1);
        }
    add = (add_t)dlsym(handle, "add");
    if( (error=dlerror())!=NULL )
        {
            printf("%s\n",error);
            exit(1);
        }
    add(2, 3);

    return 0;
}
