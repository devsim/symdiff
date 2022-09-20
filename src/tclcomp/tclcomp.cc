/***
Copyright 2012 DEVSIM LLC

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

#include <tcl.h>
#include "import.hh"
#include "TclCommands.hh"

#if 0
int main(int argc, char * argv[])
{
    Tcl_Main(argc, argv, Tcl_AppInit);

}
#endif
extern "C" {
int DLL_PUBLIC
Symdifftcl_Init(Tcl_Interp *interp)
{
  if (Tcl_InitStubs(interp, TCL_VERSION, 0) == nullptr) {
    return TCL_ERROR;
  }
  if (Tcl_PkgProvide(interp, "symdifftcl", "1.0") == TCL_ERROR) {
    return TCL_ERROR;
  }
  dsTcl::Commands_Init(interp);
  return TCL_OK;
}

DLL_PUBLIC Tcl_PackageInitProc *Symdifftcl_SafeInit = Symdifftcl_Init;
DLL_PUBLIC Tcl_PackageUnloadProc *Symdifftcl_SafeUnload = nullptr;
DLL_PUBLIC Tcl_PackageUnloadProc *Symdifftcl_Unload = nullptr;


}



