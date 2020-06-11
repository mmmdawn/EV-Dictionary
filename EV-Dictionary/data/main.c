#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <string.h>
#include "./sqlite3/sqlite3.h"

GtkWidget *textview1,*textview2,*textview3,*textview4;
GtkWidget *searchentry;
GtkWidget *entry1,*entry2, *entry3;
GtkWidget *window_main,*window_add, *window_delete, *window_edit, *window_quit, *window_help, *window_about;

GtkListStore *list;
GtkTreeIter Iter;

sqlite3 *db;
char *err_msg = 0;
char sql[10000];
char *exist=NULL;
int count = 0;
char historytext[5000];

GdkPixbuf *create_pixbuf(const gchar * filename){
    GdkPixbuf *pixbuf;
    GError *error = NULL;
    pixbuf = gdk_pixbuf_new_from_file(filename, &error);
    if (!pixbuf) {
      fprintf(stderr, "%s\n", error->message);
      g_error_free(error);
    }
    return pixbuf;
}

void enter_keyword (GtkWidget *widget, GdkEventKey *event, gpointer user_data);
void suggest(char *word);
void search_keyword(char *word);

void press_add();
void press_delete();
void press_edit();
void press_quit();
void press_help();
void press_about();

int callback_suggest(void *NotUsed, int argc, char **argv, char **azColName);
int callback_search(void *Notused, int argc, char **argv, char **azColName);
int callback_check(void *Notused, int argc, char **argv, char **azColName);

void set_textview_text(char * text) {
    GtkTextBuffer *buffer;
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview1));
    if (buffer == NULL) {
        printf("Get buffer fail!");
        buffer = gtk_text_buffer_new(NULL);
    }
    gtk_text_buffer_set_text(buffer, text, -1);
    gtk_text_view_set_buffer(GTK_TEXT_VIEW(textview1), buffer);
}

void set_history_textview_text(char * text) { //ko hay chinh sua sau 
    GtkTextBuffer *buffer;
    GtkTextIter st_iter;
    GtkTextIter ed_iter;  
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview2));
    gtk_text_buffer_set_text(buffer, text, -1);
    gtk_text_buffer_get_start_iter (gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview2)), &st_iter);
    gtk_text_buffer_get_end_iter (gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview2)), &ed_iter);
    char *histext =  gtk_text_buffer_get_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview2)), &st_iter, &ed_iter, FALSE);
    gtk_text_buffer_set_text(buffer,histext, -1);
    gtk_text_view_set_buffer(GTK_TEXT_VIEW(textview2), buffer);
}

void press_search()
{
    char word[50];
    strcpy(word,gtk_entry_get_text(GTK_ENTRY(searchentry)));
    search_keyword(word);
}

void search_keyword(char *word)
{
  exist = NULL;
  sprintf(sql,"SELECT * FROM Dictionary WHERE key_word = \"%s\" ;" ,word);
  sqlite3_exec(db, sql, callback_search, 0, &err_msg);
  if ( exist == NULL )
     set_textview_text("\nRất tiếc, từ này hiện không có trong từ điển."
                             "\nNhấn nút \"Thêm từ\" để bổ sung vào từ điển.");
}
void enter_keyword(GtkWidget *widget, GdkEventKey *event, gpointer user_data)
{
    char word[50];
    int length;
    strcpy(word, gtk_entry_get_text(GTK_ENTRY(searchentry)));
    length=strlen(word);

    if (event->keyval == GDK_KEY_F1)
        press_add();
    if (event->keyval == GDK_KEY_F2)
        press_edit();
    if (event->keyval == GDK_KEY_F3)
        press_delete();
    if (event->keyval == GDK_KEY_F4)
        press_quit();
    if (event->keyval == GDK_KEY_F5)
        press_help();
    if (event->keyval == GDK_KEY_F6)
        press_about();

    if (event->keyval != GDK_KEY_BackSpace)
    {
        if(event->keyval == GDK_KEY_KP_Tab)
            search_keyword(word);
        else
        {
            word[length]=event->keyval;
            word[length+1]='\0';
            gtk_list_store_clear(list);
            suggest(word);
        }   
    }
    else
    {
        if(length!=0)
        {
            word[length - 1] = '\0';
            if( word[0] != '\0')
            gtk_list_store_clear(list);
            suggest(word);
        } 
    }
}

void suggest(char *word)
{
    count = 0;
    sprintf(sql,"SELECT * FROM Dictionary WHERE INSTR(key_word,\"%s\") = 1 ;" ,word);
    sqlite3_exec(db, sql, callback_suggest, 0, &err_msg);
}

void show_message(GtkWidget * parent , GtkMessageType type,  char * mms, char * content)
{
    GtkWidget *mdialog;
    mdialog = gtk_message_dialog_new(GTK_WINDOW(parent),
                                     GTK_DIALOG_DESTROY_WITH_PARENT,
                                     type,
                                     GTK_BUTTONS_OK,
                                     "%s", mms);
    gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG(mdialog), "%s",  content);
    gtk_dialog_run(GTK_DIALOG(mdialog));
    gtk_widget_destroy(mdialog);
}
void press_add()
{
    GtkBuilder *builder;
    
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "data/window.glade", NULL);
    
    window_add = GTK_WIDGET(gtk_builder_get_object(builder, "window_add"));
    gtk_builder_connect_signals(builder, NULL);

    entry1 = GTK_WIDGET(gtk_builder_get_object(builder, "entry1"));
    textview3 = GTK_WIDGET(gtk_builder_get_object(builder, "textview3"));

    g_object_unref(builder);
    gtk_widget_show(window_add);
}

void click_ok_add()
{
    GtkTextIter st_iter;
    GtkTextIter ed_iter;
    char word[50];
    strcpy(word,gtk_entry_get_text(GTK_ENTRY(entry1)));
    gtk_text_buffer_get_start_iter (gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview3)), &st_iter);
    gtk_text_buffer_get_end_iter (gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview3)), &ed_iter);
    char *nghia =  gtk_text_buffer_get_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview3)), &st_iter, &ed_iter, FALSE);
    exist = NULL ;
    sprintf(sql,"SELECT * FROM Dictionary WHERE key_word = \"%s\" ;" ,word);
    sqlite3_exec(db, sql, callback_check, 0, &err_msg);
    if (exist != NULL) {
        show_message(window_add, GTK_MESSAGE_ERROR, "Xảy ra lỗi!", "Từ đã tồn tại trong từ điển.");
        gtk_widget_destroy(window_add);
        return;
    }
    sprintf(sql, "INSERT INTO Dictionary VALUES(\"%s\",\"%s\");", word, nghia);
    sqlite3_exec(db, sql, 0, 0, &err_msg);
    show_message(window_add, GTK_MESSAGE_INFO, "Thành công !","Từ mới đã được thêm vào từ điển.");
    gtk_widget_destroy(window_add);
}

void press_edit()
{
    GtkBuilder *builder;
    char word[50];

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "data/window.glade", NULL);
    
    window_edit = GTK_WIDGET(gtk_builder_get_object(builder, "window_edit"));
    gtk_builder_connect_signals(builder, NULL);

    entry2 = GTK_WIDGET(gtk_builder_get_object(builder, "entry2"));
    textview4 = GTK_WIDGET(gtk_builder_get_object(builder, "textview4"));

    strcpy(word,gtk_entry_get_text(GTK_ENTRY(searchentry)));
    gtk_entry_set_text(GTK_ENTRY(entry2),word);
    
    g_object_unref(builder);
    gtk_widget_show(window_edit); 
}

void click_ok_edit()
{
    GtkTextIter st_iter;
    GtkTextIter ed_iter;
    char word[50];
    strcpy(word,gtk_entry_get_text(GTK_ENTRY(entry2)));
    gtk_text_buffer_get_start_iter (gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview4)), &st_iter);
    gtk_text_buffer_get_end_iter (gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview4)), &ed_iter);
    char * nghia =  gtk_text_buffer_get_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview4)), &st_iter, &ed_iter, FALSE);
    exist = NULL;
    sprintf(sql,"SELECT * FROM Dictionary WHERE key_word = \"%s\" ;" ,word);
    sqlite3_exec(db, sql, callback_search, 0, &err_msg);
    if ( exist == NULL ) {
       show_message(window_edit, GTK_MESSAGE_ERROR, "Xảy ra lỗi!", "Không có từ này trong từ điển.");
       gtk_widget_destroy(window_edit);
       return;
    }
    sprintf(sql, "UPDATE Dictionary SET meaning = \"%s\" WHERE key_word = \"%s\" ;", nghia, word);
    sqlite3_exec(db, sql, 0, 0, &err_msg);
    show_message(window_edit, GTK_MESSAGE_INFO, "Thành công !", "Cập nhật từ thành công.");
    gtk_widget_destroy(window_edit);
}

void press_delete()
{
    GtkBuilder *builder;
    char word[50];

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "data/window.glade", NULL);
    
    window_delete = GTK_WIDGET(gtk_builder_get_object(builder, "window_delete"));
    gtk_builder_connect_signals(builder, NULL);

    entry3 = GTK_WIDGET(gtk_builder_get_object(builder, "entry3"));

    strcpy(word,gtk_entry_get_text(GTK_ENTRY(searchentry)));
    gtk_entry_set_text(GTK_ENTRY(entry3),word);
    
    g_object_unref(builder);
    gtk_widget_show(window_delete); 
}

void click_ok_delete() {
    char word[50];
    strcpy(word,gtk_entry_get_text(GTK_ENTRY(entry3)));
    exist = NULL ;
    sprintf(sql,"SELECT * FROM Dictionary WHERE key_word = \"%s\" ;" ,word);
    sqlite3_exec(db, sql, callback_check, 0, &err_msg);
    if (exist == NULL) {
        show_message(window_delete, GTK_MESSAGE_ERROR, "Xảy ra lỗi!", "Không tồn tại trong từ điển.");
        gtk_widget_destroy(window_delete);
        return;
    }
    sprintf(sql,"DELETE FROM Dictionary WHERE key_word = \"%s\" ;", word);
    sqlite3_exec(db, sql, 0, 0, &err_msg);
    show_message(window_delete, GTK_MESSAGE_ERROR, "Xóa từ", "Xóa từ thành công.");
    set_textview_text("Bạn đã xóa từ này khỏi từ điển thành công.\n");
    gtk_widget_destroy(window_delete);
}

void press_quit() {
    gtk_widget_destroy(window_main);
}

void press_help() {
    GtkBuilder *builder;

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "data/window.glade", NULL);
    
    window_help = GTK_WIDGET(gtk_builder_get_object(builder, "window_help"));
    gtk_builder_connect_signals(builder, NULL);

    g_object_unref(builder);
    gtk_widget_show(window_help);
}

void click_ok_help() {
    gtk_widget_destroy(window_help);
}

void press_about() {
    GtkBuilder *builder;

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "data/window.glade", NULL);
    
    window_about = GTK_WIDGET(gtk_builder_get_object(builder, "window_about"));
    gtk_builder_connect_signals(builder, NULL);

    g_object_unref(builder);
    gtk_widget_show(window_about);
}

void click_ok_about() {
    gtk_widget_destroy(window_about);
}

int callback_suggest(void *Notused, int argc, char **argv, char **azColName) {
  Notused = 0;
  if (count > 9) return 0;
  gtk_list_store_append(list, &Iter);
  gtk_list_store_set(list, &Iter, 0, argv[0], -1 );

  count++;

  return 0;
}

int callback_search(void *Notused, int argc, char **argv, char **azColName) {
    Notused = 0;
    exist = argv[0];
    set_textview_text(argv[1]);
    strcat(historytext,argv[0]);
    strcat(historytext,"\n");
    set_history_textview_text(historytext);
    return 0;
}  
        
int callback_check(void *Notused, int argc, char **argv, char **azColName) {
    Notused = 0;
    exist = argv[0];
    return 0;
  } 

int main(int argc, char *argv[])
{
    sqlite3_open("data/dictionary.db", &db);
    
    GtkBuilder *builder;
    GtkEntryCompletion *complete;
    
    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "data/window.glade", NULL);

    window_main = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    gtk_builder_connect_signals(builder, NULL);


    GdkPixbuf *icon;
    icon = create_pixbuf("data/penguin.jpg");
    gtk_window_set_icon(GTK_WINDOW(window_main), icon);


    // khoi tao bien tuong tac
    textview1 = GTK_WIDGET(gtk_builder_get_object(builder, "textview1"));
    textview2 = GTK_WIDGET(gtk_builder_get_object(builder, "textview2"));
    searchentry=GTK_WIDGET(gtk_builder_get_object(builder, "searchentry1"));

    // khoi tao phan goi y tu
    complete = gtk_entry_completion_new();
    gtk_entry_completion_set_text_column(complete, 0);
    list = gtk_list_store_new(1, G_TYPE_STRING);
    gtk_entry_completion_set_model(complete, GTK_TREE_MODEL(list));
    gtk_entry_set_completion(GTK_ENTRY(searchentry), complete);
    g_signal_connect (searchentry, "key_press_event", G_CALLBACK(enter_keyword), NULL);
    g_signal_connect(window_main, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    g_object_unref(builder);

    gtk_widget_show(window_main);
    gtk_main();

    sqlite3_close(db);
    return 0;
}
