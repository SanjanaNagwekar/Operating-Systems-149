//
// Created by Sanjana Nagwekar on 11/24/23.
//

//Program runs and finishes with exit code 0

//Using valgrind:
/*
 * sanjana_n@sanjananagwekar:~/CLionProjects/cs149/WS12$ valgrind •/q5
==13344== Memcheck, a memory error detector ==13344== Copyright (C) 2002-2017,
and GNU GPL'd, by Julian Seward et al.
==13344== Using Valgrind-3.18.1 and Libvex; rerun with -h for copyright info ==13344== Command: • /q5
==13344==
==13344== Invalid write of size 4
==13344==
at 0x108804: main (in /home/sanjana_n/CLionProjects/cs149/WS12/q5)
==13344==
Address 0x4a4a1do is 0 bytes after a block of size 400 alloc'd
==13344==
at 0x4865058: malloc (in /us/libexec/valgrind/vgpreload_memcheck-arm64-linux
• 50)
==13344==
by 0x1087E3: main (in /home/sanjana_n/CLionProjects/cs149/WS12Iq5)
==13344==
==13344==
==13344==
HEAP SUMMARY:
==13344==
in use at exit: 0 bytes in o blocks
==13344==
total heap usage: 1 allocs, 1 frees, 400 bytes allocated
==13344==
==13344== All heap blocks were freed -- no leaks are possible
==13344==
==13344== For lists of detected and suppressed errors, rerun with: -5
==13344== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
 */

#include <stdlib.h>

int main() {
    int *data = (int*)malloc(sizeof(int) * 100); // Allocate memory for 100 integers.

    if (data == NULL) {
        return 1;
    }

    data[100] = 0;

    free(data);

    return 0;
}