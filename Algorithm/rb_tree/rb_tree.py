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
        else:
            # 找到目标插入点
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

        print("show before insert_fixup: ", value)
        self.show()
        self.insert_fixup(tmp_node)

    """
    1. 目标节点没有子节点,删除目标节点,将目标节点的父节点设为Nil节点
    2. 目标节点只有一个子节点,删除目标节点,重新连接目标节点的父节点和子节点
    3. 目标节点有两个子节点:
        3.1 找到值最接近的替换节点.可以选择右子树的最左孩子节点,或者左子树的最右孩子节点.
        3.2 将替换节点的值拷贝到目标节点.
        3.3 将目标节点 更新为 替换节点, 重复步骤1~3
    """
    def delete(self, target):
        # 没有找到目标节点
        if target.is_nil():
            print("WARNING: search target fail")
            return

        """
         y: 真正将被删除的节点
         x: 替代y的节点

        注意: y一定只有0/1个子节点
        """
        z = target

        # 决定真正要被删除的节点
        # 如果z只有0/1个子节点,则z是要被删除的节点
        if(z.left.is_nil() or z.right.is_nil()):
            y = z
        else:
            # 否则,将删除离z值最接近的节点
            y = z.right
            while(y.left.is_not_nil()):
                y = y.left

        # 决定要替换y的节点
        if(y.left.is_not_nil()):
            x = y.left
        else:
            x = y.right
        # 更新x的父节点
        x.parent = y.parent

        # 删除节点为根节点
        if not y.parent:
            self.root = x
            if x.is_nil():
                self.root = None
        elif y == y.parent.left:
            y.parent.left = x
        else:
            y.parent.right = x

        # Case 3
        if y is not z:
            z.value = y.value

        if y.is_black():
            print("show before delete fixup: ", x.value)
            self.show()
            self.delete_fixup(x)

        return y

    """
    """
    def delete_fixup(self, node):
        target = node
        # 目标节点不是根节点,且为黑色节点
        while target != self.root and target.is_black():
            # 目标节点是父节点的左节点
            if target == target.parent.left:
                brother = target.parent.right

                # 目标节点是"黑+黑"节点,即 目标节点+父节点 均为黑色
                # 兄弟节点为红色,兄弟节点的子节点均为黑色
                if brother.is_red():
                    brother.set_black()
                    target.parent.set_red()
                    self.left_rotate(target.parent)
                    brother = target.parent.right
                # 目标节点是"黑+黑"节点,即 目标节点+父节点 均为黑色
                # 兄弟节点为黑色, 兄弟节点的子节点均为黑色
                if brother.left.is_black() and brother.right.is_black():
                    brother.set_red()
                    target = target.parent
                # 兄弟节点为黑色,兄弟节点的右子节点为黑色,左子节点为红色
                elif brother.right.is_black():
                    brother.left.set_black()
                    brother.set_red()
                    self.right_rotate(brother)
                    brother = target.parent.right
                # 兄弟节点为黑色,兄弟节点的右子节点为红色,左子节点为黑色
                else:
                    # target.parent.set_black()
                    # brother.right.set_black()
                    self.left_rotate(target.parent)
                    target = target.parent.parent
                    # self.root = target
            else:
                # 目标节点是父节点的左节点
                brother = target.parent.left

                # 目标节点是"黑+黑"节点,即 目标节点+父节点 均为黑色
                # 兄弟节点为红色,兄弟节点的子节点均为黑色
                if brother.is_red():
                    brother.set_black()
                    target.parent.set_red()
                    self.right_rotate(target.parent)
                    brother = target.parent.left
                # 目标节点是"黑+黑"节点,即 目标节点+父节点 均为黑色
                # 兄弟节点为黑色, 兄弟节点的子节点均为黑色
                if brother.left.is_black() and brother.right.is_black():
                    brother.set_red()
                    target = target.parent
                # 兄弟节点为黑色,兄弟节点的左子节点为黑色,右子节点为红色
                elif brother.left.is_black():
                    brother.right.set_black()
                    brother.set_red()
                    self.left_rotate(brother)
                    brother = target.parent.left
                # 兄弟节点为黑色,兄弟节点的左子节点为红色,右子节点为黑色
                else:
                    target.parent.set_black()
                    brother.left.set_black()
                    self.right_rotate(target.parent)
                    self.root = target

        target.set_black()

    """
    input: value
    return: Node
    """
    def search(self, value):
        current = self.root
        while(current.is_not_nil() and current.value != value):
            if(current.value > value):
                current = current.left
            else:
                current = current.right

        return current

    """
    1. 父节点是祖父节点的左节点
        1.1 目标节点的父节点和其叔叔节点(祖父节点的另一个子节点)均为红色的;
        1.2 目标节点的父节点是红色,叔叔节点是黑色,且目标节点是其父节点的右子节点;
        1.3 目标节点的父节点是红色,叔叔节点是黑色,且目标节点是其父节点的左子节点.
    2. 父节点是祖父节点的右节点,与1对称
    """
    def insert_fixup(self, node):
        target = node
        # 目标节点为根节点
        if not target.parent:
            target.set_black()

        # 需要修正的条件: 父节点存在,且为红色
        while(target.parent and target.parent.is_red()):
            grandparent = target.parent.parent

            # 父节点是祖父节点的左节点
            if(target.parent == grandparent.left):
                uncle = grandparent.right

                # case 1: 叔叔节点也是红色
                if(uncle and uncle.is_red()):
                    # 将父节点和叔叔节点涂黑
                    # 将祖父节点图红
                    self.change_color(target)
                    # 目标节点更新为祖父节点
                    target = grandparent
                    continue

                # case 2: 叔叔节点是黑色,且当前节点是父节点的右节点
                if(target == target.parent.right):
                    target = target.parent
                    self.left_rotate(target)

                # case 3: 叔叔节点是黑色,且当前节点是父节点的左节点
                # 将父节点和叔叔节点涂黑
                # 将祖父节点图红
                self.change_color(target)
                # target = grandparent
                self.right_rotate(grandparent)
            else:
                # 父节点是祖父节点的右节点
                uncle = grandparent.left

                # case 1: 叔叔节点也是红色
                if(uncle and uncle.is_red()):
                    self.change_color(target)
                    # 目标节点更新为祖父节点
                    target = grandparent
                    continue

                # case 2: 叔叔节点是黑色,且当前节点是父节点的左节点
                if(target == target.parent.left):
                    target = target.parent
                    self.right_rotate(target)

                # case 3: 叔叔节点是黑色,且当前节点是父节点的右节点
                # 将父节点和叔叔节点涂黑
                # 将祖父节点图红
                self.change_color(target)
                # target = grandparent
                self.left_rotate(grandparent)

        if self.root.is_red():
            self.root.set_black()
            print("show after set root black: ", self.root.value)
            self.show()

    def show(self):
        if self.root:
            rb_draw.draw(self.root)

    """
    父节点和叔叔节点均为红色
    1. 父节点和叔叔节点 改为 黑色
    2. 祖父节点 改为 红色
    """
    def change_color(self, target):
        parent = target.parent
        grandparent = target.parent.parent
        uncle = target.get_uncle()

        grandparent.set_red()
        uncle.set_black()
        parent.set_black()
        print("show after change_color: ", target.value)
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
        S = Y.right
        P = Y.parent
        lS = S.left

        S.left = Y
        Y.parent = S

        Y.right = lS
        lS.parent = Y

        S.parent = P
        if(P):
            if(Y == P.left):
                P.left = S
            else:
                P.right = S
        else:
            self.root = S

        print("show after left_rotate: ", Y.value)
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
        S = Y.left
        P = Y.parent
        rS = S.right

        S.right = Y
        Y.parent = S

        Y.left = rS
        rS.parent = Y

        S.parent = P
        if(P):
            if(Y == P.left):
                P.left = S
            else:
                P.right = S
        else:
            self.root = S

        print("show after right_rotate: ", Y.value)
        self.show()
