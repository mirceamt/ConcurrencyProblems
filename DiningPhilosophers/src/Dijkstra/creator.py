from fork import Fork
from philosopher import Philosopher
from time import sleep


class Creator:

    def __init__(self, no_philosophers):
        self.no_philosophers = no_philosophers
        self.no_forks = no_philosophers

        self.philosophers = []
        self.forks = []

        for index in range(self.no_forks):
            self.forks.append(Fork(index))

        for index in range(self.no_philosophers):
            ph = Philosopher(f'PH_{index}')
            left_fork = self.forks[(index + 1) % self.no_forks]
            right_fork = self.forks[index]
            ph.set_left_fork(left_fork)
            ph.set_right_fork(right_fork)
            self.philosophers.append(ph)

    def start(self, session_time):
        for ph in self.philosophers:
            ph.start()

        sleep(session_time)
        for ph in self.philosophers:
            ph.stop_philosopher()

        all_finished = False
        while all_finished is False:
            sleep(0.5)
            all_finished = True
            for ph in self.philosophers:
                if ph.finished is False:
                    all_finished = False
                    break

            if all_finished is True:
                for ph in self.philosophers:
                    print(f'Philosopher({ph.name}) ate {ph.eat_count} times')

if __name__ == '__main__':
    creator = Creator(5)
    creator.start(120)