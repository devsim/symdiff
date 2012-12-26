/***
Copyright 2012 Devsim LLC

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
***/

#include "Python.h"
#include "import.h"

#include "EquationFunctions.hh"
#include "Context.hh"
#include "SubExpr.hh"
#include "ProcessModelOrder.hh"

#include <vector>
#include <string>
#include <sstream>

namespace {
  PyObject *symdiff_exception = NULL;
};

/// Visual C++ does not allow c++ return values in extern "C"
/// There will be a python error unless there is only 1 argument
static dsHelper::ret_pair GetStringArgument(PyObject *args)
{
  dsHelper::ret_pair result = std::make_pair(false, std::string());
  const char *fromPython;
  if (PyArg_Parse(args, "(s)", &fromPython))
  {
    result.first  = true;
    result.second = fromPython;
  }
  else
  {
    result.first  = false;
//    result.second = fromPython;
  }
  return result;
}

extern "C" {
typedef std::vector<std::string> StringVector_t;

static bool HasZeroArguments(PyObject *args)
{
  bool ret = false;
  const char *fromPython;
  if (PyArg_Parse(args, "()", &fromPython))
  {
    ret = true;
  }
  return ret;
}

static PyObject *returnNone()
{
  Py_INCREF(Py_None);
  PyObject *returnObj = Py_None;
  return returnObj;
}

static PyObject *returnString(const std::string &s)
{
  return Py_BuildValue("s", s.c_str());
//  return PyUnicode_DecodeUTF8(s.c_str(), s.length(), NULL);
}


static bool GetStringArguments(PyObject *args, StringVector_t &result)
{
  bool ret = true;
  Py_ssize_t len = PyTuple_Size(args);
  result.resize(0);
  result.reserve(len);
  for (Py_ssize_t i = 0; i < len; ++i)
  {
    PyObject *item = PyTuple_GET_ITEM(args, i);
    const char *fromPython;
    if (PyArg_Parse(item, "s", &fromPython))
    {
      const std::string &tres = fromPython;
      result.push_back(tres);
    }
    else
    {
      ret = false;
      break;
    }
  }
  
  return ret;
}

static void SetErrorString(const std::string &errorString)
{

  if (!errorString.empty())
  {
    std::ostringstream os;
    os << "While calling symdiff interpreter\n";
    std::string temp_string = os.str() + errorString;
    PyErr_SetString(symdiff_exception, temp_string.c_str());
  }
}



/**
Takes one argument, which is the command to evaluate
*/
static PyObject *
symdiffCmd(PyObject *, PyObject *args)
{
  PyObject *returnObj = NULL;
  std::string errorString;

  dsHelper::ret_pair tret  = GetStringArgument(args);
  
  if (tret.first)
  {
    dsHelper::ret_pair result = std::make_pair(false, errorString);
    result = dsHelper::SymdiffEval(tret.second);
    if (!result.first)
    {
      errorString += result.second;
    }
    else
    {
      returnObj = returnString(result.second);
    }
  }

  SetErrorString(errorString);

  return returnObj;
}

static PyObject *
modelListCmd(PyObject *, PyObject *args)
{
  PyObject *returnObj = NULL;
  if (HasZeroArguments(args))
  {
    const ModelMap_t &model_list = Context::GetInstance().GetModelMap(); 
    if (model_list.empty())
    {
      //// Return none
      returnObj = returnNone();
    }
    else
    {
      returnObj = PyTuple_New(model_list.size());
      Py_ssize_t i = 0;
      for (ModelMap_t::const_iterator it = model_list.begin(); it != model_list.end(); ++it)
      {
        const std::string &model_name = (it->first);
        PyObject *subobj = returnString(model_name);
        Py_INCREF(subobj);
        PyTuple_SET_ITEM(returnObj, i, subobj);
        ++i;
      }
    }
  }

  return returnObj;
}

static PyObject *
subexpressionCmd(PyObject *, PyObject *args)
{
  PyObject *returnObj = NULL;
  std::string errorString;
  dsHelper::ret_pair result = std::make_pair(false, errorString);

  if (HasZeroArguments(args))
  {
    SubExpr subexpr;
    ModelMap_t &model_list = Context::GetInstance().GetModelMap(); 
    subexpr.CreateSubexpressions(model_list);
    errorString = subexpr.GetErrorString();
    returnObj = returnNone();
  }

  SetErrorString(errorString);

  return returnObj;
}

static PyObject *
removeZerosCmd(PyObject *, PyObject *args)
{
  PyObject *returnObj = NULL;
  if (HasZeroArguments(args))
  {
    SubExpr subexpr;
    ModelMap_t &model_list = Context::GetInstance().GetModelMap(); 
    subexpr.RemoveZeros(model_list);
    returnObj = returnNone();
  }
  return returnObj;
}

static PyObject *
orderedListCmd(PyObject *, PyObject *args)
{
  std::string errorString;
  PyObject *returnObj = NULL;
  StringVector_t model_vector_in;
  if (GetStringArguments(args, model_vector_in))
  {
    ProcessModelOrder process;
    const ModelMap_t &model_list = Context::GetInstance().GetModelMap(); 

    const ModelNameVector_t &model_vector_out = process.GetModelVector(model_list, model_vector_in);
    errorString = process.GetErrorString();

    if (errorString.empty())
    {
      if (!model_vector_out.empty())
      {
        returnObj = PyTuple_New(model_vector_out.size());
        Py_ssize_t i = 0;
        for (ModelNameVector_t::const_iterator it = model_vector_out.begin(); it != model_vector_out.end(); ++it)
        {
          const std::string &model_name = *it;
          PyObject *subobj = returnString(model_name);
          Py_INCREF(subobj);
          PyTuple_SET_ITEM(returnObj, i, subobj);
          ++i;
        }
      }
      else
      {
        returnObj = returnNone();
      }
    }
  }

  SetErrorString(errorString);

  return returnObj;
}

static struct PyMethodDef symdiff_methods[] = {
  {"symdiff",       symdiffCmd,       METH_VARARGS},
  {"model_list",    modelListCmd,     METH_VARARGS},
  {"subexpression", subexpressionCmd, METH_VARARGS},
  {"remove_zeros",  removeZerosCmd,   METH_VARARGS},
  {"ordered_list",  orderedListCmd,   METH_VARARGS},
  {NULL, NULL, 0}
};



//http://docs.python.org/2/extending/extending.html
void DLL_PUBLIC initsymdiff()
{
  PyObject *m = Py_InitModule("symdiff", symdiff_methods);
  if (m == NULL)
  {
    return;
  }
  symdiff_exception = PyErr_NewException(const_cast<char *>("symdiff.SymdiffError"), NULL, NULL);
  Py_INCREF(symdiff_exception);
  PyModule_AddObject(m, "SymdiffError", symdiff_exception);
}

#if 0
static struct _inittab symdiffinittab[] =
{
  {(char *)"symdiff", initsymdiff},
  {(char *)NULL, NULL}
};
#endif
}


