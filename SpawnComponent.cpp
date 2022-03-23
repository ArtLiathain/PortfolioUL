// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnComponent.h"
#include <ctime>
#include <iostream>
#include <windows.h>
using namespace std;

// Sets default values for this component's properties
USpawnComponent::USpawnComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void USpawnComponent::BeginPlay()
{
	Super::BeginPlay();
	SpawnPlatformSize = SpawnPlatformSize/2;

	
    
	


	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	// declare vector of locations and type
	//declare vector of origins and type
	
	if(InputComponent)
	{
		srand(time(NULL));
		// UE_LOG(LogTemp, Warning, TEXT("Input component found"), *GetOwner()->GetName());
		//pass reference as argument
		InputComponent->BindAction("Spawn_Human", IE_Pressed, this, &USpawnComponent::SpawnHuman);
		InputComponent->BindAction("Spawn_Elf", IE_Pressed, this, &USpawnComponent::SpawnElf);
		InputComponent->BindAction("Spawn_Dwarf", IE_Pressed, this, &USpawnComponent::SpawnDwarf);
		InputComponent->BindAction("Spawn_Orc", IE_Pressed, this, &USpawnComponent::SpawnOrc);

	}
	
}

void USpawnComponent::SpawnHuman()
{
	TArray<float> temparray;
	float XValue, YValue;
	int bias1, bias2;
	if(rand()%HumanBias == 1)
	{
		bias1 = rand()%100+1;
		bias2 = rand()%100+1;
	}
	else 
	{
		bias1 = 200;
		bias2 = 200;
	}

	XValue = RandomXLocationCreator(true, bias1);
	YValue = RandomYLocationCreator(true, bias2);
	
	temparray.Add(XValue);
	temparray.Add(YValue);
	//push back evcotr
	Locations.Add(temparray);
	LocationChecker(0);
}

void USpawnComponent::SpawnElf()
{
	TArray<float> temparray1;
	float XValue, YValue;
	int bias1, bias2;
	if(rand()%ElfBias == 1)
	{
		bias1 = rand()%100 + 1;
		bias2 = rand()%100 + 1;
	}
	else 
	{
		bias1 = 200;
		bias2 = 200;
	}

	XValue = RandomXLocationCreator(false, bias1);
	YValue = RandomYLocationCreator(true, bias2);

	temparray1.Add(XValue);
	temparray1.Add(YValue);
	Locations.Add(temparray1);
	LocationChecker(1);
	
}

void USpawnComponent::SpawnDwarf()
{
	TArray<float> temparray2;
	float XValue, YValue;
	int bias1, bias2;
	if(rand()%DwarfBias == 1)
	{
		bias1 = rand()%100 + 1;
		bias2 = rand()%100 + 1;
	}
	else 
	{
		bias1 = 200;
		bias2 = 200;
	}

	XValue = RandomXLocationCreator(true, bias1);
	YValue = RandomYLocationCreator(false, bias2);

	temparray2.Add(XValue);
	temparray2.Add(YValue);
	Locations.Add(temparray2);
	LocationChecker(2);
}

void USpawnComponent::SpawnOrc()
{
	TArray<float> temparray3;
	float XValue, YValue;
	int bias1, bias2;
	if(rand()%OrcBias == 1)
	{
		bias1 = rand()%100+1;
		bias2 = rand()%100+1;
	}
	else 
	{
		bias1 = 200;
		bias2 = 200;
	}

	XValue = RandomXLocationCreator(false, bias1);
	YValue = RandomYLocationCreator(false, bias2);
	
	temparray3.Add(XValue);
	temparray3.Add(YValue);
	//push back evcotr
	Locations.Add(temparray3);
	LocationChecker(3);
}

float USpawnComponent::RandomXLocationCreator(bool XCoordMinus, int bias)
{
	float XValue = 0.f;
	int temp = rand();
	XValue = (SpawnPlatformSize - ((((temp%bias) + 1)*SpawnPlatformSize)/100));
	if(XCoordMinus)
	{
		XValue = XValue*-1;
	}
	
	return XValue;
}

float USpawnComponent::RandomYLocationCreator(bool YCoordMinus, int bias)
{
	float YValue = 0.f;
	int temp = rand();

	YValue = (SpawnPlatformSize - ((((temp%bias) + 1)*SpawnPlatformSize)/100));
	if(YCoordMinus)
	{
		YValue = YValue*-1;
	}

	return YValue;
}

void USpawnComponent::LocationChecker(float race)
{
	WrongOverlap = false;
	RightOverlap = false;
	float OverlapOrigin = 0;
	float WrongOverlapOrigin = 0;
	float WrongOverlapRace = 0;
	float OverlapPos = 0;
	int arraylenght = Locations.Num();
	float size = Locations[arraylenght-1][0];
	float size1 = Locations[arraylenght-1][1];	
	int templenght = Origins.Num();
	if (Locations.Num() == 1)
	{
		OriginAdder(0, race);
		LocationSpawner(race);
	}

	for (float i = 0; i < templenght; i++)
	{
		// itereate thtrough origins
		if (Origins[i][0] >= size-boxsize && Origins[i][0] <= size+boxsize && Origins[i][1] >= size1-boxsize && Origins[i][1] <= size1+boxsize && Origins[i][4] == 0)
		{	
			if(Origins[i][3] != race)
			{
				WrongOverlap = true;
				WrongOverlapOrigin = i;
				WrongOverlapRace = Origins[i][3];

			}
			else if(Origins[i][3] == race)
			{
				RightOverlap = true;
				OverlapOrigin = Origins[i][3];
			}

			//i is referencing the first origin in sequence to it

		}

		if(i == templenght-1 && WrongOverlap == false && RightOverlap == true)
		{
			OriginAdder(OverlapOrigin, race);
			LocationSpawner(race);
		}
		else if(i == templenght-1 && WrongOverlap == false && RightOverlap == false)
		{
			OriginAdder(i, race);
			LocationSpawner(race);
		}	

			//if it overlaps wrong race don't spawn
		else if(i == templenght-1 && WrongOverlap == true && RightOverlap == false)
		{
			float ActualWrongOrigin = OriginFinder(WrongOverlapOrigin, WrongOverlapRace);
			//delete the most recent mesh in that shape
			//get most recent shape added
			for(int h=templenght-1; h > 0; h--)
			{
				float test = OriginFinder(h, WrongOverlapRace);
				if(test == ActualWrongOrigin)
				{
					//delete actor using the actor array as reference
					//delete SpawnedActors[h]
					Origins[h][4] = 1;
					SpawnedActors[h]->Destroy();
					break;
				}
			}
		}

	}
}

void USpawnComponent::LocationSpawner(float race)
{
	float XValue = Origins[Origins.Num()-1][0];
	float YValue = Origins[Origins.Num()-1][1];
	FVector Location = FVector(XValue, YValue, 0.f);
	FRotator Rotation = FRotator(0.f, 0.f, 0.f);

	if(race == 0)
	{
		SpawnedActor = GetWorld()->SpawnActor<AActor>(HumanToSpawn, Location, Rotation);
		SpawnedActors.Add(SpawnedActor);
	}
	if(race == 1)
	{
		SpawnedActor = GetWorld()->SpawnActor<AActor>(ElfToSpawn, Location, Rotation);
		SpawnedActors.Add(SpawnedActor);
	}
	if(race == 2)
	{
		SpawnedActor = GetWorld()->SpawnActor<AActor>(DwarfToSpawn, Location, Rotation);
		SpawnedActors.Add(SpawnedActor);
	}

	if(race == 3)
	{
		SpawnedActor = GetWorld()->SpawnActor<AActor>(OrcToSpawn, Location, Rotation);
		SpawnedActors.Add(SpawnedActor);
	}
		
}

float USpawnComponent::OriginFinder(float pos, float race)
{	
	float temppos = Origins[pos][2];
	if(temppos != Origins[temppos][2] && race != Origins[temppos][3])
	{
		OriginFinder(temppos, race);
	}
	
	return temppos;

}

void USpawnComponent::OriginAdder(float pos, float race)
{
	int arraylenght = Locations.Num();
	Origins.Add({0,0,pos,race,0});
	int Originslenght = Origins.Num();
	for(int j = 0; j < 2; j++)
	{
		Origins[Originslenght-1][j] = Locations[arraylenght-1][j];
	}
}

void USpawnComponent::SpawnRandom()
{
	int random = rand()%4;
	UE_LOG(LogTemp, Warning, TEXT("Random: %i"), random)
	if(random == 0)
	{
		SpawnHuman();
	}
	
	else if(random == 1)
	{
		SpawnElf();
	}

	else if(random == 2)
	{
		SpawnDwarf();
	}

	else if(random == 3)
	{
		SpawnOrc();
	}

}
// Called every frame
void USpawnComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	SpawnRandom();
}

