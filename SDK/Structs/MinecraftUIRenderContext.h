#pragma once

class ComponentRenderBatch;
class NinesliceInfo;
class HashedString;
class TextMeasureData;
class CaretMeasureData;
class TexturePtr;


class MinecraftUIRenderContext {
public:
    ClientInstance* ClientInstance;

private:
    virtual void Destructor();
public:
    virtual float getLineLength(void* font, TextHolder* str, float measureCalculation, bool calculateWidth);
private:
    virtual int getTextAlpha();
    virtual void setTextAlpha();
    virtual void drawDebugText();
public:
    virtual void drawText(void* font, vec4_t const& pos, TextHolder* str, UIColor const& colour, float idk, float alinM, TextMeasureData const& textdata, CaretMeasureData const& caretdata);
    virtual void flushText(float flushDelta);
private:
    virtual void drawImage();
    virtual void drawNineslice();
    virtual void flushImages();
    virtual void beginSharedMeshBatch();
    virtual void endSharedMeshBatch();
public:
    virtual void drawRectangle(vec4_t const& rect, UIColor const& colour, float alpha, int width);
    virtual void fillRectangle(vec4_t const& rect, UIColor const& colour, float alpha);
};