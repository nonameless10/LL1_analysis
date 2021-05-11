'''
Author       : czq
Date         : 2021-04-11 12:40:00
LastEditors  : czq
LastEditTime : 2021-04-12 12:32:28
'''
from graphviz import Digraph
from queue import Queue

# 画图
'''
K: 状态集
f: 图
S：初态集
Z：终态集
pic_name: 图片名
'''
def draw(K, f, S, Z, pic_name):
    dot = Digraph(name = pic_name, format = "png")
    for i in S:
        dot.node(name = i, label = i, color = 'green')
    for i in Z:
        dot.node(name = i, label = i, color = 'red')
    for i in K:
        if i not in S and i not in Z:
            dot.node(name = i, label = i)
    for i in f:
        dot.edge(i[0], i[2], label = i[1])
    dot.view(filename = pic_name, directory = "./picture")


def ε_closure(S, f):
    res = []
    vis = {}
    q = Queue(maxsize = 0)
    for i in S: 
        q.put(i)
        vis[i] = 1
    while q.empty() is False:
        node = q.get()
        if node not in res: res.append(node)
        for i in f:
            if i[0] == node and i[1] == 'ε' and vis[i[1]] != 1:
                q.put(i[2])
                vis[i[1]] = 1
    res.sort()
    return res

def move(S, f, a):
    res = []
    for i in S:
        for j in f:
            if j[0] == i and j[1] == a:
                res.append(j[2])
    return res

def judge_end_node(u, z):
    for i in u:
        for j in z:
            if (i == j): return True
    return False

if __name__ == "__main__":
    nfa_k = ['0', '1', '2', '3', '4']
    nfa_t = ['a', 'b']
    nfa_f = [('0', 'a', '0'), ('0', 'a', '3'),
             ('0', 'b', '0'), ('0', 'b', '1'),
             ('1', 'b', '2'), ('2', 'a', '2'),
             ('2', 'b', '2'), ('3', 'a', '4'),
             ('4', 'a', '4'), ('4', 'b', '4')]
    nfa_s = ['0']
    nfa_z = ['2', '4']
    draw(nfa_k, nfa_f, nfa_s, nfa_z, 'nfa')
    # dfa 的节点对于之前的 nfa 的节点
    dfa_node_to_nfa = {}
    vis = {}
    node_id = 0
    dfa_f = []
    dfa_z = []
    dfa_s = []
    dfa_k = []
    dfa_s.append(str(node_id))
    dfa_k.append(str(node_id))
    tmp = ε_closure(nfa_s, nfa_f)
    dfa_node_to_nfa[str(node_id)] = tmp
    c = Queue(maxsize = 0)
    c.put(tmp)
    vis[str(tmp)] = str(node_id)
    while c.empty() is False:
        t = c.get()
        for a in nfa_t:
            u = ε_closure(move(t, nfa_f, a), nfa_f)
            if str(u) not in vis:
                c.put(u)
                node_id += 1
                dfa_node_to_nfa[str(node_id)] = u
                vis[str(u)] = str(node_id)
                if judge_end_node(u, nfa_z): dfa_z.append(str(node_id))
                dfa_k.append(str(node_id))
            dfa_f.append((vis[str(t)], a, vis[str(u)]))
    for i in vis:
        print(vis[i] + ":  " + i)
    draw(dfa_k, dfa_f, dfa_s, dfa_z, 'dfa')