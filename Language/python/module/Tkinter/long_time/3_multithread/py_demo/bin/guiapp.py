""" GUI version of the program """
# $Id: guiapp.py,v 1.1 2004/03/31 03:51:49 prof Exp $
import MainWindowApp
import CumulativeLogger
import logging
import gettext
_ = gettext.gettext

logging.basicConfig()
l = logging.getLogger()
l.setLevel(logging.INFO)
cl = CumulativeLogger.CumulativeLogger()
l.info(_('Starting the program...'))
MainWindowApp.MainWindowApp(cl).run()
