#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAXOUT 1000
#define MAXIN 1000
#define MAXCOMMAND 100
#define MAXPATH 200

#define OUTFILE "/tmp/pdfman-tempfile"
// home gets prepended in main
#define DATAPATH "/.local/share/pdfman"
#define DBNAME "db"

#define HELPMES "-h\n\tPrint this help message\n-a CATEGORY PATH/s\n\tAdd file in PATH/s to CATEGORY\n-d CATEGORY FILE/s\n\tDelete file from list\n-l CATEGORY\n\tList files in CATEGORY, list tree if no category is given\n-o CATEGORY FILE\n\tOpens file, uses dmenu if no options are given\n-c CATEGORY\n\tClear all files in CATEGORY or everything if no option is given"

#define DELIM "|"

struct stat stbuf = {0};

char dbpath[MAXPATH];

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

void delLines(char* file)
{
    char buf[MAXIN];
    char* bufptr = buf;
    FILE* f = fopen(file, "r");
    char c;
    while ((c = getc(f)) != EOF) {
	*(bufptr++) = c;
	if ((bufptr-buf) == MAXIN) {
	    printf("Warning: INput file too large stopping at %d\n", MAXIN);
	    break;
	}
    }
    
}

void addFile(int argc, char* argv[]) {
    if (argc < 4) {
	printf("Error: Too few arguments to add a file, see -h\n");
	return;
    }
    FILE* f = fopen(dbpath, "a");
    for (int i = 3; i<argc; i++) {
	fprintf(f, "%s"DELIM"%s\n", argv[2], argv[i]);
    }
    fclose(f);
}
void delFile(int argc, char* argv[]);
void list(int argc, char* argv[]);
void open(int argc, char* argv[]);
void clear(char* category);

int main(int argc, char* argv[]) {
    // database file and dir
    runcommand(dbpath, "echo -n $HOME");
    strcat(dbpath, DATAPATH);
    if (stat(dbpath, &stbuf) == -1) {
	printf("pdfman requires a database, which will be created in %s. Is this acceptable? [y/n]\n", dbpath);
	if (getchar() == 'y') {
	    system("mkdir ~"DATAPATH);
	    printf("Directory has been created, continuing...\n");
	} else {
	    printf("Exiting...\n");
	    return 0;
	}
    }
    strcat(dbpath, "/"DBNAME);

    delLines("test.txt");

	//    if (argc == 1)
	// printf(HELPMES);
	//    else if (strcmp(argv[1], "-a")==0)
	// addFile(argc, argv);
	// //    else if (argv[1] == "-x")
	// // delFile(argc, argv);
	// //    else if (argv[1] == "-l")
	// // list(argc, argv);
	// //    else if (argv[1] == "-o")
	// // open(argc, argv);
	//    else
	// printf("Error: Incorrect option, %s, try -h\n", argv[1]);

    return 0;
}

// add category (-a "category name")
// delete category (-d)
// add entry in category (-f "path" "category")
// delete entry -x
// list (-l "category") (list in tree view if no category)
// open (-o category entry) (dmenu if run optionless)
// -h help also if no options
