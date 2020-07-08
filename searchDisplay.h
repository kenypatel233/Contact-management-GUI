
#include<stdio.h>
#include<stdlib.h>
#include<gtk/gtk.h>
#include<glib.h>
#include<glib/gprintf.h>

#define WINWIDTH 600
#define WINHEIGHT 600

typedef struct _AppState
{

    GtkWidget *window;
    GtkWidget *text_view;
    GtkWidget *open_button;
    GtkWidget *print_button;

}AppState;

void on_open_button (GtkWidget *button, AppState *app_state);
void on_print_button (GtkWidget *button, AppState *app_state);


int display_all(int argc, char *argv[])
{
    GtkWidget *scrolled_window;
    GtkWidget *vbox;
    GtkWidget *hbox;
    AppState app_state;

    gtk_init(&argc,&argv);
    app_state.window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(app_state.window),"Contact Viewer");
    gtk_window_set_default_size(GTK_WINDOW(app_state.window),WINWIDTH,WINHEIGHT);
    g_signal_connect(G_OBJECT(app_state.window),"destroy",G_CALLBACK(gtk_main_quit),NULL);
    vbox=gtk_vbox_new(FALSE,2);
    gtk_container_add(GTK_CONTAINER(app_state.window),vbox);

    app_state.text_view=gtk_text_view_new();
    gtk_text_view_set_left_margin(GTK_TEXT_VIEW(app_state.text_view),10);
    gtk_text_view_set_right_margin(GTK_TEXT_VIEW(app_state.text_view),10);

    scrolled_window=gtk_scrolled_window_new(NULL,NULL);
    gtk_container_add(GTK_CONTAINER(scrolled_window),app_state.text_view);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),GTK_POLICY_AUTOMATIC,GTK_POLICY_ALWAYS);
    gtk_box_pack_start(GTK_BOX(vbox),scrolled_window,1,1,0);

    hbox=gtk_hbox_new(FALSE,2);
    gtk_box_pack_start(GTK_BOX(vbox),hbox,0,0,0);

    app_state.open_button=gtk_button_new_with_label("Open file");
    gtk_box_pack_start(GTK_BOX(hbox),app_state.open_button,0,0,0);
    g_signal_connect(G_OBJECT(app_state.open_button),"clicked",G_CALLBACK(on_open_button),&app_state);

    app_state.print_button=gtk_button_new_with_label("Print file");
    gtk_box_pack_start(GTK_BOX(hbox),app_state.print_button,0,0,0);
    g_signal_connect(G_OBJECT(app_state.open_button),"clicked",G_CALLBACK(on_print_button),&app_state);

    gtk_widget_set_sensitive(app_state.open_button, TRUE);
    gtk_widget_set_sensitive(app_state.print_button, FALSE);
    gtk_widget_show_all(app_state.window);

    gtk_main();
    return 0;


}


void on_open_button (GtkWidget *button, AppState *app_state)
{
    GtkTextBuffer *buffer;
    GtkFileFilter *filter;
    GtkWidget *dialog;
    int result;
    gchar *filename;
    GError *error =NULL;
    gulong nBytesInBuf;
    gchar *contents;
    dialog= gtk_file_chooser_dialog_new("Select File...", GTK_WINDOW(app_state->window),
                                         GTK_FILE_CHOOSER_ACTION_OPEN,
                                         GTK_STOCK_OK,GTK_RESPONSE_ACCEPT,
                                         GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,
                                         NULL);

    gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog),g_get_home_dir());

    result = gtk_dialog_run(GTK_DIALOG(dialog));
    switch(result)
    {
    case GTK_RESPONSE_ACCEPT:
        filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        gtk_widget_destroy(dialog);
        break;
    case GTK_RESPONSE_DELETE_EVENT:
    case GTK_RESPONSE_CANCEL:
    case GTK_RESPONSE_NONE:
        gtk_widget_destroy(dialog);
        return;


    }
     if (NULL==filename){
        GtkWidget *msg;
        msg = gtk_message_dialog_new(GTK_WINDOW(app_state->window),
                                     GTK_DIALOG_MODAL,
                                     GTK_MESSAGE_ERROR,
                                     GTK_BUTTONS_OK,
                                     "Failed to get file");
        gtk_dialog_run(GTK_DIALOG(msg));
        return;

     }

     buffer= gtk_text_view_get_buffer(GTK_TEXT_VIEW(app_state->text_view));

     if(!g_file_get_contents(filename, &contents, &nBytesInBuf,&error))
     {

         g_printf(error->message);
         g_clear_error(&error);
         g_free(filename);
         exit(1);
     }

    gtk_text_buffer_set_text(buffer, contents,-1);
    g_free(filename);
    g_free(contents);

    gtk_widget_set_sensitive(app_state->print_button,TRUE);
    gtk_widget_show_all(app_state->window);

  }
void on_print_button (GtkWidget *button, AppState *app_state)
    {
        GtkTextIter start;
        GtkTextIter end;
        gchar *text;
        GtkTextBuffer *buffer;

        buffer= gtk_text_view_get_buffer(GTK_TEXT_VIEW(app_state->text_view));
        if (NULL!= buffer)
        {
            gtk_text_buffer_get_bounds(buffer,&start,&end);
            text=gtk_text_buffer_get_slice(buffer,&start,&end,FALSE);

            g_print("%s",text);
            g_free(text);
        }
    }



