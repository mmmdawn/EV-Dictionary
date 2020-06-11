#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <string.h>
#include "../mylib/sqlite3.h"

GtkWidget *textview1,*textview2,*textview3,*textview4;
GtkWidget *searchentry;
GtkWidget *entry1,*entry2;
GtkWidget *window,*window_them_tu,*window_sua_tu;

GtkListStore *list;
GtkTreeIter Iter;

sqlite3 *db;
char *err_msg = 0;
char sql[10000];
int check=0;
char *exist; 
char historytext[5000];

void on_key_press (GtkWidget *widget, GdkEventKey *event, gpointer user_data);
void kiem_tra_tu(char *word);
void findwordmean(char *word);


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
// called when button is clicked
void clicked_search()
{
    char word[40];
    strcpy(word,gtk_entry_get_text(GTK_ENTRY(searchentry)));
    findwordmean(word);
}

void findwordmean(char *word)
{
  exist = NULL;
  sprintf(sql,"SELECT * FROM Dictionary WHERE key_word = \"%s\" ;" ,word);
  sqlite3_exec(db, sql, callback_search, 0, &err_msg);
  if ( exist == NULL )
     set_textview_text("\nRất tiếc, từ này hiện không có trong từ điển."
                             "\nNhấn nút \"Thêm từ\" để bổ sung vào từ điển.");
}
void on_key_press (GtkWidget *widget, GdkEventKey *event, gpointer user_data)
{
    char word[40];
    int x;
    strcpy(word, gtk_entry_get_text(GTK_ENTRY(searchentry)));
    x=strlen(word);
    if (event->keyval != GDK_KEY_BackSpace)
    {
        if(event->keyval == GDK_KEY_KP_Enter)
            findwordmean(word);
        else
        {
            word[x]=event->keyval;
            word[x+1]='\0';
            gtk_list_store_clear(list);
            kiem_tra_tu(word);
        }   
    }
    else
    {
        if(x!=0)
        {
            word[x - 1] = '\0';
            if( word[0] != '\0')
            gtk_list_store_clear(list);
            kiem_tra_tu(word);
        } 
    }
}

void kiem_tra_tu(char *word)
{
    sprintf(sql,"SELECT * FROM Dictionary WHERE INSTR(key_word,\"%s\") = 1 ;" ,word);
    sqlite3_exec(db, sql, callback_suggest, 0, &err_msg);
}

void Show_message(GtkWidget * parent , GtkMessageType type,  char * mms, char * content) 
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
void press_them_tu()
{
    GtkBuilder *builder;
    
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "window.glade", NULL);
    
    window_them_tu = GTK_WIDGET(gtk_builder_get_object(builder, "window1"));
    gtk_builder_connect_signals(builder, NULL);

    entry1 = GTK_WIDGET(gtk_builder_get_object(builder, "entry1"));
    textview3 = GTK_WIDGET(gtk_builder_get_object(builder, "textview3"));

    g_object_unref(builder);
    gtk_widget_show(window_them_tu);
}

void clicked_cap_nhat_them_tu()
{
    GtkTextIter st_iter;
    GtkTextIter ed_iter;
    char word[40];
    strcpy(word,gtk_entry_get_text(GTK_ENTRY(entry1)));
    gtk_text_buffer_get_start_iter (gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview3)), &st_iter);
    gtk_text_buffer_get_end_iter (gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview3)), &ed_iter);
    char *nghia =  gtk_text_buffer_get_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview3)), &st_iter, &ed_iter, FALSE);
    check=0;
    sprintf(sql,"SELECT * FROM Dictionary WHERE key_word = \"%s\" ;" ,word);
    sqlite3_exec(db, sql, callback_check, 0, &err_msg);
    if (check==0) {
    sprintf(sql, "INSERT INTO Dictionary VALUES(\"%s\",\"%s\");", word, nghia);
    sqlite3_exec(db, sql, 0, 0, &err_msg);
    Show_message(window_them_tu, GTK_MESSAGE_INFO, "Thành công !","Từ mới đã được thêm vào từ điển.");
    }
    gtk_widget_destroy(window_them_tu);
}

void press_sua_tu()
{
    GtkBuilder *builder;
    char word[40];

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "window.glade", NULL);
    
    window_sua_tu = GTK_WIDGET(gtk_builder_get_object(builder, "window2"));
    gtk_builder_connect_signals(builder, NULL);

    entry2 = GTK_WIDGET(gtk_builder_get_object(builder, "entry2"));
    textview4 = GTK_WIDGET(gtk_builder_get_object(builder, "textview4"));

    strcpy(word,gtk_entry_get_text(GTK_ENTRY(searchentry)));
    gtk_entry_set_text(GTK_ENTRY(entry2),word);
    
    g_object_unref(builder);
    gtk_widget_show(window_sua_tu); 
}

void clicked_cap_nhat_sua_tu()
{
    GtkTextIter st_iter;
    GtkTextIter ed_iter;
    char word[40];
    strcpy(word,gtk_entry_get_text(GTK_ENTRY(entry2)));
    gtk_text_buffer_get_start_iter (gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview4)), &st_iter);
    gtk_text_buffer_get_end_iter (gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview4)), &ed_iter);
    char * nghia =  gtk_text_buffer_get_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview4)), &st_iter, &ed_iter, FALSE);
    exist = NULL;
    sprintf(sql,"SELECT * FROM Dictionary WHERE key_word = \"%s\" ;" ,word);
    sqlite3_exec(db, sql, callback_search, 0, &err_msg);
    if ( exist == NULL ) {
       Show_message(window_them_tu, GTK_MESSAGE_ERROR, "Xảy ra lỗi!", "Không có từ này trong từ điển.");
       gtk_widget_destroy(window_sua_tu);
       return;
    }
    sprintf(sql, "UPDATE Dictionary SET meaning = \"%s\" WHERE key_word = \"%s\" ;", nghia, word);
    sqlite3_exec(db, sql, 0, 0, &err_msg);
    Show_message(window_sua_tu, GTK_MESSAGE_INFO, "Thành công !", "Cập nhật từ thành công.");
    gtk_widget_destroy(window_sua_tu);
}

void press_xoa_tu()
{
    char word[40];
    strcpy(word,gtk_entry_get_text(GTK_ENTRY(searchentry)));
    sprintf(sql,"DELETE FROM Dictionary WHERE key_word = \"%s\" ;", word);
    sqlite3_exec(db, sql, 0, 0, &err_msg);
    Show_message(window, GTK_MESSAGE_ERROR, "Xóa từ", "Xóa từ thành công.");
    set_textview_text("Bạn đã xóa từ này khỏi từ điển thành công.\n");
}

int callback_suggest(void *Notused, int argc, char **argv, char **azColName) {
  Notused = 0;
  int count=0;
  if (count<10) {
  gtk_list_store_append(list, &Iter);
  gtk_list_store_set(list, &Iter, 0, argv[0], -1 );
  count++;
  }
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
    if(argc > 0 ) {
        Show_message(window_them_tu, GTK_MESSAGE_ERROR, "Xảy ra lỗi!", "Từ đã tồn tại trong từ điển.");
        check=1;
    }
    return 0;   
  } 

int main(int argc, char *argv[])
{
    sqlite3_open("dictionary.db", &db);
    
    GtkBuilder *builder;
    GtkEntryCompletion *complete;
    
    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "window.glade", NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    gtk_builder_connect_signals(builder, NULL);
    
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
    g_signal_connect (searchentry, "key_press_event", G_CALLBACK(on_key_press), NULL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    g_object_unref(builder);

    gtk_widget_show(window);                
    gtk_main();

    sqlite3_close(db);
    return 0;
}
