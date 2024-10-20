// DiscordRPC.c
#include "DiscordRPC.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // For sleep function on Unix systems

// Callback functions for Discord events
void handleDiscordReady(const char* applicationId) {
    printf("Discord is ready!\n");
}

void handleDiscordDisconnected(int code, const char* message) {
    printf("Disconnected from Discord: %s (code: %d)\n", message, code);
}

void handleDiscordError(int code, const char* message) {
    printf("Discord error: %s (code: %d)\n", message, code);
}

// Function to initialize Discord Rich Presence
void initDiscordRPC() {
    DiscordEventHandlers handlers;
    memset(&handlers, 0, sizeof(handlers));

    handlers.ready = handleDiscordReady;
    handlers.disconnected = handleDiscordDisconnected;
    handlers.errored = handleDiscordError;

    // Initialize Discord with your application's ID
    Discord_Initialize("YOUR_APPLICATION_ID", &handlers, 1, NULL);
}

// Function to update Discord Rich Presence
void updateDiscordRPC(const char* state, const char* details) {
    DiscordRichPresence presence;
    memset(&presence, 0, sizeof(presence));

    presence.state = state;            // e.g., "In Game"
    presence.details = details;        // e.g., "Playing a match"
    presence.largeImageKey = "chess";  // Key for the large image (must be set in Discord developer portal)
    presence.largeImageText = "Chess Game"; // Text for large image
    presence.smallImageKey = "playing"; // Key for the small image
    presence.smallImageText = "Playing"; // Text for small image
    presence.startTimestamp = time(NULL); // Start time of the activity

    Discord_UpdatePresence(&presence); // Update Discord presence
}

// Main loop to keep the Discord RPC active
void runDiscordRPCLoop() {
    while (1) {
        Discord_RunCallbacks(); // Keep Discord connected
        // Here, you could check the game state and update accordingly
        updateDiscordRPC("In Game", "Playing a match"); // Example update
        sleep(15); // Update every 15 seconds (adjust as needed)
    }
}

// Clean up Discord on exit
void cleanupDiscordRPC() {
    Discord_Shutdown(); // Shutdown the Discord connection
}


#include <stdio.h>
#include "DiscordRPC.h"

int main() {
    initDiscordRPC(); // Initialize Discord RPC

    // Run the main application loop
    runDiscordRPCLoop(); // This can run in its own thread or main loop

    cleanupDiscordRPC(); // Clean up on exit
    return 0;
}
