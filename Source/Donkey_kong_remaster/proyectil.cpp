// Fill out your copyright notice in the Description page of Project Settings.


#include "proyectil.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"
// Sets default values
Aproyectil::Aproyectil()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;



	// Carga estática del mesh para el proyectil
  // Utiliza FObjectFinder para buscar y cargar el asset del mesh para el proyectil
	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		ProjectileMeshAsset(TEXT("StaticMesh'/Game/Meshes/Projectile.Projectile'"));

	proyectilMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh0"));
	proyectilMesh->SetStaticMesh(ProjectileMeshAsset.Object);

	InitialLifeSpan = 3.0f;
	vel = 1000;
}

void Aproyectil::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 20.0f, GetActorLocation());

		/*Destroy();*/
	}
}

// Called when the game starts or when spawned
void Aproyectil::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void Aproyectil::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Mover(DeltaTime);
}

void Aproyectil::Mover(float DeltaTime)
{
	FVector NewLocation = GetActorLocation() + GetActorForwardVector() * vel * GetWorld()->GetDeltaSeconds();
	//FVector NewLocation = GetActorLocation() + FVector(0.0f, -vel, 0.0f) * DeltaTime;
	SetActorLocation(NewLocation);
}