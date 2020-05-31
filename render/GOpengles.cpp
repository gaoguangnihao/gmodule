
#include "GOpengles.h"
#include "nsCOMPtr.h"

#include "Gutils.h"

#include "../../../widget/gonk/GLCursorImageManager.h"

#include <android/log.h>
#undef LOG
#define LOG(args...) \
  __android_log_print(ANDROID_LOG_INFO, "GOpengles", ## args)

//static 
DrawType GOpengles::mDrawType = TYPE_NONE;

/*static*/
void GOpengles::SetDrawType(DrawType type){
 	LOG("Set draw type to %d", type);
 	mDrawType = type;
 }

 /*static*/
void GOpengles::SetDrawType(const nsAString& data){
	int ret = 0;
	convertEventType(data, ret);
 	LOG("Set draw type to %d", ret);
 	mDrawType = DrawType(ret);
 }

 void
 GOpengles::render() {

 }

void 
GOpengles::render(Compositor *aCompositor) {
	LOG("Render called, draw type is %d", mDrawType);
	switch(mDrawType) {
	   case TYPE_COLOR:
	     drawColor(aCompositor);
	     break;
	   case TYPE_TEXTURE:
	     drawTexture(aCompositor);    
	     break;
	   case TYPE_NONE:
	   default:
	     LOG("GOpengles draw type is 0, break");
	     break;
	 }
}

void GOpengles::loadCursorImage(Compositor *aCompositor) {
	//nsWindow* aWindow = static_cast<nsWindow*>(aCompositor->GetWidget());
	//if(!aWindow) {
	//	return;
	//}
	// nsIPresShell* presShell = aWindow->GetWidgetListener()->GetPresShell();

	// RefPtr<mozilla::dom::AnonymousContent> cursorElementHolder;
	// if(presShell && presShell->GetDocument()) {
	// 	nsIDocument* doc = presShell->GetDocument();
	// 	nsCOMPtr<dom::Element>  image = doc->CreateHTMLElement(nsGkAtoms::div);

	// 	ErrorResult rv;
	// 	image->ClassList()->Add(NS_LITERAL_STRING("kaios-cursor"), rv);
	// 	image->ClassList()->Add(NS_LITERAL_STRING("std"), rv);
	// 	cursorElementHolder = doc->InsertAnonymousContent(*image, rv);

	// 	if(cursorElementHolder) {
	// 		nsCOMPtr<dom::Element> element = cursorElementHolder->GetContentNode();
	// 		nsIFrame* frame = element->GetPrimaryFrame();

	// 	}

	// }
}

void GOpengles::drawColor(Compositor *aCompositor) {
 	float alpha2 = 1;
 	EffectChain effects2;
 	Rect bounds(0.0f, 0.0f, 240, 320);
 	effects2.mPrimaryEffect = new EffectSolidColor(mozilla::gfx::Color(1, 1, 1, 1));
 	aCompositor->DrawQuad(gfx::Rect(50, 50, 80, 80),
 	                    bounds, effects2, alpha2, mozilla::gfx::Matrix4x4());
 }

void GOpengles::drawTexture(Compositor *aCompositor) {
	nsIWidget* aWidget = aCompositor->GetWidget();
	nsWindow* aWindow = static_cast<nsWindow*>(aWidget);
	GLCursorImageManager* aGLimage = aWindow->GetGLCursorImageManager();

	if (!aGLimage->IsCursorImageReady(eCursor_standard)) {
		LOG("Load cursor image");
		aGLimage->PrepareCursorImage(eCursor_standard, aWindow);
	} else {
		GLCursorImageManager::GLCursorImage cursorImage =
	                aGLimage->GetGLCursorImage(eCursor_standard);

	    EffectChain effects;
	    float alpha = 1;
	    RefPtr<DataTextureSource> textrueSource = aCompositor->CreateDataTextureSource(); 
	    textrueSource->Update(cursorImage.mSurface);
	    effects.mPrimaryEffect = CreateTexturedEffect(SurfaceFormat::B8G8R8A8,
	    												textrueSource,
	                                                   	Filter::POINT,
	                                                     true);

	    LOG("Draw cursor image");
	    Rect bounds(0.0f, 0.0f, 240, 320);
	    aCompositor->DrawQuad(gfx::Rect(100,100,30,30),
	    						bounds, effects, alpha, mozilla::gfx::Matrix4x4());
	}
}