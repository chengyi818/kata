#include <Python.h>

// 导出函数
PyObject* wrap_fact(PyObject* self, PyObject* args)
{
    int n, result;

    if (! PyArg_ParseTuple(args, "i:fact", &n))
        return NULL;
    result = fact(n);
    return Py_BuildValue("i", result);

}

// 方法列表
static PyMethodDef exampleMethods[] =
{
    {"fact", wrap_fact, METH_VARARGS, "Caculate N!"},
    {NULL, NULL}

};

// 初始化函数
void initexample()
{
    PyObject* m;
    m = Py_InitModule("example", exampleMethods);
}
