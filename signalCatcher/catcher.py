#!/usr/bin/env python3

import signal
import sys
from time import sleep

def signal_handler(sig, frame):
    print('You pressed Ctrl+C!')
    print(" OR you sent SIG INT")
    sys.exit(0)

def signal_handler_usr1(sig, frame):
    print('User 1 Rocks!')

def signal_handler_usr2(sig, frame):
    print('User 2 is first loser!')

signal.signal(signal.SIGINT, signal_handler)
signal.signal(signal.SIGUSR1, signal_handler_usr1)
signal.signal(signal.SIGUSR2, signal_handler_usr2)

if __name__ == "__main__":
    print('Press Ctrl+C')
    signal.pause()

    print("Caught a signal!")

    count = 0
    while(True):
        print(f"Sleeping : {count}")
        sleep(1)
        count += 1
