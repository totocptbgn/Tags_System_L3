#ifndef FIND_H
#define FIND_H

    #include <string.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <dirent.h>
    #include <sys/stat.h>
    #include <unistd.h>
    #include <sys/xattr.h>
    #include <errno.h>
    #include "tag_manag.h"

    int isTagOf(char *path, char *tagName);


    /*
    dir_cur = 0 : appliquer la fonction find seulement sur les fichier du repertoire courant
    dir_cur = 1 : appliquer la fonction find sur toute l'arborescence
    */
    void find_files_arbor(char *path, int tag_number, char **tags);

    void find_files_dir(char *path, int tag_number, char **tags);

    int analyse_tags_file(char *path, int tag_number, char **tags);

#endif
