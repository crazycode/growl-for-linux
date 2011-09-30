/* Copyright 2011 by Kohei Takahashi
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * REGENTS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <gtk/gtk.h>
#ifdef _WIN32
# include <gdk/gdkwin32.h>
#endif

#include <libnotify/notify.h>

#include "../../gol.h"
#include "display_libnotify.xpm"

G_MODULE_EXPORT gboolean
display_init() {
  return notify_init("Growl for Linux");
}

G_MODULE_EXPORT void
display_term() {
  notify_uninit();
}

G_MODULE_EXPORT gboolean
display_show(const gpointer data) {
  const NOTIFICATION_INFO* const ni = (NOTIFICATION_INFO*) data;

  gchar* const newurl = ni->icon ? g_filename_from_uri(ni->icon, NULL, NULL) : NULL;
  // TODO: libnotify can't handle image URLs.
  NotifyNotification *nt = notify_notification_new(ni->title, ni->text, newurl ? newurl : ni->icon, NULL);

  GError* error = NULL;
  if (!notify_notification_show(nt, &error))
  {
      g_error("%s: %s", G_STRFUNC, error->message);
      g_error_free(error);
  }

  //g_free(newurl);
  return FALSE;
}

G_MODULE_EXPORT const gchar*
display_name() {
  return "libnotify";
}

G_MODULE_EXPORT const gchar*
display_description() {
  return
    "<span size=\"large\"><b>libnotify</b></span>\n"
    "<span>This is front-end of libnotify.</span>\n"
    "<span>For more detail, see <a href=\"https://launchpad.net/notify-osd\">here</a>.</span>\n";
}

G_MODULE_EXPORT char**
display_thumbnail() {
  return display_libnotify;
}

// vim:set et sw=2 ts=2 ai: