#ifndef TAG_MANAG_H
#define TAG_MANAG_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <fcntl.h>
    #include <unistd.h>

    /**
     * Crée le fichier qui liste les tags.
     * Retourne 0 en cas de succès et -1 et un affichage en cas d'erreur.
     * 
     * RETIRÉ DU PROJET CAR FAIT À L'INSTALLATION EN COPIANT LE FICHIER DIRECTEMENT...
     */

    // int create_tag_file();


    /**
     * Ajoute un tag au fichier ~/.tag
     * Si vous ne voulez pas que le tag ai un parent, mettre `father` à NULL.
     * Retourne 0 en cas de succès et -1 et un affichage en cas d'erreur.
     */

    int add_new_tag(char* name, char* father);

    /**
     * Renvoie 1 si `child_tag` est le fils de `father_tag`.
     * Renvoie 0 si `child_tag` n'est pas le fils de `father_tag`.
     * Renvoie -1 en cas d'erreur.
     */

    int is_child_tag(char* child_tag, char* father_tag);


    /**
     * Renvoie 1 si le tag existe.
     * Renvoie 0 si le tag n'existe pas.
     * Renvoie -1 en cas d'erreur.
     */

    int is_tag_exists(char* name);
#endif
