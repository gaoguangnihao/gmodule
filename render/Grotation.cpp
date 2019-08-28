
#include "nsDebug.h"   // for assertion
#include "nsCOMPtr.h"
#include "nsServiceManagerUtils.h"  // for do_GetService


#include "Grotation.h"

#include "mozilla/StaticPtr.h"
#include "nsIScreen.h"
#include "nsIScreenManager.h"

void 
Grotation::render() {
	nsCOMPtr<nsIScreenManager> screenMgr =
    do_GetService("@mozilla.org/gfx/screenmanager;1");

    NS_ENSURE_TRUE_VOID(screenMgr);

    nsCOMPtr<nsIScreen> screen;
    screenMgr->GetPrimaryScreen(getter_AddRefs(screen));
    NS_ENSURE_TRUE_VOID(screen);

    LOG("SetRotation to 90 deg");
    screen->SetRotation(nsIScreen::ROTATION_90_DEG);
}