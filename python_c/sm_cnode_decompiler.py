import ctypes

class cnode_t(ctypes.Structure):
    _fields_ = [
        ('s', ctypes.c_char_p),
        ('l', ctypes.c_char_p),
        ('f', ctypes.c_char_p),
        ('j', ctypes.c_char_p),
        ('m', ctypes.c_char_p),
        ('s_', ctypes.c_int32),
        ('l_', ctypes.c_int32),
        ('f_', ctypes.c_int32),
        ('j_', ctypes.c_int32),
        ('m_', ctypes.c_int32),
    ]

    def get_s(self) -> bytes:
        return self.s[:self.s_] if self.s else ''
    
    def get_l(self) -> bytes:
        return self.l[:self.l_] if self.l else ''

    def get_f(self) -> bytes:
        return self.f[:self.f_] if self.f else ''

    def get_j(self) -> bytes:
        return self.j[:self.j_] if self.j else ''

    def get_m(self) -> bytes:
        return self.m[:self.m_] if self.m else ''

    def __str__(self):
        s = self.get_s()
        l = self.get_l()
        f = self.get_f()
        j = self.get_j()
        m = self.get_m()
        return '{}:{}:{}:{}:{}'.format(s,l,f,j,m)

lib = ctypes.cdll.LoadLibrary('./bin/sourcemappings.so')
cf_decompile = lib.sm_decompile
cf_free = lib.sm_free
cf_decompile.restype = ctypes.POINTER(cnode_t)
cf_decompile.argtypes = [ctypes.c_char_p, ctypes.POINTER(ctypes.c_int)]
cf_free.argtypes = [ctypes.POINTER(cnode_t)]

class cnode_decompiler:
    def __init__(self, bstr):
        self.bstr = bstr
        self.nodes_count = ctypes.c_int()
        self.nodes = cf_decompile(bstr, ctypes.byref(self.nodes_count))
    
    def __del__(self):
        cf_free(self.nodes)
    
    def get_nodes_count(self) -> int:
        return self.nodes_count.value
    
    def get_node_at(self, ix: int) -> cnode_t:
        return self.nodes[ix]