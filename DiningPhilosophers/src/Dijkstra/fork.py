from threading import Lock


class Fork:

    def __init__(self, index):
        self.index = index
        self.lock = Lock()

    def acquire_fork(self):
        self.lock.acquire()

    def release_fork(self):
        self.lock.release()
