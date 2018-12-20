#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Wed 19 Dec 2018 09:46:48 PM CST
import networkx as nx
import matplotlib.pyplot as plt
from multiprocessing import Process
INDEX = 0


def create_graph(G, node, pos={}, x=0, y=0, layer=1):
    node_id = id(node)
    G.add_node(node_id)
    G.nodes[node_id]['color'] = node.color
    G.nodes[node_id]['value'] = node.value
    pos[node_id] = (x, y)

    if node.left:
        G.add_edge(node_id, id(node.left))
        l_x, l_y = x - 1 / 2 ** layer, y - 1
        l_layer = layer + 1
        create_graph(G, node.left, x=l_x, y=l_y, pos=pos,
                     layer=l_layer)
    if node.right:
        G.add_edge(node_id, id(node.right))
        r_x, r_y = x + 1 / 2 ** layer, y - 1
        r_layer = layer + 1
        create_graph(G, node.right, x=r_x, y=r_y, pos=pos,
                     layer=r_layer)
    return (G, pos)

# 以某个节点为根画图
def _draw(node, index):
    graph = nx.DiGraph()
    graph, pos = create_graph(graph, node)

    # 获取节点颜色
    node_color = []
    labels = {}
    for node_id in graph.nodes:
        node_color.append(graph.nodes.data()[node_id]['color'])
        labels[node_id] = r'${}$'.format(graph.nodes.data()[node_id]['value'])

    # 比例可以根据树的深度适当调节
    fig, ax = plt.subplots(figsize=(8, 10))
    ax.set_title("Figure {0}".format(index))
    nx.draw_networkx(graph, pos, node_color=node_color, with_labels=True,
                     labels=labels, ax=ax, node_size=300)
    plt.show()


def draw(node):
    global INDEX
    INDEX += 1
    p = Process(target=_draw, args=(node, INDEX))
    p.start()
