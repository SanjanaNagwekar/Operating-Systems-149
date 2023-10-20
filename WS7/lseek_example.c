// C program to read nth byte of a file and
// copy it to another file using lseek
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>

void func(char arr[])
{
    // Open the input file for READ only.
    int f_read = open("start.txt", O_RDONLY);

    if (f_read == -1) {
        perror("Error opening input file");
        return; // Exit the function if the file can't be found
    }

    // Open the output file for WRITE only.
    int f_write = open("end.txt", O_WRONLY | O_CREAT, 0777);

    int i = 0;

    while (read(f_read, arr, 1))
    {
        if (i % 4 == 0)
        {
            write(f_write, arr, 1);
        }
        i++;
    }

    close(f_write);
    close(f_read);
}

int main()
{
    char arr[1]; // We read one character at a time

    // Calling the function
    func(arr);
    return 0;
}