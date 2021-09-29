#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>
#include <time.h>
#include <chrono>
#include <thread>
#include <sys/mman.h>

using std::cout; using std::endl;
using std::vector;


void produce(int* shared) {
	cout << shared << endl;
	int curr_val = 0;
	while(true) {
		curr_val += 1;
		cout << "Parent (" << getpid() << ") curr value: " << curr_val << endl;
		*shared = curr_val;
        	int sleep_seconds = rand() % 3;
		sleep(sleep_seconds);
		// cout << "Parent curr value: " << *shared << endl;
	}

}

void consume(int* shared) {
	cout << shared << endl;
	int consumer_curr_val = 0;
	while(true) {
		// cout << "Child shared value: " << *shared << endl;
		if(consumer_curr_val != *shared) {
			cout << "Consumer child (" << getpid() << ") value changing from " << consumer_curr_val << " -> " << *shared << endl;
			consumer_curr_val = *shared;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

int main() {
    srand(time(NULL));
    cout << "Starting first program " << getpid() << endl;

	cout << "STDOUT Number: " << STDOUT_FILENO << endl;
	cout << "STDIN Number: " << STDIN_FILENO << endl;

	// Read documentation on mmap - it's got many features
	void *shared_memory = mmap(
		/* addr= */ NULL,
        /* length= */ sizeof(int),
        /* prot= */ PROT_READ | PROT_WRITE,
        /* flags= */ MAP_SHARED | MAP_ANONYMOUS,
        /* fd= */ -1,
        /* offset= */ 0
	);

	int *shared = (int*)shared_memory;

    pid_t c_pid = fork();	// Create a single child

	// Can make more consumer children processes
	//for( int i = 0; i < 3; i++ ) {
	//  if(c_pid > 0) { c_pid = fork(); }
	//}

    if (c_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (c_pid > 0) {     // Only the parent gets a c_pid other than zero
        cout << "printed from parent process (created new child)" << getpid() << endl;
	produce(shared);
    } else if (c_pid == 0) {        // Children all get a c_pid value of zero
        cout << "printed from child process " << getpid() << endl;
	consume(shared);
    }

    cout << getpid() << " process quitting" << endl;

    return EXIT_SUCCESS;
}
