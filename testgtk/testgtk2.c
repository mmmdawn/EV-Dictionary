#include "mylib/sqlite3.h"
#include "gtk/gtk.h"
#include <stdio.h>


int callback(void *, int, char **, char **);


enum {
  LIST_KEY,
  LIST_MEANING,
  N_COLUMNS
};


int main(int argc, char** argv) {
   GtkCellRenderer *renderer;
   GtkTreeViewColumn *column;
   GtkListStore *store; 
   GtkWidget *window;
   GtkWidget *list;

   GtkWidget *vbox;
   GtkWidget *label;
   GtkTreeSelection *selection;

   gtk_init(&argc, &argv);


   // THIS IS THE MODEL: 2 Columns of Type String

   store = gtk_list_store_new(N_COLUMNS, G_TYPE_STRING, G_TYPE_STRING);

    sqlite3 *db;
  char *err_msg = 0;
  int rc = sqlite3_open("../SQLite_database/dictionary.db", &db);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "Cannot open database: %s\n",
        sqlite3_errmsg(db));
    sqlite3_close(db);
    return 1;
  }
   char sql[200];
  sprintf(sql,"SELECT * FROM Dictionary WHERE INSTR(key_word,\"%s\") = 1 ;" ,"hell");
  rc = sqlite3_exec(db, sql, callback, 0, &err_msg);
  if (rc != SQLITE_OK ) {
    fprintf(stderr, "Failed to select data\n");
    fprintf(stderr, "SQL error: %s\n", err_msg);
    sqlite3_free(err_msg);
    sqlite3_close(db);
    return 1;
  }
  sqlite3_close(db);

   window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   list = gtk_tree_view_new();

   // CREATE 2 COLUMNS WITH TEXT CELL RENDERERS

   renderer = gtk_cell_renderer_text_new ();
   column = gtk_tree_view_column_new_with_attributes("KEYWORD",
          renderer, "text", LIST_KEY, NULL);
   gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);

   renderer = gtk_cell_renderer_text_new ();
   column = gtk_tree_view_column_new_with_attributes("MEANING",
          renderer, "text", LIST_MEANING, NULL);
   gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);


   // SET THE TREE VIEW MODEL 
   gtk_tree_view_set_model(GTK_TREE_VIEW(list), GTK_TREE_MODEL(store));

   // TREEVIEW WILL KEEP A REFERENCE SO DECREASE REFCOUNT
   g_object_unref(store);

   // SETUP THE UI
   gtk_window_set_title(GTK_WINDOW(window), "List view");
   gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
   gtk_container_set_border_width(GTK_CONTAINER(window), 10);
   gtk_window_set_default_size(GTK_WINDOW(window), 270, 250);

   gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(list), FALSE);

   vbox = gtk_box_new(FALSE, 0);

   gtk_box_pack_start(GTK_BOX(vbox), list, TRUE, TRUE, 5);

   label = gtk_label_new("");
   gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 5);

   gtk_container_add(GTK_CONTAINER(window), vbox);

   g_signal_connect(G_OBJECT (window), "destroy",
      G_CALLBACK(gtk_main_quit), NULL);

   gtk_widget_show_all(window);

   gtk_main();

   return 0;
}

int callback(void *model, int argc, char **argv, char **azColName) {
   GtkTreeIter iter;

   for (int i = 0; i < argc; i++) {

      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");

   }

   printf("\n");

   // AFTER PRINTING TO CONSOLE FILL THE MODEL WITH THE DATA

   gtk_list_store_append (GTK_LIST_STORE(model), &iter);
   gtk_list_store_set (GTK_LIST_STORE(model), &iter, LIST_KEY, argv[0], LIST_MEANING, argv[1], -1);

   return 0;
}