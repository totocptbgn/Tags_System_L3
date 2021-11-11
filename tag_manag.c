#include "tag_manag.h"

char* get_path_tag_file() {
    char *filename = "/.tag/tags";
    char *home_dir = getenv("HOME");
    char *filepath = malloc(strlen(home_dir) + strlen(filename) + 1);
    strncpy(filepath, home_dir, strlen(home_dir) + 1);
    strncat(filepath, filename, strlen(filename) + 1);
    return filepath;
}
/*
int create_tag_file() {
    char* filepath = get_path_tag_file();
    remove(filepath);
    int fl = open(filepath, O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);
    if (fl < 0) {
        perror("open");
        free(filepath);
        return -1;
    }
    int tag = open("tags_default", O_RDONLY);
    if (tag < 0) {
        perror("open");
        close(fl);
        free(filepath);
        return -1;
    }

    char buffer[400];
    memset(buffer, '\0', 400);
    int r = read(tag, buffer, 400);
    if (write(fl, buffer, r) == -1) {
        perror("write");
        close(fl);
        close(tag);
        free(filepath);
        return -1;
    }

    close(fl);
    close(tag);
    free(filepath);
    return 0;
}
*/
int add_new_tag(char* name, char* father) {

    if (name == NULL || strlen(name) == 0) return -1;
    if (father != NULL && strlen(father) == 0) return -1;

    // On vérifie que le fichier ~/.tag existe
    char* filepath = get_path_tag_file();
    int test = open(filepath, O_RDONLY);
    if (test < 0) {
        perror("open");
        return -1;
    }
    close(test);
    FILE* file = fopen(filepath, "r");
    if (file == NULL) {
        perror("fopen");
        return -1;
    }

    // On compte le nombre de char dans le fichier
    char c;
    int compt = 0;
    int i = 0;
    while ((c = getc(file)) != EOF) {
        compt++;
    }

    // On créer un buffer et on le rempli avec le fichier de tag
    rewind(file);
    char buffer[compt + 1];
    while ((c = getc(file)) != EOF) {
        buffer[i] = c;
        i++;
    }
    buffer[compt] = '\0';

    // On cherche le dernier id et l'id du tag père
    char* tpid = NULL;
    char* id = NULL;
    char* p_id = NULL;
    char* tag_name = NULL;
    char* ptr = strtok(buffer, " \n");
    while(ptr != NULL) {
        id = p_id;
        p_id = tag_name;
        tag_name = ptr;
        if (father != NULL &&strcmp(tag_name, father) == 0) {
            tpid = id;
        }
        ptr = strtok(NULL, " \n");
    }
    if (father != NULL && tpid == NULL) {
        fprintf(stderr, "Father not found.\n");
        return -1;
    }
    int new_id = atoi(id);
    new_id++;

    // On écrit le nouveau tag à la fin du fichier
    fclose(file);
    FILE* app = fopen(filepath, "a");
    int len;
    if (father == NULL) {
        len = strlen(id) + strlen(name) + 5;
        char buff[len];
        snprintf(buff, len, "%d 0 %s\n", new_id, name);
        fputs(buff, app);
    } else {
        len = strlen(id) + strlen(name) + strlen(tpid) + 4;
        if (strcmp(id, "99") == 0 || strcmp(id, "999") == 0) len++;
        char buff[len];
        snprintf(buff, len, "%d %s %s\n", new_id, tpid, name);
        fputs(buff, app);
    }

    fclose(app);
    free(filepath);
    return 0;
}

int is_child_tag(char* child_tag, char* father_tag) {

    if (child_tag == NULL || strlen(child_tag) == 0) return 0;
    if (father_tag == NULL || strlen(father_tag) == 0) return 0;

    // On vérifie que le fichier ~/.tag existe
    char* filepath = get_path_tag_file();
    int test = open(filepath, O_RDONLY);
    if (test < 0) {
        perror("open");
        return -1;
    }
    close(test);
    FILE* file = fopen(filepath, "r");
    if (file == NULL) {
        perror("fopen");
        return -1;
    }

    // On compte le nombre de char dans le fichier
    char c;
    int compt = 0;
    int i = 0;
    while ((c = getc(file)) != EOF) {
        compt++;
    }

    // On créer un buffer et on le rempli avec le fichier de tag
    rewind(file);
    char buffer[compt + 1];
    while ((c = getc(file)) != EOF) {
        buffer[i] = c;
        i++;
    }
    buffer[compt] = '\0';

    // On cherche l'id du tag père de child_tag et l'id du tag du père
    char* id = NULL;
    char* p_id = NULL;
    char* tag_name = NULL;

    char* fathers_child = NULL;
    char* father = NULL;

    char* ptr = strtok(buffer, " \n");
    while (ptr != NULL) {
        id = p_id;
        p_id = tag_name;
        tag_name = ptr;
        if (strcmp(child_tag, tag_name) == 0) {
            fathers_child = p_id;
        } else if (strcmp(father_tag, tag_name) == 0) {
            father = id;
        }
        ptr = strtok(NULL, " \n");
    }
    free(filepath);
    fclose(file);
    if (fathers_child == NULL || father == NULL) {
        //fprintf(stderr, "Tag not found.\n");
        return -1;
    }
    if (strcmp(father, fathers_child) == 0) {
        return 1;
    }
    return 0;
}

int is_tag_exists(char* name) {
    if (name == NULL || strlen(name) == 0) return 0;

    // On vérifie que le fichier ~/.tag existe
    char* filepath = get_path_tag_file();
    int test = open(filepath, O_RDONLY);
    if (test < 0) {
        perror("open");
        return -1;
    }
    close(test);
    FILE* file = fopen(filepath, "r");
    if (file == NULL) {
        perror("fopen");
        return -1;
    }

    // On compte le nombre de char dans le fichier
    char c;
    int compt = 0;
    int i = 0;
    while ((c = getc(file)) != EOF) {
        compt++;
    }

    // On créer un buffer et on le rempli avec le fichier de tag
    rewind(file);
    char buffer[compt + 1];
    while ((c = getc(file)) != EOF) {
        buffer[i] = c;
        i++;
    }
    buffer[compt] = '\0';

    // On cherche le tag
    char* ptr = strtok(buffer, " \n");
    while (ptr != NULL) {
        if (strcmp(ptr, name) == 0) {
            free(filepath);
            fclose(file);
            return 1;
        }
        ptr = strtok(NULL, " \n");
    }
    free(filepath);
    fclose(file);
    return 0;
}

// int main(void) {
//     create_tag_file();
//     /*
//     add_new_tag("Nom_Tag", NULL);
//     add_new_tag("Nom_Tag", "Nom_Tag_Père");
//
//     printf("%d\n", is_child_tag("L3", "Uni"));
//     printf("%d\n", is_child_tag("Java", "Color"));
//     printf("%d\n", is_child_tag("Toto", "Boss"));
//
//     printf("%d\n", is_tag_exists("Color"));
//     printf("%d\n", is_tag_exists("Toto"));
//     */
//     return 0;
// }
