# ARCHITECTURE

Ce document sert à donner des précisions sur l'implémentation du système de tag. L'installation du projet et les commandes sont décrites dans le fichier [README.md](README.md).

## Architecture du programme 
```
.
├── README.md // Fichiers d'informations en Markdown
├── ARCHITECTURE.md
├── AUTHORS.md
│ 
├── CMakeLists.txt // Configuration du cmake
├── Makefile // Makefile avec installation, clean, build 
├── build.sh // Compile avec CMake 
├── install.sh // Compile et installe 
│ 
├── add_tag.c // Fonctions pour ajouter les tags 
├── find.c // Fonctions pour la recherche de fichiers avec tags 
├── list_tag.c // Fonctions pour la lecture des tags d'un fichier 
├── remove_tag.c // Fonctions pour retirer les tags 
├── tag_manag.c // Fonction pour la gestions de la hierachies des tags 
│ 
├── add_tag.h // Headers 
├── find.h 
├── list_tag.h 
├── remove_tag.h 
├── tag_manag.h 
│ 
├── tag.c // Traitements des paramètres et main 
└── tags_default // Fichier des tags par défault
```

## Choix d'implémentation 
Nous avons fait le choix d'utiliser la bibliothèque `<sys/xattr.h>` pour écrire les tags directement dans les i-nœuds. Les tags et leur hierarchie sont stockée dans des fichiers dans le répertoire `$HOME`.

### Où sont stockés les tags ? 
Les tags sont stockés dans le fichier `~/.tag/tags`.
On peut en ajouter avec la commande `tag -c`.

### Comment sont-ils mis à jour ?
Après avoir concaténé le nom du tag donné par l'utilisateur à la chaîne de caractères `user.`, nous utilisons les fonctions `setxattr()` et `removexattr()` de la bibliothèque XATTR pour ajouter et supprimer un tag. 

### Quand sont mis à jour les tags des fichiers ? 
Les tags des fichiers sont mis à jour lorsque l'on appelle les commandes`tag -a [path] [tag_name_0] ... [tag_name_i]` et `tag -r [path] [tag_name_0] ... [tag_name_i]` qui, respectivement, permettent d'ajouter ou de supprimer un ou plusieurs tag(s) d'un fichier. 

### Algorithmes implémentés 
Pour comparer un tag donné par l'utilisateur aux tags d'un fichier, nous concaténons la chaîne `user.` au nom du tag.

#### Lister les tags d'un fichier
La fonction `list_tag` (du fichier `list_tag.c`) utilise `listxattr()` pour parcourir et afficher les tags d'un fichier. Après avoir récupéré la taille de la liste de tags, nous parcourons celle-ci grâce à la fonction `getxattr()`. En effet, la liste représente une suite de chaînes de caractères séparés par le caractère nul `\0`. Nous nous sommes inspirés de l'exemple de la page de manuel de [LISTXATTR(2)](http://man7.org/linux/man-pages/man2/listxattr.2.html) pour écrire cet algorithme. 

#### Lister les fichiers possédant une combinaison de tags 

Pour savoir si un fichier possède une certaine combinaison de tags, nous utilisons la fonction `analyse_tags_file()` (dans `find.c`). Si le caractère `-` a été placé avant le nom du tag, il ne faut pas que le fichier possède ce tag. Nous supprimons alors ce caractère et vérifions que ce tag, ou un de ces enfants s'il en a, n'est pas un tag du fichier dont il est question grâce à la fonction `isTagOf()`(`find.c`). Cette fonction utilise `is_child_tag()` (du fichier `tag_manag.h`)  qui nous indique si un certain tag du fichier est le père du tag donné par l'utilisateur. S'il n'y a pas le caractère `-` avant le nom du tag, il faut que les fichiers que l'on va afficher possèdent ce tag. Dans ce cas là, nous effectuons les tests adéquats.


L'utilisateur peut choisir de lister soit seulement les fichiers du répertoire donné qui correspondent à une combinaison de tags (avec la commande `tag -rf`), soit tous les fichiers de l'arborescence à partir du répertoire donné (`tag -r`). 


Dans le premier cas, la fonction `find_files_dir()` (du fichier `find.c`) parcourt les fichiers du répertoire donné et affiche les fichiers voulus grâce à la fonction `analyse_tags_file` décrite plus haut. 


Dans le deuxième cas, la fonction `find_files_arbor()` (dans `find.c`) parcourt les fichiers du répertoire donné ainsi que tous ceux de tous les sous-répertoires à partir du répertoire donné. 


Pour ces deux dernières fonctions, nous nous sommes servis de l'exercice 4 du TP7 de Systèmes. 

