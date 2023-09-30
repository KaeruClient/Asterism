#pragma once

class ComponentRenderBatch;
class NinesliceInfo;
class HashedString;
class TextMeasureData;
class CaretMeasureData;
void* calltext;
class TexturePtr {
private:
	char pad_0x0[0x18];  //0x0000
public:
	TextHolder filePath;  //0x0018
private:
	char pad_0x0038[0x20];  //0x0038
};



class MinecraftUIRenderContext {
public:
    void* ClientInstance;

private:
    virtual void Destructor();
public:
    virtual float getLineLength(void* font, TextHolder* str, float measureCalculation, bool calculateWidth);
private:
    virtual int getTextAlpha();
    virtual void setTextAlpha();
    virtual void drawDebugText();
public:
    virtual void drawText(void* font, Vector4<float> const& pos, TextHolder* str, UIColor const& colour, float idk, float alinM, TextMeasureData const& textdata, CaretMeasureData const& caretdata);
    virtual void flushText(float flushDelta);
private:
    virtual void drawImage();
    virtual void drawNineslice();
    virtual void flushImages();
    virtual void beginSharedMeshBatch();
    virtual void endSharedMeshBatch();
public:
    virtual void drawRectangle(Vector4<float> const& rect, UIColor const& colour, float alpha, int width);
    virtual void fillRectangle(Vector4<float> const& rect, UIColor const& colour, float alpha);
};