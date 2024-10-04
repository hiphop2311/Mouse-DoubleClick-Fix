#include <windows.h>
#include <stdio.h>

// Configuration flags to apply filtering
int applyLeftClickFilter = 0;
int applyRightClickFilter = 0;

HHOOK mouseHook;
DWORD lastLeftClickTime = 0;  // Independent timer for left click
DWORD lastRightClickTime = 0; // Independent timer for right click
DWORD minClickInterval = 80;  // Minimum click interval (80 milliseconds)

LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0) {
        DWORD currentTime = GetTickCount();
        DWORD timeDiff;

        // Handle left mouse button
        if (wParam == WM_LBUTTONDOWN && applyLeftClickFilter) {
            timeDiff = currentTime - lastLeftClickTime;
            if (timeDiff <= minClickInterval) {
                printf("Left click rejected (too fast): %lu ms\n", timeDiff);
                return 1; // Block fast left-click
            } else {
                printf("Left click accepted: %lu ms\n", timeDiff);
                lastLeftClickTime = currentTime; // Update left click time
            }
        }
        // Handle right mouse button
        else if (wParam == WM_RBUTTONDOWN && applyRightClickFilter) {
            timeDiff = currentTime - lastRightClickTime;
            if (timeDiff <= minClickInterval) {
                printf("Right click rejected (too fast): %lu ms\n", timeDiff);
                return 1; // Block fast right-click
            } else {
                printf("Right click accepted: %lu ms\n", timeDiff);
                lastRightClickTime = currentTime; // Update right click time
            }
        }
        // Handle button release for both left and right
        else if (wParam == WM_LBUTTONUP) {
            printf("Left mouse button released.\n");
        } else if (wParam == WM_RBUTTONUP) {
            printf("Right mouse button released.\n");
        }
    }
    return CallNextHookEx(mouseHook, nCode, wParam, lParam); // Pass all other events
}

void askUserForClickFilter() {
    int choice;
    printf("Select which click(s) to apply the filter:\n");
    printf("1. Left Click only\n");
    printf("2. Right Click only\n");
    printf("3. Both Left and Right Clicks\n");
    printf("Enter your choice (1/2/3): ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            applyLeftClickFilter = 1;
            applyRightClickFilter = 0;
            printf("Filter applied to Left Click only.\n");
            break;
        case 2:
            applyLeftClickFilter = 0;
            applyRightClickFilter = 1;
            printf("Filter applied to Right Click only.\n");
            break;
        case 3:
            applyLeftClickFilter = 1;
            applyRightClickFilter = 1;
            printf("Filter applied to both Left and Right Clicks.\n");
            break;
        default:
            printf("Invalid choice. No filter applied.\n");
            applyLeftClickFilter = 0;
            applyRightClickFilter = 0;
            break;
    }
}

int main() {
    // Ask the user whether to filter left click, right click, or both
    askUserForClickFilter();

    // Set the mouse hook
    mouseHook = SetWindowsHookEx(WH_MOUSE_LL, MouseProc, NULL, 0);
    
    if (!mouseHook) {
        printf("Failed to install mouse hook!\n");
        return 1;
    }

    printf("Mouse hook installed. Press Ctrl+C to exit.\n");

    // Message loop to keep the program running and processing mouse events
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnhookWindowsHookEx(mouseHook);
    return 0;
}
