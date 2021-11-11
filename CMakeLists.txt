# Nous voulons un cmake "récent" pour utiliser les dernières fonctionnalités
cmake_minimum_required(VERSION 3.0)

# Notre projet est étiqueté systeme
project(systeme)

# Crée des variables avec les fichiers à compiler
set(MANAGE
    tag_manag.c
    tag_manag.h
    )

set(ADD
    add_tag.c
    add_tag.h
    )

set(LIST
    list_tag.c
    list_tag.h
    )

set(REMOVE
    remove_tag.c
    remove_tag.h
    )

set(FIND
    find.c
    find.h
    )

set(TAG 
    tag.c
    )

set(HEADERS
    tag_manag.h
    add_tag.h
    list_tag.h
    remove_tag.h
    find.h
    )

# Créer des éxectuables
#add_executable(manage ${MANAGE})
#add_executable(add_tag ${ADD} ${MANAGE})
#add_executable(remove_tag ${REMOVE})
#add_executable(list_tag ${LIST})
#add_executable(find ${FIND} ${MANAGE})

add_executable(tag ${MANAGE} ${ADD} ${LIST} ${REMOVE} ${FIND} ${TAG})
