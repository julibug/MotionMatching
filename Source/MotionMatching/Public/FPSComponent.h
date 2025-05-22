// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSComponent.generated.h"

UCLASS()
class MOTIONMATCHING_API AFPSComponent : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AFPSComponent();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FPS Monitor")
    bool bEnableFPSLogging = true;

private:
    FString FilePath;

    void AppendFPSData(float FPS);

    float TimeSinceLastWrite = 0.f;
    float WriteInterval = 0.1f; // zapis co 0.1 sekundy
};
