/*File: template.c		*/
/*Author: James Nelson		*/

#include <stdio.h>
#include "fileIO.h"
#include <string.h>
#include "template.h"
#include <stdlib.h>
#include <assert.h>

void createTemplate (char *in/*GtkWidget *wid, GtkWidget *inputButton*/)
{
    assert(in);
    //char input[SLEN] = in;//gtk_entry_get_text(inputButton);
    //printf("%s",input);

    int length = strlen(in);


    double values[100000]={0};//stores all values, only needs one letter at a time
    double *p;
    p = &values[0]; //*(p+i) to access variables

    char * newName;
    //newName = strcat(input,".stl");
    newName = "John.stl";
    FILE *newFileptr = fopen(newName, "w");
    if(newFileptr==NULL)
        exit(1);
    for(int x = 0; x < length; x++)
    {
        retrieve(in[x], p, x, newFileptr,length);
        for(int c = 0; c<100000; c++)
            *(p+c) = 0;
    }
    #ifdef DEBUG
 	printf("Template Created and Saved ......\n");
    #endif
}


/*EOF*/
