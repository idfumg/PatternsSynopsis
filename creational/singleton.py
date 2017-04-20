class Singleton(object):

    instance = None

    def __new__(cls):
        if instance is None:
            cls.instance = super(Singleton, cls).__new__(cls)

        return cls.instance
