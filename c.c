#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/extensions/XTest.h>
#include <stdbool.h>
typedef struct {
    GtkWidget *treeview_L;
    GtkWidget *treeview_R;
} TreeviewsData;

gboolean on_treeview_key_press(GtkWidget *widget, GdkEventKey *event, gpointer user_data)
{  
    // GtkTreeView *treeview = GTK_TREE_VIEW(widget);
    switch (event->keyval) {
        case GDK_KEY_Escape:
            gtk_main_quit();
            exit(0);
            break;
        case GDK_KEY_x:
            gtk_main_quit();
            exit(0);
            break;
        case GDK_KEY_Right:
            system("xdotool key Tab");
            break;
        case GDK_KEY_Left:
            system("xdotool key shift+Tab");
            break;
        default:
            break;
    }
    return FALSE;
}
gchar* recuperer_elements_droite_string(const char* fichier, const char* chaine) {
    FILE* file = fopen(fichier, "r");
    if (file == NULL) {
        fprintf(stderr, "Failed to open file: %s\n", fichier);
        return NULL;
    }
    char ligne[256];
    gchar* mots = NULL;
    while (fgets(ligne, sizeof(ligne), file)) {
        if (strstr(ligne, chaine)) {
            // Trouver l'index de la chaîne "chaine" dans la ligne
            char* index = strstr(ligne, chaine);
            // Avancer l'index jusqu'au caractère suivant "chaine"
            index += strlen(chaine);
            // Copier la valeur de droite dans la variable "mots"
            mots = strdup(index);
            break;
        }
    }
    if (mots == NULL) return NULL;
    fclose(file);
    return mots;
}

gchar *escamote_line(const gchar *ligne)
{
    gchar *ligne_escamotee = g_strdup(ligne);
    gchar *current_appli = g_strstrip(recuperer_elements_droite_string("/home/sdethyre/sandbox/dash_dev_boisson/config.conf", "current_appli:"));
    if (strcmp(current_appli, "openads") == 0) {
        gchar *develop_pos = strstr(ligne_escamotee, "develop");
        if (develop_pos && !g_str_has_suffix(develop_pos, "develop"))
        {
            guint longueur = develop_pos - ligne_escamotee + strlen("develop");
            gchar *espaces = g_strdup_printf("%*s", (int)(longueur + 8), " "); // Convertir en int ici
            memcpy(ligne_escamotee, espaces, longueur);
            g_free(espaces);
        }
        gchar *develop_pos_2 = strstr(ligne_escamotee, "10289");
        if (develop_pos_2 && !g_str_has_suffix(develop_pos_2, "10289"))
        {
            guint longueur = develop_pos_2 - ligne_escamotee + strlen("10289");
            gchar *espaces = g_strdup_printf("%*s", (int)(longueur + 8), " "); // Convertir en int ici
            memcpy(ligne_escamotee, espaces, longueur);
            g_free(espaces);
        }
        // Cherche les lignes commençant par "rg-"
        gchar *rg_pos = ligne_escamotee;
        while ((rg_pos = strstr(rg_pos, "rg-")) != NULL)
        {
            // Rajoute 4 espaces devant chaque occurrence de "rg-"
            gchar *espaces_rg = g_strdup_printf("%*s", (int)(rg_pos - ligne_escamotee + 12), " "); // Convertir en int ici
            gchar *ancienne_ligne = ligne_escamotee;
            ligne_escamotee = g_strconcat(espaces_rg, rg_pos, NULL);
            g_free(ancienne_ligne);
            g_free(espaces_rg);
            // Avance pour éviter une boucle infinie si "rg-" est vide
            if (strlen(rg_pos) <= 3)
                break;
            // Passe au prochain "rg-" dans la ligne
            rg_pos += 3;
        }
    }
    if (strcmp(current_appli, "opendebitdeboisson") == 0) {
        gchar *develop_pos = strstr(ligne_escamotee, "rec4");
        if (develop_pos && !g_str_has_suffix(develop_pos, "rec4"))
        {
            guint longueur = develop_pos - ligne_escamotee + strlen("rec4");
            gchar *espaces = g_strdup_printf("%*s", (int)(longueur + 8), " "); // Convertir en int ici
            memcpy(ligne_escamotee, espaces, longueur);
            g_free(espaces);
        }
        // Cherche les lignes commençant par "rg-"
        gchar *rg_pos = ligne_escamotee;
        gboolean first = false;
        while ((rg_pos = strstr(rg_pos, "3.0.0-rec4")) != NULL)
        {   
            if (!first) 
            first = true;
            break;
            // Rajoute 4 espaces devant chaque occurrence de "rg-"
            gchar *espaces_rg = g_strdup_printf("%*s", (int)(rg_pos - ligne_escamotee + 12), " "); // Convertir en int ici
            gchar *ancienne_ligne = ligne_escamotee;
            ligne_escamotee = g_strconcat(espaces_rg, rg_pos, NULL);
            g_free(ancienne_ligne);
            g_free(espaces_rg);
            // Avance pour éviter une boucle infinie si "rg-" est vide
            if (strlen(rg_pos) <= 3)
                break;
            // Passe au prochain "rg-" dans la ligne
            rg_pos += 3;
        }
    }
    return ligne_escamotee;
}

bool checkSuffix(gchar *text, gchar *suffixes[], size_t numSuffixes) {
    for (size_t i = 0; i < numSuffixes; ++i) {
        if (g_str_has_suffix(text, suffixes[i])) {
            return true;
        }
    }
    return false;
}

void button_clicked(GtkButton *button, gpointer user_data)
{
    TreeviewsData *data = (TreeviewsData *)user_data;
    GtkWidget *treeview_L = data->treeview_L;
    GtkWidget *treeview_R = data->treeview_R;
    GtkTreeSelection *selection_L = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview_L));
    GtkTreeModel *model_L;
    GtkTreeIter iter_L;
    gchar *left_text;
    gchar *right_text;

    gchar *current_appli = g_strstrip(recuperer_elements_droite_string("/home/sdethyre/sandbox/dash_dev_boisson/config.conf", "current_appli:"));


    if (gtk_tree_selection_get_selected(selection_L, &model_L, &iter_L))
    {
        gtk_tree_model_get(model_L, &iter_L, 1, &left_text, -1);
        GtkTreeSelection *selection_R = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview_R));
        GtkTreeModel *model_R;
        GtkTreeIter iter_R;
        if (gtk_tree_selection_get_selected(selection_R, &model_R, &iter_R)) {
            gtk_tree_model_get(model_R, &iter_R, 1, &right_text, -1);
            gchar *appli_name;
            if (strcmp(current_appli, "openads") == 0) {
                appli_name = "openfoncier";
            }
            if (strcmp(current_appli, "openaria") == 0) {
                appli_name = "openaria";
            }
            if (strcmp(current_appli, "opencimetiere") == 0) {
                appli_name = "opencimetiere";
            }
            if (strcmp(current_appli, "opendebitdeboisson") == 0) {
                appli_name = "openboisson"; 
            }
            if (strcmp(current_appli, "openelec") == 0) {
                appli_name = "openelec";
            }
            if (strcmp(current_appli, "openresultat") == 0) {
                appli_name = "openresultat";
            }
            g_strstrip(current_appli);
            GError *error = NULL;
            gchar *directory = g_strdup_printf("/home/sdethyre/public_html/%s/%s", current_appli, right_text);
            gchar *svn_command = g_strdup_printf("svn merge svn+ssh://sdethyre@scm.adullact.net/svn/%s/branches/%s", appli_name, left_text);
            // gchar *command_string = g_strdup(command);
            gchar *command;
            if (strcmp(current_appli, "openads") == 0) {
                gchar *suffixes[] = {"develop", "refonte-graphique", "10289"};
                size_t numSuffixes = sizeof(suffixes) / sizeof(suffixes[0]);
                if (checkSuffix(left_text, suffixes, numSuffixes))
                {
                    command = g_strdup_printf("gnome-terminal --wait -- bash -c 'cd %s && %s; echo \"\n\n merge(branch): fusion de la branche inte %s dans la branche dev %s\n\n\" ; read -s -r -p \"Appuyez sur Entrée pour fermer le terminal...\"'", directory, svn_command, left_text, right_text);
                }
                else if (checkSuffix(right_text, suffixes, numSuffixes))
                {
                    command = g_strdup_printf("gnome-terminal --wait -- bash -c 'cd %s && %s; echo \"\n\n merge(branch): fusion de la branche dev %s dans la branche inte %s\n\n\" ; read -s -r -p \"Appuyez sur Entrée pour fermer le terminal...\"'", directory, svn_command, left_text, right_text);
                }
                else
                {
                    // Si aucun des textes ne se termine par "develop" ou "refonte-graphique", utilisez le premier modèle par défaut
                    command = g_strdup_printf("gnome-terminal --wait -- bash -c 'cd %s && %s; echo \"\n\n merge(branch): fusion de la branche dev %s dans la branche dev %s\n\n\" ; read -s -r -p \"Appuyez sur Entrée pour fermer le terminal...\"'", directory, svn_command, left_text, right_text);
                }
            }
            if (strcmp(current_appli, "opendebitdeboisson") == 0) {
                gchar *suffixes[] = {"rec3", "rec4"};
                size_t numSuffixes = sizeof(suffixes) / sizeof(suffixes[0]);
                if (checkSuffix(left_text, suffixes, numSuffixes))
                {
                    command = g_strdup_printf("gnome-terminal --wait -- bash -c 'cd %s && %s; echo \"\n\n merge(branch): fusion de la branche inte %s dans la branche dev %s\n\n\" ; read -s -r -p \"Appuyez sur Entrée pour fermer le terminal...\"'", directory, svn_command, left_text, right_text);
                }
                else if (checkSuffix(right_text, suffixes, numSuffixes))
                {
                    command = g_strdup_printf("gnome-terminal --wait -- bash -c 'cd %s && %s; echo \"\n\n merge(branch): fusion de la branche dev %s dans la branche inte %s\n\n\" ; read -s -r -p \"Appuyez sur Entrée pour fermer le terminal...\"'", directory, svn_command, left_text, right_text);
                }
                else
                {
                    // Si aucun des textes ne se termine par "develop" ou "refonte-graphique", utiliser le premier modèle par défaut
                    command = g_strdup_printf("gnome-terminal --wait -- bash -c 'cd %s && %s; echo \"\n\n merge(branch): fusion de la branche dev %s dans la branche dev %s\n\n\" ; read -s -r -p \"Appuyez sur Entrée pour fermer le terminal...\"'", directory, svn_command, left_text, right_text);
                }

            }
            // Print and store the command
            // printf("Command executed: %s\n", command);
            gchar *command_string = g_strdup(command);

            g_spawn_command_line_async(command, &error);
            // printf("%s",command_string);
            if (error != NULL)
            {
                g_print("Erreur lors de l'exécution de la commande : %s\n", error->message);
                g_error_free(error);
            }

            // Free allocated memory
            g_free(left_text);
            g_free(right_text);
            g_free(directory);
            g_free(svn_command);
            g_free(command);
            g_free(command_string);

            GtkWidget *window = gtk_widget_get_toplevel(GTK_WIDGET(button));
            gtk_widget_destroy(window);
            gtk_main_quit();
            exit(0);
        }
    }
} 

int main(int argc, char *argv[])
{
    int exit_status = system("bash /home/sdethyre/sandbox/dash_dev_boisson/list_devs_merge");

    if (exit_status == -1)
    {
        // Erreur lors de l'exécution du script
        return 1;
    }
    else if (!WIFEXITED(exit_status) || WEXITSTATUS(exit_status) != 0)
    {
        // Le script s'est terminé avec une erreur
        return 1;
    }
    gtk_init(&argc, &argv);
    // Créer la fenêtre principale
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Créer le conteneur principal
    GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_container_add(GTK_CONTAINER(window), main_box);

    TreeviewsData data;
    // Créer le premier GtkTreeView et GtkListStore
    GtkListStore *list_store_1 = gtk_list_store_new(2, G_TYPE_STRING, G_TYPE_STRING);
    GtkWidget *treeview_1 = gtk_tree_view_new_with_model(GTK_TREE_MODEL(list_store_1));
    data.treeview_L = treeview_1;
    GtkCellRenderer *renderer_1 = gtk_cell_renderer_text_new();
    GtkTreeViewColumn *column_1 = gtk_tree_view_column_new_with_attributes("\nFusion de la branche\t\t\t\t\t\t▶\n\n", renderer_1, "text", 0, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview_1), column_1);
    gtk_box_pack_start(GTK_BOX(main_box), treeview_1, TRUE, TRUE, 0);

    // Créer le deuxième GtkTreeView et GtkListStore
    GtkListStore *list_store_2 = gtk_list_store_new(2, G_TYPE_STRING, G_TYPE_STRING);
    GtkWidget *treeview_2 = gtk_tree_view_new_with_model(GTK_TREE_MODEL(list_store_2));
    data.treeview_R = treeview_2;
    GtkCellRenderer *renderer_2 = gtk_cell_renderer_text_new();
    GtkTreeViewColumn *column_2 = gtk_tree_view_column_new_with_attributes("\nTab ↹   ▶\t\t\t\t\t\tvers la branche\n\n", renderer_2, "text", 0, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview_2), column_2);
    gtk_box_pack_start(GTK_BOX(main_box), treeview_2, TRUE, TRUE, 0);

    // Lire les données à partir du fichier et les ajouter aux GtkListStore
    FILE *file = fopen("/home/sdethyre/sandbox/dash_dev_boisson/results.txt", "r");
    if (file)
    {
        char line[256];
        while (fgets(line, sizeof(line), file))
        {
            gchar *trimmed_line = g_strstrip(line);
            gchar *escamoted_line = escamote_line(trimmed_line);
            GtkTreeIter iter_1, iter_2;
            gtk_list_store_append(list_store_1, &iter_1);
            gtk_list_store_append(list_store_2, &iter_2);
            gtk_list_store_set(list_store_1, &iter_1, 0, escamoted_line, 1, trimmed_line, -1);
            gtk_list_store_set(list_store_2, &iter_2, 0, escamoted_line, 1, trimmed_line, -1);
            g_free(escamoted_line);
        }
        fclose(file);
    }
    // Créer le bouton carré
    GtkWidget *button = gtk_button_new_with_label("Merge");
    gtk_widget_set_size_request(button, 50, 50);
    gtk_box_pack_start(GTK_BOX(main_box), button, FALSE, FALSE, 0);
    g_signal_connect(button, "clicked", G_CALLBACK(button_clicked), &data);
    g_signal_connect(G_OBJECT(window), "key-press-event", G_CALLBACK(on_treeview_key_press), NULL);
    
    // Afficher les éléments de la fenêtre
    gtk_widget_show_all(window);
    // Lancer la boucle principale de GTK
    gtk_main();

    return 0;
}
