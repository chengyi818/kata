import logging
import time
import gettext
_ = gettext.gettext

def calc():
  logger = logging.getLogger(__name__)
  for i in range(100, 0, -1):
    logger.info (_('Countdown value is %i'), i)
    time.sleep(.2)
  logger.info(_('Done!'))

logging.basicConfig()
logging.getLogger().setLevel(logging.INFO)
calc()
