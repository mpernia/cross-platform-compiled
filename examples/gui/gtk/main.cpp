#include <gtk/gtk.h>
#include "../../../src/includes/logger.h"

static void log_message_callback(GtkWidget *widget, gpointer data)
{
    Logger::log(LogLevel::INFO, "Button clicked in GTK GUI!");
}

static void activate(GtkApplication* app, gpointer user_data)
{
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Cross-Platform C++ GUI Template");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_margin_start(box, 20);
    gtk_widget_set_margin_end(box, 20);
    gtk_widget_set_margin_top(box, 20);
    gtk_widget_set_margin_bottom(box, 20);
    gtk_window_set_child(GTK_WINDOW(window), box);

    GtkWidget *title_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(title_label), "<span size='x-large' weight='bold'>Hello from GTK!</span>");
    gtk_box_append(GTK_BOX(box), title_label);

    GtkWidget *info_label = gtk_label_new("This is a cross-platform GUI application example using GTK.\n"
                                         "The same code compiles and runs on Linux, macOS, and Windows.");
    gtk_label_set_wrap(GTK_LABEL(info_label), TRUE);
    gtk_label_set_justify(GTK_LABEL(info_label), GTK_JUSTIFY_CENTER);
    gtk_box_append(GTK_BOX(box), info_label);

    GtkWidget *spacer = gtk_label_new("");
    gtk_box_append(GTK_BOX(box), spacer);

    GtkWidget *log_button = gtk_button_new_with_label("Log Message");
    g_signal_connect(log_button, "clicked", G_CALLBACK(log_message_callback), NULL);
    gtk_box_append(GTK_BOX(box), log_button);

    GtkWidget *quit_button = gtk_button_new_with_label("Quit");
    g_signal_connect_swapped(quit_button, "clicked", G_CALLBACK(gtk_window_destroy), window);
    gtk_box_append(GTK_BOX(box), quit_button);

    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv)
{
    Logger::setLogLevel(LogLevel::DEBUG);
    Logger::log(LogLevel::INFO, "Starting GTK application");

    GtkApplication *app = gtk_application_new("org.example.crossplatform", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    
    Logger::log(LogLevel::INFO, "GTK application exiting");
    return status;
}
