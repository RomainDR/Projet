// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>


#include "ACharacter.generated.h"


#pragma region Utils
#define DRAW_SPHERE(from, radius, segment, color, size) DrawDebugSphere(GetWorld(), from, radius, segment, color, false, -1, 0, size);
#define DRAW_LINE(from, to, color, size) DrawDebugLine(GetWorld(), from, to, color, false, -1, 0, size);
#define DRAW_TEXT(from, text, color, size) DrawDebugString(GetWorld(), from, text, 0, color, -1, false, size);
#pragma endregion Utils

UCLASS()
class PROJETSPAWNER_API AACharacter : public ACharacter
{
	GENERATED_BODY()


		UPROPERTY(EditAnywhere)
		TObjectPtr<USpringArmComponent> arm = nullptr;
		UPROPERTY(EditAnywhere)
		TObjectPtr<UCameraComponent> camera = nullptr;

		UPROPERTY(EditAnywhere)
			TArray<FVector> pathFinding;

		UPROPERTY(VisibleAnywhere)
			int pathPointNumber = -1;

		TObjectPtr<class ASpawner> spawner;

		bool isControlled = false;

		UPROPERTY(EditAnywhere, meta = (UIMin = 1, ClampMin = 1))
		float speed = 1.0f;

public:
	AACharacter();

	UFUNCTION(BlueprintCallable) bool IsPossess();
	UFUNCTION(BlueprintCallable) void SetSpeedWalk(float _speed);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float _axis);
	void Rotate(float _axis);

	void ShowDebug();

public:
	UFUNCTION(BlueprintCallable) void MoveToNextPath();



};
