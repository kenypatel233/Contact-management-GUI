/* GUI of a basic contact management system
   Created by: Keny Patel */
#include <gtk/gtk.h>
#include "callback.h"
#include<stdio.h>
#include "searchDisplay.h"

int greet(int argc, char *argv[]) {
  GtkWidget *window;
  GtkWidget *vbox;
  GtkWidget *button;
  GtkWidget *button1;
  GtkWidget *button5;
  gtk_init(&argc, &argv);

  /* create a new window, and set its title */
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), 230, 250);

  gtk_window_set_title(GTK_WINDOW(window), "Main Menu");
  gtk_container_set_border_width(GTK_CONTAINER(window), 5);
  vbox = gtk_box_new(TRUE, 1);


  gtk_container_add (GTK_CONTAINER (window), vbox);
  button1 = gtk_button_new_with_label ("CREATE NEW CONTACT");
  g_signal_connect (button1, "clicked", G_CALLBACK (activate_1), NULL);
  button5 = gtk_button_new_with_label ("DISPLAY CONTACTS");
  g_signal_connect (button5, "clicked", G_CALLBACK (display_all), NULL);


  button = gtk_button_new_with_label ("Quit");
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);


  gtk_box_pack_start(GTK_BOX(vbox), button1, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), button5, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), button, TRUE, TRUE, 0);


  gtk_widget_show_all (window);
  gtk_main();



  return 0;
}




 void on_activate (GtkApplication *app) {
  // Create a new window
  GtkWidget *window = gtk_application_window_new (app);
  // Create a new button
  GtkWidget *button = gtk_button_new_with_label ("Welcome to CONTACT MANAGEMENT SYSTEM");

  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

  g_signal_connect (button, "clicked", G_CALLBACK (greet), window);


  g_signal_connect(G_OBJECT(window), "destroy",
      G_CALLBACK(gtk_main_quit), NULL);


  gtk_container_add (GTK_CONTAINER (window), button);
  gtk_widget_show_all (window);
}

int main (int argc, char *argv[]) {
  // Create a new application
  GtkApplication *app = gtk_application_new ("com.example.GtkApplication",
                                             G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (on_activate), NULL);
  return g_application_run (G_APPLICATION (app), argc, argv);
}
