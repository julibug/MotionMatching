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
    MapName = FPaths::GetCleanFilename(MapName); // usuwa prefix typu "UEDPIE_0_"

    FilePath = FPaths::ProjectSavedDir() + "FPSData_" + AnimationSystemTag + "_" + Timestamp + ".csv";

    if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*FilePath))
    {
        FString Header = TEXT("Time,FPS\n");
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
    float CurrentTime = GetWorld()->GetTimeSeconds();
    FString DataLine = FString::Printf(TEXT("%.2f,%.1f\n"), CurrentTime, FPS);

    FFileHelper::SaveStringToFile(DataLine, *FilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), FILEWRITE_Append);
}

