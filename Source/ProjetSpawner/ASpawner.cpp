// Fill out your copyright notice in the Description page of Project Settings.


#include "ASpawner.h"

// Sets default values
AASpawner::AASpawner()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AASpawner::BeginPlay()
{
	Super::BeginPlay();
	
}
void AASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AASpawner::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

