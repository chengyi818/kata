#!/usr/bin/env python
# -*- coding: UTF-8 -*-
'''
# =============================================================================
#      FileName: sqlite_1.py
#          Desc: SQLite3
#        Author: ChengYi
#         Email: chengyi@antiy.cn
#      HomePage: http://www.antiy.com/
#       Created: 2016-12-13 19:53:44
#       Version: 0.0.1
#    LastChange: 2016-12-13 19:53:44
#       History:
#                0.0.1 | ChengYi | init
# =============================================================================
'''

import sqlite3

def main():
    try:
        conn = sqlite3.connect('test.db')
        cursor = conn.cursor()
    except:
        pass
    else:
        cursor.execute('select * from user where id=?', ('1',))
        values = cursor.fetchall()
        print values
    finally:
        cursor.close()
        conn.commit()
        conn.close()


if __name__ == '__main__':
    main()
