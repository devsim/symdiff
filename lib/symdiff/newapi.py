from . import symdiff_py3
from ctypes import *

dll = None

class eqobj:

    def __init__(self, cobj):
        self.cobj = cobj

    def __del__(self):
        dll.SYMDIFFobj_free(self.cobj)

    def get_status(self):
        return dll.SYMDIFF_get_status(self.cobj)

    def get_string(self):
        return dll.SYMDIFF_get_string(self.cobj).decode('utf-8')

    def get_error(self):
        return dll.SYMDIFF_get_error(self.cobj).decode('utf-8')

def parse(input_string):
    res = dll.SYMDIFF_parse(input_string.encode('utf-8'))
    return eqobj(res)



if __name__ != '__main__':
    dll = cdll.LoadLibrary(symdiff_py3.__file__)

    # SYMDIFF_parse
    dll.SYMDIFF_parse.restype = c_void_p
    dll.SYMDIFF_parse.argtypes = (c_char_p,)

    # SYMDIFF_free
    dll.SYMDIFFobj_free.restype = None
    dll.SYMDIFFobj_free.argtypes = (c_void_p,)

    # SYMDIFF_get_status
    dll.SYMDIFF_get_status.restype = c_bool
    dll.SYMDIFF_get_status.argtypes = (c_void_p,)

    # SYMDIFF_get_string
    dll.SYMDIFF_get_string.restype = c_char_p
    dll.SYMDIFF_get_string.argtypes = (c_void_p,)

    # SYMDIFF_get_error
    dll.SYMDIFF_get_error.restype = c_char_p
    dll.SYMDIFF_get_error.argtypes = (c_void_p,)

