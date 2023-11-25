//
// Created by Sanjana Nagwekar on 11/24/23.
//


//Process prints 0

//Using valgrind:
/*
 * ==13356== Mencheck, a menory error detector
==13356== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al. ==13356== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==13356== Command：-/q6
==13356==
==13356== Invalid read of size 4
==13356==
==13356==
at 0x1088F0: main (in /home/sanjana_n/CLionProjects/cs149/WS12/q6)
Address 0x4a4a108 is 200 bytes inside a block of size 400 free'd
==13356==
at 0x4867AD0: free (in /us/libexec/valgrind/vgpreload_memcheck-arm64-linux.s
0)
==13356==
by 0x1088E7: main (in /home/sanjana_n/CLionProjects/cs149/WS12/q6)
==13356== Block was alloc'd at
==13356==
at 0x4865058: malloc (in /us/Libexec/valgrind/vgpreload_memcheck-arm64-linux
* 50)
==13356==
by 0x1088A3: main (in /home/sanjana_n/CLionProjects/cs149/WS12/q6)
==13356==
==13356==
==13356== HEAP SUMMARY:
==13356==
in use at exit: 0 bytes in 0 blocks
==13356==
total heap usage: 2 allocs, 2 frees, 1,424 bytes allocated
==13356==
==13356== All heap blocks were freed -- no leaks are possible
==13356==
==13356== For lists of detected and suppressed errors, rerun with: -s ==13356== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
    int *data = (int*)malloc(sizeof(int) * 100);

    if (data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    free(data);

    printf("%d\n", data[50]);

    return 0;
}