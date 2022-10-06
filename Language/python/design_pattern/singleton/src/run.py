"""
:Authors:
    Tony J. (Tibs) Ibbs,
    David Goodger
    (and sundry other good-natured folks)

:Version: 1.0 of 2001/08/08
:Dedication: To my father.
"""


def run(name) -> str:
    """_summary_

    Args:
        name (_type_): 
            _description_

    Returns:
        str: 
            #. *_description_*
            #. *_description_*

    Examples:
        >>> import run
        >>> run.run("test")
        test is running
        'test'

    .. TODO:: write
    """
    print(name, 'is running')

    return name


def add(a: int, b: int) -> int:
    """Add doc.

    :param a: _description_
    :type a: int
    :param b: _description_
    :type b: int
    :return: _description_
    :rtype: int

    .. doctest::

        >>> import run
        >>> run.add(3, 2)
        5
    """
    return a+b
