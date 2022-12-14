// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SlAiPlayerCharacter.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Data/SlAiTypes.h"

// Sets default values
ASlAiPlayerCharacter::ASlAiPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//设置胶囊体的碰撞的碰撞为ProjectSettings→Collision→Preset中的自定义碰撞文件
	GetCapsuleComponent()->SetCollisionProfileName(FName("PlayerProfile"));

	//添加第一人称骨骼模型
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> StaticMeshFirst
		(TEXT("SkeletalMesh'/Game/Res/PolygonAdventure/Mannequin/FirstPlayer/SkMesh/FirstPlayer.FirstPlayer'"));
	MeshFirst = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshFirst"));
	if (StaticMeshFirst.Succeeded())
	{
		MeshFirst->SetSkeletalMesh(StaticMeshFirst.Object);
	}
	MeshFirst->SetupAttachment((USceneComponent*)GetCapsuleComponent());
	MeshFirst->bOnlyOwnerSee = true;
	MeshFirst->bCastDynamicShadow = false;
	MeshFirst->bReceivesDecals = false;
	//更新频率衰落
	MeshFirst->MeshComponentUpdateFlag = EMeshComponentUpdateFlag::OnlyTickPoseWhenRendered;
	MeshFirst->PrimaryComponentTick.TickGroup = TG_PrePhysics;
	//设置碰撞属性
	MeshFirst->SetCollisionObjectType(ECC_Pawn);
	MeshFirst->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshFirst->SetCollisionResponseToAllChannels(ECR_Ignore);
	//设置位移
	MeshFirst->SetRelativeLocation(FVector(0.f, 0.f, -95.f));
	MeshFirst->SetRelativeRotation(FQuat::MakeFromEuler(FVector(0.f, 0.f, -90.f)));

	//获取第一人称的动作蓝图
	static ConstructorHelpers::FClassFinder<UAnimInstance> StaticAnimFirst
		(TEXT("AnimBlueprint'/Game/Blueprint/Player/FirstPlayer_Animation.FirstPlayer_Animation_C'"));
	if (StaticAnimFirst.Succeeded())
	{
		MeshFirst->AnimClass = StaticAnimFirst.Class;
	}

	//给默认Mesh添加骨骼模型
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> StaticMeshThird
		(TEXT("SkeletalMesh'/Game/Res/PolygonAdventure/Mannequin/Player/SkMesh/Player.Player'"));
	if (StaticMeshThird.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(StaticMeshThird.Object);
	}
	GetMesh()->bOnlyOwnerSee = true;
	GetMesh()->bReceivesDecals = false;
	GetMesh()->SetCollisionObjectType(ECC_Pawn);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionResponseToAllChannels(ECR_Ignore);
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -95.f));
	GetMesh()->SetRelativeRotation(FQuat::MakeFromEuler(FVector(0.f, 0.f, -90.f)));
	
	
	//获取第三人称的动作蓝图
	static ConstructorHelpers::FClassFinder<UAnimInstance> StaticAnimThird
		(TEXT("AnimBlueprint'/Game/Blueprint/Player/ThirdPlayer_Animation.ThirdPlayer_Animation_C'"));
	if (StaticAnimThird.Succeeded())
	{
		GetMesh()->AnimClass = StaticAnimThird.Class;
	}


	//摄像机手臂
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	//设置距离
	CameraBoom->TargetArmLength = 300.f;
	//设置偏移
	CameraBoom->TargetOffset = FVector(0.f, 0.f, 60.f);
	//绑定Controller的旋转
	CameraBoom->bUsePawnControlRotation = true;

	//初始化第三人称相机
	ThirdCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ThirdCamera"));
	ThirdCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	//设置ThirdCamera不跟随控制器的旋转
	ThirdCamera->bUsePawnControlRotation = false;

	//初始化第一人称摄像机
	FirstCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstCamera"));
	FirstCamera->SetupAttachment((USceneComponent*)GetCapsuleComponent());
	//设置跟随Controller的旋转
	FirstCamera->bUsePawnControlRotation = true;
	//设置偏移
	FirstCamera->AddLocalOffset(FVector(0.f, 0.f, 60.f));

	//默认第三人称
	FirstCamera->SetActive(false);
	ThirdCamera->SetActive(true);
	//不显示第一人称模型
	GetMesh()->SetOwnerNoSee(false);
	MeshFirst->SetOwnerNoSee(true);

	//初始化参数
	BaseTurnRate = 45.f;
	BaseTurnRate = 45.f;
	//设置初始速度为150
	GetCharacterMovement()->MaxWalkSpeed = 150.f;
	//初始为第三人称
	GameView = EGameViewMode::Third;
	//上半身动作初始为无动作
	UpperType = EUpperBody::None;
	//一开始允许切换视角
	IsAllowSwitch = true;
}

// Called when the game starts or when spawned
void ASlAiPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASlAiPlayerCharacter::MoveForward(float Value)
{
	if (Value != 0.f && Controller)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ASlAiPlayerCharacter::MoveRight(float Value)
{
	if (Value != 0.f)
	{
		const FQuat Rotation = GetActorQuat();
		FVector Direction = FQuatRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void ASlAiPlayerCharacter::LoopupAtRate(float Value)
{
	AddControllerPitchInput(Value * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ASlAiPlayerCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void ASlAiPlayerCharacter::TurnAtRate(float Value)
{
	AddControllerYawInput(Value * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ASlAiPlayerCharacter::OnStartJump()
{

}

void ASlAiPlayerCharacter::OnStopJump()
{

}

void ASlAiPlayerCharacter::OnStartRun()
{

}

void ASlAiPlayerCharacter::OnStopRun()
{

}

// Called every frame
void ASlAiPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASlAiPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASlAiPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASlAiPlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ASlAiPlayerCharacter::LoopupAtRate);
	PlayerInputComponent->BindAxis("TurnRate", this, &ASlAiPlayerCharacter::TurnAtRate);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASlAiPlayerCharacter::OnStartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ASlAiPlayerCharacter::OnStopJump);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ASlAiPlayerCharacter::OnStartRun);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ASlAiPlayerCharacter::OnStopRun);
}

void ASlAiPlayerCharacter::ChangeView(EGameViewMode::Type NewGameView)
{
	GameView = NewGameView;
	switch (GameView)
	{
	case EGameViewMode::First:
		FirstCamera->SetActive(true);
		ThirdCamera->SetActive(false);
		MeshFirst->SetOwnerNoSee(false);
		GetMesh()->SetOwnerNoSee(true);
		break;
	case EGameViewMode::Third:
		FirstCamera->SetActive(false);
		ThirdCamera->SetActive(true);
		MeshFirst->SetOwnerNoSee(true);
		GetMesh()->SetOwnerNoSee(false);
		break;
	}
}

