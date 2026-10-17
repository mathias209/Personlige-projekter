#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAXOUT 1000
#define MAXCOMMAND 100
#define MAXPATH 200

#define OUTFILE "/tmp/pdfman-tempfile"
#define DATAPATH "/.local/share/pdfman"

#define HELPMES "-h\n\tPrint this help message\n-a CATEGORY\n\tAdd category of name CATEGORY\n-d CATEGORY\n\tDelete category of name CATEGORY\n-f CATEGORY PATH\n\tAdd file in PATH to CATEGORY\n-x CATEGORY FILE\n\tDelete file from list\n-l CATEGORY\n\tList files in CATEGORY, list tree if no category is given\n-o CATEGORY FILE\n\tOpens file, uses dmenu if no options are given\n"

struct stat stbuf = {0};

void runcommand(char* dest, char* command) {
    int error;
    char commandpipe[MAXCOMMAND];
    sprintf(commandpipe, "%s > %s", command, OUTFILE);
    error = system(commandpipe);
    if (error)
	printf("Error in running command `$%s`, return value: `%d`\n", command, error);

    FILE* f = fopen(OUTFILE, "r");
    int i = 0;
    char c = 0;
    while ((c = getc(f)) != EOF) {
	if (++i > MAXOUT) {
	    printf("Warning: output too long stopping at %d\n", MAXOUT);
	    return;
	}
	dest[i-1] = c;
    }
    fclose(f);
}

void addCat(int argc, char* argv[]);
void delCat(int argc, char* argv[]);
void addFile(int argc, char* argv[]);
void delFile(int argc, char* argv[]);
void list(int argc, char* argv[]);
void open(int argc, char* argv[]);

int main(int argc, char* argv[]) {
    // database file and dir
    char path[MAXPATH];
    runcommand(path, "echo -n $HOME");
    strcat(path, DATAPATH);
    if (stat(path, &stbuf) == -1) {
	printf("pdfman requires a database, which will be created in %s. Is this acceptable? [y/n]\n", path);
	if (getchar() == 'y') {
	    system("mkdir ~"DATAPATH);
	    printf("Directory has been created, continuing...\n");
	} else {
	    printf("Exiting...\n");
	    return 0;
	}
    }

    if (argc == 1)
	printf(HELPMES);
	//    else if (argv[1] == "-a")
	// addCat(argc, argv);
	//    else if (argv[1] == "-d")
	// delCat(argc, argv);
	//    else if (argv[1] == "-f")
	// addFile(argc, argv);
	//    else if (argv[1] == "-x")
	// delFile(argc, argv);
	//    else if (argv[1] == "-l")
	// list(argc, argv);
	//    else if (argv[1] == "-o")
	// open(argc, argv);
    else
	printf("Error: Incorrect option, %s, try -h\n", argv[1]);

    return 0;
}

// add category (-a "category name")
// delete category (-d)
// add entry in category (-f "path" "category")
// delete entry -x
// list (-l "category") (list in tree view if no category)
// open (-o category entry) (dmenu if run optionless)
// -h help also if no options
