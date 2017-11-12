#include <stdlib.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
/*
James Nelson
September, 2017
3d template maker
Purpose: Creates STL file of a handwriting template for children with
    visual/motor impairment to allow them to sign their name


requires txt file for Upper/Lower case cursive/standard handwriting
steps to get txt file
1) design in 3d modeling program
    must be in positive octant
    dimensions are x=15mm, y=31mm, z =2.5mm
    must be oriented correctly because .5905512 is added
        to x in retrieve function to move letter over to correct spot
    MUST EXPORT IN ASCII
2) Use converter program to create an txt of only values of normal vectors
    and vertices
3) This txt is what this program to uses for letters
Future versions
    Ability to create stl from drawing out the template
3d print template
*/
int style = 0;//global variable for handwirting --> standard = 0; cursive = 1
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




void retrieve(char letter, double *p, int position, FILE *newFileptr, int length)
{
    //save values into array
    //position =1;  test for calculation (set position != 0)
    char filename[7];
    char line[20];
    int counter=0;
    double num;
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


static void setStyle(GtkWidget *wid,GtkWidget *comboBox)//get style when change comboBox
{
  style = gtk_combo_box_get_active(comboBox);
}


int main (int argc, char *argv[])
{
  GtkWidget *button = NULL;
  GtkWidget *calculateButton = NULL;
  GtkWidget *win = NULL;
  GtkWidget *vbox = NULL;
  GtkWidget *textinput = NULL;
  GtkWidget *fixed = NULL;
  GtkWidget *comboBox = NULL;

  /* Initialize GTK+ */
  g_log_set_handler ("Gtk", G_LOG_LEVEL_WARNING, (GLogFunc) gtk_false, NULL);
  gtk_init (&argc, &argv);
  g_log_set_handler ("Gtk", G_LOG_LEVEL_WARNING, g_log_default_handler, NULL);


  win = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(win),210 ,60);
  gtk_container_set_border_width (GTK_CONTAINER (win), 8);
  gtk_window_set_title (GTK_WINDOW (win), "3d Template Creater");
  gtk_window_set_position (GTK_WINDOW (win), GTK_WIN_POS_CENTER);
  gtk_widget_realize (win);
  g_signal_connect (win, "destroy", gtk_main_quit, NULL);
  fixed = gtk_fixed_new();//must creat fixed in order to set position of widgets

  gtk_container_add(win,fixed);
  textinput = gtk_entry_new_with_max_length(20);
  gtk_entry_set_text(textinput,"Insert Name Here");
  gtk_fixed_put(fixed,textinput,0,0);

  calculateButton = gtk_button_new_with_label("Create STL File");
  g_signal_connect (G_OBJECT (calculateButton), "clicked", G_CALLBACK (createTemplate), textinput);//input);//(gpointer) win, input);
  gtk_fixed_put(fixed,calculateButton,50,40);

  button = gtk_button_new_from_stock (GTK_STOCK_CLOSE);
  g_signal_connect (button, "clicked", gtk_main_quit, NULL);
  gtk_fixed_put(fixed,button,0,40);

  comboBox = gtk_combo_box_new_text();
  gtk_fixed_put(fixed,comboBox,160,39);
  gtk_combo_box_append_text(comboBox,"Standard");
  gtk_combo_box_append_text(comboBox,"Cursive");
  gtk_combo_box_set_active(comboBox,0);


  g_signal_connect (G_OBJECT (comboBox), "changed", G_CALLBACK (setStyle), comboBox);
  gtk_widget_show_all (win);
  gtk_main ();
  return 0;
}


