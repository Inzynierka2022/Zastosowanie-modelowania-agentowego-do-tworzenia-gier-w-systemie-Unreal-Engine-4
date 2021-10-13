// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "cpp_Spaceship.generated.h"

UCLASS()
class PRACAINZYNIERSKA_API Acpp_Spaceship : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	Acpp_Spaceship();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
