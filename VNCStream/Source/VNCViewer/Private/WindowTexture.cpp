// WindowTexture.cpp
#include "WindowTexture.h"

#include "TextureResource.h"
#include "RenderUtils.h"
#include "Engine.h"
#include "Rendering/Texture2DResource.h"

#include "X11Interface.h"

void UWindowTexture::SetupX11WindowTexture(int WindowID)
{
    // if (GEngine)
    // {
    //     GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Window Texture Create Transient!"));
    // }
    X11Interface X11;
    unsigned int Width;
    unsigned int Height;
    unsigned int Depth;
    X11.GetWindowPixels(WindowID, Buffer, &Width, &Height, &Depth);

    // Create a new texture object
    Texture = UTexture2D::CreateTransient(Width, Height, PF_B8G8R8A8);

    if (Texture != nullptr)
    {
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Window Texture Set MipData!"));
        }
        // Texture->MipGenSettings = TMGS_NoMipmaps;
        Texture->Filter = TF_Nearest; // Set the texture filter to nearest-neighbor

        FColor* Pixels = static_cast<FColor*>(Texture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE));

        // Checkerboard test
        // const int32 SquareSize = 16; // Adjust this value to change the size of the checkerboard pattern

        // for (int32 y = 0; y < Height; ++y)
        // {
        //     for (int32 x = 0; x < Width; ++x)
        //     {
        //         if (((x / SquareSize) + (y / SquareSize)) % 2 == 0)
        //         {
        //             // Set to blue
        //             Pixels[x + y * Width] = FColor(0, 0, 255, 255);
        //         }
        //         else
        //         {
        //             // Set to red
        //             Pixels[x + y * Width] = FColor(255, 0, 0, 255);
        //         }
        //     }
        // }
        // ----

        for (int32 y = 0; y < Height; y++)
        {
            for (int32 x = 0; x < Width; x++)
            {
                Pixels[x + y * Width] = FColor(Buffer[(x + y * Width) * 4], Buffer[(x + y * Width) * 4 + 1], Buffer[(x + y * Width) * 4 + 2], Buffer[(x + y * Width) * 4 + 3]);
            }
        }

        Texture->PlatformData->Mips[0].BulkData.Unlock();
        Texture->UpdateResource();
        Texture->RefreshSamplerStates();
    }

}

void UWindowTexture::UpdateX11WindowTexture(int WindowID)
{
    X11Interface X11;
    unsigned int Width;
    unsigned int Height;
    unsigned int Depth;
    // TArray<FColor> WindowPixels = 
    X11.GetWindowPixels(WindowID, Buffer, &Width, &Height, &Depth);

    if (Texture != nullptr)
    {

        UTexture2D* CurrentTexture = this->Texture;
        uint8* CurrentBuffer = this->Buffer;

        ENQUEUE_RENDER_COMMAND(ThornfieldX11_UpdateWindowTexture)(
            [Width, Height, CurrentTexture, CurrentBuffer](FRHICommandList& RHICmdList)
            {
                FUpdateTextureRegion2D Region;
                Region.SrcX = 0;
                Region.SrcY = 0;
                Region.DestX = 0;
                Region.DestY = 0;
                Region.Width = Width;
                Region.Height = Height;
                FTexture2DResource* Resource = (FTexture2DResource*)CurrentTexture->Resource;
                // TRefCountPtr<FRHITexture2D>
                RHIUpdateTexture2D(Resource->GetTexture2DRHI(), 0, Region, Region.Width * 4, (const uint8*)CurrentBuffer);
            }
        );
    }

}

TArray<FX11WindowDetails> UWindowTexture::GetWindowList()
{
    X11Interface X11;
    return X11.GetWindowList();
}
