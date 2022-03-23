// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpawnComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WORLDBUILDER_API USpawnComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpawnComponent();

	bool WrongOverlap;
	bool RightOverlap;
	float HumanBaseCount = 1;
	float ElfBaseCount;
	float DwarfBaseCount;
	AActor* SpawnedActor;

	TArray<TArray<float>> Locations;
	TArray<TArray<float>> Origins;
	TArray<AActor*> SpawnedActors;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UInputComponent* InputComponent = nullptr;
	UPROPERTY(EDITANYWHERE, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> HumanToSpawn;

	UPROPERTY(EDITANYWHERE, meta = (AllowPrivateAccess = "true"))
	int HumanBias;

	UPROPERTY(EDITANYWHERE, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> ElfToSpawn;

	UPROPERTY(EDITANYWHERE, meta = (AllowPrivateAccess = "true"))
	int ElfBias;

	UPROPERTY(EDITANYWHERE, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> DwarfToSpawn;

	UPROPERTY(EDITANYWHERE, meta = (AllowPrivateAccess = "true"))
	int DwarfBias;

	UPROPERTY(EDITANYWHERE, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> OrcToSpawn;

	UPROPERTY(EDITANYWHERE, meta = (AllowPrivateAccess = "true"))
	int OrcBias;

	UPROPERTY(EDITANYWHERE, meta = (AllowPrivateAccess = "true"))
	int boxsize;

	UPROPERTY(EDITANYWHERE, meta = (AllowPrivateAccess = "true"))
	int SpawnPlatformSize;

	void SpawnElf();
	void SpawnHuman();
	void SpawnDwarf();
	void SpawnOrc();
	void LocationChecker(float race);
	void LocationSpawner(float race);
	void OriginAdder(float pos, float race);
	float OriginFinder(float pos, float race);
	float RandomXLocationCreator(bool XCoordMinus, int bias);
	float RandomYLocationCreator(bool YCoordMinus, int bias);
	void SpawnRandom();
};
