#include<conio.h>
#include<string.h>
#include<stdlib.h>
struct contact
{
    const gchar *nameof;

    long int ph;

} list;

void on_window_main_destroy()
{
    gtk_main_quit();
}

static int namec_create(GtkWidget *entryy)
{

  const gchar *entry0_text;
  entry0_text = gtk_entry_get_text (GTK_ENTRY (entryy));
  list.nameof = entry0_text;
  puts(entry0_text);
  return 0;
}
static int no_create(GtkWidget *entry  )
{
  const gchar *entry1_text;
  entry1_text = gtk_entry_get_text (GTK_ENTRY (entry));
  list.ph=entry1_text;
  puts(list.ph);
  return 0;
}
static int contact_created(gpointer Window)
{
    char *filename = "con_final.txt";
    FILE *fip = fopen(filename,"a");

    fwrite(list.nameof, strlen(list.nameof), 1, fip);
    fwrite(" : ",strlen(" : "),1,fip);
    fwrite(list.ph, 8, 1, fip);
    fwrite(" \n",strlen(" \n"),1,fip);





    fflush(stdin);


    fclose(fip);
    GtkWidget *dialog;

    dialog = gtk_message_dialog_new(GTK_WINDOW(Window),
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_INFO,
            GTK_BUTTONS_OK,
            "Contact record created");
  gtk_window_set_title(GTK_WINDOW(dialog), "Information");
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy(dialog);
    return 0;
}




 int activate_1(int argc, char *argv[]){
  GtkWidget *window;
  GtkWidget *table;
  GtkWidget *button_1;
  GtkWidget *button_2;
  GtkWidget *button_3;

  GtkWidget *label1;
  GtkWidget *label2;


  GtkWidget *entry1;
  GtkWidget *entry2;

  gtk_init(&argc, &argv);



  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_title(GTK_WINDOW(window), "Create_C");
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);

  table = gtk_table_new(3, 2, FALSE);
  gtk_container_add(GTK_CONTAINER(window), table);

  label1 = gtk_label_new("Name");
  gtk_widget_set_tooltip_text(label1, "Enter the name(<=20 characters)");
  label2 = gtk_label_new("Contact No");
  gtk_widget_set_tooltip_text(label2, "Enter the contact number");

  gtk_table_attach(GTK_TABLE(table), label1, 0, 1, 0, 1,
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
  gtk_table_attach(GTK_TABLE(table), label2, 0, 1, 1, 2,
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);


  entry1 = gtk_entry_new();

  button_1 = gtk_button_new_with_label ("ok");
  button_2 = gtk_button_new_with_label ("ok");
  button_3 = gtk_button_new_with_label ("Create");




  gtk_widget_show(entry1);

  entry2 = gtk_entry_new();

  gtk_table_attach(GTK_TABLE(table), button_1, 2, 3, 0, 1,
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
  gtk_table_attach(GTK_TABLE(table), button_2, 2, 3, 1, 2,
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
  gtk_table_attach(GTK_TABLE(table), button_3, 3, 4, 0, 3,
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);

  g_signal_connect_swapped(button_1, "clicked",G_CALLBACK(namec_create),entry1);

  g_signal_connect_swapped(button_2, "clicked",G_CALLBACK(no_create),entry2);


  g_signal_connect_swapped(button_3, "clicked", G_CALLBACK(contact_created), (gpointer) window);



  gtk_table_attach(GTK_TABLE(table), entry1, 1, 2, 0, 1,
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
  gtk_table_attach(GTK_TABLE(table), entry2, 1, 2, 1, 2,
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);

  gtk_widget_show_all(window);

  g_signal_connect(window, "destroy",
      G_CALLBACK(gtk_main_quit), NULL);

  gtk_main();

  return 0;
}
