// Fill out your copyright notice in the Description page of Project Settings.
#include "FPSComponent.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "HAL/PlatformFilemanager.h"

// Sets default values
AFPSComponent::AFPSComponent()
{
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AFPSComponent::BeginPlay()
{
    Super::BeginPlay();

    if (!bEnableFPSLogging)
    {
        return;
    }

    FString Timestamp = FDateTime::Now().ToString(TEXT("%Y%m%d_%H%M%S"));
    FString MapName = GetWorld()->GetMapName();
    MapName = FPaths::GetCleanFilename(MapName);

    // Nowa czêœæ – Desktop folder
    FString UserProfile = FPlatformMisc::GetEnvironmentVariable(TEXT("USERPROFILE"));
    FString DesktopPath = FPaths::Combine(UserProfile, TEXT("Desktop/AnimationTest"));

    IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
    if (!PlatformFile.DirectoryExists(*DesktopPath))
    {
        PlatformFile.CreateDirectoryTree(*DesktopPath);
    }

    FString FileName = FString::Printf(TEXT("FPSData_%s_%s.csv"), *AnimationSystemTag, *Timestamp);
    FilePath = FPaths::Combine(DesktopPath, FileName);

    if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*FilePath))
    {
        FString Header = TEXT("FPS\n");
        FFileHelper::SaveStringToFile(Header, *FilePath);
    }
}

// Called every frame
void AFPSComponent::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!bEnableFPSLogging)
    {
        return; 
    }

    if (DeltaTime > 0.f)
    {
        TimeSinceLastWrite += DeltaTime;
        if (TimeSinceLastWrite >= WriteInterval)
        {
            float FPS = 1.f / DeltaTime;
            AppendFPSData(FPS);
            TimeSinceLastWrite = 0.f;
        }
    }
}

void AFPSComponent::AppendFPSData(float FPS)
{
    if (!GetWorld())
    {
        return;
    }
    int32 RoundedFPS = FMath::RoundToInt(FPS);

    FString DataLine = FString::Printf(TEXT("%d\n"), RoundedFPS);

    FFileHelper::SaveStringToFile(DataLine, *FilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), FILEWRITE_Append);
}

