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

	int count = 0;
	bool WrongOverlap;
	bool RightOverlap;
	TArray<TArray<float>> Locations;
	TArray<TArray<float>> Origins;

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
	TSubclassOf<AActor> ElfToSpawn;

	UPROPERTY(EDITANYWHERE, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> DwarfToSpawn;

	UPROPERTY(EDITANYWHERE, meta = (AllowPrivateAccess = "true"))
	int boxsize;

	void SpawnElf();
	void SpawnHuman();
	void SpawnDwarf();
	void LocationChecker(float race);
	void OverlapDeleter();
	void LocationSpawner(float race);
	void OriginAdder(float pos, float race);
};
