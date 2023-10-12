#pragma once
#include "../../../Includes/imgui/imgui.h"
#include "../../../SDK/Structs/GameMode.h"
#include "../../../SDK/Structs/MinecraftUIRenderContext.h"
#include "../../../Memory/GameData.h"

class Module;

enum class Category {
	COMBAT = 0,
	PLAYER = 1,
	WORLD = 2,
	RENDER = 3,
	MISC = 4
};

struct EnumEntry {
private:
	/*const */ std::string name;
	/*const */ unsigned char val;

public:
	/// <summary>Use this however you want</summary>
	void* ptr = nullptr;
	EnumEntry(const std::string _name, const unsigned char value);
	std::string GetName();
	unsigned char GetValue();
};

struct AddResult;

class SettingEnum {
private:
	Module* owner = nullptr;

public:
	std::vector<EnumEntry> Entrys;
	int selected = 0;

	SettingEnum(std::vector<EnumEntry> entr, Module* mod = nullptr);
	SettingEnum(Module* mod = nullptr);
	//SettingEnum();
	SettingEnum& addEntry(EnumEntry entr);
	EnumEntry& GetEntry(int ind);
	EnumEntry& GetSelectedEntry();
	int GetCount();
};

enum class ValueType {
	FLOAT_T,
	DOUBLE_T,
	INT64_T,
	INT_T,
	BOOL_T,
	TEXT_T,
	ENUM_T
};

struct SettingValue {
	union {
		float _float;
		double _double;
		__int64 int64;
		int _int;
		bool _bool;
		std::string* text;
		SettingEnum* Enum;
	};
};

struct SettingEntry {
	char name[0x20] = "";
	ValueType valueType;
	SettingValue* value = nullptr;
	SettingValue* defaultValue = nullptr;
	SettingValue* minValue = nullptr;
	SettingValue* maxValue = nullptr;
	void* extraData; // Only used by enum for now

	// ClickGui Data
	bool isDragging = false;  // This is incredibly hacky and i wanted to avoid this as much as possible but i want to get this clickgui done
};

class Module {
private:
	bool enabled = false;
	const char* tooltip;
	Category category;
	int key = 0x0;
	vec2_t pos;
public:

	Module(int key, Category category, const char* tooltip);
	virtual ~Module();
	void registerFloatSetting(std::string name, float* floatPtr, float defaultValue, float minValue, float maxValue);
	void registerIntSetting(std::string name, int* intpTr, int defaultValue, int minValue, int maxValue);
	void registerEnumSetting(std::string name, SettingEnum* intPtr, int defaultValue);
	void registerBoolSetting(std::string name, bool* boolPtr, bool defaultValue);

	inline Category getCategory() { return category; }

	inline std::vector<SettingEntry*>* getSettings() { return &settings; };
	inline vec2_t* getPos() {
		return &pos;
	};
	virtual bool isEnabled() {
		return this->enabled;
	};
	virtual int getBind() {
		return this->key;
	};
	virtual void onEnable() {
	};
	virtual void onDisable() {
	};
	virtual void setEnabled(bool ean);

	virtual void setBind(int ean) {
		key = ean;
	};
	std::vector<SettingEntry*> settings;
	virtual const char* getModuleName() = 0;
	virtual const char* getModeName();
	virtual void onTick(GameMode* gm) {};
	virtual void onRender(MinecraftUIRenderContext* ctx) {};
	virtual void onImRender() {};
	virtual void onKey(__int32 key);
	const char* getTooltip();
};