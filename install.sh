#!/bin/bash

## Script to install the project

if [[ -e ~/.tag ]]
then
    echo "[warn] The tag system has already been installed. You are about to lose all your tags."
    read -p "Are you sure to reinstall ? (y/n) " -n 1 -r
    echo
    if [[ $REPLY =~ ^[YyOo]$ ]]
    then
        rm -rf ~/.tag

        echo "[info] Compiling ..."
        ./build.sh

        echo "[info] Copy of tag into ~/.tag/tag ..."
        mkdir ~/.tag
        cp ./build/tag ~/.tag/tag

        echo "[info] Copy of tags into ~/.tag ..."
        cp tags_default ~/.tag/tags

        echo
        echo "[warn] Check that your ~/.bashrc has the tag configuration."
        echo "[warn] If not, make a total reinstallation (you will lose your tags): "
        echo
        echo "           rm -rf ~/.tag && ./install.sh"
        echo

        source ~/.bashrc
        echo "[warn] If tag is not installed, try the command :"
        echo
        echo "          source ~/.bashrc"
        echo
        echo "[info] Done ! Use tag --help for more info."
    else
        echo "[info] Nothing has been modified."
    fi
else
    echo "[info] Compiling ..."
    ./build.sh

    echo "[info] Copy of tag into ~/.tag/tag ..."
    mkdir ~/.tag
    cp ./build/tag ~/.tag/tag

    echo "[info] Copy of tags into ~/.tag ..."
    cp tags_default ~/.tag/tags

    echo "[info] Adding alias of cp in ~/.bashrc ..."
    echo >> ~/.bashrc
    echo "# Alias of cp command to support tags" >> ~/.bashrc
    echo "alias cp=\"cp --preserve=xattr\"" >> ~/.bashrc

    echo "[info] Adding the ~/.tag directory to \$PATH in ~/.bashrc ..."
    echo >> ~/.bashrc
    echo "# Added ~/.tag folder to the \$PATH" >> ~/.bashrc
    echo "export PATH=$HOME/.tag:\$PATH" >> ~/.bashrc

    source ~/.bashrc
    echo "[info] Done ! Use tag --help for more info."
fi
