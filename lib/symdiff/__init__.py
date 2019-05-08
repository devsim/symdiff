
import sys

if sys.version_info[0] < 3:
  from symdiff_py2 import *
else:
  from .symdiff_py3 import *


