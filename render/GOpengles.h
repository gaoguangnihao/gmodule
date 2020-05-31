
#ifndef GOPENGLES
#define GOPENGLES 

#include "Irender.h"
#include "nsIWidget.h"
#include "nsIWidgetListener.h"

#include "mozilla/layers/Compositor.h"
#include "mozilla/layers/Effects.h"
#include "mozilla/gfx/Matrix.h"         // for Matrix4x4
#include "mozilla/gfx/Point.h"          // for Point
#include "mozilla/gfx/Rect.h"           // for Rect
#include "mozilla/gfx/Types.h"          // for Color
#include "mozilla/GenericRefCounted.h"

using namespace mozilla;
using namespace mozilla::gfx;
using namespace mozilla::gl;
using namespace mozilla::layers;

enum DrawType
{
	TYPE_NONE,
	TYPE_COLOR,
	TYPE_TEXTURE
};

class GOpengles : public Irender,
				public GenericAtomicRefCounted
{
public:
	GOpengles(){};
	~GOpengles(){};

	void render();
	void render(mozilla::layers::Compositor *aCompositor);

	static void SetDrawType(DrawType type);
	static void SetDrawType(const nsAString& data);

// static GOpengles* getInstance() {
// 	if(instance == NULL) {
// 		instance = new GOpengles();
// 	}
// 	return instance;
// }

private:
//	static GOpengles* instance;

	static DrawType mDrawType;

	void drawColor(mozilla::layers::Compositor *aCompositor);
	void drawTexture(mozilla::layers::Compositor *aCompositor);

	void loadCursorImage(mozilla::layers::Compositor *aCompositor);

};

//GOpengles* GOpengles::instance = NULL;

#endif