
#include <iostream>
#include <cstring>
#include <unistd.h>

using std::cout;
using std::endl;

int main() {
	char myStr[20] = "Hello World\n";
	size_t myStrLen = strlen(myStr);

	int fileDescriptor = 1;

	// STDOUT_FILENO
	// STDIN_FILENO
	
	write(fileDescriptor, myStr, myStrLen);

}
