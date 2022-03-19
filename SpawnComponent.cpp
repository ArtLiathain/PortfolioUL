// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnComponent.h"
#include <ctime>
#include <iostream>
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

	}
	
}

void USpawnComponent::SpawnHuman()
{
	float XValue = 0.f;
	float YValue = 0.f;
	//temp vector
	TArray<float> temparray;
	for(int i = 1; i <= 2; i++)
	{
		if(i == 1)
		{
			XValue = (((rand()%100*5900)/100)-2950);
			temparray.Add(XValue);
		}
		if(i == 2)
		{
			YValue = (((rand()%100*5900)/100)-2950);
			temparray.Add(YValue);
		}
	}
	//push back evcotr
	Locations.Add(temparray);
	LocationChecker(0);
		//return locatoin as part of the vector
}

void USpawnComponent::SpawnElf()
{
	float XValue = 0.f;
	float YValue = 0.f;
	TArray<float> temparray1;
	for(int i = 1; i <= 2; i++)
	{
		if(i == 1)
		{
			XValue = (((rand()%100*5900)/100)-2950);
			temparray1.Add(XValue);
		}
		if(i == 2)
		{
			YValue = (((rand()%100*5900)/100)-2950);
			temparray1.Add(YValue);
		}
	}	
	Locations.Add(temparray1);
	// UE_LOG(LogTemp, Warning, TEXT("Array: %f"), Locations[1][0]);

	LocationChecker(1);
	
}

void USpawnComponent::SpawnDwarf()
{
	float XValue = 0.f;
	float YValue = 0.f;
	TArray<float> temparray2;
	for(int i = 1; i <= 2; i++)
	{
		if(i == 1)
		{
			XValue = (((rand()%100*5900)/100)-2950);
			temparray2.Add(XValue);
		}
		if(i == 2)
		{
			YValue = (((rand()%100*5900)/100)-2950);
			temparray2.Add(YValue);
		}
	}
	Locations.Add(temparray2);
	LocationChecker(2);

	// UE_LOG(LogTemp, Warning, TEXT("Array: %f"), Locations[2][0]);
}

void USpawnComponent::LocationChecker(float race)
{
	WrongOverlap = false;
	RightOverlap = false;
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
		if (Origins[i][0] >= size-boxsize && Origins[i][0] <= size+boxsize && Origins[i][1] >= size1-boxsize && Origins[i][1] <= size1+boxsize)
		{	
			if(Origins[i][3] != race)
			{
				WrongOverlap = true;
			}
			else if(Origins[i][3] == race)
			{
				RightOverlap = true;
			}

			//i is referencing the first origin in sequence to it

		}

		if(i == templenght-1 && WrongOverlap == false && RightOverlap == true)
		{
			UE_LOG(LogTemp, Error, TEXT("Overlaps same type"))
			OriginAdder(0, race);
			LocationSpawner(race);
		}
		if(i == templenght-1 && WrongOverlap == false && RightOverlap == false)
		{
			UE_LOG(LogTemp, Warning, TEXT("No Overlaps"))
			OriginAdder(0, race);
			LocationSpawner(race);
			//home location == 0
		}	

			//if it overlaps wrong race don't spawn
		if(i == templenght-1 && race == 0 && WrongOverlap == true)
		{
			UE_LOG(LogTemp, Warning, TEXT("Human try again"));
			if(count < 11)
			{
				SpawnHuman();
				count = 0;
			}
			count++;
		}

		if(i == templenght-1 && race == 1 && WrongOverlap == true)
		{
			UE_LOG(LogTemp, Warning, TEXT("Elf try again"));
			if(count < 11)
			{
				SpawnElf();
				count = 0;
			}
			count++;
		}

		if(i == templenght-1 && race == 2 && WrongOverlap == true)
		{
			UE_LOG(LogTemp, Warning, TEXT("Dwarf try again"));
			if(count < 11)
			{
				SpawnDwarf();
				count = 0;
			}
			count++;
		}

	}
}

void USpawnComponent::OverlapDeleter()
{

}

void USpawnComponent::LocationSpawner(float race)
{
	float XValue = Origins[Origins.Num()-1][0];
	float YValue = Origins[Origins.Num()-1][1];
	FVector Location = FVector(XValue, YValue, 0.f);
	FRotator Rotation = FRotator(0.f, 0.f, 0.f);

	if(race == 0)
	{
		GetWorld()->SpawnActor<AActor>(HumanToSpawn, Location, Rotation);
	}
	if(race == 1)
	{
		GetWorld()->SpawnActor<AActor>(ElfToSpawn, Location, Rotation);
	}
	if(race == 2)
	{
		GetWorld()->SpawnActor<AActor>(DwarfToSpawn, Location, Rotation);
	}
}

void USpawnComponent::OriginAdder(float pos, float race)
{
	int arraylenght = Locations.Num();
	Origins.Add({0,0,pos,race});
	int Originslenght = Origins.Num();
	for(int j = 0; j < 2; j++)
	{
		Origins[Originslenght-1][j] = Locations[arraylenght-1][j];
	}
}
// Called every frame
void USpawnComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

