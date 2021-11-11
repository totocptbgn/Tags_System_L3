#include "list_tag.h"

void list_tag(char * path) {
    //We get the size of the list
    size_t list_size = listxattr(path, NULL, 0);
    if (list_size == -1) {
        printf("[list_tag-ERROR] %s\n", strerror(errno));
    } else {
    //Now that we have got the size of the list, copy the list of tags to the buffer
    if (list_size == 0) {
        printf("[list_tag] The %s file does not have any tag.\n", path);
    } else {
        char * list = malloc(list_size);
        size_t rc = listxattr(path, list, list_size);
        if (rc == -1) {
            printf("[list_tag-ERROR] %s\n", strerror(errno));
            printf("[list_tag-ERROR] Unable to retrieve attribute list from file %s.\n", path);
        } else {
            int dec = 0;
            size_t tag_size;
            char * tag_value;
            while (list_size > 0) {
                char * aux = list+dec+5;
                printf("%s\n", aux);
                rc = getxattr(path, list+dec, NULL, 0);
                if (rc == -1) {
                    perror("[list_tag-ERROR] getxattr"); exit(1);
                } else if (rc == 0) {
                    //printf("<no value> \n");
                } else {
                    tag_value = malloc(rc + 1);
                    if (tag_value == NULL) {
                        perror("[list_tag-ERROR] malloc"); exit(1);
                    }
                    rc = getxattr(path, list+dec, tag_value, rc);
                    if (rc == -1) {
                        perror("[list_tag-ERROR] getxattr"); exit(1);
                    } else {
                        tag_value[rc] = 0;
                        //printf("%s", tag_value);
                    }
                    free(tag_value);
                }
                tag_size = strlen(list+dec) + 1;
                list_size -= tag_size;
                dec += tag_size;
                }
            }
        }
    }
}

// int main(int argc, char **argv) {
//     // ./list_tag [path]
//     if (argc != 2) {
//         perror("Incorrect arguments. Command: ./list_tag [path]\n"); exit(1);
//     }
//     list_tag(argv[1]);
//     return 0;
//     }
