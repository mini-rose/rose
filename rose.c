#include "rose.h"
#include "config.h"
#include "webview.h"
#include "window.h"
#include <stdio.h>
#include <stdlib.h>

static void run(GtkApplication *app)
{
	RoseWindow *window = rose_window_new(app);
	GtkWidget *webview = rose_webview_new();

	if (dark_mode) {
		g_object_set(gtk_settings_get_default(), "gtk-application-prefer-dark-theme", true, NULL);
		GdkRGBA color = { 0, 0, 0, 1 };
		webkit_web_view_get_background_color(WEBKIT_WEB_VIEW(webview), &color);
	}

	rose_window_set_webview(window, webview);
	rose_window_show(window);

	if (homepage)
		rose_webview_load_url(WEBKIT_WEB_VIEW(webview), homepage);
}

int main(int argc, char **argv)
{
	if (argc == 2) {
		homepage = argv[1];
		argv++; argc--;
	}

	GtkApplication *app = gtk_application_new("org.gtk.rose", G_APPLICATION_FLAGS_NONE);
	g_signal_connect(app, "activate", G_CALLBACK(run), NULL);
	g_application_run(G_APPLICATION(app), argc, argv);
}