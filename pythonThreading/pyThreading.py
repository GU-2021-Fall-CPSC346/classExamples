import logging
import threading
import time
import queue
import random

def thread_function(name):
    logging.info("Thread %s: starting", name)
    time.sleep(2)
    logging.info("Thread %s: finishing", name)

def thread_generator(name, buf):
    logging.info("Thread %s: starting", name)
    for i in range(10):
        msg = random.randint(1, 100)
        print(f"Enqueue new message: {msg}")
        buf.put(msg)
        time.sleep(1)
    logging.info("Thread %s: finishing", name)

def thread_consumer(name, buf):
    logging.info("Thread %s: starting", name)
    while True:
        msg = buf.get(random.randint(1,100))
        print(f"Got message! {msg}")



if __name__ == "__main__":
    format = "%(asctime)s: %(message)s"
    logging.basicConfig(format=format, level=logging.INFO,
                        datefmt="%H:%M:%S")

    buf = queue.Queue()

    logging.info("Main    : before creating thread")
    x = threading.Thread(target=thread_function, args=(1,))
    y = threading.Thread(target=thread_generator, args=(2,buf,))
    z = threading.Thread(target=thread_consumer, args=(3,buf,), daemon=True)
    logging.info("Main    : before running thread")
    x.start()
    y.start()
    z.start()
    logging.info("Main    : wait for the threads to finish")
    x.join()
    y.join()
    logging.info("Main    : all done")
