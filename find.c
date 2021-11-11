#include "find.h"

int isTagOf(char *path, char *tagName) { //0 true, 1 false, -1 error
    //We get the size of the list
    size_t list_size = listxattr(path, NULL, 0);
    if(list_size == -1) {
        //printf("[isTagOf-ERROR] list_size %s; path = %s \n", strerror(errno), path);
        return -1; //error
    } else {
        if(list_size == 0) {
            return 1; //False
        } else {
            char * list = malloc(list_size);
            size_t rc = listxattr(path, list, list_size);
            if (rc == -1) {
                printf("[isTagOf-ERROR] listxattr %s\n", strerror(errno));
                return -1; //error
            } else {
                int dec = 0;
                size_t tag_size;
                while(list_size > 0) {

                    char * aux = list+dec+5; //Sans "user."
                    char * tagNameBis = tagName+5; //Sans "user."
                    if (strcmp(list+dec,tagName) == 0 ||is_child_tag(aux, tagNameBis)==1) {
                        return 0; //true
                    }
                    tag_size = strlen(list+dec) +1;
                    list_size  -= tag_size;
                    dec += tag_size;
                }
            }
        }
    }
    return 1; //False
}

char * erase_first_char(char *tag) {
    int size = sizeof(char)*(strlen(tag));
    char *s =  malloc(size);
    memcpy(s, tag+1, size);
    return s;
}

int analyse_tags_file(char *path, int tag_number, char **tags) {
    for (int i = 3; i<tag_number;i++) {

        char first_char[100] = {0};
        memcpy(first_char, tags[i],1);

        if (strcmp(first_char, "-") == 0) {
            //On enlève le "-"
            char *t = erase_first_char(tags[i]);
            char aux[200] = "user.";
            strcat(aux, t);

            if (isTagOf(path,aux)==0){
                return 1;
            }

        } else {
            char aux[100] = "user.";
            strcat(aux, tags[i]);
            if(isTagOf(path,aux)!=0) {
                return 1;
            }
        }
    }
    return 0;

}

void find_files_dir(char *path, int tag_number, char **tags) {
    DIR * dir;
    struct dirent *read;
    dir = opendir(".");
    if (dir == NULL) {
        perror("The directory does not exist.\n");
        exit(1);
    }

    while ((read = readdir(dir)) != NULL) {


        if(strcmp(read->d_name, "..") !=0 && strcmp(read->d_name, ".") != 0) {

            struct stat s;
            stat(read -> d_name, &s);
            char pathtag[100] = {0};
            memcpy(pathtag, path,strlen(path));
            strcat(pathtag, read->d_name);

            int rc = analyse_tags_file(pathtag,tag_number, tags);
            if (rc==0) {
                printf("%s%s\n", path, read->d_name);
            }

        }
    }
    closedir(dir);
}

void find_files_arbor(char *path, int tag_number, char **tags) {

    DIR * dir;
    struct dirent *read;
    dir = opendir(".");
    if (dir == NULL) {
        perror("The directory does not exist.\n");
        exit(1);
    }

    while ((read = readdir(dir)) != NULL) {


        if(strcmp(read->d_name, "..") !=0 && strcmp(read->d_name, ".") != 0) {

            struct stat s;
            stat(read -> d_name, &s);
            char * pathfile = malloc(sizeof(char*)*strlen(path));
            memcpy(pathfile, path, sizeof(char*)*strlen(path));
            strcat(pathfile, read->d_name);

            int rc = analyse_tags_file(pathfile,tag_number, tags);
            if (rc==0) {
                printf("%s%s\n", path, read-> d_name);
            }

            if((s.st_mode & S_IFDIR) != 0) {
                int x = fork();
                if(x==0) {
                    char* path2 = malloc(sizeof(char) * (strlen(read->d_name) + 2 + strlen(path)));
                    memcpy(path2, path, strlen(path));
                    memcpy(path2 + strlen(path), read -> d_name, strlen(read->d_name));
                    memcpy(path2 + strlen(path) + strlen(read->d_name), "/", 2);
                    chdir(read -> d_name);
                    closedir(dir);
                    find_files_arbor(path2, tag_number, tags);
                    return;
                }

            }
        }
    }
    closedir(dir);
}

//
// int main(int argc, char **argv) {
//     // ./find [user.tag0] ... ![user.tagn]
//     if (argc < 2) {
//          perror("Incorrect arguments. Command: ./find [path] [ /-][user.tag0] ... [ /-][user.tagn]\n");exit(1);
//     }
//     char path[100] =  {0};
//     chdir(argv[1]);
//     find_files_arbor(argv[1],argc, argv);
//     return 0;
// }
