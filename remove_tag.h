#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/xattr.h>
#include <errno.h>

void remove_tag(char * path, char * tag);