class pnode:
    def __init__(self):
        self.s = ''
        self.l = ''
        self.f = ''
        self.j = ''
        self.m = ''

    def __str__(self):
        s = self.s if self.s else ''
        l = self.l if self.l else ''
        f = self.f if self.f else ''
        j = self.j if self.j else ''
        m = self.m if self.m else ''
        return '{}:{}:{}:{}:{}'.format(s,l,f,j,m)

class pnode_decompiler:
    def __decompile(self, sm_str):        
        prev_node = pnode()
        ss = 0
        rix = 0
        while True:
            se = sm_str.find(b";", ss)
            if se == -1: 
                break
            sub = sm_str[ss:se] if se != -1 else sm_str[ss:]
            ss = se+1
            if not sub:
                self.nodes[rix] = prev_node
                rix += 1
                continue
            
            sub_parts = sub.split(b":")    
            sub_parts_len = len(sub_parts)
            prev_node.s = sub_parts[0] if (sub_parts_len >= 1 and sub_parts[0]) else prev_node.s 
            prev_node.l = sub_parts[1] if (sub_parts_len >= 2 and sub_parts[1]) else prev_node.l
            prev_node.f = sub_parts[2] if (sub_parts_len >= 3 and sub_parts[2]) else prev_node.f
            prev_node.j = sub_parts[3] if (sub_parts_len >= 4 and sub_parts[3]) else prev_node.j
            prev_node.m = sub_parts[4] if (sub_parts_len >= 5 and sub_parts[4]) else prev_node.m
            self.nodes[rix] = prev_node
            rix += 1

    def __init__(self, sm_str):
        p_parts_count = sm_str.count(b";")
        self.nodes = [pnode] * (p_parts_count)
        self.__decompile(sm_str)