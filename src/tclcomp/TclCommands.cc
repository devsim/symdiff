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

#include "TclCommands.hh"

#include "TclSymdiffCommands.hh"

#include <tcl.h>
#include <iostream>

namespace dsTcl {

int 
CmdDispatch(ClientData clientData, Tcl_Interp *interp,
          int objc, Tcl_Obj *CONST objv[])
{
  int myerror = TCL_OK;


  try
  {
    tclcmd cmd = reinterpret_cast<dsClientData *>(clientData)->GetCommand();
    myerror = cmd(clientData, interp, objc, objv);
  }
#if 0
  catch (const dsException &x)
  {
    myerror = TCL_ERROR;
    Tcl_SetResult(interp, const_cast<char *>(x.what()), TCL_VOLATILE);
  }
#endif
  catch (std::bad_alloc &)
  {
    myerror = TCL_ERROR;
    Tcl_SetResult(interp, const_cast<char *>("OUT OF MEMORY"), TCL_VOLATILE);
  }

  return myerror;
}

void AddCommands(Tcl_Interp *interp, Commands *clist)
{
  for ( ; (clist->name) != nullptr; ++clist)
  {
    void *cdata = dsClientData::CreateData(clist->name, clist->command);

    Tcl_CreateObjCommand(interp, clist->name, CmdDispatch,
            (ClientData) cdata, (Tcl_CmdDeleteProc *) dsClientData::DeleteData);
  }
}

int 
Commands_Init(Tcl_Interp *interp) {
    AddCommands(interp, TclSymdiffCommands);
    return TCL_OK;
}
}

