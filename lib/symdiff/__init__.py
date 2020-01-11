
import sys

if sys.version_info[0] == 3:
    from .symdiff_py3 import *
    from .symdiff_py3 import __version__
else:
    raise ImportError('module not available for Python %d.%d please contact technical support' % sys.version_info[0:2])


