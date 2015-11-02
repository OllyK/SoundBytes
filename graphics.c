#include <gtk/gtk.h>
#include <glib.h>
#include <string.h> //for the CSS loading
//  https://wiki.gnome.org/Projects/GtkSourceView   https://github.com/GNOME/gtksourceview

#include "graphics.h"
#include "events.h"

extern unsigned char running;

void attachFunctions(GtkBuilder *builder);
void style(void);

void graphics_init(void){
  GtkBuilder *builder;

  gtk_init (NULL, NULL);

  builder = gtk_builder_new ();
  gtk_builder_add_from_file (builder, "graphicsFiles/ui.ui", NULL);

  attachFunctions(builder);

  style();

  g_object_unref( G_OBJECT( builder ) );
  gtk_main ();
}

void attachFunctions(GtkBuilder *builder){
  GObject *window;
  GObject *button1;
  GObject *button2;
  guint timeoutID;

  window = gtk_builder_get_object (builder, "window");
  g_signal_connect (window, "destroy", G_CALLBACK (events_quitting), NULL);

  timeoutID = g_timeout_add(NUM_MS, events_mainLoop, NULL);

  button1 = gtk_builder_get_object (builder, "button1");
  g_signal_connect (button1, "clicked", G_CALLBACK (events_drum1), NULL);

  button2 = gtk_builder_get_object (builder, "button2");
  g_signal_connect (button2, "clicked", G_CALLBACK (events_clap1), NULL);
}

void style(void){
  GtkCssProvider *provider;
  GdkDisplay *display;
  GdkScreen *screen;
  GError *error = 0;
  gsize bytes_written, bytes_read;
  const gchar* style = "graphicsFiles/style.css";

  provider = gtk_css_provider_new ();
  display = gdk_display_get_default ();
  screen = gdk_display_get_default_screen (display);
  gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

  gtk_css_provider_load_from_path (provider, g_filename_to_utf8(style, strlen(style), &bytes_read, &bytes_written, &error), NULL);
}

void graphics_close(void){
  gtk_main_quit();
}
