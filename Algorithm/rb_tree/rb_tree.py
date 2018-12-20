#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Wed 19 Dec 2018 08:57:53 PM CST
import rb_node
import rb_draw


class RbTree(object):
    def __init__(self):
        self.root = None

    def insert(self, value, color=rb_node.RED):
        tmp_node = rb_node.RbNode(value, color)

        # 插入节点为根节点
        if not self.root:
            self.root = tmp_node
            self.root.set_black()
            return

        # 找到目标插入点
        current = self.root
        x = self.root
        while(x.value != rb_node.NULL):
            current = x
            if(current.value > tmp_node.value):
                x = current.left
            else:
                x = current.right

        # 插入tmp_node
        tmp_node.parent = current
        if(current.value > tmp_node.value):
            current.left = tmp_node
        else:
            current.right = tmp_node

        print("before rebalance")
        self.show()
        self.rebalance(tmp_node)

    """
    1. 目标节点的父节点和其叔叔节点(祖父节点的另一个子节点)均为红色的;
    2. 目标节点的父节点是红色,叔叔节点是黑色,且目标节点是其父节点的右子节点;
    3. 目标节点的父节点是红色,叔叔节点是黑色,且目标节点是其父节点的左子节点.
    """
    def rebalance(self, node):
        target = node
        parent = target.parent

        # 需要修正的条件: 父节点存在,且为红色
        while(parent and parent.is_red()):
            grandparent = parent.parent

            # 父节点是祖父节点的左节点
            if(parent == grandparent.left):
                uncle = grandparent.right

                # case 1: 叔叔节点也是红色
                if(uncle and uncle.is_red()):
                    # 将父节点和叔叔节点涂黑
                    # 将祖父节点图红
                    self.change_color(target)

                    # 目标节点更新为祖父节点
                    target = grandparent
                    parent = target.parent
                    continue

                # case 2: 叔叔节点是黑色,且当前节点是父节点的右节点
                if(target == parent.right):
                    self.left_rotate(parent)
                    target, parent = parent, target

                # case 3: 叔叔节点是黑色,且当前节点是父节点的左节点
                parent.set_black()
                grandparent.set_red()
                self.right_rotate(grandparent)
            else:
                # 父节点是祖父节点的右节点
                uncle = grandparent.left

                # case 1: 叔叔节点也是红色
                if(uncle and uncle.is_red()):
                    self.change_color(target)

                    # 目标节点更新为祖父节点
                    target = grandparent
                    parent = target.parent
                    continue

                # case 2: 叔叔节点是黑色,且当前节点是父节点的右节点
                if(target == parent.right):
                    self.right_rotate(parent)
                    target, parent = parent, target

                # case 3: 叔叔节点是黑色,且当前节点是父节点的左节点
                parent.set_black()
                grandparent.set_red()
                self.left_rotate(grandparent)

        self.root.set_black()


    def show(self):
        if self.root:
            rb_draw.draw(self.root)

    """
    input: value
    return: Node
    """
    def search(self, value):
        current = self.root
        while(current and current.value != value):
            if(current.value > value):
                current = current.left
            else:
                current = current.right

        return current

    """
    父节点和叔叔节点均为红色
    1. 父节点和叔叔节点 改为 黑色
    2. 祖父节点 改为 红色
    """
    def change_color(self, son):
        print("change_color: ", son.value)

        parent = son.parent
        grandparent = son.parent.parent
        uncle = son.get_uncle()

        grandparent.set_red()
        if(uncle):
            uncle.set_black()
        parent.set_black()
        print("after change_color")
        self.show()

    """
             P              P
            /              /
           Y              S
          / \   ---->    / \
         E   S          Y  rS
            / \        / \
           lS rS      E  lS
    1. Y->left = lS; lS->parent = Y
    2. S->left = Y; Y->parent = S
    3. S->parent = P; P->left/right = S
    """
    def left_rotate(self, Y):
        print("left rotate: ", Y.value)
        S = Y.right
        P = Y.parent
        lS = S.left

        S.left = Y
        Y.parent = S

        Y.right = lS
        if(lS):
            lS.parent = Y

        if(P):
            if(Y == P.left):
                P.left = S
            else:
                P.right = S
            S.parent = P
        else:
            self.root = S

        print("after left_rotate")
        self.show()

    """
           P               P
          /               /
         Y               S
        / \    --->     / \
       S   E           lS  Y
      / \                 / \
     lS rS               rS  E
    1. Y->left = rS; rS->parent = Y
    2. S->right = Y; Y->parent = S
    3. S->parent = P; P->left/right = S
    """
    def right_rotate(self, Y):
        print("right rotate: ", Y.value)
        S = Y.left
        P = Y.parent
        rS = S.right

        S.right = Y
        Y.parent = S

        Y.left = rS
        if(rS):
            rS.parent = Y

        if(P):
            if(Y == P.left):
                P.left = S
            else:
                P.right = S
            S.parent = P
        else:
            self.root = S
        print("after right_rotate")
        self.show()
