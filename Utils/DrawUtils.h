#pragma once
#include "../SDK/Maths/UIColor.h"
#include "../SDK/Maths/Vector4.h"
#include "../SDK/Structs/MinecraftUIRenderContext.h"
namespace DrawUtils {
	static void fillRectangle(MinecraftUIRenderContext* ctx, Vector4<float> pos, UIColor col) {
		ctx->fillRectangle(pos, col, col.a);
	};
};