======
README
======

Subtitle1
---------

SubSubtitle
+++++++++++

Subtitle2
-----------

这是第一段

这是第二段
这个还是第二段

    引用

行内标记
-----------

*emphasis*

**emphasis**

`interpreted text`

``inline literal``

列表
-----------
1. 有序列表第一项
    * 无序列表第一项
    * 无序列表第二项
#. 有序列表第二项
    + 无序列表第一项
    + 无序列表第二项    


源代码
-----------

::

    some codes
    some codes
    some codes

.. code-block:: python

   def some_function():
       interesting = False
       print 'This line is highlighted.'
       print 'This one is not...'
       print '...but this one is.'

侧边栏
-----------

.. sidebar:: 这是一个侧边栏

    这是一个侧边栏, 可以放入代码, 也可以放入图像代码等等, 它下面可以是文字, 图像, 代码等等, 如本例中下面是一段文字.

冬日，在暖暖的午后，泡上一杯茶，随便拿起一本书，凑到阳光跟前，是何等的惬意与享受……

风虽然不大，但走在路上，鼻子冷的刺骨的疼；而阳光却那么地温热，温热地忍不住想和她亲吻。

我泡上一杯碧螺春，从书架上随便拿起一本书，走向靠窗的位置，凑到阳光面前，任由她吻着我的脸，就像吻着自己的情人，这感觉美好的让你忘却了所有的烦恼。

也许是身边暖气的缘故，空气的影子，映衬到桌子上、书纸上。影影绰绰如月下之花影，飘飘忽忽如山间之云气，生生腾腾如村落之炊烟，荡荡漾漾如湖面之微波，似乎在这图书馆的这一隅便可看尽天地间的朴素与祥和。


表格
-------------------

.. table:: Grid Table Demo
   :name: table-gridtable

   +------------------------+----------+----------+----------+
   | Header row, column 1   | Header 2 | Header 3 | Header 4 |
   | (header rows optional) |          |          |          |
   +========================+==========+==========+==========+
   | body row 1, column 1   | column 2 | column 3 | column 4 |
   +------------------------+----------+----------+----------+
   | body row 2             | ...      | ...      |          |
   +------------------------+----------+----------+----------+


可以使用 :ref: `table-gridtable` 引用, 在Sphinx中还可以使用 :table:numref: `table-gridtable` 来引用.

直接标记 (Explicit Markup)
----------------------------

.. NOTE:: some notes
.. image:: 2.jpg
   :height: 300px
   :width: 200 px
   :scale: 50 %
   :alt: 对于不能显示图片的时候, 显示这些文字
   :align: right

.. _guoguo:

.. figure:: 2.jpg
   :scale: 50 %
   :alt: map to buried treasure

   This is the caption of the figure (a simple paragraph).

   The legend consists of all elements after the caption.  In this
   case, the legend consists of this paragraph

.. tip:: This is a tip

.. note:: This is a note

.. hint:: This is a hint

.. danger:: This is a danger

.. error:: This is an error

.. warning:: This is a warning

.. caution:: This is a caution

.. attention:: This is an attention

.. important:: This is an important

.. topic:: Topic Title

    Subsequent indented lines comprise
    the body of the topic, and are
    interpreted as body elements.

..
   这整个缩进块都是
   一个注释.
   你只能在源码中看到我们, 我们不会被渲染出来

   仍是一个评论.

你可以看到我, 我不是注释.

超链接
-------------

使用 `Link text <http://example.com/>`_ 来表示超链接

This is a paragraph that contains `a link`_.

.. _a link: http://example.com/


内部链接
-------------

:ref: `guoguo`


脚注
------------

我后面插入了一个自编号的脚注 [#f1]_ , 后面又跟了一个手动编号的脚注 [2]_ , 后面还跟着一个自动编号的 [#fn]_ .

.. rubric:: Footnotes

.. [#f1] 我是自编号脚注1
.. [2] 我是手动编号脚注2
.. [#fn] 我是自编号脚注3


引文
------------

Lorem ipsum [Ref]_ dolor sit amet.

.. [Ref] Book or article reference, URL or whatever.


替换
----------------------

你看到了吗? 第二个单词 word |word| !

.. |word| replace:: 替换成我了


sphinx重要扩展
-------------------------