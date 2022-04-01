/* ************************************************************************ */
/*!
   \file
   \brief       Helper functions for reading and writing settings to a file.
*/
/* ************************************************************************ */
#ifndef COMPONENTS_SETTINGS_SETTINGSNVS_H_
#define COMPONENTS_SETTINGS_SETTINGSNVS_H_


#ifdef __cplusplus
extern "C" {
#endif
/* ************************************************************************ */

	// Preload is Load from NVS to Shadow

	int8_t   preloadS8(const char section[], const char key[], const int8_t defaultValue);
	int16_t  preloadS16(const char section[], const char key[], const int16_t defaultValue);
	int32_t  preloadS32(const char section[], const char key[], const int32_t defaultValue);
	int64_t  preloadS64(const char section[], const char key[], const int64_t defaultValue);
	uint8_t  preloadU8(const char section[], const char key[], const uint8_t defaultValue);
	uint16_t preloadU16(const char section[], const char key[], const uint16_t defaultValue);
	uint32_t preloadU32(const char section[], const char key[], const uint32_t defaultValue);
	uint64_t preloadU64(const char section[], const char key[], const uint64_t defaultValue);
	uint64_t preloadX64(const char section[], const char key[], const uint64_t defaultValue);
	size_t   preloadString(const char section[], const char key[], const char defaultValue[], char string[], size_t stringSize);
/* ************************************************************************ */

	// Get is Pure non-NVS reading. Only Shadow.

    int8_t   getS8(const char section[], const char key[], const int8_t defaultValue);
    int16_t  getS16(const char section[], const char key[], const int16_t defaultValue);
    int32_t  getS32(const char section[], const char key[], const int32_t defaultValue);
    int64_t  getS64(const char section[], const char key[], const int64_t defaultValue);
    uint8_t  getU8(const char section[], const char key[], const uint8_t defaultValue);
    uint16_t getU16(const char section[], const char key[], const uint16_t defaultValue);
    uint32_t getU32(const char section[], const char key[], const uint32_t defaultValue);
    uint64_t getU64(const char section[], const char key[], const uint64_t defaultValue);
    uint64_t getX64(const char section[], const char key[], const uint64_t defaultValue);
    size_t   getString(const char section[], const char key[], const char defaultValue[], char string[], size_t stringSize);
/* ************************************************************************ */

    // Set is Pure non-NVS Setting. Only Shadow.

    void setS8(const char section[], const char key[], const int8_t value);
    void setS16(const char section[], const char key[], const int16_t value);
    void setS32(const char section[], const char key[], const int32_t value);
    void setS64(const char section[], const char key[], const int64_t value);
    void setU8(const char section[], const char key[], const uint8_t value);
    void setU16(const char section[], const char key[], const uint16_t value);
    void setU32(const char section[], const char key[], const uint32_t value);
    void setU64(const char section[], const char key[], const uint64_t value);
    void setX64(const char section[], const char key[], const uint64_t value);
    void setString(const char section[], const char key[], const char value[]);
/* ************************************************************************ */

    //Commit is write from Shadow to NVS.

    void commitS8(const char section[], const char key[]);
    void commitS16(const char section[], const char key[]);
    void commitS32(const char section[], const char key[]);
    void commitS64(const char section[], const char key[]);
    void commitU8(const char section[], const char key[]);
    void commitU16(const char section[], const char key[]);
    void commitU32(const char section[], const char key[]);
    void commitU64(const char section[], const char key[]);
    void commitX64(const char section[], const char key[]);
    void commitString(const char section[], const char key[]);
/* ************************************************************************ */
    void eraseString(const char section[], const char key[]);
/* ************************************************************************ */
	//TODO
    //uint32_t getSection(const char section[], char string[], uint32_t stringSize);
	//TODO
    //void     clearSection(const char section[]);
/* ************************************************************************ */
	//TODO
    //void removeEntry(const char section[], const char key[]);
	//TODO
    //void createSection(const char section[]);
	//TODO
    //void removeSection(const char section[]);
/* ************************************************************************ */
    void initSettings(void);

/* ************************************************************************ */
#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* COMPONENTS_SETTINGS_SETTINGSNVS_H_ */
/* ************************************************************************ */
