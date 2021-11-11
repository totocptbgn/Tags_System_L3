#include "add_tag.h"
#include "find.h"
#include "list_tag.h"
#include "remove_tag.h"
#include "tag_manag.h"


int main (int argc, char **argv){
    if(argc == 1){
    printf("Use tag -c to create a tag in the list tag.\n");
    printf("Use tag -a to add a tag to a file.\n");
    printf("Use tag -r to remove a tag from a file.\n");
    printf("Use tag -l to list all the tags from a file.\n");
    printf("Use tag -f to list file with a tag filter.\n");
    return 0;
    }
    /*
    if(strcmp(argv[1],"-i")==0){
        if (argc != 2) {
            perror("Incorrect arguments. Command: tag -i\n");
            exit(1);
        }
        create_tag_file();

    }
    */


    if(strcmp(argv[1],"-a")==0){
        if (argc < 4) {
            perror("Incorrect arguments. Command: tag -a <path> <tag_name> ...\n");
            exit(1);
        }
        for (int i = 3 ; i < argc ; i++) {
            int rc = is_tag_exists(argv[i]);
            if (rc == -1) {
                printf("[main-ERROR] is_tag_exists\n");
            }
            if (is_tag_exists(argv[i]) == 1) {
                add_tag_to_file(argv[2], argv[i]);
            } else {
                rc = 0;
                while (rc == 0) {
                    printf("The tag %s is not in our database. Do you want to add it ? (yes/no)", argv[i]);
                    char res[3] = {0};
                    scanf("%s", res);
                    if (strcmp(res,"yes")==0) {
                        int r = add_new_tag(argv[i],NULL);
                        if (r == -1) {
                            printf("Error : Cannot add the tag to the database.\n");
                        }
                        add_tag_to_file(argv[2], argv[i]);
                        rc = 1;
                    } else if (strcmp(res,"no")==0) {
                        rc = 1;
                    }
                }

            }
        }
    }

    if(strcmp(argv[1],"-c")==0){
        if (argc < 3) {
            perror("Incorrect arguments. Command: tag -c <tag_name> ...\n");
            exit(1);
        }
        if(argc == 3){
            if(is_tag_exists(argv[2])==1){
                perror("The tag already in our the database.");
                exit(1);
                //PEUT CHANGER
            }
            add_new_tag(argv[2],NULL);
        } else if(argc == 4){
            if(is_tag_exists(argv[3])==0){
                perror("We can't find the father_tag.");
                exit(1);
                //PEUT CHANGER
            }
            if(is_tag_exists(argv[2])==1){
                perror("The tag already in our the database.");
                exit(1);
                //PEUT CHANGER
            }
            add_new_tag(argv[2],argv[3]);

        } else {
            perror("Incorrect arguments. Command: tag -c <tag_name> tag -c <tag_name> <father_tag_name>");
        }

    }
    if(strcmp(argv[1],"-r")==0){
        if (argc < 4) {
            perror("Incorrect arguments. Command: tag -r [path] [user.tag0_name] ... [user.tagi_name]\n");
            exit(1);
        }
        for (int i = 3 ; i < argc ; i++) {

            char aux[100] = "user.";
            strcat(aux, argv[i]);

            remove_tag(argv[2], aux);

        }


    }
    if(strcmp(argv[1],"-l")==0){
        if (argc != 3) {
            perror("Incorrect arguments. Command: ./list_tag [path]\n");
            exit(1);
        }
        list_tag(argv[2]);
    }
    if(strcmp(argv[1],"-f")==0){
        if (argc < 4) {
         perror("Incorrect arguments. Command: ./tag -f [path] [ /-][user.tag0] ... [ /-][user.tagn]\n");
         exit(1);
        }

        if (strcmp(argv[2], ".")==0) {
            chdir("./");
            find_files_arbor("./",argc, argv);
        } else {
            chdir(argv[2]);
            find_files_arbor(argv[2],argc, argv);
        }


    }
    if(strcmp(argv[1],"-rf")==0){
        if (argc < 4) {
         perror("Incorrect arguments. Command: ./tag -rf [path] [ /-][user.tag0] ... [ /-][user.tagn]\n");
         exit(1);
        }

        if (strcmp(argv[2], ".")==0) {
            find_files_dir("",argc, argv);
        } else {

            chdir(argv[2]);
            find_files_dir(argv[2],argc, argv);
        }
    }




    return 0;
}
