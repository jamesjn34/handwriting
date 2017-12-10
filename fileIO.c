/*File: fileIO.c        */
/*Author: James Nelson  */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "fileIO.h"

void retrieve(char letter, double *p, int position, FILE *newFileptr, int length)
{

    //save values into array
    //position =1;  test for calculation (set position != 0)
    char filename[7];
    char line[20];
    int counter=0;
    double num;
    //temp
    int style = 0;
    if(isspace(letter))//set the file to space
    {
        filename[0] = 's';
        filename[1] = 'p';
        filename[2] = '.';
        filename[3] = 't';
        filename[4] = 'x';
        filename[5] = 't';
    }
    else
    {
        if(style == 0)//Standard letters -- upper and lower
        {
            //filename[0] = letter;
            if(isupper(letter))
                {
                    filename[0]=tolower(letter);
                    filename[1]='u';
                }
            else
                {
                    filename[0]=letter;
                    filename[1]='l';
                }

            filename[2] = '.';
            filename[3] = 't';
            filename[4] = 'x';
            filename[5] = 't';
        }
        else //cursive letters
        {
            filename[0] = letter;
            if(isupper(letter))
                filename[1]='u';
            else
                filename[1]='l';
            filename[2] = 'c';
            filename[3] = '.';
            filename[4] = 't';
            filename[5] = 'x';
            filename[6] = 't';
            if(isupper(letter))//upper case cursive
                filename[1] = 'C';
            else
                filename[1] = 'c';//lowercase cursive
        }
    }     
     #ifdef DEBUG
	printf("Retrieving Values from %s.......\n",filename);
     #endif
    FILE* ptr = fopen(filename, "r");
    if(ptr == NULL)//Catch for not having txt file
    {
        printf("File Not Found");
        printf("%c",letter);
        exit(1);//exit program
    }
while(fgets(line,20,ptr) != NULL)
      {
            //fgets(line,20,ptr);
            char *s = line;
            num = atof(s);
            if(counter % 3 == 0 && counter %4 != 0 && position !=0)//3 6 9 15 18 19 25 28 31 (all x vertices values NOT NORMAL VECTOR)
            {
                *(p + counter) = num + roundf((.59055118*position)*1000000)/1000000;//.590..... since width is 15mm(see top)
                //Edit 10/7 changed .5905512 ---> .590551
                //printf("%d\n",counter);
            }
            else
                *(p + counter) = num;

            //printf("%e   %e   %d   %d\n",num,*(p + counter),counter,position);
            counter++;
      }
    fclose(ptr);
    save(p,position,newFileptr,counter,length);
}


void save(double *p, int postion, FILE *newFileptr, int counter,int length)
{
    #ifdef DEBUG
	printf("Starting Save to file .......\n");
    #endif
    if(postion == 0)//add beginning "solid 'filename'";
        fprintf(newFileptr,"solid newsolid\n");
    int i = 0;

    while(i<=counter)
    {

        fprintf(newFileptr,"   facet normal %e",*(p+i));
        i++;
        fprintf(newFileptr," %.6e",*(p+i));
        i++;
        fprintf(newFileptr," %.6e\n",*(p+i));
        i++;
        fprintf(newFileptr,"      outer loop\n");
        fprintf(newFileptr,"         vertex %.6e",*(p+i));//vertex 1
        i++;
        fprintf(newFileptr," %.6e",*(p+i));
        i++;
        fprintf(newFileptr," %.6e\n",*(p+i));
        i++;
        fprintf(newFileptr,"         vertex %.6e",*(p+i)); //vertex 2
        i++;
        fprintf(newFileptr," %.6e",*(p+i));
        i++;
        fprintf(newFileptr," %.6e\n",*(p+i));
        i++;
        fprintf(newFileptr,"         vertex %.6e",*(p+i)); //vertex 3
        i++;
        fprintf(newFileptr," %.6e",*(p+i));
        i++;
        fprintf(newFileptr," %.6e\n",*(p+i));
        i++;
        fprintf(newFileptr,"      endloop\n");
        fprintf(newFileptr,"   endfacet\n");
        /*
        open stl files in txt app to understand form
        */

    }

    if(postion == length -1)//add ending "endsolid" after last letter
    {
        fprintf(newFileptr,"endsolid");
        fclose(newFileptr);
    }


}




/*EOF*/
