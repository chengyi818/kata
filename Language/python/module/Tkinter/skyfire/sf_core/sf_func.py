#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Fri 16 Jun 2017 04:34:22 PM CST
from tkinter import messagebox as msgbox
from sf_gui import sf_register
from sf_core.sf_worker import SfWorker


class SfFunc(object):
    def __init__(self):
        print("SfFunc init")
        self.worker = None

    # config menu
    def btn_config_clicked(self):
        msg = 'btn_config_clicked'
        self.__text_mid_right_insert(msg)
        msgbox.showwarning("警告", "功能尚未开发,敬请期待")

    def btn_reload_clicked(self):
        msg = 'btn_reload_clicked'
        self.__text_mid_right_insert(msg)
        msgbox.showwarning("警告", "功能尚未开发,敬请期待")

    # device menu
    def btn_clean_device_clicked(self):
        msg = "btn_clean_device_clicked"
        self.__text_mid_right_insert(msg)
        msgbox.showwarning("警告", "功能尚未开发,敬请期待")

    # update menu
    def btn_local_update_clicked(self):
        msgbox.showwarning("警告", "功能尚未开发,敬请期待")

    def btn_remote_update_clicked(self):
        msgbox.showwarning("警告", "功能尚未开发,敬请期待")

    # log menu
    def btn_open_log_clicked(self):
        msgbox.showwarning("警告", "功能尚未开发,敬请期待")

    def btn_scp_log_clicked(self):
        msgbox.showwarning("警告", "功能尚未开发,敬请期待")

    def btn_clean_log_clicked(self):
        msg = "btn_clean_log_clicked"
        self.__text_mid_right_insert(msg)
        msgbox.showwarning("警告", "功能尚未开发,敬请期待")

    # help menu
    def btn_manual_clicked(self):
        msgbox.showwarning("警告", "功能尚未开发,敬请期待")

    # quick menu
    def btn_refresh_clicked(self):
        msg = 'btn_refresh_clicked'
        self.__text_mid_right_insert(msg)
        msgbox.showwarning("警告", "功能尚未开发,敬请期待")

    def btn_check_device_clicked(self):
        msg = "btn_check_device_clicked"
        self.__text_mid_right_insert(msg)
        msgbox.showwarning("警告", "功能尚未开发,敬请期待")

    def btn_start_clicked(self):
        msg = 'btn_start_clicked'
        self.__text_mid_right_insert(msg)
        # FIXME
        # self.worker = SfWorker()
        # self.worker.run()

    def btn_stop_clicked(self):
        msg = 'btn_stop_clicked'
        self.__text_mid_right_insert(msg)
        # FIXME
        # if self.worker:
        #     self.worker.stop()

    # inter function
    def __text_mid_right_insert(self, value):
        sf_register.text_mid_right_insert(value)
