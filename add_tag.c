#include "add_tag.h"


void add_tag_to_file(char * path, char * tag) {
    char aux[100] = "user.";
    strcat(aux, tag);
    int rc = setxattr (path, aux, NULL, 0, 0);
    if (rc == -1) {
        printf("[add_tag-ERROR] %s\n", strerror(errno));
        printf("[add_tag-ERROR] The tag %s could not be added to the file %s. \n", tag, path);
    } else {
        printf("[add_tag] The tag %s has been added to the file %s. \n", tag, path);
    }
}

// int main(int argc, char **argv) {
//
//     create_tag_file();
//
//     // ./add_tag [path] [user.tag0_name] .... [user.tagi_name]
//     if (argc < 3) {
//         perror("Incorrect arguments. Command: ./add_tag [path] [user.tag0_name] ... [user.tagi_name]\n"); exit(1);
//     }
//     for (int i = 2 ; i < argc ; i++) {
//         int rc = is_tag_exists(argv[i]);
//         if (rc == -1) {
//             printf("[main-ERROR] is_tag_exists\n");
//         }
//         if (is_tag_exists(argv[i]) == 1) {
//             add_tag_to_file(argv[1], argv[i]);
//         } else {
//             rc = 0;
//             while (rc == 0) {
//                 printf("The tag %s is not in our database. Do you want to add it ? (yes/no)", argv[i]);
//                 char res[3] = {0};
//                 scanf("%s", res);
//                 if (strcmp(res,"yes")==0) {
//                     int r = add_new_tag(argv[i],NULL);
//                     if (r == -1) {
//                         printf("Error : Cannot add the tag to the database.\n");
//                     }
//                     rc = 1;
//                 } else if (strcmp(res,"no")==0) {
//                     rc = 1;
//                 }
//             }
//             add_tag_to_file(argv[1], argv[i]);
//         }
//     }
//     return 0;
// }
