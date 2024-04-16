#include "X11Interface.h"

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>

#include "Misc/StringBuilder.h"
#include "Misc/Parse.h"

#include "HAL/UnrealMemory.h"

TArray<FX11WindowDetails> X11Interface::GetWindowList() {
    TArray<FX11WindowDetails> window_details;

    FString buffer;
    FString errors;
    int32 return_code;

    // FString command = FString( );
    FPlatformProcess::ExecProcess(TEXT("/usr/bin/wmctrl"), TEXT("-lpG"), &return_code, &buffer, &errors);

    if (return_code != 0) {
        UE_LOG(LogTemp, Error, TEXT("wmctrl command failed with return code %d. Errors: %s"), return_code, *errors);
        return window_details;
    }

    if (buffer.IsEmpty()) {
        UE_LOG(LogTemp, Error, TEXT("wmctrl command output is empty"));
        return window_details;
    }

    TArray<FString> Lines;
    const int32 nArraySize = buffer.ParseIntoArray(Lines, TEXT("\n"), true);
    for (const FString& Line : Lines) {
        TArray<FString> Stats;
        Line.ParseIntoArray(Stats, TEXT(" "), true);
        FX11WindowDetails X11Window;
        X11Window.WindowID = FParse::HexNumber(*Stats[0]);
        X11Window.X = FCString::Atoi(*Stats[3]);
        X11Window.Y = FCString::Atoi(*Stats[4]);
        X11Window.Width = FCString::Atoi(*Stats[5]);
        X11Window.Height = FCString::Atoi(*Stats[6]);
        // TODO: WindowName is everything after 8th space...
        // X11Window.WindowName = Stats[8];
        for (int n = 8; n < Stats.Num(); n++)
        {
            if (n != 8)
            {
                X11Window.WindowName += " ";
            }
            X11Window.WindowName += Stats[n];
        }
        window_details.Add(X11Window);
    }

    // FILE* pipe = popen("wmctrl -lpG", "r");
    // char buffer[128];
    // while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
    //     FString Line(buffer);
    //     TArray<FString> Stats;
    //     Line.ParseIntoArray(Stats, TEXT(" "), true);
    //     FX11WindowDetails X11Window;
    //     X11Window.WindowID = FParse::HexNumber(*Stats[0]);
    //     X11Window.X = FCString::Atoi(*Stats[3]);
    //     X11Window.Y = FCString::Atoi(*Stats[4]);
    //     X11Window.Width = FCString::Atoi(*Stats[5]);
    //     X11Window.Height = FCString::Atoi(*Stats[6]);
    //     X11Window.WindowName = Stats[8];
    //     window_details.Add(X11Window);
    // }
    // int status = pclose(pipe);

    return window_details;
}


void X11Interface::GetWindowPixels(unsigned long target_window_id, uint8*& buffer, unsigned int *width, unsigned int *height, unsigned int *depth) {
    // TODO: Multithreaded (check the MediaTexture or WmfMedia to see how it streams the texture...)
    // TArray<FColor> pixels;
    
    Display *display = XOpenDisplay(NULL);
    Window window = XDefaultRootWindow(display);
    int screen = DefaultScreen(display);
    Colormap defaultColormap = XDefaultColormap(display, screen);
    Window target_window = static_cast<Window>(target_window_id);

    // TODO: If target_window is not valid, then return...

    XWindowAttributes attributes;
    if (XGetWindowAttributes(display, target_window, &attributes) == 0) {
        fprintf(stderr, "Failed to get window attributes\n");
        return;
        // return pixels;
    }

    XSetWindowAttributes attrs;
    attrs.backing_store = Always;
    XChangeWindowAttributes(display, target_window, CWBackingStore, &attrs);
    XMapWindow(display, target_window);

    XGetWindowAttributes(display, target_window, &attributes);
    *width = attributes.width;
    *height = attributes.height;
    if (!buffer)
    {
        buffer = new uint8[attributes.width * attributes.height * 4];
    }

    Visual *visual = DefaultVisual(display, DefaultScreen(display));
    bool isTrueColor = (visual->c_class == TrueColor && visual->red_mask == 0xff0000 && visual->green_mask == 0x00ff00 && visual->blue_mask == 0x0000ff);
    *depth = (isTrueColor) ? 3 : 1;

    if (isTrueColor) {
        XImage *img = XGetImage(display, target_window, 0, 0, *width, *height, AllPlanes, ZPixmap);
        for (unsigned int y = 0; y < *height; y++) {
            for (unsigned int x = 0; x < *width; x++) {
                unsigned long pixel_value = XGetPixel(img, x, y);
                unsigned char red = (pixel_value & visual->red_mask) >> 16;
                unsigned char green = (pixel_value & visual->green_mask) >> 8;
                unsigned char blue = (pixel_value & visual->blue_mask);
                buffer[(x + y * (*width)) * 4] = blue;
                buffer[(x + y * (*width)) * 4 + 1] = green;
                buffer[(x + y * (*width)) * 4 + 2] = red;
                buffer[(x + y * (*width)) * 4 + 3] = 255;
                // pixels.Add(FColor(red, green, blue, 255));
            }
        }
        XDestroyImage(img);
    }
    XCloseDisplay(display);
}