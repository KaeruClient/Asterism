#pragma once
#include "../../../SDK/Structs/MinecraftUIRenderContext.h"
#include "../../../Utils/DrawUtils.h"
#include "../../../Utils/ImGuiUtils.h"
// Declare a void pointer called __o__Render
void* __o__Render;
void* __o__drawtext;
void* __o__drawimage;

// Declare a variable called layerCounter and initialize it to 0
int layerCounter = 0;

void drawtextDetour(MinecraftUIRenderContext* ctx, void* font, float* pos, std::string* text, float* color, float alpha, unsigned int textAlignment, const TextMeasureData* textMeasureData, const CaretMeasureData* caretMeasureData) {
   Utils::CallFunc<void*, MinecraftUIRenderContext*, void*, float*, std::string*, float*, float, unsigned int, const TextMeasureData*, const CaretMeasureData*>(
        __o__drawtext,
        ctx,
        font,
        pos,
        text,
        color,
        alpha,
        textAlignment,
        textMeasureData,
        caretMeasureData
    );
}
void onDrawImage(MinecraftUIRenderContext* ctx,  void* a2, vec2_t const& ImagePos, vec2_t const& ImageDimension, vec2_t const& uvPos, vec2_t const& uvSize) {
    Utils::CallFunc<void*, MinecraftUIRenderContext*, void*, vec2_t const&, vec2_t const&, vec2_t const&, vec2_t const&>(
        __o__drawimage,
        ctx,
        a2,
        ImagePos,
        ImageDimension,
        uvPos,
        uvSize
    );
}
// Call the function at the address stored in __o__Render, passing in __this and ctx as arguments
void renderDetour(void* a1, MinecraftUIRenderContext* renderCtx) {
    // Call the function at the address stored in __o__Render, passing in __this and ctx as arguments/
    Utils::CallFunc<void*, void*, MinecraftUIRenderContext*>(
        __o__Render,
        a1,
        renderCtx
    );
    auto vtable = *(uintptr_t**)renderCtx;
    static bool tryHook5 = false;
    static bool tryHook7 = false;
    if (!tryHook5) {
        tryHook5 =
            Utils::HookFunction(
                (void*)vtable[5], // DrawText
                (void*)&drawtextDetour,
                &__o__drawtext
            );
    }
    if (!tryHook7) {
        tryHook7 = Utils::HookFunction(
            (void*)vtable[7], // DrawImage
            (void*)&onDrawImage,
            &__o__drawimage
        );
    }
    // Increment layerCounter
    layerCounter++;

    // If layerCounter is equal to 3
    if (layerCounter == 3) {
        // Set layerCounter to 0
        layerCounter = 0;

        // Declare a UIColor object called color and initialize it with the values 255, 255, 255, 255
        
        DrawUtils::Initialize(renderCtx);
        //renderCtx->fillRectangle(vec4_t({ 2, 2 }, { 10, 20 }), color, color.a);
        //DrawUtils::fillRectangle(vec4_t({ 2, 2 }, { 60, 20 }), color2);
        //DrawUtils::drawRectangle(vec4_t({ 2, 2 }, { 60, 20 }), color, 1);
    }
}

class RenderContextHook : public FuncHook {
public:
    bool Initialize() override
    {
        // 2873 is the size of the machine code (Excluding variables) at the time im making this

        // Find the address of the function specified by the signature {SIG} and store it in a void pointer called renderAddr
        void* renderAddr = Utils::findSig("48 8b c4 48 89 58 ? 55 56 57 41 54 41 55 41 56 41 57 48 8d a8 ? ? ? ? 48 81 ec ? ? ? ? 0f 29 70 ? 0f 29 78 ? 48 8b 05 ? ? ? ? 48 33 c4 48 89 85 ? ? ? ? 4c 8b fa 48 89 54 24 ? 4c 8b e9 48 89 4c 24");
        
        // Attempt to hook the function at the address stored in renderAddr by replacing it with the address of renderDetour and store the original function's address in __o__Render
        return Utils::HookFunction(
            renderAddr,
            (void*)&renderDetour,
            &__o__Render
        );
    }

    static RenderContextHook& Instance() {
        static RenderContextHook instance;
        return instance;
    }
};