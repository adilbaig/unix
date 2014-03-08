#include <sys/types.h>
#include <attr/xattr.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if(argc < 2) {
        fprintf(stderr, "$s <file path> \n", argv[0]);
        return 1;
    }

    char *list;

    // If 0 is passed for size, the return value is the size of the keys
    ssize_t list_l = listxattr(argv[1], list, 0);
    if(list_l < 0) {
        perror("listxattr");
        return 1;
    }

    printf("Xattr list size is %zd\n", list_l);

    // Using the size, malloc for actually getting the list
    list = malloc(list_l);

    // Get the list of xattr keys
    ssize_t ret = listxattr(argv[1], list, list_l);
    if(ret < 0) {
        perror("listxattr");
        return 1;
    }

    // Now allocated enough memory at *attr so i can fetch each key
    char *attr = malloc(list_l);

    // token_size = The size returned by sprintf;
    int token_size;

    // The remaining number of chars unprocessed in 'list'
    int diff = list_l;

    // The value of the xattr key
    char *value;

    while(diff > 0) {

        // Extract the key
        token_size = sprintf(attr, "%s", list);

        //Fetch the length of value
        ssize_t attr_l = getxattr(argv[1], attr, value, 0);
        if(ret < 0) {
            perror("getxattr");
            return 1;
        }

        //Get the actual value
        value = malloc(attr_l);
        if(getxattr(argv[1], attr, value, attr_l) < 0) {
            perror("listxattr");
            return 1;
        }

        //Print key/value
        printf("- %s : '%s' \n", attr, value);

        free(value);

        list += (token_size + 1);
        diff -= token_size + 1;
    }

    return 0;
}
