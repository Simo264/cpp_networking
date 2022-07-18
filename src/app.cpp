#include "app.h"
#include "app_frame.h"

wxIMPLEMENT_APP(App);
 
bool App::OnInit()
{
    AppFrame *frame = new AppFrame();
    frame->Show(true);
    return true;
}
 
