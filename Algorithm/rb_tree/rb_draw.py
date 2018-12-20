#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Wed 19 Dec 2018 09:46:48 PM CST
import networkx as nx
import matplotlib.pyplot as plt


def create_graph(G, node, pos={}, x=0, y=0, layer=1):
    pos[node.value] = (x, y)
    G.add_node(node.value)
    if node.left:
        G.add_edge(node.value, node.left.value)
        l_x, l_y = x - 1 / 2 ** layer, y - 1
        l_layer = layer + 1
        create_graph(G, node.left, x=l_x, y=l_y, pos=pos,
                     layer=l_layer)
    if node.right:
        G.add_edge(node.value, node.right.value)
        r_x, r_y = x + 1 / 2 ** layer, y - 1
        r_layer = layer + 1
        create_graph(G, node.right, x=r_x, y=r_y, pos=pos,
                     layer=r_layer)
    return (G, pos)


def draw(node, index):   # 以某个节点为根画图
    graph = nx.DiGraph()
    graph, pos = create_graph(graph, node)

    # 比例可以根据树的深度适当调节
    fig, ax = plt.subplots(figsize=(8, 10))
    ax.set_title("Figure {0}".format(index))
    # 获取节点颜色
    node_color = []
    for tmp in graph.nodes:
        tmp_node = search(node, tmp)
        node_color.append(tmp_node.color)

    nx.draw_networkx(graph, pos, node_color=node_color,
                     ax=ax, node_size=300)
    plt.show()


# input: value
# return: Node
def search(root, value):
    current = root
    while(current and current.value != value):
        if(current.value > value):
            current = current.left
        else:
            current = current.right

    return current
