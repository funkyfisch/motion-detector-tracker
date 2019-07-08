#pragma once

#include <gtkmm-3.0/gtkmm.h> 
  
#include "CameraDrawingArea.hpp" 

class MainWindow : public Gtk::Window { 
public: 
    MainWindow(int width, int height); 
    virtual ~MainWindow() = default;
  
protected: 
    bool on_key_press_event(GdkEventKey* event) override; 
  
private: 
    void buttonClick(); 
    bool probablyInFullScreen;  
    Gtk::Box m_box;
    CameraDrawingArea cameraDrawingArea; 
};