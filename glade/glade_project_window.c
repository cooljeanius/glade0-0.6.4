/*  Gtk+ User Interface Builder
 *  Copyright (C) 1998  Damon Chaplin
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include <string.h>
#include <locale.h>

#include <gdk/gdkkeysyms.h>
#include <gtk/gtkcheckmenuitem.h>
#include <gtk/gtkfilesel.h>
#include <gtk/gtkhbbox.h>
#include <gtk/gtkmain.h>
#include <gtk/gtkmenu.h>
#include <gtk/gtkmenubar.h>
#include <gtk/gtkscrolledwindow.h>
#include <gtk/gtkstatusbar.h>
#include <gtk/gtktext.h>
#include <gtk/gtkvbox.h>

#include "gladeconfig.h"

#ifdef USE_GNOME
#include <gnome.h>
#endif

#include "glade.h"
#include "glade_clipboard.h"
#include "glade_project_options.h"
#include "glade_project_window.h"
#include "editor.h"
#include "gbwidget.h"
#include "load.h"
#include "utils.h"

/* Include pixmaps if not using Gnome. */
#ifndef USE_GNOME
#include "graphics/new.xpm"
#include "graphics/open.xpm"
#include "graphics/save.xpm"
#include "graphics/source.xpm"
#include "graphics/options.xpm"
#endif

/* This is used to store a pointer to a GladeProjectWindow in the main window.
 */
static gchar *GladeProjectWindowKey = "GladeProjectWindowKey";


static gboolean glade_project_window_delete_event (GtkWidget *widget,
						   GdkEvent *event,
						   GladeProjectWindow *project_window);
static void glade_project_window_destroy (GtkWidget *widget,
					  gpointer   data);

static void glade_project_window_new_project (GtkWidget *widget,
					      gpointer   data);
static void glade_project_window_on_new_project_ok (GtkWidget *button,
						    GladeProjectWindow *project_window);
static void glade_project_window_on_open_project (GtkWidget *widget,
					       gpointer   data);
static void glade_project_window_real_open_project (GtkWidget          *widget,
						    GladeProjectWindow *project_window);
static void glade_project_window_show_loading_errors (GladeProjectWindow *project_window,
						      GList		 *errors);
static GtkWidget* glade_project_window_new_errors_dialog (GladeProjectWindow *project_window,
							  GtkWidget **text_return);

static void glade_project_window_on_edit_options (GtkWidget *widget,
						  gpointer   data);
static void glade_project_window_edit_options (GladeProjectWindow *project_window,
					       GladeProjectOptionsAction action);
static void glade_project_window_save_project (GtkWidget *widget,
					       gpointer   data);
#if 0
static void glade_project_window_on_save_project_as (GtkWidget *widget,
						     gpointer   data);
static void glade_project_window_save_project_as (GladeProjectWindow *project_window);
static void glade_project_window_save_as_callback (GtkWidget          *widget,
						   GladeProjectWindow *project_window);
#endif
static gboolean glade_project_window_real_save_project (GladeProjectWindow *project_window,
							gboolean            warn_before_overwrite);
static void glade_project_window_write_source (GtkWidget *widget,
					       gpointer   data);
static void glade_project_window_real_write_source (GladeProjectWindow *project_window);
static void glade_project_window_show_error (GladeProjectWindow *project_window,
					     GladeError         *error,
					     gchar              *title);

static void glade_project_window_quit (GtkWidget *widget,
				       gpointer   data);
static void glade_project_window_show_quit_dialog (GladeProjectWindow *project_window);
static void glade_project_window_on_quit_ok (GtkWidget *button,
					     GladeProjectWindow *project_window);

static void glade_project_window_cut (GtkWidget *widget,
				      gpointer   data);
static void glade_project_window_copy (GtkWidget *widget,
				       gpointer   data);
static void glade_project_window_paste (GtkWidget *widget,
					gpointer   data);
static void glade_project_window_delete (GtkWidget *widget,
					 gpointer   data);
static void glade_project_window_real_delete (GladeProjectWindow *project_window);

static void glade_project_window_show_palette (GtkWidget *widget,
					       gpointer   data);
static void glade_project_window_show_property_editor (GtkWidget *widget,
						       gpointer   data);
static void glade_project_window_show_widget_tree (GtkWidget *widget,
						   gpointer   data);
static void glade_project_window_show_clipboard (GtkWidget *widget,
						 gpointer   data);
static void glade_project_window_toggle_tooltips (GtkWidget *widget,
						  gpointer   data);
static void glade_project_window_toggle_grid (GtkWidget *widget,
					      gpointer   data);
static void glade_project_window_edit_grid_settings (GtkWidget *widget,
						     gpointer   data);
static void glade_project_window_toggle_snap (GtkWidget *widget,
					      gpointer   data);
static void glade_project_window_edit_snap_settings (GtkWidget *widget,
						     gpointer   data);

static void glade_project_window_about (GtkWidget *widget,
					gpointer   data);

static gint glade_project_window_key_press_event (GtkWidget * widget,
						  GdkEventKey * event,
						  gpointer data);

static void glade_project_window_options_ok (GtkWidget	    *widget,
					     GladeProjectWindow *project_window);
static void glade_project_window_update_title (GladeProjectWindow *project_window);

/*
 * These are the menubar and toolbar definitions for Gnome.
 */
#ifdef USE_GNOME
static GnomeUIInfo FileMenu[] =
{
  GNOMEUIINFO_MENU_NEW_ITEM (N_("_New Project"), N_("Create a new project"),
			     glade_project_window_new_project, NULL),
  GNOMEUIINFO_MENU_OPEN_ITEM (glade_project_window_on_open_project, NULL),
  GNOMEUIINFO_MENU_SAVE_ITEM (glade_project_window_save_project, NULL),
  /*GNOMEUIINFO_MENU_SAVE_AS_ITEM (glade_project_window_on_save_project_as,
    NULL),*/
  GNOMEUIINFO_SEPARATOR,
  {
    GNOME_APP_UI_ITEM, N_("_Build Source Code"),
    N_("Output the project source code"),
    glade_project_window_write_source, NULL, NULL,
    GNOME_APP_PIXMAP_STOCK, GNOME_STOCK_MENU_EXEC,
    'W', GDK_CONTROL_MASK, NULL
  },
  {
    GNOME_APP_UI_ITEM, N_("_Project Options..."),
    N_("Edit the project options"),
    glade_project_window_on_edit_options, NULL, NULL,
    GNOME_APP_PIXMAP_STOCK, GNOME_STOCK_MENU_PREF,
    0, 0, NULL
  },
  GNOMEUIINFO_SEPARATOR,
  GNOMEUIINFO_MENU_EXIT_ITEM (glade_project_window_quit, NULL),
  GNOMEUIINFO_END
};

static GnomeUIInfo EditMenu[] =
{
  GNOMEUIINFO_MENU_CUT_ITEM (glade_project_window_cut, NULL),
  GNOMEUIINFO_MENU_COPY_ITEM (glade_project_window_copy, NULL),
  GNOMEUIINFO_MENU_PASTE_ITEM (glade_project_window_paste, NULL),
  { GNOME_APP_UI_ITEM, N_("_Delete"), N_("Delete the selected widget"),
    glade_project_window_delete, NULL, NULL,
    GNOME_APP_PIXMAP_STOCK, GNOME_STOCK_MENU_TRASH,
    GDK_DELETE, 0, NULL },
  GNOMEUIINFO_END
};

static GnomeUIInfo ViewMenu[] =
{
  {
    GNOME_APP_UI_ITEM, N_("Show _Palette"), N_("Show the palette of widgets"),
    glade_project_window_show_palette, NULL, NULL,
    GNOME_APP_PIXMAP_NONE, NULL,
    0, 0, NULL
  },
  {
    GNOME_APP_UI_ITEM, N_("Show Property _Editor"),
    N_("Show the property editor"),
    glade_project_window_show_property_editor, NULL, NULL,
    GNOME_APP_PIXMAP_NONE, NULL,
    0, 0, NULL
  },
  {
    GNOME_APP_UI_ITEM, N_("Show Widget _Tree"),
    N_("Show the widget tree"),
    glade_project_window_show_widget_tree, NULL, NULL,
    GNOME_APP_PIXMAP_NONE, NULL,
    0, 0, NULL
  },
  {
    GNOME_APP_UI_ITEM, N_("Show _Clipboard"),
    N_("Show the clipboard"),
    glade_project_window_show_clipboard, NULL, NULL,
    GNOME_APP_PIXMAP_NONE, NULL,
    0, 0, NULL
  },
  GNOMEUIINFO_END
};


/* These must match the indices of the appropriate items in the settings
   GnomeUIInfo array. We need them to set the initial state. */
#define GLADE_SHOW_GRID_ITEM 0
#define GLADE_SNAP_TO_GRID_ITEM 1
#define GLADE_SHOW_TOOLTIPS_ITEM 2

static GnomeUIInfo SettingsMenu[] =
{
  {
    GNOME_APP_UI_TOGGLEITEM, N_("Show _Grid"),
    N_("Show the grid (in fixed containers only)"),
    glade_project_window_toggle_grid, NULL, NULL,
    GNOME_APP_PIXMAP_NONE, NULL,
    0, 0, NULL
  },
  {
    GNOME_APP_UI_TOGGLEITEM, N_("_Snap to Grid"),
    N_("Snap widgets to the grid"),
    glade_project_window_toggle_snap, NULL, NULL,
    GNOME_APP_PIXMAP_NONE, NULL,
    0, 0, NULL
  },
  {
    GNOME_APP_UI_TOGGLEITEM, N_("Show _Widget Tooltips"),
    N_("Show the tooltips of created widgets"),
    glade_project_window_toggle_tooltips, NULL, NULL,
    GNOME_APP_PIXMAP_NONE, NULL,
    0, 0, NULL
  },

  GNOMEUIINFO_SEPARATOR,

  {
    GNOME_APP_UI_ITEM, N_("Set Grid _Options..."),
    N_("Set the grid style and spacing"),
    glade_project_window_edit_grid_settings, NULL, NULL,
    GNOME_APP_PIXMAP_NONE, NULL,
    0, 0, NULL
  },
  {
    GNOME_APP_UI_ITEM, N_("Set Snap O_ptions..."),
    N_("Set options for snapping to the grid"),
    glade_project_window_edit_snap_settings, NULL, NULL,
    GNOME_APP_PIXMAP_NONE, NULL,
    0, 0, NULL
  },
  GNOMEUIINFO_END
};

static GnomeUIInfo HelpMenu[] =
{
  GNOMEUIINFO_HELP ("glade"),

  GNOMEUIINFO_SEPARATOR,

  GNOMEUIINFO_MENU_ABOUT_ITEM (glade_project_window_about, NULL),
  GNOMEUIINFO_END
};

static GnomeUIInfo MainMenu[] =
{
  GNOMEUIINFO_MENU_FILE_TREE (FileMenu),
  GNOMEUIINFO_MENU_EDIT_TREE (EditMenu),
  GNOMEUIINFO_MENU_VIEW_TREE (ViewMenu),
  GNOMEUIINFO_MENU_SETTINGS_TREE (SettingsMenu),
  GNOMEUIINFO_MENU_HELP_TREE (HelpMenu),
  GNOMEUIINFO_END
};

static GnomeUIInfo ToolBar[] =
{
  /* I've taken this out to try to make the window smaller. */
  /*
  {
    GNOME_APP_UI_ITEM, N_("New"), N_("New Project"), 
    glade_project_window_new_project, NULL, NULL,
    GNOME_APP_PIXMAP_STOCK, GNOME_STOCK_PIXMAP_NEW, 0, 0, NULL
  },
  */
  {
    GNOME_APP_UI_ITEM, N_("Open"), N_("Open Project"), 
    glade_project_window_on_open_project, NULL, NULL,
    GNOME_APP_PIXMAP_STOCK, GNOME_STOCK_PIXMAP_OPEN, 0, 0, NULL
  },
  {
    GNOME_APP_UI_ITEM, N_("Save"), N_("Save Project"), 
    glade_project_window_save_project, NULL, NULL,
    GNOME_APP_PIXMAP_STOCK, GNOME_STOCK_PIXMAP_SAVE, 0, 0, NULL
  },
  GNOMEUIINFO_SEPARATOR,
  {
    GNOME_APP_UI_ITEM, N_("Options"), N_("Project Options"), 
    glade_project_window_on_edit_options, NULL, NULL,
    GNOME_APP_PIXMAP_STOCK, GNOME_STOCK_PIXMAP_PREFERENCES, 0, 0, NULL
  },
  GNOMEUIINFO_SEPARATOR,
  {
    GNOME_APP_UI_ITEM, N_("Build"), N_("Build the Source Code"), 
    glade_project_window_write_source, NULL, NULL,
    GNOME_APP_PIXMAP_STOCK, GNOME_STOCK_PIXMAP_EXEC, 0, 0, NULL
  },
  GNOMEUIINFO_END
};
#endif


#ifdef USE_GNOME
GladeProjectWindow*
glade_project_window_new (void)
{
  GladeProjectWindow *project_window;
  GtkWidget *scrolled_win;
  GtkWidget *show_grid_item, *snap_to_grid_item, *show_tooltips_item;

  project_window = g_new (GladeProjectWindow, 1);
  project_window->current_directory = NULL;

  project_window->window = gnome_app_new ("Glade", "Glade");
  gtk_widget_set_name (project_window->window, "GladeProjectWindow");
  gtk_window_set_wmclass (GTK_WINDOW (project_window->window),
			  "project", "Glade");

  /* We want all the keyboard accelerators from the menus in the default
     accel_group (or they won't work within the interface windows), so we
     change the app's accel_group. This is a slight kludge. */
  GNOME_APP (project_window->window)->accel_group = gtk_accel_group_get_default ();

  /* Save a pointer to the GladeProjectWindow, so we can find it in callbacks.
   */
  gtk_object_set_data (GTK_OBJECT (project_window->window),
		       GladeProjectWindowKey, project_window);

  gtk_widget_set_uposition (project_window->window, 0, 0);

  gtk_signal_connect (GTK_OBJECT (project_window->window), "destroy",
		      GTK_SIGNAL_FUNC (glade_project_window_destroy), NULL);
  gtk_signal_connect (GTK_OBJECT (project_window->window), "delete_event",
		      GTK_SIGNAL_FUNC (glade_project_window_delete_event),
		      project_window);
  gtk_signal_connect_after (GTK_OBJECT (project_window->window),
			    "key_press_event",
			    GTK_SIGNAL_FUNC (glade_project_window_key_press_event),
			    NULL);

  gnome_app_create_menus (GNOME_APP (project_window->window), MainMenu);
  /* Set the states of the toggle items. */
  show_grid_item = SettingsMenu[GLADE_SHOW_GRID_ITEM].widget;
  gtk_check_menu_item_set_active (GTK_CHECK_MENU_ITEM (show_grid_item),
				 editor_get_show_grid ());

  snap_to_grid_item = SettingsMenu[GLADE_SNAP_TO_GRID_ITEM].widget;
  gtk_check_menu_item_set_active (GTK_CHECK_MENU_ITEM (snap_to_grid_item),
				  editor_get_snap_to_grid ());

  show_tooltips_item = SettingsMenu[GLADE_SHOW_TOOLTIPS_ITEM].widget;
  gtk_check_menu_item_set_active (GTK_CHECK_MENU_ITEM (show_tooltips_item),
				  gb_widget_get_show_tooltips ());


  gnome_app_create_toolbar (GNOME_APP (project_window->window), ToolBar);

  /* Create list of components */
  project_window->project_view = glade_project_view_new ();
  gtk_widget_show (project_window->project_view);

  scrolled_win = gtk_scrolled_window_new (NULL, NULL);
  gtk_container_add (GTK_CONTAINER (scrolled_win),
		     project_window->project_view);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_win),
				  GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
  gtk_widget_show(scrolled_win);

  gnome_app_set_contents (GNOME_APP (project_window->window), scrolled_win);

  /* Create status bar. */
  project_window->statusbar = gtk_statusbar_new ();
  gnome_app_set_statusbar (GNOME_APP (project_window->window),
			   project_window->statusbar);
  gnome_app_install_statusbar_menu_hints (GTK_STATUSBAR (project_window->statusbar), MainMenu);

  return project_window;
}

#else
GladeProjectWindow*
glade_project_window_new (void)
{
  GladeProjectWindow *project_window;
  GtkTooltips *tooltips;

  GtkWidget *menubar;
  GtkWidget *menu;
  GtkWidget *menuitem;
  GtkWidget *toolbar;
  GdkColormap *colormap;
  GtkAccelGroup *accel_group;
  GtkWidget *scrolled_win;
  GtkWidget *vbox_main;

  project_window = g_new (GladeProjectWindow, 1);
  project_window->current_directory = NULL;

  project_window->window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_name (project_window->window, "GladeProjectWindow");
  gtk_window_set_title (GTK_WINDOW (project_window->window), "Glade");
  gtk_window_set_wmclass (GTK_WINDOW (project_window->window),
			  "project", "Glade");

  /* Save a pointer to the GladeProjectWindow, so we can find it in callbacks.
   */
  gtk_object_set_data (GTK_OBJECT (project_window->window),
		       GladeProjectWindowKey, project_window);

  gtk_widget_set_uposition (project_window->window, 0, 0);

  gtk_signal_connect (GTK_OBJECT (project_window->window), "destroy",
		      GTK_SIGNAL_FUNC (glade_project_window_destroy), NULL);
  gtk_signal_connect (GTK_OBJECT (project_window->window), "delete_event",
		      GTK_SIGNAL_FUNC (glade_project_window_delete_event),
		      project_window);
  gtk_signal_connect_after (GTK_OBJECT (project_window->window),
			    "key_press_event",
			    GTK_SIGNAL_FUNC (glade_project_window_key_press_event),
			    NULL);

  tooltips = gtk_tooltips_new ();

  vbox_main = gtk_vbox_new (FALSE, 0);
  gtk_container_add (GTK_CONTAINER (project_window->window), vbox_main);
  gtk_widget_show (vbox_main);

  /* create menu bar */
  menubar = gtk_menu_bar_new ();
  gtk_box_pack_start (GTK_BOX (vbox_main), menubar, FALSE, TRUE, 0);
  gtk_widget_show (menubar);

  /* Create accelerator table */
  accel_group = gtk_accel_group_get_default ();

  /* create File menu */
  menuitem = gtk_menu_item_new_with_label (_("File"));
  gtk_menu_bar_append (GTK_MENU_BAR (menubar), menuitem);
  gtk_widget_show (menuitem);

  menu = gtk_menu_new ();
  gtk_menu_item_set_submenu (GTK_MENU_ITEM (menuitem), menu);

  menuitem = gtk_menu_item_new_with_label (_("New Project"));
  gtk_signal_connect (GTK_OBJECT (menuitem), "activate",
		      GTK_SIGNAL_FUNC (glade_project_window_new_project),
		      NULL);
  gtk_menu_append (GTK_MENU (menu), menuitem);

  gtk_tooltips_set_tip (tooltips, menuitem, _("Create a new project"), NULL);
  gtk_widget_show (menuitem);

  menuitem = gtk_menu_item_new_with_label (_("Open..."));
  gtk_signal_connect (GTK_OBJECT (menuitem), "activate",
		      GTK_SIGNAL_FUNC (glade_project_window_on_open_project),
		      NULL);
  gtk_widget_add_accelerator (menuitem, "activate", accel_group,
			      'O', GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
  gtk_menu_append (GTK_MENU (menu), menuitem);
  gtk_tooltips_set_tip (tooltips, menuitem, _("Open an existing project"),
			NULL);
  gtk_widget_show (menuitem);

  menuitem = gtk_menu_item_new_with_label (_("Save"));
  gtk_signal_connect (GTK_OBJECT (menuitem), "activate",
		      GTK_SIGNAL_FUNC (glade_project_window_save_project),
		      NULL);
  gtk_widget_add_accelerator (menuitem, "activate", accel_group,
			      'S', GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
  gtk_menu_append (GTK_MENU (menu), menuitem);
  gtk_tooltips_set_tip (tooltips, menuitem, _("Save project"), NULL);
  gtk_widget_show (menuitem);

  /*
  menuitem = gtk_menu_item_new_with_label (_("Save As..."));
  gtk_signal_connect (GTK_OBJECT (menuitem), "activate",
		      GTK_SIGNAL_FUNC (glade_project_window_on_save_project_as),
		      NULL);
  gtk_menu_append (GTK_MENU (menu), menuitem);
  gtk_tooltips_set_tip (tooltips, menuitem, _("Save project to a new file"),
			NULL);
  gtk_widget_show (menuitem);
  */

  menuitem = gtk_menu_item_new ();
  gtk_menu_append (GTK_MENU (menu), menuitem);
  gtk_widget_show (menuitem);

  menuitem = gtk_menu_item_new_with_label (_("Write Source Code..."));
  gtk_signal_connect (GTK_OBJECT (menuitem), "activate",
		      GTK_SIGNAL_FUNC (glade_project_window_write_source),
		      NULL);
  gtk_widget_add_accelerator (menuitem, "activate", accel_group,
			      'W', GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
  gtk_menu_append (GTK_MENU (menu), menuitem);
  gtk_tooltips_set_tip (tooltips, menuitem,
			_("Output the project source code"), NULL);
  gtk_widget_show (menuitem);

  menuitem = gtk_menu_item_new_with_label (_("Project Options..."));
  gtk_signal_connect (GTK_OBJECT (menuitem), "activate",
		      GTK_SIGNAL_FUNC (glade_project_window_on_edit_options),
		      NULL);

  gtk_menu_append (GTK_MENU (menu), menuitem);
  gtk_tooltips_set_tip (tooltips, menuitem, _("Edit the project options"),
			NULL);
  gtk_widget_show (menuitem);

  menuitem = gtk_menu_item_new ();
  gtk_menu_append (GTK_MENU (menu), menuitem);
  gtk_widget_show (menuitem);

  menuitem = gtk_menu_item_new_with_label (_("Exit"));
  gtk_menu_append (GTK_MENU (menu), menuitem);
  gtk_signal_connect (GTK_OBJECT (menuitem), "activate",
		      GTK_SIGNAL_FUNC (glade_project_window_quit), NULL);
  gtk_widget_add_accelerator (menuitem, "activate", accel_group,
			      'Q', GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
  gtk_tooltips_set_tip (tooltips, menuitem, _("Exit Glade"), NULL);
  gtk_widget_show (menuitem);


  /* Create Edit menu */
  menuitem = gtk_menu_item_new_with_label (_("Edit"));
  gtk_menu_bar_append (GTK_MENU_BAR (menubar), menuitem);
  gtk_widget_show (menuitem);

  menu = gtk_menu_new ();
  gtk_menu_item_set_submenu (GTK_MENU_ITEM (menuitem), menu);

  menuitem = gtk_menu_item_new_with_label (_("Cut"));
  gtk_menu_append (GTK_MENU (menu), menuitem);
  gtk_signal_connect (GTK_OBJECT (menuitem), "activate",
		      GTK_SIGNAL_FUNC (glade_project_window_cut),
		      NULL);
  gtk_widget_add_accelerator (menuitem, "activate", accel_group,
			      'X', GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
  gtk_widget_show (menuitem);

  menuitem = gtk_menu_item_new_with_label (_("Copy"));
  gtk_menu_append (GTK_MENU (menu), menuitem);
  gtk_signal_connect (GTK_OBJECT (menuitem), "activate",
		      GTK_SIGNAL_FUNC (glade_project_window_copy),
		      NULL);
  gtk_widget_add_accelerator (menuitem, "activate", accel_group,
			      'C', GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
  gtk_widget_show (menuitem);

  menuitem = gtk_menu_item_new_with_label (_("Paste"));
  gtk_menu_append (GTK_MENU (menu), menuitem);
  gtk_signal_connect (GTK_OBJECT (menuitem), "activate",
		      GTK_SIGNAL_FUNC (glade_project_window_paste),
		      NULL);
  gtk_widget_add_accelerator (menuitem, "activate", accel_group,
			      'V', GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
  gtk_widget_show (menuitem);

  menuitem = gtk_menu_item_new_with_label (_("Delete"));
  gtk_menu_append (GTK_MENU (menu), menuitem);
  gtk_signal_connect (GTK_OBJECT (menuitem), "activate",
		      GTK_SIGNAL_FUNC (glade_project_window_delete), NULL);
  gtk_widget_add_accelerator (menuitem, "activate", accel_group,
			      GDK_DELETE, 0, GTK_ACCEL_VISIBLE);
  gtk_widget_show (menuitem);


  /* Create View menu */
  menuitem = gtk_menu_item_new_with_label (_("View"));
  gtk_menu_bar_append (GTK_MENU_BAR (menubar), menuitem);
  gtk_widget_show (menuitem);

  menu = gtk_menu_new ();
  gtk_menu_item_set_submenu (GTK_MENU_ITEM (menuitem), menu);

  menuitem = gtk_menu_item_new_with_label (_("Show Palette"));
  gtk_signal_connect (GTK_OBJECT (menuitem), "activate",
		      GTK_SIGNAL_FUNC (glade_project_window_show_palette),
		      NULL);
  gtk_menu_append (GTK_MENU (menu), menuitem);
  gtk_tooltips_set_tip (tooltips, menuitem, _("Show the palette of widgets"),
			NULL);
  gtk_widget_show (menuitem);

  menuitem = gtk_menu_item_new_with_label (_("Show Properties"));
  gtk_signal_connect (GTK_OBJECT (menuitem), "activate",
		      GTK_SIGNAL_FUNC (glade_project_window_show_property_editor),
		      NULL);
  gtk_menu_append (GTK_MENU (menu), menuitem);
  gtk_tooltips_set_tip (tooltips, menuitem,
			_("Show the properties of the selected widget"), NULL);
  gtk_widget_show (menuitem);

  menuitem = gtk_menu_item_new_with_label (_("Show Widget Tree"));
  gtk_signal_connect (GTK_OBJECT (menuitem), "activate",
		      GTK_SIGNAL_FUNC (glade_project_window_show_widget_tree),
		      NULL);
  gtk_menu_append (GTK_MENU (menu), menuitem);
  gtk_tooltips_set_tip (tooltips, menuitem,
			_("Show the project widget tree"), NULL);
  gtk_widget_show (menuitem);

  menuitem = gtk_menu_item_new_with_label (_("Show Clipboard"));
  gtk_signal_connect (GTK_OBJECT (menuitem), "activate",
		      GTK_SIGNAL_FUNC (glade_project_window_show_clipboard),
		      NULL);
  gtk_menu_append (GTK_MENU (menu), menuitem);
  gtk_tooltips_set_tip (tooltips, menuitem,
			_("Show the clipboard"), NULL);
  gtk_widget_show (menuitem);

  menuitem = gtk_check_menu_item_new_with_label (_("Show Widget Tooltips"));
  gtk_check_menu_item_set_active (GTK_CHECK_MENU_ITEM (menuitem),
				 gb_widget_get_show_tooltips ());
  gtk_signal_connect (GTK_OBJECT (menuitem), "activate",
		      GTK_SIGNAL_FUNC (glade_project_window_toggle_tooltips),
		      NULL);
  gtk_menu_append (GTK_MENU (menu), menuitem);
  gtk_tooltips_set_tip (tooltips, menuitem,
			_("Show the tooltips of created widgets"), NULL);
  gtk_widget_show (menuitem);


  menuitem = gtk_menu_item_new_with_label (_("Grid"));
  gtk_menu_append (GTK_MENU (menu), menuitem);
  gtk_widget_show (menuitem);

  /* Create Grid submenu */
  menu = gtk_menu_new ();
  gtk_menu_item_set_submenu (GTK_MENU_ITEM (menuitem), menu);

  menuitem = gtk_check_menu_item_new_with_label (_("Show Grid"));
  gtk_check_menu_item_set_active (GTK_CHECK_MENU_ITEM (menuitem),
				 editor_get_show_grid ());
  gtk_signal_connect (GTK_OBJECT (menuitem), "activate",
		      GTK_SIGNAL_FUNC (glade_project_window_toggle_grid),
		      NULL);
  gtk_menu_append (GTK_MENU (menu), menuitem);
  gtk_tooltips_set_tip (tooltips, menuitem,
			_("Show the grid (in fixed containers only)"), NULL);
  gtk_widget_show (menuitem);

  menuitem = gtk_menu_item_new_with_label (_("Set Grid Options..."));
  gtk_signal_connect (GTK_OBJECT (menuitem), "activate",
		      GTK_SIGNAL_FUNC (glade_project_window_edit_grid_settings),
		      NULL);
  gtk_menu_append (GTK_MENU (menu), menuitem);
  gtk_tooltips_set_tip (tooltips, menuitem,
			_("Set the spacing between grid lines"), NULL);
  gtk_widget_show (menuitem);

  menuitem = gtk_check_menu_item_new_with_label (_("Snap to Grid"));
  gtk_check_menu_item_set_active (GTK_CHECK_MENU_ITEM (menuitem),
				  editor_get_snap_to_grid ());
  gtk_signal_connect (GTK_OBJECT (menuitem), "activate",
		      GTK_SIGNAL_FUNC (glade_project_window_toggle_snap),
		      NULL);
  gtk_menu_append (GTK_MENU (menu), menuitem);
  gtk_tooltips_set_tip (tooltips, menuitem,
		      _("Snap widgets to the grid (in fixed containers only)"),
			NULL);
  gtk_widget_show (menuitem);

  menuitem = gtk_menu_item_new_with_label (_("Set Snap Options..."));
  gtk_signal_connect (GTK_OBJECT (menuitem), "activate",
		      GTK_SIGNAL_FUNC (glade_project_window_edit_snap_settings),
		      NULL);
  gtk_menu_append (GTK_MENU (menu), menuitem);
  gtk_tooltips_set_tip (tooltips, menuitem,
		      _("Set which parts of a widget snap to the grid"), NULL);
  gtk_widget_show (menuitem);

  /* Create Help menu */
  menuitem = gtk_menu_item_new_with_label (_("Help"));
  gtk_menu_bar_append (GTK_MENU_BAR (menubar), menuitem);
  gtk_widget_show (menuitem);

  menu = gtk_menu_new ();
  gtk_menu_item_set_submenu (GTK_MENU_ITEM (menuitem), menu);

  /* Don't show these yet as we have no help pages.
  menuitem = gtk_menu_item_new_with_label (_("Contents"));
  gtk_menu_append (GTK_MENU (menu), menuitem);
  gtk_widget_show (menuitem);

  menuitem = gtk_menu_item_new_with_label (_("Index"));
  gtk_menu_append (GTK_MENU (menu), menuitem);
  gtk_widget_show (menuitem);

  menuitem = gtk_menu_item_new ();
  gtk_menu_append (GTK_MENU (menu), menuitem);
  gtk_widget_show (menuitem);
  */

  menuitem = gtk_menu_item_new_with_label (_("About..."));
  gtk_menu_append (GTK_MENU (menu), menuitem);
  gtk_signal_connect (GTK_OBJECT (menuitem), "activate",
		      GTK_SIGNAL_FUNC (glade_project_window_about),
		      NULL);
  gtk_widget_show (menuitem);

  /* Create toolbar */
  toolbar = gtk_toolbar_new (GTK_ORIENTATION_HORIZONTAL, GTK_TOOLBAR_ICONS);
  /*gtk_toolbar_set_button_relief (GTK_TOOLBAR (toolbar), GTK_RELIEF_HALF);*/
  gtk_box_pack_start (GTK_BOX (vbox_main), toolbar, FALSE, TRUE, 0);
  gtk_widget_show (toolbar);

  colormap = gtk_widget_get_colormap (toolbar);
  gtk_toolbar_append_item (GTK_TOOLBAR (toolbar),
			   _("New"), _("New Project"), "",
			   glade_util_create_pixmap_using_colormap (colormap,
								    new_xpm),
			   GTK_SIGNAL_FUNC (glade_project_window_new_project),
			   NULL);
  gtk_toolbar_append_item (GTK_TOOLBAR (toolbar),
			   _("Open"), _("Open Project"), "",
			   glade_util_create_pixmap_using_colormap (colormap,
								    open_xpm),
			   GTK_SIGNAL_FUNC (glade_project_window_on_open_project),
			   NULL);
  gtk_toolbar_append_item (GTK_TOOLBAR (toolbar),
			   _("Save"), _("Save Project"), "",
			   glade_util_create_pixmap_using_colormap (colormap,
								    save_xpm),
			   GTK_SIGNAL_FUNC (glade_project_window_save_project),
			   NULL);
  gtk_toolbar_append_space (GTK_TOOLBAR (toolbar));
  gtk_toolbar_append_item (GTK_TOOLBAR (toolbar),
			   _("Options"), _("Project Options"), "",
			   glade_util_create_pixmap_using_colormap (colormap,
								    options_xpm),
			   GTK_SIGNAL_FUNC (glade_project_window_on_edit_options),
			   NULL);
  gtk_toolbar_append_item (GTK_TOOLBAR (toolbar),
			   _("Build"), _("Write Source Code"), "",
			   glade_util_create_pixmap_using_colormap (colormap,
								    source_xpm),
			   GTK_SIGNAL_FUNC (glade_project_window_write_source),
			   NULL);

  /* Create list of components */
  project_window->project_view = glade_project_view_new ();
  gtk_widget_show (project_window->project_view);

  scrolled_win = gtk_scrolled_window_new (NULL, NULL);
  gtk_container_add (GTK_CONTAINER (scrolled_win),
		     project_window->project_view);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_win),
				  GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
  gtk_widget_show(scrolled_win);
  gtk_box_pack_start (GTK_BOX (vbox_main), scrolled_win, TRUE, TRUE, 0);

  /* Create status bar. */
  project_window->statusbar = gtk_statusbar_new ();
  gtk_box_pack_start (GTK_BOX (vbox_main), project_window->statusbar,
		      FALSE, FALSE, 0);
  gtk_widget_show (project_window->statusbar);

  return project_window;
}
#endif


/* This returns the GladeProjectWindow given any widget in the window,
   e.g. a menuitem or a toolbar item, or NULL if not found. */
static GladeProjectWindow*
get_glade_project_window (GtkWidget *widget)
{
  return (gtk_object_get_data (GTK_OBJECT (glade_util_get_toplevel (widget)),
			       GladeProjectWindowKey));
}


static gboolean
glade_project_window_delete_event (GtkWidget *widget,
				   GdkEvent *event,
				   GladeProjectWindow *project_window)
{
  glade_project_window_show_quit_dialog (project_window);
  return TRUE;
}


static void
glade_project_window_destroy (GtkWidget *widget,
			      gpointer   data)
{
  GladeProjectWindow *project_window;

  project_window = get_glade_project_window (widget);
  g_return_if_fail (project_window != NULL);

  gtk_widget_destroy (project_window->window);
  g_free (project_window->current_directory);
  g_free (project_window);

  gtk_exit (0);
}


static void
glade_project_window_new_project (GtkWidget *widget,
				  gpointer   data)
{
  GladeProjectWindow *project_window;
  GtkWidget *dialog;
  const gchar *buttons[] = { N_("OK"), N_("Cancel") };
  GtkSignalFunc handlers[] = { glade_project_window_on_new_project_ok, NULL };

  project_window = get_glade_project_window (widget);
  g_return_if_fail (project_window != NULL);

  dialog = glade_util_create_dialog_with_buttons (_("Are you sure you want to create a new project?"), 2, buttons, 2, handlers, project_window, project_window->window);
  gtk_window_set_position (GTK_WINDOW (dialog), GTK_WIN_POS_MOUSE);
  gtk_window_set_wmclass (GTK_WINDOW (dialog), "new_project", "Glade");
  gtk_window_set_transient_for (GTK_WINDOW (dialog),
				GTK_WINDOW (project_window->window));
  gtk_window_set_modal (GTK_WINDOW (dialog), TRUE);
  gtk_widget_show (dialog);
}


static void
glade_project_window_on_new_project_ok (GtkWidget *button,
					GladeProjectWindow *project_window)
{
  GladeProject *project;

  project = glade_project_new ();
  glade_project_view_set_project (GLADE_PROJECT_VIEW (project_window->project_view), project);
  glade_project_window_update_title (project_window);

  gtk_statusbar_pop (GTK_STATUSBAR (project_window->statusbar), 1);
  gtk_statusbar_push (GTK_STATUSBAR (project_window->statusbar), 1,
		      _("New project created."));
}


static void
glade_project_window_on_open_project (GtkWidget *widget,
				      gpointer   data)
{
  GladeProjectWindow *project_window;
  GtkWidget *filesel;

  project_window = get_glade_project_window (widget);
  g_return_if_fail (project_window != NULL);

  filesel = gtk_file_selection_new (_("Open Project"));
  gtk_window_set_position (GTK_WINDOW (filesel), GTK_WIN_POS_MOUSE);
  gtk_window_set_wmclass (GTK_WINDOW (filesel), "open_project", "Glade");  
  if (GTK_IS_WINDOW (project_window->window))
    gtk_window_set_transient_for (GTK_WINDOW (filesel),
				  GTK_WINDOW (project_window->window));
  if (project_window->current_directory)
    gtk_file_selection_set_filename (GTK_FILE_SELECTION (filesel),
				     project_window->current_directory);

  gtk_signal_connect (GTK_OBJECT (GTK_FILE_SELECTION (filesel)->ok_button),
		      "clicked",
		      GTK_SIGNAL_FUNC (glade_project_window_real_open_project),
		      project_window);
  gtk_signal_connect_object (GTK_OBJECT (GTK_FILE_SELECTION (filesel)->cancel_button),
			     "clicked", GTK_SIGNAL_FUNC (gtk_widget_destroy),
			     GTK_OBJECT (filesel));
  gtk_signal_connect (GTK_OBJECT (filesel), "key_press_event",
		      GTK_SIGNAL_FUNC (glade_util_check_key_is_esc),
		      GINT_TO_POINTER (GladeEscDestroys));
  gtk_widget_show (filesel);
}


static void
glade_project_window_real_open_project (GtkWidget          *widget,
					GladeProjectWindow *project_window)
{
  GtkWidget *filesel;
  gchar *filename;

  filesel = gtk_widget_get_toplevel (widget);
  filename = gtk_file_selection_get_filename (GTK_FILE_SELECTION (filesel));

  glade_project_window_open_project (project_window, filename);
  gtk_widget_destroy (filesel);
}


void
glade_project_window_open_project (GladeProjectWindow *project_window,
				   const gchar        *filename)
{
  GladeProject *project;
  GladeStatusCode status;
  GList *errors;

  g_free (project_window->current_directory);
  project_window->current_directory = glade_util_dirname (filename);

  status = glade_project_open (filename, &project, &errors);
  if (errors)
    glade_project_window_show_loading_errors (project_window, errors);

  gtk_statusbar_pop (GTK_STATUSBAR (project_window->statusbar), 1);
  if (status == GLADE_STATUS_OK)
    {
      glade_project_view_set_project (GLADE_PROJECT_VIEW (project_window->project_view), project);
      gtk_statusbar_push (GTK_STATUSBAR (project_window->statusbar), 1,
			  _("Project opened."));
    }
  else
    {
      /* FIXME: We have to do this at present to reset everything. */
      project = glade_project_new ();
      glade_project_view_set_project (GLADE_PROJECT_VIEW (project_window->project_view), project);
      gtk_statusbar_push (GTK_STATUSBAR (project_window->statusbar), 1,
			  _("Error opening project."));
    }
  glade_project_window_update_title (project_window);
}


/* This shows the errors in a dialog, and frees them. */
static void
glade_project_window_show_loading_errors (GladeProjectWindow *project_window,
					  GList		     *errors)
{
  GtkWidget *dialog, *text;
  GList *element;
  gchar *message, buf[16];
  gint pos = 0;

  dialog = glade_project_window_new_errors_dialog (project_window, &text);

  gtk_window_set_title (GTK_WINDOW (dialog), _("Errors opening project file"));
  gtk_window_set_wmclass (GTK_WINDOW (dialog), "error", "Glade");

  gtk_text_freeze (GTK_TEXT (text));
  sprintf (buf, "\n%i", g_list_length (errors));
  gtk_editable_insert_text (GTK_EDITABLE (text), buf, strlen (buf), &pos);

  message = _(" errors opening project file:");
  gtk_editable_insert_text (GTK_EDITABLE (text), message, strlen (message),
			    &pos);
  gtk_editable_insert_text (GTK_EDITABLE (text), "\n\n", 2, &pos);

  element = errors;
  while (element)
    {
      message = (gchar*) element->data;
      gtk_editable_insert_text (GTK_EDITABLE (text), message, strlen (message),
				&pos);
      g_free (message);
      element = element->next;
    }
  g_list_free (errors);
  gtk_text_thaw (GTK_TEXT (text));

  gtk_widget_show (dialog);
}


static GtkWidget*
glade_project_window_new_errors_dialog (GladeProjectWindow *project_window,
					GtkWidget **text_return)
{
  GtkWidget *dialog, *vbox, *text, *hbbox, *ok_button, *scrolled_win;

  dialog = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position (GTK_WINDOW (dialog), GTK_WIN_POS_MOUSE);
  gtk_container_set_border_width (GTK_CONTAINER (dialog), 2);

  vbox = gtk_vbox_new (FALSE, 4);
  gtk_widget_show (vbox);
  gtk_container_add (GTK_CONTAINER (dialog), vbox);

  text = gtk_text_new (NULL, NULL);
  gtk_widget_show (text);
  gtk_widget_set_usize (text, 400, 150);
  gtk_text_set_editable (GTK_TEXT (text), FALSE);
  GTK_WIDGET_UNSET_FLAGS (text, GTK_CAN_FOCUS);

  scrolled_win = gtk_scrolled_window_new (NULL, NULL);
  gtk_container_add (GTK_CONTAINER (scrolled_win), text);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_win),
				  GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
  gtk_box_pack_start (GTK_BOX (vbox), scrolled_win, TRUE, TRUE, 0);
  gtk_widget_show(scrolled_win);

  hbbox = gtk_hbutton_box_new ();
  gtk_widget_show (hbbox);
  gtk_button_box_set_layout (GTK_BUTTON_BOX (hbbox), GTK_BUTTONBOX_END);
  gtk_box_pack_start (GTK_BOX (vbox), hbbox, FALSE, TRUE, 0);

  ok_button = gtk_button_new_with_label (_("OK"));
  gtk_widget_show (ok_button);
  GTK_WIDGET_SET_FLAGS (ok_button, GTK_CAN_DEFAULT);
  gtk_container_add (GTK_CONTAINER (hbbox), ok_button);
  gtk_widget_grab_default (ok_button);
  gtk_signal_connect_object (GTK_OBJECT (ok_button), "clicked",
			     GTK_SIGNAL_FUNC (gtk_widget_destroy),
			     GTK_OBJECT (dialog));
  gtk_signal_connect (GTK_OBJECT (dialog), "key_press_event",
		      GTK_SIGNAL_FUNC (glade_util_check_key_is_esc),
		      GINT_TO_POINTER (GladeEscDestroys));

  *text_return = text;
  return dialog;
}


static void
glade_project_window_on_edit_options (GtkWidget *widget,
				      gpointer   data)
{
  GladeProjectWindow *project_window;

  project_window = get_glade_project_window (widget);
  g_return_if_fail (project_window != NULL);

  glade_project_window_edit_options (project_window,
				     GLADE_PROJECT_OPTIONS_ACTION_NORMAL);
}


/* The action specifies what to do when 'OK' is clicked. It can be NULL, to
   simply update the options, or 'Save' or 'Build' to save the XML file, or
   build the source code. */
static void
glade_project_window_edit_options (GladeProjectWindow *project_window,
				   GladeProjectOptionsAction action)
{
  GladeProject *project;
  GtkWidget *options;

  project = glade_project_view_get_project (GLADE_PROJECT_VIEW (project_window->project_view));
  if (project)
    {
      options = glade_project_options_new (project);
      gtk_signal_connect (GTK_OBJECT (GLADE_PROJECT_OPTIONS (options)->ok_button),
			  "clicked",
			  GTK_SIGNAL_FUNC (glade_project_window_options_ok),
			  project_window);
      if (action)
	glade_project_options_set_action (GLADE_PROJECT_OPTIONS (options),
					  action);
      if (GTK_IS_WINDOW (project_window->window))
	gtk_window_set_transient_for (GTK_WINDOW (options),
				      GTK_WINDOW (project_window->window));
      				      
      gtk_widget_show (options);
    }
}


static void
glade_project_window_options_ok (GtkWidget	    *widget,
				 GladeProjectWindow *project_window)
{
  GladeProjectOptions *options;
  GladeProjectOptionsAction action;
  gboolean saved;

  options = GLADE_PROJECT_OPTIONS (gtk_widget_get_toplevel (widget));
  action = options->action;

  glade_project_window_update_title (project_window);

  gtk_widget_destroy (GTK_WIDGET (options));

  switch (action)
    {
    case GLADE_PROJECT_OPTIONS_ACTION_NORMAL:
      /* Don't need to do anything here. */
      break;
    case GLADE_PROJECT_OPTIONS_ACTION_SAVE:
      glade_project_window_real_save_project (project_window, FALSE);
      break;
    case GLADE_PROJECT_OPTIONS_ACTION_BUILD:
      saved = glade_project_window_real_save_project (project_window, FALSE);
      if (saved)
	glade_project_window_real_write_source (project_window);
      break;
    }
}


static void
glade_project_window_save_project (GtkWidget *widget,
				   gpointer   data)
{
  GladeProjectWindow *project_window;
  GladeProject *project;
  gchar *xml_filename = NULL;

  project_window = get_glade_project_window (widget);
  g_return_if_fail (project_window != NULL);

  project = glade_project_view_get_project (GLADE_PROJECT_VIEW (project_window->project_view));
  if (project)
    {
      xml_filename = glade_project_get_xml_filename (project);

      /* If the XML filename isn't set, show the project options dialog,
	 and tell it we are saving. */
      if (xml_filename == NULL || xml_filename[0] == '\0')
	glade_project_window_edit_options (project_window,
					   GLADE_PROJECT_OPTIONS_ACTION_SAVE);
      else
	glade_project_window_real_save_project (project_window, FALSE);
    }
}


#if 0
static void
glade_project_window_on_save_project_as (GtkWidget *widget,
					 gpointer   data)
{
  GladeProjectWindow *project_window;

  project_window = get_glade_project_window (widget);
  g_return_if_fail (project_window != NULL);

  glade_project_window_save_project_as (project_window);
}


static void
glade_project_window_save_project_as (GladeProjectWindow *project_window)
{
  GtkWidget *filesel;

  filesel = gtk_file_selection_new (_("Save Project"));
  gtk_window_set_position (GTK_WINDOW (filesel), GTK_WIN_POS_MOUSE);
  gtk_window_set_wmclass (GTK_WINDOW (filesel), "save_project", "Glade");  
  if (GTK_IS_WINDOW (project_window->window))
    gtk_window_set_transient_for (GTK_WINDOW (filesel),
				  GTK_WINDOW (project_window->window));
  if (project_window->current_directory)
    gtk_file_selection_set_filename (GTK_FILE_SELECTION (filesel),
				     project_window->current_directory);
  gtk_signal_connect (GTK_OBJECT (GTK_FILE_SELECTION (filesel)->ok_button),
		      "clicked",
		      GTK_SIGNAL_FUNC (glade_project_window_save_as_callback),
		      project_window);
  gtk_signal_connect_object (GTK_OBJECT (GTK_FILE_SELECTION (filesel)->cancel_button),
			     "clicked", GTK_SIGNAL_FUNC (gtk_widget_destroy),
			     GTK_OBJECT (filesel));
  gtk_signal_connect (GTK_OBJECT (filesel), "key_press_event",
		      GTK_SIGNAL_FUNC (glade_util_check_key_is_esc),
		      GINT_TO_POINTER (GladeEscDestroys));
  gtk_widget_show (filesel);
}


static void
glade_project_window_save_as_callback (GtkWidget          *widget,
				       GladeProjectWindow *project_window)
{
  GladeProject *project;
  GtkWidget *filesel;
  gchar *filename;
  gboolean saved;

  filesel = gtk_widget_get_toplevel (widget);
  filename = gtk_file_selection_get_filename (GTK_FILE_SELECTION (filesel));

  g_free (project_window->current_directory);
  project_window->current_directory = glade_util_dirname (filename);

  project = glade_project_view_get_project (GLADE_PROJECT_VIEW (project_window->project_view));
  if (project)
    {
      glade_project_set_xml_filename (project, filename);
      glade_project_window_real_save_project (project_window, TRUE);
    }
  gtk_widget_destroy (filesel);
}
#endif


/* Returns TRUE if the XML file is saved OK.
   FIXME: Doesn't use warn_before_overwrite. */
static gboolean
glade_project_window_real_save_project (GladeProjectWindow *project_window,
					gboolean            warn_before_overwrite)
{
  GladeProject *project;
  GladeError *error;

  project = glade_project_view_get_project (GLADE_PROJECT_VIEW (project_window->project_view));
  g_return_val_if_fail (project != NULL, GLADE_STATUS_ERROR);

  error = glade_project_save (project);

  gtk_statusbar_pop (GTK_STATUSBAR (project_window->statusbar), 1);
  if (error)
    {
      glade_project_window_show_error (project_window, error,
				       _("Error saving project"));
      gtk_statusbar_push (GTK_STATUSBAR (project_window->statusbar), 1,
			  _("Error saving project."));
      glade_error_free (error);
      return FALSE;
    }
  else
    gtk_statusbar_push (GTK_STATUSBAR (project_window->statusbar), 1,
			_("Project saved."));
  return TRUE;
}


static void
glade_project_window_write_source (GtkWidget *widget,
				   gpointer   data)
{
  GladeProjectWindow *project_window;
  GladeProject *project;
  gchar *directory, *xml_filename, *project_name, *program_name;
  gchar *source_directory, *pixmaps_directory;

  project_window = get_glade_project_window (widget);
  g_return_if_fail (project_window != NULL);

  project = glade_project_view_get_project (GLADE_PROJECT_VIEW (project_window->project_view));
  g_return_if_fail (project != NULL);

  /* First we need to make sure we have an XML file, a project name, and a
     program name. */
  directory = glade_project_get_directory (project);
  xml_filename = glade_project_get_xml_filename (project);
  project_name = glade_project_get_name (project);
  program_name = glade_project_get_program_name (project);
  source_directory = glade_project_get_source_directory (project);
  pixmaps_directory = glade_project_get_pixmaps_directory (project);

  /* First check we have all the options we need. If not show the project
     options dialog, and tell it we are building the source. */
  if (directory == NULL || directory[0] == '\0'
      || xml_filename == NULL || xml_filename[0] == '\0'
      || project_name == NULL || project_name[0] == '\0'
      || program_name == NULL || program_name[0] == '\0'
      || source_directory == NULL || source_directory[0] == '\0'
      || pixmaps_directory == NULL || pixmaps_directory[0] == '\0')
    {
      glade_project_window_edit_options (project_window,
					 GLADE_PROJECT_OPTIONS_ACTION_BUILD);
      return;
    }

  /* If there is an error saving the XML file we simply return. The user
     will already have been informed of the error. */
  if (!glade_project_window_real_save_project (project_window, FALSE))
    return;
  glade_project_window_real_write_source (project_window);
}


static void
glade_project_window_real_write_source (GladeProjectWindow *project_window)
{
  GladeProject *project;
  GladeError *error;

  project = glade_project_view_get_project (GLADE_PROJECT_VIEW (project_window->project_view));
  g_return_if_fail (project != NULL);

  error = glade_project_write_source (project);

  gtk_statusbar_pop (GTK_STATUSBAR (project_window->statusbar), 1);
  if (error)
    {
      glade_project_window_show_error (project_window, error,
				       _("Errors writing source code"));
      gtk_statusbar_push (GTK_STATUSBAR (project_window->statusbar), 1,
			  _("Error writing source."));
      glade_error_free (error);
      return;
    }

  gtk_statusbar_push (GTK_STATUSBAR (project_window->statusbar), 1,
		      _("Source code written."));
}


/* This shows a single GladeError in a dialog. */
static void
glade_project_window_show_error (GladeProjectWindow *project_window,
				 GladeError         *error,
				 gchar		    *title)
{
  GtkWidget *dialog, *text;
  gchar *message;
  gint pos = 0;

  dialog = glade_project_window_new_errors_dialog (project_window, &text);

  gtk_window_set_title (GTK_WINDOW (dialog), title);
  gtk_window_set_wmclass (GTK_WINDOW (dialog), "error", "Glade");
  if (GTK_IS_WINDOW (project_window->window))
    gtk_window_set_transient_for (GTK_WINDOW (dialog),
				      GTK_WINDOW (project_window->window));

  gtk_text_freeze (GTK_TEXT (text));

  gtk_editable_insert_text (GTK_EDITABLE (text), error->message,
			    strlen (error->message), &pos);

  /* For system errors, we also output the system error message. */
  if (error->status == GLADE_STATUS_SYSTEM_ERROR)
    {
      /* Insert a blank line between our message and the system message. */
      gtk_editable_insert_text (GTK_EDITABLE (text), "\n", 1, &pos);

      message = _("System error message:");
      gtk_editable_insert_text (GTK_EDITABLE (text), message,
				strlen (message), &pos);

      /* Place the system error message on the next line, indented slightly. */
      gtk_editable_insert_text (GTK_EDITABLE (text), "\n  ", 3, &pos);

      message = g_strerror (error->system_errno);
      gtk_editable_insert_text (GTK_EDITABLE (text), message,
				strlen (message), &pos);
    }

  gtk_text_thaw (GTK_TEXT (text));

  gtk_widget_show (dialog);
}


static void
glade_project_window_quit (GtkWidget *widget,
			   gpointer   data)
{
  GladeProjectWindow *project_window;

  project_window = get_glade_project_window (widget);
  g_return_if_fail (project_window != NULL);

  glade_project_window_show_quit_dialog (project_window);
}


static void
glade_project_window_show_quit_dialog (GladeProjectWindow *project_window)
{
  GtkWidget *dialog;
  const gchar *buttons[] = { N_("Exit"), N_("Cancel") };
  GtkSignalFunc handlers[] = { glade_project_window_on_quit_ok, NULL };

  dialog = glade_util_create_dialog_with_buttons (_("Are you sure you want to exit?"), 2, buttons, 2, handlers, project_window, project_window->window);
  gtk_window_set_position (GTK_WINDOW (dialog), GTK_WIN_POS_MOUSE);
  gtk_window_set_transient_for (GTK_WINDOW (dialog),
				GTK_WINDOW (project_window->window));
  gtk_window_set_modal (GTK_WINDOW (dialog), TRUE);
  gtk_widget_show (dialog);
}


static void
glade_project_window_on_quit_ok (GtkWidget *button,
				 GladeProjectWindow *project_window)
{
  gtk_widget_destroy (project_window->window);
}


static void
glade_project_window_cut (GtkWidget *widget,
			  gpointer   user_data)
{
  GladeProjectWindow *project_window;
  GladeProject *project;

  project_window = get_glade_project_window (widget);
  g_return_if_fail (project_window != NULL);

  project = glade_project_view_get_project (GLADE_PROJECT_VIEW (project_window->project_view));
  if (project == NULL)
    return;

  glade_clipboard_cut (GLADE_CLIPBOARD (glade_clipboard), project, NULL);
}


static void
glade_project_window_copy (GtkWidget *widget,
			   gpointer   data)
{
  GladeProjectWindow *project_window;
  GladeProject *project;

  project_window = get_glade_project_window (widget);
  g_return_if_fail (project_window != NULL);

  project = glade_project_view_get_project (GLADE_PROJECT_VIEW (project_window->project_view));
  if (project == NULL)
    return;

  glade_clipboard_copy (GLADE_CLIPBOARD (glade_clipboard), project, NULL);
}


static void
glade_project_window_paste (GtkWidget *widget,
			    gpointer  user_data)
{
  GladeProjectWindow *project_window;
  GladeProject *project;

  project_window = get_glade_project_window (widget);
  g_return_if_fail (project_window != NULL);

  project = glade_project_view_get_project (GLADE_PROJECT_VIEW (project_window->project_view));
  if (project == NULL)
    return;

  glade_clipboard_paste (GLADE_CLIPBOARD (glade_clipboard), project, NULL);
}


static void
glade_project_window_delete (GtkWidget *widget,
			     gpointer   data)
{
  GladeProjectWindow *project_window;

  project_window = get_glade_project_window (widget);
  g_return_if_fail (project_window != NULL);

  glade_project_window_real_delete (project_window);
}


/* If one or more items in the project view is selected, we delete them.
   If not, we delete any widgets selected in the interface.
   FIXME: I'm not sure of the correct way to handle the Delete key. Should we
   be using X selections to determine what is currently selected? */
static void
glade_project_window_real_delete (GladeProjectWindow *project_window)
{
  if (glade_project_view_has_selection (GLADE_PROJECT_VIEW (project_window->project_view)))
    glade_project_view_delete_selection (GLADE_PROJECT_VIEW (project_window->project_view));
  else
    editor_on_delete ();
}


static void
glade_project_window_show_palette (GtkWidget *widget,
				   gpointer   data)
{
  glade_show_palette ();
}


static void
glade_project_window_show_property_editor (GtkWidget *widget,
					   gpointer   data)
{
  glade_show_property_editor ();
}


static void
glade_project_window_show_widget_tree (GtkWidget *widget,
				       gpointer   data)
{
  glade_show_widget_tree ();
}


static void
glade_project_window_show_clipboard (GtkWidget *widget,
				     gpointer   data)
{
  glade_show_clipboard ();
}


static void
glade_project_window_toggle_tooltips (GtkWidget *widget,
				      gpointer   data)
{
  gboolean show_tooltips;

  show_tooltips =  GTK_CHECK_MENU_ITEM (widget)->active;
  gb_widget_set_show_tooltips (show_tooltips);
}


static void
glade_project_window_toggle_grid (GtkWidget *widget,
				  gpointer   data)
{
  gboolean show_grid;

  show_grid = GTK_CHECK_MENU_ITEM (widget)->active;
  editor_set_show_grid (show_grid);
}


static void
glade_project_window_edit_grid_settings (GtkWidget *widget,
					 gpointer   data)
{
  editor_show_grid_settings_dialog (widget);
}


static void
glade_project_window_toggle_snap (GtkWidget *widget,
				  gpointer   data)
{
  gboolean snap_to_grid;

  snap_to_grid = GTK_CHECK_MENU_ITEM (widget)->active;
  editor_set_snap_to_grid (snap_to_grid);
}


static void
glade_project_window_edit_snap_settings (GtkWidget *widget,
					 gpointer   data)
{
  editor_show_snap_settings_dialog (widget);
}


static void
glade_project_window_about (GtkWidget *widget,
			    gpointer   data)
{
  /* VERSION comes from configure.in - the only place it should be defined */

#ifdef USE_GNOME
  const gchar *author[] = { "Damon Chaplin <damon@ximian.com>",
			    "Martijn van Beers <martijn@earthling.net>",
			    NULL };
  GtkWidget *about, *transient_parent, *hbox, *href;

  about = gnome_about_new (_("Glade"),
			   VERSION,
			   _("(C) 1998-2001 Damon Chaplin"),
			   author,
			   _("Glade is a User Interface Builder for GTK+ and GNOME.\n"),
			   PACKAGE G_DIR_SEPARATOR_S "glade_logo.png");
  gtk_window_set_modal (GTK_WINDOW (about), TRUE);
  gtk_window_set_wmclass (GTK_WINDOW (about), "about", "Glade");
  transient_parent = glade_util_get_toplevel (widget);
  if (GTK_IS_WINDOW (transient_parent))
    gtk_window_set_transient_for (GTK_WINDOW (about),
				  GTK_WINDOW (transient_parent));

  hbox = gtk_hbox_new (TRUE, 0);
  href = gnome_href_new ("http://glade.gnome.org/",
			 _("Glade Home Page"));
  gtk_box_pack_start (GTK_BOX (hbox), href, FALSE, FALSE, 0);
  gtk_box_pack_start (GTK_BOX (GNOME_DIALOG (about)->vbox),
		      hbox, TRUE, FALSE, 0);
  gtk_widget_show_all (hbox);

  gtk_widget_show (about);

#else
  gchar *message;

  message = g_strdup_printf (_("G L A D E\n\n"
			       "A User Interface Builder for GTK+ and GNOME\n\n"
			       "Version %s\n"
			       "\n"
			       "By\n"
			       "Damon Chaplin\n"
			       "Martijn van Beers\n"
			       "\n"
			       "Email: damon@ximian.com\n"
			       "Home Page: http://glade.gnome.org\n"),
			     VERSION);
  glade_util_show_message_box (message, widget);
  g_free (message);
#endif
}


static gint
glade_project_window_key_press_event (GtkWidget * widget,
				      GdkEventKey * event,
				      gpointer data)
{
  GladeProjectWindow *project_window;

  project_window = get_glade_project_window (widget);
  g_return_val_if_fail (project_window != NULL, FALSE);

  switch (event->keyval)
    {
    case GDK_Delete:
      glade_project_window_real_delete (project_window);
      break;
    }
  return TRUE;
}


void
glade_project_window_set_project	(GladeProjectWindow *project_window,
					 GladeProject       *project)
{
  glade_project_view_set_project (GLADE_PROJECT_VIEW (project_window->project_view),
				  project);
  glade_project_window_update_title (project_window);
}


static void
glade_project_window_update_title	(GladeProjectWindow *project_window)
{
  GladeProject *project;
  gchar *title, *project_name = NULL;

  project = glade_project_view_get_project (GLADE_PROJECT_VIEW (project_window->project_view));

  if (project)
    project_name = glade_project_get_name (project);

  if (!project_name || !project_name[0])
    project_name = _("<untitled>");

  title = g_strdup_printf ("Glade: %s", project_name);
  gtk_window_set_title (GTK_WINDOW (project_window->window), title);
  g_free (title);
}
