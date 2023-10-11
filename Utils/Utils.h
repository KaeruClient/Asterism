#pragma once

#include <Windows.h>
#include <Psapi.h>
#include <sstream>
#include <winnt.h>
#include <xmemory>

#include "../Memory/minhook.h"


#define logstr(str);

static const char* const KeyNames[] = {
	"Unknown",
	"VK_LBUTTON",
	"VK_RBUTTON",
	"VK_CANCEL",
	"VK_MBUTTON",
	"VK_XBUTTON1",
	"VK_XBUTTON2",
	"Unknown",
	"VK_BACK",
	"TAB",
	"Unknown",
	"Unknown",
	"VK_CLEAR",
	"VK_RETURN",
	"Unknown",
	"Unknown",
	"Shift",
	"CTRL",
	"VK_MENU",
	"VK_PAUSE",
	"VK_CAPITAL",
	"VK_KANA",
	"Unknown",
	"VK_JUNJA",
	"VK_FINAL",
	"VK_KANJI",
	"Unknown",
	"VK_ESCAPE",
	"VK_CONVERT",
	"VK_NONCONVERT",
	"VK_ACCEPT",
	"VK_MODECHANGE",
	"VK_SPACE",
	"VK_PRIOR",
	"VK_NEXT",
	"VK_END",
	"VK_HOME",
	"VK_LEFT",
	"VK_UP",
	"VK_RIGHT",
	"VK_DOWN",
	"VK_SELECT",
	"VK_PRINT",
	"VK_EXECUTE",
	"VK_SNAPSHOT",
	"INSERT",
	"DELETE",
	"VK_HELP",
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"A",
	"B",
	"C",
	"D",
	"E",
	"F",
	"G",
	"H",
	"I",
	"J",
	"K",
	"L",
	"M",
	"N",
	"O",
	"P",
	"Q",
	"R",
	"S",
	"T",
	"U",
	"V",
	"W",
	"X",
	"Y",
	"Z",
	"VK_LWIN",
	"VK_RWIN",
	"VK_APPS",
	"Unknown",
	"VK_SLEEP",
	"NUMPAD0",
	"NUMPAD1",
	"NUMPAD2",
	"NUMPAD3",
	"NUMPAD4",
	"NUMPAD5",
	"NUMPAD6",
	"NUMPAD7",
	"NUMPAD8",
	"NUMPAD9",
	"VK_MULTIPLY",
	"VK_ADD",
	"VK_SEPARATOR",
	"VK_SUBTRACT",
	"VK_DECIMAL",
	"VK_DIVIDE",
	"F1",
	"F2",
	"F3",
	"F4",
	"F5",
	"F6",
	"F7",
	"F8",
	"F9",
	"F10",
	"F11",
	"F12",
	"VK_F13",
	"VK_F14",
	"VK_F15",
	"VK_F16",
	"VK_F17",
	"VK_F18",
	"VK_F19",
	"VK_F20",
	"VK_F21",
	"VK_F22",
	"VK_F23",
	"VK_F24",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"VK_NUMLOCK",
	"VK_SCROLL",
	"VK_OEM_NEC_EQUAL",
	"VK_OEM_FJ_MASSHOU",
	"VK_OEM_FJ_TOUROKU",
	"VK_OEM_FJ_LOYA",
	"VK_OEM_FJ_ROYA",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"LeftShift",
	"RightShift",
	"VK_LCONTROL",
	"VK_RCONTROL",
	"VK_LMENU",
	"VK_RMENU",
	"Browser Back",
	"Browser Forward",
	"Browser Refresh",
	"Browser Stop",
	"Browser Search",
	"Browser Favourites",
	"Browser Home",
	"Volume Mute",
	"Volume Down",
	"Volume Up",
	"Media_Next",
	"Media_Prev",
	"Media_Stop",
	"Media_Pause",
	"Mail",
	"Media",
	"App1",
	"App2",
	"Unknown",
	"Unknown",
	"OEM_1",
	"PLUS",
	"COMMA",
	"MINUS",
	"DOT",
	"OEM_2",
	"OEM_3" };

namespace Utils {

	static inline unsigned int getCrcHash(const char* str, int seed = 0) {
		static unsigned int crc32_lut[256] = { 0 };
		if (!crc32_lut[1]) {
			const unsigned int polynomial = 0xEDB88320;
			for (unsigned int i = 0; i < 256; i++) {
				unsigned int crc = i;
				for (unsigned int j = 0; j < 8; j++)
					crc = (crc >> 1) ^ (((unsigned int)(-((int)(crc & 1)))) & polynomial);
				crc32_lut[i] = crc;
			}
		}

		seed = ~seed;
		unsigned int crc = seed;
		const unsigned char* current = (const unsigned char*)str;
		{
			// Zero-terminated string
			while (unsigned char c = *current++) {
				// We support a syntax of "label###id" where only "###id" is included in the hash, and only "label" gets displayed.
				// Because this syntax is rarely used we are optimizing for the common case.
				// - If we reach ### in the string we discard the hash so far and reset to the seed.
				// - We don't do 'current += 2; continue;' after handling ### to keep the code smaller.
				if (c == '#' && current[0] == '#' && current[1] == '#')
					crc = seed;
				crc = (crc >> 8) ^ crc32_lut[(crc & 0xFF) ^ c];
			}
		}
		return ~crc;
	}
	static inline const char* getKeyName(int keybind) {
		return KeyNames[keybind];
	};
    template <typename R, typename... Args>
    R CallFunc(void* func, Args... args) //namespaceをclassにしないんですか？！？！？！
    {
        // Call the function and return the result.
        return ((R(*)(Args...))func)(args...);
    }
    
    template <unsigned int index, typename returnType, typename... args>
    static inline auto callVirtualTable(void* ptr, args... argList) -> returnType {
        using function = returnType(__thiscall*)(void*, decltype(argList)...);
        return (*static_cast<function**>(ptr))[index](ptr, argList...);
    }
    // template function that converts the specified value to a string using a stringstream
    template <typename T>
    std::string combine(T t)
    {
        std::stringstream ss;
        ss << t;
        return ss.str();
    }

    // template function that converts the specified values to a string using a stringstream
    template <typename T, typename... Args>
    std::string combine(T t, Args... args)
    {
        std::stringstream ss;
        ss << t << combine(args...);
        return ss.str();
    }

    // template function that creates a hook at the specified target function with the provided detour function and stores the original function in the specified location
    template <typename T>
    bool HookFunction(void* pTarget, T pDetour, void* pOriginal) {
        static bool initialized = false;
        if (!initialized)
        {
            initialized = true;
            if (MH_Initialize() != MH_OK)
            {
              //  log("Error: Failed to initialize MinHook\n");
                return false;
            }
        }

        if (MH_CreateHook(pTarget, pDetour, (LPVOID*)pOriginal) != MH_OK)
        {
            //log("Error: Failed to create hook\n");
            return false;
        }

        if (MH_EnableHook(pTarget) != MH_OK)
        {
            //log("Error: Failed to enable hook\n");
            return false;
        }

        logstr(combine("Success: Enabled hook for ", pTarget, "\n").c_str());
        return true;
    }

    // macro that checks if a value is within a range
    #define INRANGE(x, a, b) (x >= a && x <= b)

    // macro that converts two characters to a single byte
    #define GET_BYTE(x) ((GET_BITS(x[0]) << 4) | GET_BITS(x[1]))

    // macro that converts a character to a nibble (4 bits)
    #define GET_BITS(x) (INRANGE((x & (~0x20)), 'A', 'F') ? ((x & (~0x20)) - 'A' + 0xa) : (INRANGE(x, '0', '9') ? (x - '0') : 0))

    // This function searches for a pattern of bytes within the memory range specified by range_start and range_end
    // The pattern to search for is specified as a string, where each byte in the pattern is represented by 2 hexadecimal characters
    // For example, the pattern "90 90 90 90" would represent the byte sequence 0x90 0x90 0x90 0x90
    // If the pattern is found within the specified memory range, a pointer to the start of the pattern is returned
    // Otherwise, a null pointer is returne
    static void* findSig(const char* sig) {
        // pointer to the current position in the pattern
        const char* pattern = sig;

        // store the first matched address
        uintptr_t first_match = 0;

        // store the first matched address
        static const uintptr_t range_start = reinterpret_cast<uintptr_t>(GetModuleHandleA("Minecraft.Windows.exe"));

        // store information about the module
        static MODULEINFO mi_mod_info;

        // flag to initialize mi_mod_info only once
        static bool init = false;
        if (!init) {
            // initialize mi_mod_info
            init = true;
            GetModuleInformation(GetCurrentProcess(), reinterpret_cast<HMODULE>(range_start), &mi_mod_info, sizeof(MODULEINFO));
        }
        // calculate the end address of the module
        static const uintptr_t range_end = range_start + mi_mod_info.SizeOfImage;

        // store the current byte in the pattern as a BYTE
        BYTE pat_byte = GET_BYTE(pattern);

        // store the original position in the pattern
        const char* old_pat = pattern;

        // iterate through all addresses in the module
        for (uintptr_t p_cur = range_start; p_cur < range_end; p_cur++) {
            // if we reached the end of the pattern, return the first matched address
            if (!*pattern) {
                return reinterpret_cast<void*>(first_match);
            }

            // skip spaces in the pattern
            while (*(PBYTE)pattern == ' ') {
                pattern++;
            }

            // if we reached the end of the pattern, return the first matched address
            if (!*pattern) {
                return reinterpret_cast<void*>(first_match);
            }

            // if the pattern has changed from the last iteration, update the pat_byte value
            if (old_pat != pattern) {
                old_pat = pattern;
                // if the current byte in the pattern is not a wildcard '?', update pat_byte to the current byte value
                if (*(PBYTE)pattern != '\?') {
                    pat_byte = GET_BYTE(pattern);
                }
            }

            // if the current byte in the pattern is a wildcard or if the current byte in the pattern matches the current byte in the range,
            // increment the pattern by 2 and set first_match to the current address if it is not already set
            if (*(PBYTE)pattern == '\?' || *(BYTE*)p_cur == pat_byte) {
                if (!first_match) {
                    first_match = p_cur;
                }

                // if the next byte in the pattern is the end, return the first matched address
                if (!pattern[2]) {
                    return reinterpret_cast<void*>(first_match);
                }

                pattern += 2;
            }
            else { // if the current byte in the pattern does not match the current byte in the range, reset the pattern to the start and clear first_match
                pattern = sig;
                first_match = 0;
            }
        }
    }
}