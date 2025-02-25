#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int screenWidth;
	int screenHeight;
	int monitorFPS;
	bool showFPS;
	bool useVSync;
} AppConfig;

void SaveConfig(const char *filename, AppConfig config);
AppConfig LoadConfig(const char *filename);

AppConfig LoadConfig(const char *filename) {
	AppConfig config = {
		// Default settings
		800,  // screen width
		450,  // screen height
		true, // monitor refresh rate
		true, // show FPS
		true  // use VSync
	};

	FILE *file = fopen(filename, "r");
	if (file == NULL) {
		printf("Config file not found, creating with default settings.\n");
		SaveConfig(filename, config);
		return config;
	}

	char line[128];
	char key[64];
	char value[64];
	while (fgets(line, sizeof(line), file)) {
		if (line[0] == '#' || line[0] == '\n') continue; // Skip comments and empty lines

		if (sscanf(line, "%[^=]=%[^\n]", key, value) == 2) {
			// Remove whitespace
			char *k = key;
			while (*k == ' ')
				k++;
			char *v = value;
			while (*v == ' ')
				v++;

			// Remove trailing spaces from key
			char *end = k + strlen(k) - 1;
			while (end > k && *end == ' ') {
				*end = '\0';
				end--;
			}

			if (strcmp(k, "screenWidth") == 0)
				config.screenWidth = atoi(v);
			else if (strcmp(k, "screenHeight") == 0)
				config.screenHeight = atoi(v);
			else if (strcmp(k, "monitorFPS") == 0)
				config.monitorFPS = (strcmp(v, "true") == 0);
			else if (strcmp(k, "showFPS") == 0)
				config.showFPS = (strcmp(v, "true") == 0);
			else if (strcmp(k, "useVSync") == 0)
				config.useVSync = (strcmp(v, "true") == 0);
		}
	}
	fclose(file);

	return config;
}

void SaveConfig(const char *filename, AppConfig config) {
	FILE *file = fopen(filename, "w");
	if (file == NULL) {
		printf("Error: Could not create config file.\n");
		return;
	}

	fprintf(file, "screenWidth=%d\n", config.screenWidth);
	fprintf(file, "screenHeight=%d\n", config.screenHeight);
	fprintf(file, "monitorFPS=%s\n", config.monitorFPS ? "true" : "false");
	fprintf(file, "showFPS=%s\n", config.showFPS ? "true" : "false");
	fprintf(file, "useVSync=%s\n", config.useVSync ? "true" : "false");

	fclose(file);
}

int main(void) {
	AppConfig config = LoadConfig("config.ini");

	InitWindow(config.screenWidth, config.screenHeight, "FiscAtal");

	int monitorRefreshRate = GetMonitorRefreshRate(GetCurrentMonitor());
	printf("Monitor refresh rate: %d Hz\n", monitorRefreshRate);

	if (config.useVSync) {
		SetTargetFPS(0);				 // 0 means unlimited FPS, but VSync will cap it
		SetWindowState(FLAG_VSYNC_HINT); // Enable VSync
		printf("Using VSync: ON (monitor refresh rate: %d Hz)\n", monitorRefreshRate);
	} else if (!config.monitorFPS) {
		SetTargetFPS(0); // 0 means unlimited FPS
	} else {
		SetTargetFPS(monitorRefreshRate);
		printf("Using fixed refresh rate: %d Hz (VSync: OFF)\n", monitorRefreshRate);
	}

	// Main game loop
	while (!WindowShouldClose()) {
		BeginDrawing();

		ClearBackground(RAYWHITE);

		if (config.useVSync) {
			DrawText(TextFormat("VSync: ON (%d Hz)", monitorRefreshRate), 190, 180, 20, LIGHTGRAY);
		} else {
			DrawText(TextFormat("Fixed FPS: %d Hz", monitorRefreshRate), 190, 180, 20, LIGHTGRAY);
		}

		if (config.showFPS) {
			DrawFPS(config.screenWidth - 90, 10);
		}

		EndDrawing();
	}

	CloseWindow();

	return 0;
}
