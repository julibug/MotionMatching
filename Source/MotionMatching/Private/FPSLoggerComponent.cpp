// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSLoggerComponent.h"

// Sets default values
AFPSLoggerComponent::AFPSLoggerComponent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFPSLoggerComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPSLoggerComponent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

