
// Fill out your copyright notice in the Description page of Project Settings.


#include "cpp_Spaceship.h"

// Sets default values
Acpp_Spaceship::Acpp_Spaceship()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->forwardGears = 5;
	this->backwardGears = 2;
	this->actualGear = 0;
	this->maxSpeed = 2;
	this->shipMass = 1;

	this->maxEnergyVector = this->shipMass * this->maxSpeed * this->maxSpeed * 0.5;

	this->reverseThrusterPower = 2;
	this->forwardThrusterPower = 10;
	this->rotationThrusterPower = 0.5;
	this->velocityVector = { 0,0,0 };
	this->energyVector = { 0,0,0 };
	this->fluidDensity = 1.225; //density of air
	this->dragFactor = 2.05;//drag factor of square
}

// Called when the game starts or when spawned
void Acpp_Spaceship::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void Acpp_Spaceship::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void Acpp_Spaceship::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void Acpp_Spaceship::gearUp()
{
	if (this->actualGear < this->forwardGears)this->actualGear++;
}

void Acpp_Spaceship::gearDown()
{
	if (this->actualGear > 0 || this->actualGear > (-1 * this->backwardGears))this->actualGear--;
}

void Acpp_Spaceship::stop()
{
	this->actualGear = 0;
}

void Acpp_Spaceship::addEnergy(UPARAM(ref) float deltaTime, UPARAM(ref) float actorRotation)
{
	FVector deltaEnergyVector = {};

	if (this->actualGear == 0)return;
	if (this->actualGear > 0)
	{
		deltaEnergyVector = { this->forwardThrusterPower * deltaTime * ((float)this->actualGear / (float)this->forwardGears),0,0 };
	}
	else if (this->actualGear < 0)
	{
		deltaEnergyVector = { this->forwardThrusterPower * deltaTime * ((float)this->actualGear / (float)this->backwardGears),0,0 };
	}

	deltaEnergyVector = deltaEnergyVector.RotateAngleAxis(actorRotation, FVector(0, 0, 1));
	this->energyVector += deltaEnergyVector;

	if (this->energyVector.Size() > this->maxEnergyVector)
	{
		this->energyVector.Normalize();
		this->energyVector *= this->maxEnergyVector;
	}
}

void Acpp_Spaceship::calculateVelocityVector(UPARAM(ref) float actorRotation)
{
	this->velocityVector = this->energyVector;
	this->velocityVector = (this->energyVector * 2) / this->shipMass;

	/*this->velocityVector = FVector( (this->energyVector.Size() * 2) / this->shipMass ,0,0);
	this->velocityVector = this->velocityVector.RotateAngleAxis(actorRotation, FVector(0, 0, 1));*/
}

void Acpp_Spaceship::calculateDragForce(UPARAM(ref) float velocity)
{
	this->dragForce = 0.5 * this->fluidDensity * pow(velocity, 2) * this->dragFactor * 1;
}

void Acpp_Spaceship::calculateDragVector(UPARAM(ref) float deltaTime)
{
	this->dragVector = this->energyVector;
	this->dragVector.Normalize();
	this->dragVector *= this->dragForce * deltaTime * -1;
}

int Acpp_Spaceship::determineTurnDirection(UPARAM(ref) float actualAngle, UPARAM(ref) float targetAngle)
{
	//https://math.stackexchange.com/questions/110080/shortest-way-to-achieve-target-angle/2898118
	float t = (targetAngle + 180);
	float c = (actualAngle + 180);
	float a = t - c;
	float b = t - c + 360;
	float y = t - c - 360;

	if (abs(a) < abs(b))
	{
		if (abs(a) < abs(y))
		{
			if (a < 0)return -1;
			else return 1;
		}
		else
		{
			if (y < 0)return -1;
			else return 1;
		}
	}
	else
	{
		if (abs(b) < abs(y))
		{
			if (b < 0)return -1;
			else return 1;
		}
		else
		{
			if (b < 0)return -1;
			else return 1;
		}
	}
}

void Acpp_Spaceship::collisiohnHit()
{
	float energy = this->energyVector.Size();

	this->energyVector.RotateAngleAxis(180, FVector(0, 0, 1));
}

void Acpp_Spaceship::setMaxSpeed(UPARAM(ref) float newSpeed)
{
	this->maxSpeed = newSpeed;
	this->maxEnergyVector = this->shipMass * this->maxSpeed * this->maxSpeed * 0.5;
}