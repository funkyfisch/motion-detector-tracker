#include <syslog.h>
#include <unistd.h>

#include "MainWindow.hpp"

MainWindow::MainWindow(int width, int height)
    : probablyInFullScreen(false), m_box(Gtk::ORIENTATION_VERTICAL)
{
    // Configure this window:
    this->set_default_size(width, height);

    // Make the second label visible:
    cameraDrawingArea.show();

    // Pack all elements in the box:
    m_box.pack_start(cameraDrawingArea, Gtk::PACK_EXPAND_WIDGET);

    // Add the box in this window:
    add(m_box);

    // Make the box visible:
    m_box.show();

    // Activate Key-Press events
    add_events(Gdk::KEY_PRESS_MASK);
}

void MainWindow::buttonClick()
{
    syslog(LOG_NOTICE, "User %d says 'Hello World'", getuid());
}

bool MainWindow::on_key_press_event(GdkEventKey* event)
{
    switch (event->keyval) {
    // Ctrl + C: Ends the app:
    case GDK_KEY_C:
    case GDK_KEY_c:
        if ((event->state & GDK_CONTROL_MASK) == GDK_CONTROL_MASK) {
            get_application()->quit();
        }
        return true;

    // [F] toggles fullscreen mode:
    case GDK_KEY_F:
    case GDK_KEY_f:
        if (probablyInFullScreen) {
            unfullscreen();
            probablyInFullScreen = false;
        }
        else {
            fullscreen();
            probablyInFullScreen = true;
        }
        return true;

    // [esc] exits fullscreen mode:
    case GDK_KEY_Escape:
        unfullscreen();
        probablyInFullScreen = false;
        return true;
    }

    return false;
}