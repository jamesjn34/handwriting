/*File: template.c		*/
/*Author: James Nelson		*/


static void createTemplate (GtkWidget *wid, GtkWidget *inputButton)
{
    char *input = gtk_entry_get_text(inputButton);
    printf("%s",input);

    int length = strlen(input);


    double values[100000]={0};//stores all values, only needs one letter at a time
    double *p;
    p = &values; //*(p+i) to access variables

    char * newName;
    newName = strcat(input,".stl");

    FILE *newFileptr = fopen(newName, "w");
    if(newFileptr==NULL)
        exit(1);
    for(int x = 0; x < length; x++)
    {
        retrieve(input[x], p, x, newFileptr,length);
        for(int c = 0; c<100000; c++)
            *(p+c) = 0;
    }
}


/*EOF*/
