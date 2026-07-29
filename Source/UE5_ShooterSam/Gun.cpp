// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"

#define LOG(x) UE_LOG(LogTemp, Display, TEXT(x))
#define LOG_WARNING(x) UE_LOG(LogTemp, Warning, TEXT(x))

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Root"));
	SetRootComponent(SceneRoot);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(SceneRoot);

	MuzzleFlashParticleSystem = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Muzzle Flash"));
	MuzzleFlashParticleSystem->SetupAttachment(SceneRoot);

}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();

	MuzzleFlashParticleSystem->Deactivate();
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::PullTrigger()
{
	//Activating Gun Muzzle Flash
	MuzzleFlashParticleSystem->Activate();

	//Play Shoot Sound
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), ShootSound, GetActorLocation());

	if (OwnerController) {
		//Getting Player View Location and Rotation to Set Line Trace Position
		FVector ViewPointLocation;
		FRotator ViewPointRotation;
		OwnerController->GetPlayerViewPoint(ViewPointLocation, ViewPointRotation);

		//Setting End location of Line Trace
		FVector EndLocation = ViewPointLocation + ViewPointRotation.Vector() * MaxRange;

		//Setting Off Line Trace To shoot At Objects In World
		FHitResult HitResult;
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);
		Params.AddIgnoredActor(GetOwner());
		bool IsHit = GetWorld()->LineTraceSingleByChannel(HitResult, ViewPointLocation, EndLocation, ECC_GameTraceChannel2, Params);

		//If Its a Successful Hit
		if (IsHit) {
			//Spawning Hit Particles at Ray Impact Point
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ImpactParticleSystem, HitResult.ImpactPoint, HitResult.ImpactPoint.Rotation(),(FVector)0.3F);
			
			//Play Impact Sound
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, GetActorLocation());

			//Getting Hit Actor To Apply Damage
			AActor* HitActor = HitResult.GetActor();
			if (HitActor) {
				//Applying Damage
				UGameplayStatics::ApplyDamage(HitActor, BulletDamage, OwnerController, this, UDamageType::StaticClass());
			}
		}
	}
}

