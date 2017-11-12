/*File: Top.c		*/
/*Author: James Nelson	*/

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


static void setStyle(GtkWidget *wid,GtkWidget *comboBox)//get style when change comboBox
{
  style = gtk_combo_box_get_active(comboBox);
}




/*EOF*/
