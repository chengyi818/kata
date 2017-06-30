#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Fri 16 Jun 2017 04:26:40 PM CST
import tkinter as tk
from sf_core.sf_func import SfFunc


class SfButton(object):
    def __init__(self, root, frm_top):
        print("SfButton init")
        self.root = root
        self.frm_top = frm_top
        self.funcer = SfFunc()

        self.menubar = None

    def run(self):
        print("SfButton run")
        self.__prepare_buttons_start()

        self.__prepare_config_menu()
        self.__prepare_device_menu()
        self.__prepare_update_menu()
        self.__prepare_log_menu()
        self.__prepare_help_menu()

        self.__prepare_refresh_btn()
        self.__prepare_check_device_btn()
        self.__prepare_start_btn()
        self.__prepare_stop_btn()

        self.__prepare_buttons_over()

    def __prepare_buttons_start(self):
        self.menubar = tk.Menu(self.frm_top)

    def __prepare_buttons_over(self):
        self.root.config(menu=self.menubar)

    def __prepare_config_menu(self):
        config_menu = tk.Menu(self.menubar, tearoff=0)
        config_menu.add_command(label="更改配置",
                                command=self.funcer.btn_config_clicked)
        config_menu.add_command(label="重载配置",
                                command=self.funcer.btn_reload_clicked)

        self.menubar.add_cascade(label="配置", menu=config_menu)

    def __prepare_device_menu(self):
        device_menu = tk.Menu(self.menubar, tearoff=0)
        device_menu.add_command(label="清理设备",
                                command=self.funcer.btn_clean_device_clicked)

        self.menubar.add_cascade(label="设备", menu=device_menu)

    def __prepare_update_menu(self):
        update_menu = tk.Menu(self.menubar, tearoff=0)
        update_menu.add_command(label="从本地更新",
                                command=self.funcer.btn_local_update_clicked)
        update_menu.add_command(label="从远程更新",
                                command=self.funcer.btn_remote_update_clicked)

        self.menubar.add_cascade(label="更新", menu=update_menu)

    def __prepare_log_menu(self):
        log_menu = tk.Menu(self.menubar, tearoff=0)
        log_menu.add_command(label="打开log目录",
                             command=self.funcer.btn_open_log_clicked)
        log_menu.add_command(label="拷贝log到远程",
                             command=self.funcer.btn_scp_log_clicked)
        log_menu.add_command(label="清理log",
                             command=self.funcer.btn_clean_log_clicked)

        self.menubar.add_cascade(label="log", menu=log_menu)

    def __prepare_help_menu(self):
        help_menu = tk.Menu(self.menubar, tearoff=0)
        help_menu.add_command(label="使用手册",
                              command=self.funcer.btn_manual_clicked)

        self.menubar.add_cascade(label="帮助", menu=help_menu)

    def __prepare_refresh_btn(self):
        refresh_btn = tk.Button(self.frm_top, text="刷新设备列表",
                                command=self.funcer.btn_refresh_clicked)
        refresh_btn.pack(side=tk.LEFT)

    def __prepare_check_device_btn(self):
        refresh_btn = tk.Button(self.frm_top, text="检查设备",
                                command=self.funcer.btn_check_device_clicked)
        refresh_btn.pack(side=tk.LEFT)

    def __prepare_start_btn(self):
        start_btn = tk.Button(self.frm_top, text="开始测试",
                              command=self.funcer.btn_start_clicked)
        start_btn.pack(side=tk.LEFT)

    def __prepare_stop_btn(self):
        stop_btn = tk.Button(self.frm_top, text="停止测试",
                             command=self.funcer.btn_stop_clicked)
        stop_btn.pack(side=tk.LEFT)
