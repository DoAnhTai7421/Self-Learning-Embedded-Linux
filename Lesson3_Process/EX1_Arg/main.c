#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) // argc là số lượng các đối số môi trường; argv là mảng chứa thông tin/nội dung của từng đối số
{
    int i;

    // In ra số lượng command-line truyền vào
    printf("Number of arguments: %d\n", argc);

    // In ra nội dung của mỗi command-line:
    for(int i = 0; i < argc; i++)
    {
        printf("argv[%d] = %s\n", i, argv[i]);
    }

    return 0;
}