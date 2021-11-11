#include "remove_tag.h"

void remove_tag(char * path, char * tag) {
    int rc = removexattr (path, tag);
    char * aux = tag+5;
    if (rc == -1) {
        printf("[add_tag-ERROR] %s\n", strerror(errno));
        printf("[add_tag-ERROR] The tag %s could not be remove to the file %s. \n", aux, path);
    } else {
        printf("[add_tag] The tag %s has been remove to the file %s. \n", aux, path);
    }
}


// int main(int argc, char **argv) {
//     // ./remove_tag [path] [user.tag0_name] .... [user.tagi_name]
//     if (argc < 3) {
//         perror("Incorrect arguments. Command: ./remove_tag [path] [user.tag0_name] ... [user.tagi_name]\n"); exit(1);
//     }
//     for (int i = 2 ; i < argc ; i++) {
//
//         //TO DO : vérifier que le tag existe dans la hiérarchie ?
//
//         remove_tag(argv[1], argv[i]);
//     }
//
//     return 0;
// }
