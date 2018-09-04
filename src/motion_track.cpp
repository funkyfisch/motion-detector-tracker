#include <iostream>
#include "motion_track.h"

using namespace std;
void pointCameraTowards(int region) {
    cout << "Moving camera" << region << endl;
    switch(region) {
      case 1:
      //panleft(),pitchup();
        break;
      case 2:
      //pitchup();
        break;
      case 3:
      //panright(), pitchup();
        break;
      case 4:
      //panleft();
        break;
      case 5:
        break;
      case 6:
      //panright();
        break;
      case 7:
      //panleft(), pitchdown();
        break;
      case 8:
      //pitchdown();
        break;
      case 9:
      //panright(), pitchdown();
        break;
      default:
        break;
      return;
    }
}