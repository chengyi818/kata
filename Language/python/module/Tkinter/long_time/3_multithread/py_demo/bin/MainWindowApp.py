""" Handle the main application window """
# $Id: MainWindowApp.py,v 1.3 2004/04/12 04:46:16 prof Exp $
import tkinter as Tkinter
import logging
import ViewLog
import ThreadsConnector
import ActionWindow
import app2
import gettext
_ = gettext.gettext

class MainWindowApp:

  def __init__(self, log):
    """ Remember cumulative log, get logger """
    self.log    = log
    self.logger = logging.getLogger(self.__class__.__name__)

  def run(self):
    """ Create and run GUI """
    self.root = root = Tkinter.Tk()
    root.title(_('Long Operation Demo'));
    Tkinter.Button(root, text=_('Start'), command=self.onStart, width=10).pack(side=Tkinter.LEFT)
    Tkinter.Button(root, text=_('View Log'), command=self.onViewLog, width=10).pack(side=Tkinter.LEFT)
    Tkinter.Button(root, text=_('Exit'), command=self.onExit, width=10).pack(side=Tkinter.LEFT)
    root.mainloop()

  def onExit(self):
    """ Process 'Exit' command """
    self.root.quit()
    self.root.destroy()

  def onViewLog(self):
    """ Process 'View Log' command """
    ViewLog.ViewLog(self.root, self.log)

  def onStart(self):
    """ Process 'Start' command """
    self.logger.info(_('Preparing and starting calculations'))
    conn = ThreadsConnector.ThreadsConnector()
    wnd = ActionWindow.ActionWindow(self.root, _('Countdown Calculations'), _('Counting down from 100 to 1'))
    conn.runInGui(wnd, conn, None, app2.calc, 'calc')

