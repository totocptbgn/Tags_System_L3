# Projet Système

Repository importé du GitLab de l'Université. Réalisé en Printemps 2020 avec [Léana Alfonso](https://github.com/leanaafs/) et Nemo Kott.

> Système de gestion de fichiers avec tag.
> Thomas BIGNON, Léana AFONSO, Nemo KOTT

Le but du projet est d'ajouter une couche par-dessus le système de gestion de fichiers (SGF), permettant de gérer les fichiers grâce à des tags. Ce système a été conçu pour le SGF des machines sous Unix et tout particulièrement la version [18.04](http://releases.ubuntu.com/18.04.3/ubuntu-18.04.3-desktop-amd64.iso) d'Ubuntu.
Plus de détails sur l'implémentation dans le fichier [ARCHITECTURE.md](ARCHITECTURE.md).

## Dépendances
Les paquets requis pour le fonctionnement du projet sont : 
- gcc
- cmake
- make

Pour les installer faites simplement :
```bash
$ sudo apt install gcc make cmake
```

## Installation

L'installation du projet se fait en plusieurs étapes :
- Compilation des fichiers sources (avec CMake)
- Installation d'un répertoire `.tag/` dans le répertoire `$HOME` et copie de :
	-  l'exécutable `build/tag` dans `.tag/tag`,
	-  du fichier de gestions des tags `tags_default` dans `.tag/tags`.
- Ajout dans le fichier de configuration du terminal `~/.bashrc` de :
	- L'alias de `cp` pour qu'il supporte les attributs étendus
	- L'ajout du répertoire `~/.tag/` à la variable `$PATH` pour que la commande soit exécutée de n'importe où.

Pour faire tout cela, il suffit de faire appel à :
```bash
$ ./install.sh
```
Il suffit ensuite de ré-ouvrir son terminal ou alors de recharger la configuration avec :
```bash
$ source ~/.bashrc
```

Le fichier `build.sh` sert à compiler avec CMake et créer un répertoire `build/`.
Il y a aussi un `Makefile` qui va simplement appeler les scripts, avec les commandes :
- `all` : Installe le projet.
- `build` : Compile le projet.
- `clean` : Désinstalle le projet. Attention,  cela retire les 5 dernières lignes du `.bashrc`, à utiliser seulement pour les tests.

## Commande `tag`

Toute les manipulations se font avec la commande `tag`. Voici les actions et les paramètres correspondants :

### Créer un tag
Pour créer un tag et l'ajouter à la liste des tags utilisez le paramètre `-c`:
```bash
$ tag -c <tag_name>
```
Cela va créer un tag sans père. Si vous voulez en rajoutez un :
```bash
$ tag -c <tag_name> <father_tag_name>
```
Les tags et leurs hiérarchies sont stockés dans le fichier `~/.tag/tags`.

### Ajouter un tag à un fichier
Pour ajouter un ou des tags à un fichier, utilisez le paramètre `-a` :

```bash
$ tag -a <path> <tag_name> ...
```
Vous pouvez mettre autant de tags que vous voulez. Si le tag est inconnu, vous pouvez l'ajouter directement sans père.

### Retirer un tag d'un fichier
Pour retirer un ou des tags à un fichier, utilisez le paramètre `-r` :
```bash
$ tag -r <path> <tag_name> ... 
```

### Lister les tags d'un fichier
Pour lister les tags d'un fichier, utilisez le paramètre `-l` :
```bash
$ tag -l <path>
```
  
### Lister les fichiers avec filtres de tags
Vous pouvez chercher des fichiers récursivement à un emplacement en utilisant le paramètre `-rf`. Cette commande est comparable à la commande `find`. Elle permet de chercher dans un répertoire `<path>` et dans les sous-répertoires, récursivement, les fichiers respectant les filtres.

```
$ tag -f <path> <tag_name> -<tag_name> ...
$ tag -rf <path> <tag_name> -<tag_name> ...
```

Vous avez le choix d'utiliser le paramètre `-rf` pour ne pas chercher récursivement. Le programme va regarder tout les fichiers en prenant comme point d'origine `<path>`.
Ensuite il faut ajouter au moins un filtre. On peut soit mettre un nom de tag `<tag_name>`, le programme va alors trouver tout les fichiers ayant ce tag ou alors un de ses sous-tag. Même fonctionnement mais avec effet inverse si on rajoute le caractère `-`.
