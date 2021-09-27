#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>
#include <time.h>

using std::cout; using std::endl;
using std::vector;

int main() {
    srand(time(NULL));
    cout << "Starting first program " << getpid() << endl;

    for(int i = 0; i < 10; i++) {
        pid_t c_pid = fork();

        if (c_pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (c_pid > 0) {     // Only the parent gets a c_pid other than zero
            cout << "printed from parent process (created new child)" << getpid() << endl;
        } else if (c_pid == 0) {        // Children all get a c_pid value of zero
            int sleep_seconds = rand() % 5;
            cout << "printed from child process " << getpid() << " -- Waiting " << sleep_seconds << " sec" << endl;
            sleep(sleep_seconds);
            break;
        }
    }

    wait(nullptr);  // Waits for *all* children to change state (finish)
    cout << getpid() << " process quitting" << endl;

    return EXIT_SUCCESS;
}
