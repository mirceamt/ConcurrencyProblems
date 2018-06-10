from fork import Fork

from threading import Thread
from time import sleep
from random import uniform


class Philosopher(Thread):

    def __init__(self, name):
        Thread.__init__(self)
        self.name = name
        self.left_fork = None
        self.right_fork = None
        self.stop = False
        self.eat_count = 0
        self.finished = False

    def run(self):
        while self.stop is False:
            self.think()
            self.eat()
        self.finished = True

    def think(self):
        print(f'Philosopher({self.name}) started thinking')
        sleep(uniform(0.001, 1))
        print(f'Philosopher({self.name}) finished thinking')

    def eat(self):
        if self.left_fork.index < self.right_fork.index:
            self.left_fork.acquire_fork()
            print(f'Philosopher({self.name}) acquired fork({self.left_fork.index})')
            self.right_fork.acquire_fork()
            print(f'Philosopher({self.name}) acquired fork({self.right_fork.index})')
        else:
            self.right_fork.acquire_fork()
            print(f'Philosopher({self.name}) acquired fork({self.right_fork.index})')
            self.left_fork.acquire_fork()
            print(f'Philosopher({self.name}) acquired fork({self.left_fork.index})')
        print(f'Philosopher({self.name}) started eating')
        sleep(uniform(0.001, 1))
        self.left_fork.release_fork()
        self.right_fork.release_fork()
        print(f'Philosopher({self.name}) finished eating')
        self.eat_count += 1

    def set_left_fork(self, left_fork):
        self.left_fork = left_fork

    def set_right_fork(self, right_fork):
        self.right_fork = right_fork

    def stop_philosopher(self):
        self.stop = True
