#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int length;
    char name[10];

    //myType *pointer;                // pointer creation
    //pointer = &tab1;                // assignation
    //(*pointer)[5][12] = 517;        // set (write)
    //int myint = (*pointer)[5][12];  // get (read)

    printf("Enter amount of letters: ");
    scanf("%d", &length);
    gets();

    double values[100000]={0}; //= {6.54324,723.234,32423.234,23423.243};
    double *p;
    p = &values; //*(p+i) to access variables



    printf("Enter Name (Caps Sensitive): ");
    scanf("%[^\n]%*c", name);
    FILE *newFileptr = fopen("newsolid.txt", "w");
    for(int x = 0; x < length; x++)
    {
        retrieve(name[x], p, x, newFileptr,length);
        for(int c = 0; c<100000; c++)
            *(p+c) = 0;

    }
    //addE();
   // save();


}


void retrieve(char letter, double *p, int position, FILE *newFileptr, int length)
{
    //save values into array
    //position =1;  test for calculation (set position != 0)
    char filename[5];
    char line[20];
    int counter=0;
    double num;
    filename[0] = letter;
    filename[1] = '.';
    filename[2] = 't';
    filename[3] = 'x';
    filename[4] = 't';

    FILE* ptr = fopen(filename, "r");
    if(ptr == NULL)
    {
        printf("File Not Found");
        exit(1);
    }
while(fgets(line,20,ptr) != NULL)
      {
            //fgets(line,20,ptr);
            char *s = line;
            num = atof(s);
            if(counter % 3 == 0 && counter %4 != 0 && position !=0)//3 6 9 15 18 19 25 28 31  && position != 0
            {
                //num +=(.5905512 * position);
                *(p + counter) = num + (.5905512*position);//num;
            }
            else
                *(p + counter) = num;
            //*(p + counter) = num;

            printf("%e   %e   %d   %d\n",num,*(p + counter),counter,position);
            counter++;
      }
    fclose(ptr);
    save(p,position,newFileptr,counter,length);
}

/*void add()
{


}*/

void save(double *p, int postion, FILE *newFileptr, int counter,int length)
{
    if(postion == 0)//add beginning "solid 'filename'";
        fprintf(newFileptr,"solid newsolid\n");
    int i = 0;

    /*if(postion == length -1)//add ending "endsolid"
    {
        fprintf(newFileptr,"endsolid");
        fclose(newFileptr);
    }*/
    while(i<=counter)
    {
        /*fprintf(newFileptr,"face normal %e %e %e\n",*(p + (++i)),*(p + (++i)),*(p + (++i)));
        fprintf(newFileptr,"outer loop\n");
        fprintf(newFileptr,"vertex %e %e %e\n",*(p + (++i)),*(p + (++i)),*(p + (++i)));
        fprintf(newFileptr,"vertex %e %e %e\n",*(p + (++i)),*(p + (++i)),*(p + (++i)));
        fprintf(newFileptr,"vertex %e %e %e\n",*(p + (++i)),*(p + (++i)),*(p + (++i)));
        fprintf(newFileptr,"endloop\n");
        fprintf(newFileptr,"endfacet\n");*/
        //fprintf(newFileptr,"%e\n",*(p+i));
        //if(i != counter && postion != length - 1)
        //{
        fprintf(newFileptr,"   facet normal %e",*(p+i));
        i++;
        fprintf(newFileptr," %e",*(p+i));
        i++;
        fprintf(newFileptr," %e\n",*(p+i));
        i++;
        fprintf(newFileptr,"      outer loop\n");
        fprintf(newFileptr,"         vertex %e",*(p+i));//vertex 1
        i++;
        fprintf(newFileptr," %e",*(p+i));
        i++;
        fprintf(newFileptr," %e\n",*(p+i));
        i++;
        fprintf(newFileptr,"         vertex %e",*(p+i)); //vertex 2
        i++;
        fprintf(newFileptr," %e",*(p+i));
        i++;
        fprintf(newFileptr," %e\n",*(p+i));
        i++;
        fprintf(newFileptr,"         vertex %e",*(p+i)); //vertex 3
        i++;
        fprintf(newFileptr," %e",*(p+i));
        i++;
        fprintf(newFileptr," %e\n",*(p+i));
        i++;
        fprintf(newFileptr,"      endloop\n");
        fprintf(newFileptr,"   endfacet\n");
      //  }
    }

    if(postion == length -1)//add ending "endsolid"
    {
        fprintf(newFileptr,"endsolid");
        fclose(newFileptr);
    }


}


void addE(double *p,int postion)
{

}
