try:
    raise Exception("I am a Exception")
except Exception as e:
    print(e)
finally:
    print("the finally code")
