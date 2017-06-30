""" View Log """
# $Id: ViewLog.py,v 1.2 2004/04/12 04:38:58 prof Exp $
import tkinter as Tkinter
import tkinter.simpledialog as tkSimpleDialog
import tkinter.scrolledtext as ScrolledText
import gettext
_ = gettext.gettext

class ViewLog(tkSimpleDialog.Dialog):
  """ Display log messages of a program """

  def __init__(self, parent, log):
    """ Create and display window. Log is CumulativeLogger. """
    self.log = log
    tkSimpleDialog.Dialog.__init__(self, parent, _('Log Entries'))

  def body(self, master):
    """ Create dialog body """
    master.pack_configure(fill=Tkinter.BOTH, expand=1)
    t = ScrolledText.ScrolledText(master, width=60, height=37)
    t.insert(Tkinter.END, self.log.getText())
    t.configure(state=Tkinter.DISABLED)
    t.see(Tkinter.END)
    t.pack(fill=Tkinter.BOTH)

  def buttonbox(self):
    """ Create custom buttons """
    w = Tkinter.Button(self, text=_('Close'), width=10, command=self.ok, default=Tkinter.ACTIVE)
    w.pack(side=Tkinter.RIGHT)
    self.bind("<Return>", self.ok)
    self.bind("<Escape>", self.cancel)

if __name__ == '__main__':
  #
  # Create log entries
  #
  import CumulativeLogger
  import logging
  logging.basicConfig()
  l = logging.getLogger()
  l.setLevel(logging.INFO)
  cl = CumulativeLogger.CumulativeLogger()
  for i in range(100):
    l.info('log entry %i' % i)
  #
  # Create GUI
  #
  root = Tkinter.Tk()
  ViewLog(root, cl)
