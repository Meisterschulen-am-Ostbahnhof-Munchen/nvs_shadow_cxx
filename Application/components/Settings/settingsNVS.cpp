/* ************************************************************************ */
/*!
   \file
   \brief       Helper functions for reading and writing settings to a file.

*/
/* ************************************************************************ */

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <cstring>
#include <map>
#include <any>

#include "settingsNVSinternal.h"
#include "settingsNVS.h"
#include "esp_err.h"
#include "esp_log.h"
#include "nvs.h"
#include "nvs_flash.h"



/* ************************************************************************ */

static const char * const TAG = "settings";






struct Settings::Impl
{
	static nvs_handle_t my_handle;
	static std::map<std::string, std::any> shadow_memory;
};

nvs_handle_t Settings::Impl::my_handle;
std::map<std::string, std::any> Settings::Impl::shadow_memory;


void Settings::init(void)
{
	// Initialize NVS
	esp_err_t err = nvs_flash_init();
	if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND)
	{
		// NVS partition was truncated and needs to be erased
		// Retry nvs_flash_init
		ESP_ERROR_CHECK (nvs_flash_erase());
		err = nvs_flash_init();
	}
	ESP_ERROR_CHECK(err);
	// Open
	ESP_LOGD(TAG, "\n");
	ESP_LOGD(TAG, "Opening Non-Volatile Storage (NVS) handle... ");
	esp_err_t result = nvs_open("storage", NVS_READWRITE, &Impl::my_handle);
	if (result != ESP_OK) {
		ESP_LOGD(TAG, "Error (%s) opening NVS handle!\n", esp_err_to_name(result));
	} else {
		ESP_LOGD(TAG, "Done\n");
	}
	return;
}


int8_t Settings::getS8(const char section[], const char key[], const int8_t defaultValue)
{
	int8_t value;
	std::any tmp = Impl::shadow_memory[key];
	if (tmp.has_value())
	{
		value = std::any_cast<int8_t>(tmp);
	}
	else
	{
		Impl::shadow_memory[key] = defaultValue;
		value = defaultValue;
	}
	ESP_LOGI(TAG, "getS8, section = %s, key = %s, value = %i", section, key, value);
	return (value);
}

int8_t Settings::preloadS8(const char section[], const char key[], const int8_t defaultValue)
{
	int8_t value;
	esp_err_t error = nvs_get_i8(Impl::my_handle, key, &value);
	if (error != ESP_OK)
	{
		value = defaultValue;
		Settings::setS8(section, key, value);
	}
	Impl::shadow_memory[key] = value;
	ESP_LOGI(TAG, "getS8, section = %s, key = %s, value = %i", section, key, value);
	return (value);
}

int16_t Settings::preloadS16(const char section[], const char key[], const int16_t defaultValue)
{
	int16_t value;
	esp_err_t error = nvs_get_i16(Impl::my_handle, key, &value);
	if (error != ESP_OK)
	{
		value = defaultValue;
		Settings::setS16(section, key, value);
	}
	ESP_LOGI(TAG, "getS16, section = %s, key = %s, value = %i", section, key, value);
	return (value);
}

int32_t Settings::preloadS32(const char section[], const char key[], const int32_t defaultValue)
{
	int32_t value;
	esp_err_t error = nvs_get_i32(Impl::my_handle, key, &value);
	if (error != ESP_OK)
	{
		value = defaultValue;
		Settings::setS32(section, key, value);
	}
	ESP_LOGI(TAG, "getS32, section = %s, key = %s, value = %i", section, key, value);
	return (value);
}

int64_t Settings::preloadS64(const char section[], const char key[], const int64_t defaultValue)
{
	int64_t value;
	esp_err_t error = nvs_get_i64(Impl::my_handle, key, &value);
	if (error != ESP_OK)
	{
		value = defaultValue;
		Settings::setS64(section, key, value);
	}
	ESP_LOGI(TAG, "getS64, section = %s, key = %s, value = %lli", section, key, value);
	return (value);
}

uint8_t Settings::preloadU8(const char section[], const char key[], const uint8_t defaultValue)
{
	uint8_t value;
	esp_err_t error = nvs_get_u8(Impl::my_handle, key, &value);
	if (error != ESP_OK)
	{
		value = defaultValue;
		Settings::setU8(section, key, value);
	}
	ESP_LOGI(TAG, "getU8, section = %s, key = %s, value = %u", section, key, value);
	return (value);
}

uint16_t Settings::preloadU16(const char section[], const char key[], const uint16_t defaultValue)
{
	uint16_t value;
	esp_err_t error = nvs_get_u16(Impl::my_handle, key, &value);
	if (error != ESP_OK)
	{
		value = defaultValue;
		Settings::setU16(section, key, value);
	}
	ESP_LOGI(TAG, "getU16, section = %s, key = %s, value = %u", section, key, value);
	return (value);
}

uint32_t Settings::preloadU32(const char section[], const char key[], const uint32_t defaultValue)
{
	uint32_t value;
	esp_err_t error = nvs_get_u32(Impl::my_handle, key, &value);
	if (error != ESP_OK)
	{
		value = defaultValue;
		Settings::setU32(section, key, value);
	}
	ESP_LOGI(TAG, "getU32, section = %s, key = %s, value = %u", section, key, value);
	return (value);
}

uint64_t Settings::preloadU64(const char section[], const char key[], const uint64_t defaultValue)
{
	uint64_t value;
	esp_err_t error = nvs_get_u64(Impl::my_handle, key, &value);
	if (error != ESP_OK)
	{
		value = defaultValue;
		Settings::setU64(section, key, value);
	}
	ESP_LOGI(TAG, "getU64, section = %s, key = %s, value = %llu", section, key, value);
	return (value);
}

uint64_t Settings::preloadX64(const char section[], const char key[], const uint64_t defaultValue)
{
	uint64_t value;
	esp_err_t error = nvs_get_u64(Impl::my_handle, key, &value);
	if (error != ESP_OK)
	{
		value = defaultValue;
		Settings::setX64(section, key, value);
	}
	ESP_LOGI(TAG, "getX64, section = %s, key = %s, value = %llX", section, key, value);
	return (value);
}

size_t Settings::preloadString(const char section[], const char key[], const char defaultValue[], char captionOut[], size_t size)
{

	esp_err_t error = nvs_get_str(Impl::my_handle, key, captionOut, &size);
	if (error != ESP_OK)
	{
		if (defaultValue == nullptr)
		{
			return (size_t)0U;
		}
		Settings::setString(section, key, defaultValue);
	}
	ESP_LOGI(TAG, "getString, section = %s, key = %s, value = %s", section, key, captionOut);
	return (strlen(captionOut));
}

void Settings::setS8(const char section[], const char key[], const int8_t value)
{
	ESP_LOGI(TAG, "setS8, section = %s, key = %s, value = %i", section, key, value);
	Impl::shadow_memory[key] = value;
}


void Settings::commitS8(const char section[], const char key[])
{
	std::any tmp = Impl::shadow_memory[key];
	int8_t value = std::any_cast<int8_t>(tmp);
	ESP_LOGI(TAG, "setS8, section = %s, key = %s, value = %i", section, key, value);
	nvs_set_i8(Impl::my_handle, key, value);
	ESP_LOGD(TAG, "Committing updates in NVS ... ");
	esp_err_t err = nvs_commit(Impl::my_handle);
	ESP_LOGI(TAG, "Result: %s, %i, %s ", (err != ESP_OK) ? "Failed!" : "Done", err, esp_err_to_name(err));
}

void Settings::commitS16(const char section[], const char key[])
{
	std::any tmp = Impl::shadow_memory[key];
	int16_t value = std::any_cast<int16_t>(tmp);
	ESP_LOGI(TAG, "setS16, section = %s, key = %s, value = %i", section, key, value);
	nvs_set_i16(Impl::my_handle, key, value);
	ESP_LOGD(TAG, "Committing updates in NVS ... ");
	esp_err_t err = nvs_commit(Impl::my_handle);
	ESP_LOGI(TAG, "Result: %s, %i, %s ", (err != ESP_OK) ? "Failed!" : "Done", err, esp_err_to_name(err));
}

void Settings::commitS32(const char section[], const char key[])
{
	std::any tmp = Impl::shadow_memory[key];
	int32_t value = std::any_cast<int32_t>(tmp);
	ESP_LOGI(TAG, "setS32, section = %s, key = %s, value = %i", section, key, value);
	nvs_set_i32(Impl::my_handle, key, value);
	ESP_LOGD(TAG, "Committing updates in NVS ... ");
	esp_err_t err = nvs_commit(Impl::my_handle);
	ESP_LOGI(TAG, "Result: %s, %i, %s ", (err != ESP_OK) ? "Failed!" : "Done", err, esp_err_to_name(err));
}

void Settings::commitS64(const char section[], const char key[])
{
	std::any tmp = Impl::shadow_memory[key];
	int64_t value = std::any_cast<int64_t>(tmp);
	ESP_LOGI(TAG, "setS64, section = %s, key = %s, value = %lli", section, key, value);
	nvs_set_i64(Impl::my_handle, key, value);
	ESP_LOGD(TAG, "Committing updates in NVS ... ");
	esp_err_t err = nvs_commit(Impl::my_handle);
	ESP_LOGI(TAG, "Result: %s, %i, %s ", (err != ESP_OK) ? "Failed!" : "Done", err, esp_err_to_name(err));
}

void Settings::commitU8(const char section[], const char key[])
{
	std::any tmp = Impl::shadow_memory[key];
	uint8_t value = std::any_cast<uint8_t>(tmp);
	ESP_LOGI(TAG, "setU8, section = %s, key = %s, value = %u", section, key, value);
	nvs_set_u8(Impl::my_handle, key, value);
	ESP_LOGD(TAG, "Committing updates in NVS ... ");
	esp_err_t err = nvs_commit(Impl::my_handle);
	ESP_LOGI(TAG, "Result: %s, %i, %s ", (err != ESP_OK) ? "Failed!" : "Done", err, esp_err_to_name(err));
}

void Settings::commitU16(const char section[], const char key[])
{
	std::any tmp = Impl::shadow_memory[key];
	uint16_t value = std::any_cast<uint16_t>(tmp);
	ESP_LOGI(TAG, "setU16, section = %s, key = %s, value = %u", section, key, value);
	nvs_set_u16(Impl::my_handle, key, value);
	ESP_LOGD(TAG, "Committing updates in NVS ... ");
	esp_err_t err = nvs_commit(Impl::my_handle);
	ESP_LOGI(TAG, "Result: %s, %i, %s ", (err != ESP_OK) ? "Failed!" : "Done", err, esp_err_to_name(err));
}

void Settings::commitU32(const char section[], const char key[])
{
	std::any tmp = Impl::shadow_memory[key];
	uint32_t value = std::any_cast<uint32_t>(tmp);
	ESP_LOGI(TAG, "setU32, section = %s, key = %s, value = %u", section, key, value);
	nvs_set_u32(Impl::my_handle, key, value);
	ESP_LOGD(TAG, "Committing updates in NVS ... ");
	esp_err_t err = nvs_commit(Impl::my_handle);
	ESP_LOGI(TAG, "Result: %s, %i, %s ", (err != ESP_OK) ? "Failed!" : "Done", err, esp_err_to_name(err));
}

void Settings::commitU64(const char section[], const char key[])
{
	std::any tmp = Impl::shadow_memory[key];
	uint64_t value = std::any_cast<uint64_t>(tmp);
	ESP_LOGI(TAG, "setU64, section = %s, key = %s, value = %llu", section, key, value);
	nvs_set_u64(Impl::my_handle, key, value);
	ESP_LOGD(TAG, "Committing updates in NVS ... ");
	esp_err_t err = nvs_commit(Impl::my_handle);
	ESP_LOGI(TAG, "Result: %s, %i, %s ", (err != ESP_OK) ? "Failed!" : "Done", err, esp_err_to_name(err));
}

void Settings::commitX64(const char section[], const char key[])
{
	std::any tmp = Impl::shadow_memory[key];
	uint64_t value = std::any_cast<uint64_t>(tmp);
	ESP_LOGI(TAG, "setX64, section = %s, key = %s, value = %llX", section, key, value);
	nvs_set_u64(Impl::my_handle, key, value);
	ESP_LOGD(TAG, "Committing updates in NVS ... ");
	esp_err_t err = nvs_commit(Impl::my_handle);
	ESP_LOGI(TAG, "Result: %s, %i, %s ", (err != ESP_OK) ? "Failed!" : "Done", err, esp_err_to_name(err));
}

void Settings::commitString(const char section[], const char key[])
{
	std::any tmp = Impl::shadow_memory[key];
	std::string value_s = std::any_cast<std::string>(tmp);
	const char* value = value_s.c_str();
	ESP_LOGI(TAG, "setString, section = %s, key = %s, value = %s", section, key, value);
	nvs_set_str(Impl::my_handle, key, value);
	ESP_LOGD(TAG, "Committing updates in NVS ... ");
	esp_err_t err = nvs_commit(Impl::my_handle);
	ESP_LOGI(TAG, "Result: %s, %i, %s ", (err != ESP_OK) ? "Failed!" : "Done", err, esp_err_to_name(err));
}

void Settings::eraseString(const char section[], const char key[])
{
	ESP_LOGI(TAG, "erase_item, section = %s, key = %s", section, key);
	nvs_erase_key(Impl::my_handle, key);
	ESP_LOGD(TAG, "Committing updates in NVS ... ");
	esp_err_t err = nvs_commit(Impl::my_handle);
	ESP_LOGI(TAG, "Result: %s, %i, %s ", (err != ESP_OK) ? "Failed!" : "Done", err, esp_err_to_name(err));
}





/* ************************************************************************ */

int8_t preloadS8(const char section[], const char key[], const int8_t defaultValue)
{
	return (Settings::preloadS8(section, key, defaultValue));
}

int16_t preloadS16(const char section[], const char key[], const int16_t defaultValue)
{
	return (Settings::preloadS16(section, key, defaultValue));
}

int32_t preloadS32(const char section[], const char key[], const int32_t defaultValue)
{
	return (Settings::preloadS32(section, key, defaultValue));
}

int64_t preloadS64(const char section[], const char key[], const int64_t defaultValue)
{
    return (Settings::preloadS64(section, key, defaultValue));
}

/* ************************************************************************ */

uint8_t preloadU8(const char section[], const char key[], const uint8_t defaultValue)
{
	return (Settings::preloadU8(section, key, defaultValue));
}

uint16_t preloadU16(const char section[], const char key[], const uint16_t defaultValue)
{
	return (Settings::preloadU16(section, key, defaultValue));
}

uint32_t preloadU32(const char section[], const char key[], const uint32_t defaultValue)
{
	return (Settings::preloadU32(section, key, defaultValue));
}

uint64_t preloadU64(const char section[], const char key[], const uint64_t defaultValue)
{
	return (Settings::preloadU64(section, key, defaultValue));
}

/* ************************************************************************ */

uint64_t preloadX64(const char section[], const char key[], const uint64_t defaultValue)
{
	return (Settings::preloadX64(section, key, defaultValue));
}

size_t preloadString(const char section[], const char key[], const char defaultValue[], char caption[], size_t size)
{
	return (Settings::preloadString(section, key, defaultValue, caption, size));
}

/* ************************************************************************ */

/* ************************************************************************ */

int8_t getS8(const char section[], const char key[], const int8_t defaultValue)
{
	return (Settings::getS8(section, key, defaultValue));
}

int16_t getS16(const char section[], const char key[], const int16_t defaultValue)
{
	return (Settings::getS16(section, key, defaultValue));
}

int32_t getS32(const char section[], const char key[], const int32_t defaultValue)
{
	return (Settings::getS32(section, key, defaultValue));
}

int64_t getS64(const char section[], const char key[], const int64_t defaultValue)
{
    return (Settings::getS64(section, key, defaultValue));
}

/* ************************************************************************ */

uint8_t getU8(const char section[], const char key[], const uint8_t defaultValue)
{
	return (Settings::getU8(section, key, defaultValue));
}

uint16_t getU16(const char section[], const char key[], const uint16_t defaultValue)
{
	return (Settings::getU16(section, key, defaultValue));
}

uint32_t getU32(const char section[], const char key[], const uint32_t defaultValue)
{
	return (Settings::getU32(section, key, defaultValue));
}

uint64_t getU64(const char section[], const char key[], const uint64_t defaultValue)
{
	return (Settings::getU64(section, key, defaultValue));
}

/* ************************************************************************ */

uint64_t getX64(const char section[], const char key[], const uint64_t defaultValue)
{
	return (Settings::getX64(section, key, defaultValue));
}

size_t getString(const char section[], const char key[], const char defaultValue[], char caption[], size_t size)
{
	return (Settings::getString(section, key, defaultValue, caption, size));
}

/* ************************************************************************ */

void setS8(const char section[], const char key[], const int8_t value)
{
	return (Settings::setS8(section, key, value));
}

void setS16(const char section[], const char key[], const int16_t value)
{
	return (Settings::setS16(section, key, value));
}

void setS32(const char section[], const char key[], const int32_t value)
{
	return (Settings::setS32(section, key, value));
}

void setS64(const char section[], const char key[], const int64_t value)
{
	return (Settings::setS64(section, key, value));
}

/* ************************************************************************ */

void setU8(const char section[], const char key[], const uint8_t value)
{
	Settings::setU8(section, key, value);
}

void setU16(const char section[], const char key[], const uint16_t value)
{
	Settings::setU16(section, key, value);
}

void setU32(const char section[], const char key[], const uint32_t value)
{
	Settings::setU32(section, key, value);
}

void setU64(const char section[], const char key[], const uint64_t value)
{
	Settings::setU64(section, key, value);
}

/* ************************************************************************ */

void setX64(const char section[], const char key[], const uint64_t value)
{
	Settings::setX64(section, key, value);
}

void setString(const char section[], const char key[], const char value[])
{
	Settings::setString(section, key, value);
}

/* ************************************************************************ */

/* ************************************************************************ */

void commitS8(const char section[], const char key[])
{
	return (Settings::commitS8(section, key));
}

void commitS16(const char section[], const char key[])
{
	return (Settings::commitS16(section, key));
}

void commitS32(const char section[], const char key[])
{
	return (Settings::commitS32(section, key));
}

void commitS64(const char section[], const char key[])
{
	return (Settings::commitS64(section, key));
}

/* ************************************************************************ */

void commitU8(const char section[], const char key[])
{
	Settings::commitU8(section, key);
}

void commitU16(const char section[], const char key[])
{
	Settings::commitU16(section, key);
}

void commitU32(const char section[], const char key[])
{
	Settings::commitU32(section, key);
}

void commitU64(const char section[], const char key[])
{
	Settings::commitU64(section, key);
}

/* ************************************************************************ */

void commitX64(const char section[], const char key[])
{
	Settings::commitX64(section, key);
}

void commitString(const char section[], const char key[])
{
	Settings::commitString(section, key);
}

/* ************************************************************************ */

void eraseString(const char section[], const char key[])
{
	Settings::eraseString(section, key);
}
/* ************************************************************************ */
void initSettings(void)
{
	Settings::init();
}
/* ************************************************************************ */
