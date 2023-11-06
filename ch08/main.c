/* SPDX-License-Identifier: GPL-2.0 */
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>

static void fsize(char *);

int main(int argc, char *argv[])
{
	if (argc == 1)
		fsize(".");
	else
		while (--argc > 0)
			fsize(*++argv);
	return 0;
}

static void fsize(char *name)
{
	void dirwalk(char *, void (*fn)(char *));
	struct stat statbuf;

	if (stat(name, &statbuf) == -1) {
		fprintf(stderr, "fsize: can't access %s\n", name);
		return;
	}
	if ((statbuf.st_mode & S_IFMT) == S_IFDIR)
		dirwalk(name, fsize);
	printf("%10ld %s\n", statbuf.st_size, name);
}

void dirwalk(char *dir, void (*fn)(char *))
{
#define MAX_PATH 1024
	char name[MAX_PATH];
	struct dirent *de;
	DIR *dp;
	int ret;

	if ((dp = opendir(dir)) == NULL) {
		fprintf(stderr, "dirwalk: can't open directory %s\n", dir);
		return;
	}
	while ((de = readdir(dp)) != NULL) {
		if (strcmp(de->d_name, ".") == 0 ||
		    strcmp(de->d_name, "..") == 0)
			continue;
		ret = snprintf(name, sizeof(name), "%s/%s", dir, de->d_name);
		if (ret == -1)
			fprintf(stderr, "dirwalk: name %s/%s too long\n",
				dir, de->d_name);
		else
			(*fn)(name);
	}
	closedir(dp);
}
