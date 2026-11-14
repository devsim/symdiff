/***
Copyright 2012 DEVSIM LLC

SPDX-License-Identifier: Apache-2.0
***/

/* removes Python_d.lib from any contention */
//#undef _DEBUG
#ifdef _WIN32
/* remove warning on windows for function we do not use */
#define HAVE_ROUND
#endif
#include "Python.h"
#include "import.h"

#include "EquationFunc.hh"
#include "Context.hh"
#include "SubExpr.hh"
#include "ProcessModelOrder.hh"
#include "ProcessOrderedTable.hh"
#include "EngineAPI.hh"

#include <vector>
#include <string>
#include <sstream>
#include <mutex>

namespace {
  std::mutex symdiff_command_mutex;
};

namespace {
struct module_state {
  PyObject *error;
};

#define GETSTATE(m) ((struct module_state*)PyModule_GetState(m))
}

/// Visual C++ does not allow c++ return values in extern "C"
/// There will be a python error unless there is only 1 argument
static sdHelp::ret_pair GetStringArgument(PyObject *args)
{
  sdHelp::ret_pair result;
  result.first = false;
  const char *fromPython;
  if (PyArg_Parse(args, "(s)", &fromPython))
  {
    result.first  = true;
    result.second.string_ = fromPython;
  }
  else
  {
    result.first  = false;
  }
  return result;
}

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
}

static PyObject *returnLong(size_t i)
{
  return PyLong_FromSsize_t(i);
}

static PyObject *returnTupleLong(const std::vector<size_t> &index)
{
  PyObject *returnObj = PyTuple_New(index.size());
  PyObject *subobj;
  for (size_t i = 0; i < index.size(); ++i)
  {
    subobj = returnLong(index[i]);
    PyTuple_SetItem(returnObj, i, subobj);
    Py_INCREF(subobj);
  }
  return returnObj;
}


static bool GetStringArguments(PyObject *args, StringVector_t &result)
{
  bool ret = true;
  Py_ssize_t len = PyTuple_Size(args);
  result.resize(0);
  result.reserve(len);
  for (Py_ssize_t i = 0; i < len; ++i)
  {
    PyObject *item = PyTuple_GetItem(args, i);
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

static void SetErrorString(PyObject *exception, const std::string &errorString)
{

  if (!errorString.empty())
  {
    std::ostringstream os;
    os << "While calling symdiff interpreter\n";
    std::string temp_string = os.str() + errorString;
    PyErr_SetString(exception, temp_string.c_str());
  }
}



/**
Takes one argument, which is the command to evaluate
*/
static PyObject *
symdiffCmd(PyObject *self, PyObject *args)
{
  std::lock_guard<std::mutex> lock(symdiff_command_mutex);
  PyObject *returnObj = nullptr;
  std::string errorString;

  sdHelp::ret_pair tret  = GetStringArgument(args);
  
  if (tret.first)
  {
    sdHelp::ret_pair result;
    result.first = false;
    result = sdHelp::SymdiffEval(tret.second.string_);
    if (!result.first)
    {
      errorString += result.second.string_;
    }
    else
    {
      returnObj = returnString(result.second.string_);
    }
  }

  SetErrorString(GETSTATE(self)->error, errorString);

  return returnObj;
}

static PyObject *
symdiffTableCmd(PyObject *self, PyObject *args)
{
  std::lock_guard<std::mutex> lock(symdiff_command_mutex);
  PyObject *returnObj = nullptr;
  std::string errorString;

  sdHelp::ret_pair tret  = GetStringArgument(args);
  
  if (tret.first)
  {
    sdHelp::ret_pair result;
    result.first = false;
    result = sdHelp::SymdiffEval(tret.second.string_);
    if (!result.first)
    {
      errorString += result.second.string_;
    }
    else
    {
      ProcessOrderedTable pot;
      pot.run(result.second.eqptr_);
//      returnObj = returnString(result.second.string_);
      OrderedTable_t table = pot.GetOrderedTable();
      if (table.empty())
      {
        returnObj = returnNone();
      }
      else
      {
        returnObj = PyTuple_New(table.size());
        for (size_t i = 0; i < table.size(); ++i)
        {
          const OrderedTableData &data = table[i];
          PyObject *rowobj = PyTuple_New(5);

          const std::string &name = EngineAPI::getName(data.ptr_);
          const std::string &type = EngineAPI::getType(data.ptr_);
          const std::string &value = data.value_;
          const std::vector<size_t> &indexes = data.indexes_;
          const std::vector<size_t> &references = data.references_;

          PyObject *subobj;
          subobj = returnString(name);
          Py_INCREF(subobj);
          PyTuple_SetItem(rowobj, 0, subobj);

          subobj = returnString(type);
          Py_INCREF(subobj);
          PyTuple_SetItem(rowobj, 1, subobj);

          subobj = returnTupleLong(indexes);
          Py_INCREF(subobj);
          PyTuple_SetItem(rowobj, 2, subobj);

          subobj = returnTupleLong(references);
          Py_INCREF(subobj);
          PyTuple_SetItem(rowobj, 3, subobj);

          subobj = returnString(value);
          Py_INCREF(subobj);
          PyTuple_SetItem(rowobj, 4, subobj);

          Py_INCREF(rowobj);
          PyTuple_SetItem(returnObj, i, rowobj);
        }
      }
    }
  }

  SetErrorString(GETSTATE(self)->error, errorString);

  return returnObj;
}

static PyObject *
modelListCmd(PyObject *, PyObject *args)
{
  std::lock_guard<std::mutex> lock(symdiff_command_mutex);
  PyObject *returnObj = nullptr;
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
        PyTuple_SetItem(returnObj, i, subobj);
        ++i;
      }
    }
  }

  return returnObj;
}

static PyObject *
subexpressionCmd(PyObject *self, PyObject *args)
{
  std::lock_guard<std::mutex> lock(symdiff_command_mutex);
  PyObject *returnObj = nullptr;
  std::string errorString;
  sdHelp::ret_pair result;
  result.first = false;

  if (HasZeroArguments(args))
  {
    SubExpr subexpr;
    ModelMap_t &model_list = Context::GetInstance().GetModelMap(); 
    subexpr.CreateSubexpressions(model_list);
    errorString = subexpr.GetErrorString();
    returnObj = returnNone();
  }

  SetErrorString(GETSTATE(self)->error, errorString);

  return returnObj;
}

static PyObject *
removeZerosCmd(PyObject *, PyObject *args)
{
  std::lock_guard<std::mutex> lock(symdiff_command_mutex);
  PyObject *returnObj = nullptr;
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
orderedListCmd(PyObject *self, PyObject *args)
{
  std::lock_guard<std::mutex> lock(symdiff_command_mutex);
  std::string errorString;
  PyObject *returnObj = nullptr;
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
          PyTuple_SetItem(returnObj, i, subobj);
          ++i;
        }
      }
      else
      {
        returnObj = returnNone();
      }
    }
  }

  SetErrorString(GETSTATE(self)->error, errorString);

  return returnObj;
}

static struct PyMethodDef symdiff_methods[] = {
  {"symdiff",       symdiffCmd,       METH_VARARGS},
  {"symdiff_table", symdiffTableCmd,  METH_VARARGS},
  {"model_list",    modelListCmd,     METH_VARARGS},
  {"subexpression", subexpressionCmd, METH_VARARGS},
  {"remove_zeros",  removeZerosCmd,   METH_VARARGS},
  {"ordered_list",  orderedListCmd,   METH_VARARGS},
  {nullptr, nullptr, 0}
};



static int symdiff_traverse(PyObject *m, visitproc visit, void *arg) {
    Py_VISIT(GETSTATE(m)->error);
    return 0;
}

static int symdiff_clear(PyObject *m) {
    Py_CLEAR(GETSTATE(m)->error);
    return 0;
}

#ifndef SYMDIFF_PYTHON3T
static struct PyModuleDef moduledef = {
        PyModuleDef_HEAD_INIT,
        "symdiff_py3",
        nullptr,
        sizeof(struct module_state),
        symdiff_methods,
        nullptr,
        symdiff_traverse,
        symdiff_clear,
        nullptr
};
#endif

static int symdiff_exec(PyObject *m)
{
  module_state *state = GETSTATE(m);
  Py_CLEAR(state->error);

  state->error = PyErr_NewException(const_cast<char *>("symdiff.SymdiffError"), nullptr, nullptr);
  if (state->error == nullptr)
  {
    return -1;
  }
#ifdef SYMDIFF_PYTHON3T
  if (PyModule_AddObjectRef(m, "SymdiffError", state->error) < 0)
  {
    return -1;
  }
#else
  Py_INCREF(state->error);
  if (PyModule_AddObject(m, "SymdiffError", state->error) < 0)
  {
    Py_DECREF(state->error);
    return -1;
  }
#endif

  PyObject *version = PyUnicode_FromString(SYMDIFF_VERSION_STRING);
  if (version == nullptr)
  {
    return -1;
  }
#ifdef SYMDIFF_PYTHON3T
  int result = PyModule_AddObjectRef(m, "__version__", version);
  Py_DECREF(version);
  return result;
#else
  if (PyModule_AddObject(m, "__version__", version) < 0)
  {
    Py_DECREF(version);
    return -1;
  }

  return 0;
#endif
}

#ifdef SYMDIFF_PYTHON3T
PyABIInfo_VAR(abi_info);

static PySlot symdiff_module_slots[] = {
  PySlot_DATA(Py_mod_gil, Py_MOD_GIL_NOT_USED),
  PySlot_DATA(Py_mod_multiple_interpreters, Py_MOD_MULTIPLE_INTERPRETERS_NOT_SUPPORTED),
  PySlot_FUNC(Py_mod_exec, symdiff_exec),
  PySlot_END
};

static PySlot symdiff_export_slots[] = {
  PySlot_STATIC_DATA(Py_mod_abi, &abi_info),
  PySlot_STATIC_DATA(Py_mod_name, const_cast<char *>("symdiff_py3")),
  PySlot_SIZE(Py_mod_state_size, sizeof(module_state)),
  PySlot_STATIC_DATA(Py_mod_methods, symdiff_methods),
  PySlot_STATIC_DATA(Py_mod_slots, symdiff_module_slots),
  PySlot_FUNC(Py_mod_state_traverse, symdiff_traverse),
  PySlot_FUNC(Py_mod_state_clear, symdiff_clear),
  PySlot_END
};

PyMODEXPORT_FUNC
PyModExport_symdiff_py3(void)
{
  return symdiff_export_slots;
}
#else
extern "C" DLL_PUBLIC PyObject *PyInit_symdiff_py3(void)
{
  PyObject *m = PyModule_Create(&moduledef);
  if (m == nullptr)
  {
    return nullptr;
  }
  if (symdiff_exec(m) < 0)
  {
    Py_DECREF(m);
    return nullptr;
  }
  return m;
}
#endif


