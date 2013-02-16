/*
 * DO NOT EDIT THIS FILE - it is generated by Glade.
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"

GtkWidget*
create_main_window ()
{
  GtkWidget *main_window;
  GtkWidget *vbox1;
  GtkWidget *handlebox2;
  GtkWidget *menubar1;
  guint tmp_key;
  GtkWidget *File;
  GtkWidget *File_menu;
  GtkAccelGroup *File_menu_accels;
  GtkWidget *New;
  GtkWidget *Open;
  GtkWidget *Save;
  GtkWidget *Save_As;
  GtkWidget *separator1;
  GtkWidget *Exit;
  GtkWidget *Edit;
  GtkWidget *Edit_menu;
  GtkAccelGroup *Edit_menu_accels;
  GtkWidget *Cut;
  GtkWidget *Copy;
  GtkWidget *Paste;
  GtkWidget *Clear;
  GtkWidget *View;
  GtkWidget *View_menu;
  GtkAccelGroup *View_menu_accels;
  GtkWidget *Font;
  GtkWidget *Help;
  GtkWidget *Help_menu;
  GtkAccelGroup *Help_menu_accels;
  GtkWidget *About;
  GtkWidget *handlebox1;
  GtkWidget *toolbar1;
  GtkWidget *tmp_toolbar_icon;
  GtkWidget *button1;
  GtkWidget *button2;
  GtkWidget *button3;
  GtkWidget *scrolledwindow1;
  GtkWidget *text1;
  GtkWidget *statusbar1;
  GtkAccelGroup *accel_group;

  accel_group = gtk_accel_group_new ();

  main_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_ref (main_window);
  gtk_object_set_data_full (GTK_OBJECT (main_window), "main_window", main_window,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_window_set_title (GTK_WINDOW (main_window), _("Glade Text Editor"));
  gtk_window_set_default_size (GTK_WINDOW (main_window), 600, 450);

  vbox1 = gtk_vbox_new (FALSE, 0);
  gtk_widget_ref (vbox1);
  gtk_object_set_data_full (GTK_OBJECT (main_window), "vbox1", vbox1,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (vbox1);
  gtk_container_add (GTK_CONTAINER (main_window), vbox1);

  handlebox2 = gtk_handle_box_new ();
  gtk_widget_ref (handlebox2);
  gtk_object_set_data_full (GTK_OBJECT (main_window), "handlebox2", handlebox2,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (handlebox2);
  gtk_box_pack_start (GTK_BOX (vbox1), handlebox2, FALSE, TRUE, 0);

  menubar1 = gtk_menu_bar_new ();
  gtk_widget_ref (menubar1);
  gtk_object_set_data_full (GTK_OBJECT (main_window), "menubar1", menubar1,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (menubar1);
  gtk_container_add (GTK_CONTAINER (handlebox2), menubar1);

  File = gtk_menu_item_new_with_label ("");
  tmp_key = gtk_label_parse_uline (GTK_LABEL (GTK_BIN (File)->child),
                                   _("_File"));
  gtk_widget_add_accelerator (File, "activate_item", accel_group,
                              tmp_key, GDK_MOD1_MASK, 0);
  gtk_widget_ref (File);
  gtk_object_set_data_full (GTK_OBJECT (main_window), "File", File,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (File);
  gtk_container_add (GTK_CONTAINER (menubar1), File);

  File_menu = gtk_menu_new ();
  gtk_widget_ref (File_menu);
  gtk_object_set_data_full (GTK_OBJECT (main_window), "File_menu", File_menu,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_menu_item_set_submenu (GTK_MENU_ITEM (File), File_menu);
  File_menu_accels = gtk_menu_ensure_uline_accel_group (GTK_MENU (File_menu));

  New = gtk_menu_item_new_with_label ("");
  tmp_key = gtk_label_parse_uline (GTK_LABEL (GTK_BIN (New)->child),
                                   _("_New"));
  gtk_widget_add_accelerator (New, "activate_item", File_menu_accels,
                              tmp_key, 0, 0);
  gtk_widget_ref (New);
  gtk_object_set_data_full (GTK_OBJECT (main_window), "New", New,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (New);
  gtk_container_add (GTK_CONTAINER (File_menu), New);
  gtk_widget_add_accelerator (New, "activate", accel_group,
                              GDK_N, GDK_CONTROL_MASK,
                              GTK_ACCEL_VISIBLE);

  Open = gtk_menu_item_new_with_label ("");
  tmp_key = gtk_label_parse_uline (GTK_LABEL (GTK_BIN (Open)->child),
                                   _("_Open..."));
  gtk_widget_add_accelerator (Open, "activate_item", File_menu_accels,
                              tmp_key, 0, 0);
  gtk_widget_ref (Open);
  gtk_object_set_data_full (GTK_OBJECT (main_window), "Open", Open,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (Open);
  gtk_container_add (GTK_CONTAINER (File_menu), Open);
  gtk_widget_add_accelerator (Open, "activate", accel_group,
                              GDK_O, GDK_CONTROL_MASK,
                              GTK_ACCEL_VISIBLE);

  Save = gtk_menu_item_new_with_label ("");
  tmp_key = gtk_label_parse_uline (GTK_LABEL (GTK_BIN (Save)->child),
                                   _("_Save"));
  gtk_widget_add_accelerator (Save, "activate_item", File_menu_accels,
                              tmp_key, 0, 0);
  gtk_widget_ref (Save);
  gtk_object_set_data_full (GTK_OBJECT (main_window), "Save", Save,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (Save);
  gtk_container_add (GTK_CONTAINER (File_menu), Save);
  gtk_widget_add_accelerator (Save, "activate", accel_group,
                              GDK_S, GDK_CONTROL_MASK,
                              GTK_ACCEL_VISIBLE);

  Save_As = gtk_menu_item_new_with_label ("");
  tmp_key = gtk_label_parse_uline (GTK_LABEL (GTK_BIN (Save_As)->child),
                                   _("Save _As..."));
  gtk_widget_add_accelerator (Save_As, "activate_item", File_menu_accels,
                              tmp_key, 0, 0);
  gtk_widget_ref (Save_As);
  gtk_object_set_data_full (GTK_OBJECT (main_window), "Save_As", Save_As,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (Save_As);
  gtk_container_add (GTK_CONTAINER (File_menu), Save_As);

  separator1 = gtk_menu_item_new ();
  gtk_widget_ref (separator1);
  gtk_object_set_data_full (GTK_OBJECT (main_window), "separator1", separator1,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (separator1);
  gtk_container_add (GTK_CONTAINER (File_menu), separator1);
  gtk_widget_set_sensitive (separator1, FALSE);

  Exit = gtk_menu_item_new_with_label ("");
  tmp_key = gtk_label_parse_uline (GTK_LABEL (GTK_BIN (Exit)->child),
                                   _("E_xit"));
  gtk_widget_add_accelerator (Exit, "activate_item", File_menu_accels,
                              tmp_key, 0, 0);
  gtk_widget_ref (Exit);
  gtk_object_set_data_full (GTK_OBJECT (main_window), "Exit", Exit,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (Exit);
  gtk_container_add (GTK_CONTAINER (File_menu), Exit);
  gtk_widget_add_accelerator (Exit, "activate", accel_group,
                              GDK_Q, GDK_CONTROL_MASK,
                              GTK_ACCEL_VISIBLE);

  Edit = gtk_menu_item_new_with_label ("");
  tmp_key = gtk_label_parse_uline (GTK_LABEL (GTK_BIN (Edit)->child),
                                   _("_Edit"));
  gtk_widget_add_accelerator (Edit, "activate_item", accel_group,
                              tmp_key, GDK_MOD1_MASK, 0);
  gtk_widget_ref (Edit);
  gtk_object_set_data_full (GTK_OBJECT (main_window), "Edit", Edit,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (Edit);
  gtk_container_add (GTK_CONTAINER (menubar1), Edit);

  Edit_menu = gtk_menu_new ();
  gtk_widget_ref (Edit_menu);
  gtk_object_set_data_full (GTK_OBJECT (main_window), "Edit_menu", Edit_menu,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_menu_item_set_submenu (GTK_MENU_ITEM (Edit), Edit_menu);
  Edit_menu_accels = gtk_menu_ensure_uline_accel_group (GTK_MENU (Edit_menu));

  Cut = gtk_menu_item_new_with_label ("");
  tmp_key = gtk_label_parse_uline (GTK_LABEL (GTK_BIN (Cut)->child),
                                   _("C_ut"));
  gtk_widget_add_accelerator (Cut, "activate_item", Edit_menu_accels,
                              tmp_key, 0, 0);
  gtk_widget_ref (Cut);
  gtk_object_set_data_full (GTK_OBJECT (main_window), "Cut", Cut,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (Cut);
  gtk_container_add (GTK_CONTAINER (Edit_menu), Cut);
  gtk_widget_add_accelerator (Cut, "activate", accel_group,
                              GDK_X, GDK_CONTROL_MASK,
                              GTK_ACCEL_VISIBLE);

  Copy = gtk_menu_item_new_with_label ("");
  tmp_key = gtk_label_parse_uline (GTK_LABEL (GTK_BIN (Copy)->child),
                                   _("_Copy"));
  gtk_widget_add_accelerator (Copy, "activate_item", Edit_menu_accels,
                              tmp_key, 0, 0);
  gtk_widget_ref (Copy);
  gtk_object_set_data_full (GTK_OBJECT (main_window), "Copy", Copy,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (Copy);
  gtk_container_add (GTK_CONTAINER (Edit_menu), Copy);
  gtk_widget_add_accelerator (Copy, "activate", accel_group,
                              GDK_C, GDK_CONTROL_MASK,
                              GTK_ACCEL_VISIBLE);

  Paste = gtk_menu_item_new_with_label ("");
  tmp_key = gtk_label_parse_uline (GTK_LABEL (GTK_BIN (Paste)->child),
                                   _("_Paste"));
  gtk_widget_add_accelerator (Paste, "activate_item", Edit_menu_accels,
                              tmp_key, 0, 0);
  gtk_widget_ref (Paste);
  gtk_object_set_data_full (GTK_OBJECT (main_window), "Paste", Paste,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (Paste);
  gtk_container_add (GTK_CONTAINER (Edit_menu), Paste);
  gtk_widget_add_accelerator (Paste, "activate", accel_group,
                              GDK_V, GDK_CONTROL_MASK,
                              GTK_ACCEL_VISIBLE);

  Clear = gtk_menu_item_new_with_label ("");
  tmp_key = gtk_label_parse_uline (GTK_LABEL (GTK_BIN (Clear)->child),
                                   _("C_lear"));
  gtk_widget_add_accelerator (Clear, "activate_item", Edit_menu_accels,
                              tmp_key, 0, 0);
  gtk_widget_ref (Clear);
  gtk_object_set_data_full (GTK_OBJECT (main_window), "Clear", Clear,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (Clear);
  gtk_container_add (GTK_CONTAINER (Edit_menu), Clear);
  gtk_widget_add_accelerator (Clear, "activate", accel_group,
                              GDK_Delete, 0,
                              GTK_ACCEL_VISIBLE);

  View = gtk_menu_item_new_with_label ("");
  tmp_key = gtk_label_parse_uline (GTK_LABEL (GTK_BIN (View)->child),
                                   _("_View"));
  gtk_widget_add_accelerator (View, "activate_item", accel_group,
                              tmp_key, GDK_MOD1_MASK, 0);
  gtk_widget_ref (View);
  gtk_object_set_data_full (GTK_OBJECT (main_window), "View", View,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (View);
  gtk_container_add (GTK_CONTAINER (menubar1), View);

  View_menu = gtk_menu_new ();
  gtk_widget_ref (View_menu);
  gtk_object_set_data_full (GTK_OBJECT (main_window), "View_menu", View_menu,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_menu_item_set_submenu (GTK_MENU_ITEM (View), View_menu);
  View_menu_accels = gtk_menu_ensure_uline_accel_group (GTK_MENU (View_menu));

  Font = gtk_menu_item_new_with_label ("");
  tmp_key = gtk_label_parse_uline (GTK_LABEL (GTK_BIN (Font)->child),
                                   _("Change _Font..."));
  gtk_widget_add_accelerator (Font, "activate_item", View_menu_accels,
                              tmp_key, 0, 0);
  gtk_widget_ref (Font);
  gtk_object_set_data_full (GTK_OBJECT (main_window), "Font", Font,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (Font);
  gtk_container_add (GTK_CONTAINER (View_menu), Font);

  Help = gtk_menu_item_new_with_label ("");
  tmp_key = gtk_label_parse_uline (GTK_LABEL (GTK_BIN (Help)->child),
                                   _("_Help"));
  gtk_widget_add_accelerator (Help, "activate_item", accel_group,
                              tmp_key, GDK_MOD1_MASK, 0);
  gtk_widget_ref (Help);
  gtk_object_set_data_full (GTK_OBJECT (main_window), "Help", Help,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (Help);
  gtk_container_add (GTK_CONTAINER (menubar1), Help);

  Help_menu = gtk_menu_new ();
  gtk_widget_ref (Help_menu);
  gtk_object_set_data_full (GTK_OBJECT (main_window), "Help_menu", Help_menu,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_menu_item_set_submenu (GTK_MENU_ITEM (Help), Help_menu);
  Help_menu_accels = gtk_menu_ensure_uline_accel_group (GTK_MENU (Help_menu));

  About = gtk_menu_item_new_with_label ("");
  tmp_key = gtk_label_parse_uline (GTK_LABEL (GTK_BIN (About)->child),
                                   _("_About..."));
  gtk_widget_add_accelerator (About, "activate_item", Help_menu_accels,
                              tmp_key, 0, 0);
  gtk_widget_ref (About);
  gtk_object_set_data_full (GTK_OBJECT (main_window), "About", About,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (About);
  gtk_container_add (GTK_CONTAINER (Help_menu), About);

  handlebox1 = gtk_handle_box_new ();
  gtk_widget_ref (handlebox1);
  gtk_object_set_data_full (GTK_OBJECT (main_window), "handlebox1", handlebox1,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (handlebox1);
  gtk_box_pack_start (GTK_BOX (vbox1), handlebox1, FALSE, TRUE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (handlebox1), 2);

  toolbar1 = gtk_toolbar_new (GTK_ORIENTATION_HORIZONTAL, GTK_TOOLBAR_BOTH);
  gtk_widget_ref (toolbar1);
  gtk_object_set_data_full (GTK_OBJECT (main_window), "toolbar1", toolbar1,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (toolbar1);
  gtk_container_add (GTK_CONTAINER (handlebox1), toolbar1);
  gtk_toolbar_set_button_relief (GTK_TOOLBAR (toolbar1), GTK_RELIEF_NONE);

  tmp_toolbar_icon = create_pixmap (main_window, "new.xpm");
  button1 = gtk_toolbar_append_element (GTK_TOOLBAR (toolbar1),
                                GTK_TOOLBAR_CHILD_BUTTON,
                                NULL,
                                _("New"),
                                NULL, NULL,
                                tmp_toolbar_icon, NULL, NULL);
  gtk_widget_ref (button1);
  gtk_object_set_data_full (GTK_OBJECT (main_window), "button1", button1,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (button1);

  tmp_toolbar_icon = create_pixmap (main_window, "open.xpm");
  button2 = gtk_toolbar_append_element (GTK_TOOLBAR (toolbar1),
                                GTK_TOOLBAR_CHILD_BUTTON,
                                NULL,
                                _("Open"),
                                NULL, NULL,
                                tmp_toolbar_icon, NULL, NULL);
  gtk_widget_ref (button2);
  gtk_object_set_data_full (GTK_OBJECT (main_window), "button2", button2,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (button2);

  tmp_toolbar_icon = create_pixmap (main_window, "save.xpm");
  button3 = gtk_toolbar_append_element (GTK_TOOLBAR (toolbar1),
                                GTK_TOOLBAR_CHILD_BUTTON,
                                NULL,
                                _("Save"),
                                NULL, NULL,
                                tmp_toolbar_icon, NULL, NULL);
  gtk_widget_ref (button3);
  gtk_object_set_data_full (GTK_OBJECT (main_window), "button3", button3,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (button3);

  scrolledwindow1 = gtk_scrolled_window_new (NULL, NULL);
  gtk_widget_ref (scrolledwindow1);
  gtk_object_set_data_full (GTK_OBJECT (main_window), "scrolledwindow1", scrolledwindow1,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (scrolledwindow1);
  gtk_box_pack_start (GTK_BOX (vbox1), scrolledwindow1, TRUE, TRUE, 0);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolledwindow1), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

  text1 = gtk_text_new (NULL, NULL);
  gtk_widget_ref (text1);
  gtk_object_set_data_full (GTK_OBJECT (main_window), "text1", text1,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (text1);
  gtk_container_add (GTK_CONTAINER (scrolledwindow1), text1);
  gtk_text_set_editable (GTK_TEXT (text1), TRUE);

  statusbar1 = gtk_statusbar_new ();
  gtk_widget_ref (statusbar1);
  gtk_object_set_data_full (GTK_OBJECT (main_window), "statusbar1", statusbar1,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (statusbar1);
  gtk_box_pack_start (GTK_BOX (vbox1), statusbar1, FALSE, TRUE, 0);

  gtk_signal_connect (GTK_OBJECT (main_window), "delete_event",
                      GTK_SIGNAL_FUNC (on_main_window_delete_event),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (New), "activate",
                      GTK_SIGNAL_FUNC (on_New_activate),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (Open), "activate",
                      GTK_SIGNAL_FUNC (on_Open_activate),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (Save), "activate",
                      GTK_SIGNAL_FUNC (on_Save_activate),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (Save_As), "activate",
                      GTK_SIGNAL_FUNC (on_Save_As_activate),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (Exit), "activate",
                      GTK_SIGNAL_FUNC (on_Exit_activate),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (Cut), "activate",
                      GTK_SIGNAL_FUNC (on_Cut_activate),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (Copy), "activate",
                      GTK_SIGNAL_FUNC (on_Copy_activate),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (Paste), "activate",
                      GTK_SIGNAL_FUNC (on_Paste_activate),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (Clear), "activate",
                      GTK_SIGNAL_FUNC (on_Clear_activate),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (Font), "activate",
                      GTK_SIGNAL_FUNC (on_Font_activate),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (About), "activate",
                      GTK_SIGNAL_FUNC (on_About_activate),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (button1), "clicked",
                      GTK_SIGNAL_FUNC (on_new_button_clicked),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (button2), "clicked",
                      GTK_SIGNAL_FUNC (on_open_button_clicked),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (button3), "clicked",
                      GTK_SIGNAL_FUNC (on_save_button_clicked),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (text1), "changed",
                      GTK_SIGNAL_FUNC (on_text_changed),
                      NULL);

  gtk_window_add_accel_group (GTK_WINDOW (main_window), accel_group);

  return main_window;
}

GtkWidget*
create_open_file_selection ()
{
  GtkWidget *open_file_selection;
  GtkWidget *ok_button1;
  GtkWidget *cancel_button1;

  open_file_selection = gtk_file_selection_new (_("Open File"));
  gtk_widget_ref (open_file_selection);
  gtk_object_set_data_full (GTK_OBJECT (open_file_selection), "open_file_selection", open_file_selection,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_container_set_border_width (GTK_CONTAINER (open_file_selection), 10);
  gtk_window_set_position (GTK_WINDOW (open_file_selection), GTK_WIN_POS_MOUSE);

  ok_button1 = GTK_FILE_SELECTION (open_file_selection)->ok_button;
  gtk_widget_ref (ok_button1);
  gtk_object_set_data_full (GTK_OBJECT (open_file_selection), "ok_button1", ok_button1,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (ok_button1);
  GTK_WIDGET_SET_FLAGS (ok_button1, GTK_CAN_DEFAULT);

  cancel_button1 = GTK_FILE_SELECTION (open_file_selection)->cancel_button;
  gtk_widget_ref (cancel_button1);
  gtk_object_set_data_full (GTK_OBJECT (open_file_selection), "cancel_button1", cancel_button1,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (cancel_button1);
  GTK_WIDGET_SET_FLAGS (cancel_button1, GTK_CAN_DEFAULT);

  gtk_signal_connect (GTK_OBJECT (open_file_selection), "delete_event",
                      GTK_SIGNAL_FUNC (on_open_filesel_delete_event),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (ok_button1), "clicked",
                      GTK_SIGNAL_FUNC (on_open_filesel_ok_button_clicked),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (cancel_button1), "clicked",
                      GTK_SIGNAL_FUNC (on_open_filesel_cancel_button_clicked),
                      NULL);

  return open_file_selection;
}

GtkWidget*
create_font_selection ()
{
  GtkWidget *font_selection;
  GtkWidget *ok_button2;
  GtkWidget *cancel_button2;
  GtkWidget *apply_button1;

  font_selection = gtk_font_selection_dialog_new (_("Select Font"));
  gtk_widget_ref (font_selection);
  gtk_object_set_data_full (GTK_OBJECT (font_selection), "font_selection", font_selection,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_container_set_border_width (GTK_CONTAINER (font_selection), 4);
  gtk_window_set_position (GTK_WINDOW (font_selection), GTK_WIN_POS_MOUSE);
  gtk_window_set_policy (GTK_WINDOW (font_selection), FALSE, TRUE, TRUE);

  ok_button2 = GTK_FONT_SELECTION_DIALOG (font_selection)->ok_button;
  gtk_widget_ref (ok_button2);
  gtk_object_set_data_full (GTK_OBJECT (font_selection), "ok_button2", ok_button2,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (ok_button2);
  GTK_WIDGET_SET_FLAGS (ok_button2, GTK_CAN_DEFAULT);

  cancel_button2 = GTK_FONT_SELECTION_DIALOG (font_selection)->cancel_button;
  gtk_widget_ref (cancel_button2);
  gtk_object_set_data_full (GTK_OBJECT (font_selection), "cancel_button2", cancel_button2,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (cancel_button2);
  GTK_WIDGET_SET_FLAGS (cancel_button2, GTK_CAN_DEFAULT);

  apply_button1 = GTK_FONT_SELECTION_DIALOG (font_selection)->apply_button;
  gtk_widget_ref (apply_button1);
  gtk_object_set_data_full (GTK_OBJECT (font_selection), "apply_button1", apply_button1,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (apply_button1);
  GTK_WIDGET_SET_FLAGS (apply_button1, GTK_CAN_DEFAULT);

  gtk_signal_connect (GTK_OBJECT (font_selection), "delete_event",
                      GTK_SIGNAL_FUNC (on_fontsel_delete_event),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (ok_button2), "clicked",
                      GTK_SIGNAL_FUNC (on_fontsel_ok_button_clicked),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (cancel_button2), "clicked",
                      GTK_SIGNAL_FUNC (on_fontsel_cancel_button_clicked),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (apply_button1), "clicked",
                      GTK_SIGNAL_FUNC (on_fontsel_apply_button_clicked),
                      NULL);

  return font_selection;
}

GtkWidget*
create_about_dialog ()
{
  GtkWidget *about_dialog;
  GtkWidget *dialog_vbox2;
  GtkWidget *label2;
  GtkWidget *dialog_action_area2;
  GtkWidget *button7;

  about_dialog = gtk_dialog_new ();
  gtk_widget_ref (about_dialog);
  gtk_object_set_data_full (GTK_OBJECT (about_dialog), "about_dialog", about_dialog,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_window_set_title (GTK_WINDOW (about_dialog), _("About The Glade Text Editor"));
  gtk_window_set_position (GTK_WINDOW (about_dialog), GTK_WIN_POS_MOUSE);
  gtk_window_set_policy (GTK_WINDOW (about_dialog), TRUE, TRUE, FALSE);

  dialog_vbox2 = GTK_DIALOG (about_dialog)->vbox;
  gtk_widget_ref (dialog_vbox2);
  gtk_object_set_data_full (GTK_OBJECT (about_dialog), "dialog_vbox2", dialog_vbox2,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (dialog_vbox2);
  gtk_container_set_border_width (GTK_CONTAINER (dialog_vbox2), 2);

  label2 = gtk_label_new (_("The Glade Text Editor\n\nv 1.0\n\n(Example program for Glade)"));
  gtk_widget_ref (label2);
  gtk_object_set_data_full (GTK_OBJECT (about_dialog), "label2", label2,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label2);
  gtk_box_pack_start (GTK_BOX (dialog_vbox2), label2, TRUE, TRUE, 10);
  gtk_misc_set_padding (GTK_MISC (label2), 12, 0);

  dialog_action_area2 = GTK_DIALOG (about_dialog)->action_area;
  gtk_widget_ref (dialog_action_area2);
  gtk_object_set_data_full (GTK_OBJECT (about_dialog), "dialog_action_area2", dialog_action_area2,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (dialog_action_area2);
  gtk_container_set_border_width (GTK_CONTAINER (dialog_action_area2), 10);

  button7 = gtk_button_new_with_label (_("  OK  "));
  gtk_widget_ref (button7);
  gtk_object_set_data_full (GTK_OBJECT (about_dialog), "button7", button7,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (button7);
  gtk_box_pack_start (GTK_BOX (dialog_action_area2), button7, FALSE, FALSE, 0);
  GTK_WIDGET_SET_FLAGS (button7, GTK_CAN_DEFAULT);
  gtk_widget_grab_default (button7);

  gtk_signal_connect (GTK_OBJECT (button7), "clicked",
                      GTK_SIGNAL_FUNC (on_about_ok_clicked),
                      NULL);

  return about_dialog;
}

GtkWidget*
create_save_file_selection ()
{
  GtkWidget *save_file_selection;
  GtkWidget *ok_button3;
  GtkWidget *cancel_button3;

  save_file_selection = gtk_file_selection_new (_("Save File"));
  gtk_widget_ref (save_file_selection);
  gtk_object_set_data_full (GTK_OBJECT (save_file_selection), "save_file_selection", save_file_selection,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_container_set_border_width (GTK_CONTAINER (save_file_selection), 10);
  gtk_window_set_position (GTK_WINDOW (save_file_selection), GTK_WIN_POS_MOUSE);

  ok_button3 = GTK_FILE_SELECTION (save_file_selection)->ok_button;
  gtk_widget_ref (ok_button3);
  gtk_object_set_data_full (GTK_OBJECT (save_file_selection), "ok_button3", ok_button3,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (ok_button3);
  GTK_WIDGET_SET_FLAGS (ok_button3, GTK_CAN_DEFAULT);

  cancel_button3 = GTK_FILE_SELECTION (save_file_selection)->cancel_button;
  gtk_widget_ref (cancel_button3);
  gtk_object_set_data_full (GTK_OBJECT (save_file_selection), "cancel_button3", cancel_button3,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (cancel_button3);
  GTK_WIDGET_SET_FLAGS (cancel_button3, GTK_CAN_DEFAULT);

  gtk_signal_connect (GTK_OBJECT (save_file_selection), "delete_event",
                      GTK_SIGNAL_FUNC (on_save_filesel_delete_event),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (ok_button3), "clicked",
                      GTK_SIGNAL_FUNC (on_save_filesel_ok_button_clicked),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (cancel_button3), "clicked",
                      GTK_SIGNAL_FUNC (on_save_filesel_cancel_button_clicked),
                      NULL);

  return save_file_selection;
}

