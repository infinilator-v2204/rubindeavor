#include <stdio.h>
#include <stdlib.h>
#include "zip.h"

struct zip_t* za;
const char* ASSETS_PASSWORD = "the master lulu";

typedef struct {
	int isDir;
	char name[256];
	void* data;
	size_t size;
} GfxCryptFile;

int main() {
	// Read
	za = zip_open("assets.dat", ZIP_DEFAULT_COMPRESSION_LEVEL, 'r');
	if (za == NULL) {
		printf("Failed to read assets.dat\n");
		return -1;
	}
	
	int entryCount = zip_entries_total(za);
	GfxCryptFile* files = (GfxCryptFile*)calloc(entryCount, sizeof(GfxCryptFile));
	if (files == NULL) {
		printf("Memory allocation error\n");
		return -1;
	}
	
	for (int i = 0; i < entryCount; i++) {
		files[i].data = NULL;
		zip_entry_openbyindex(za, i);
		const char* name = zip_entry_name(za);
		for (int j = 0; j < 256; j++) {
			files[i].name[j] = name[j];
			if (name[j] == 0) break;
		}
		if (zip_entry_isdir(za)) {
			files[i].isDir = 1;
			files[i].data = NULL;
			zip_entry_close(za);
			continue;
		}
		files[i].isDir = 0;
		if (zip_entry_read(za, &files[i].data, &files[i].size) < 0) {
			printf("Entry read error\n");
			return -1;
		}
		zip_entry_close(za);
	}
	zip_close(za);
	
	// Write
	za = zip_open("assets.dat", ZIP_DEFAULT_COMPRESSION_LEVEL, 'w');
	if (za == NULL) {
		printf("Failed to write assets.dat\n");
		return -1;
	}
	
	for (int i = 0; i < entryCount; i++) {
		if (files[i].isDir) continue;
		int c = 0;
		for (int j = 0; j < files[i].size; j++) {
			if (ASSETS_PASSWORD[c] == 0) break;
			((unsigned char*)files[i].data)[j] ^= ASSETS_PASSWORD[c++];
		}
		zip_entry_open(za, files[i].name);
		zip_entry_write(za, files[i].data, files[i].size);
		zip_entry_close(za);
		free(files[i].data);
	}
	
	zip_close(za);
	free(files);
	return 0;
}
