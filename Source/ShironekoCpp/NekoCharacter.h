// ==================================================
// Filename	:	NekoCharacter.h
// Author	:	22cu0214 JinWener
// Description:	This file implements the player character as part of the BP_NekoCharacter.
// Notes		:	This file includes the following as dependencies:
//				- NekoHUD.h/cpp
//				- NekoOverlay.h/cpp
//				- NekoMapUIComponent.h/cpp
//				- NekoComponentInteract.h/cpp
//				QuestLogComponent will be implemented in BP.
// ==================================================
// ==================================================
// ファイル名: NekoCharacter.h
// 作成者: 22cu0214 JinWener
// 説明: このファイルはBP_NekoCharacterの一部としてプレイヤーキャラクターを実装します。
// 備考: このファイルには、以下の依存関係が含まれます:
//        - NekoHUD.h/cpp
//        - NekoOverlay.h/cpp
//        - NekoMapUIComponent.h/cpp
//        - NekoComponentInteract.h/cpp
//        QuestLogComponentはBPで実装されます。
// ==================================================
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NekoCharacter.generated.h"

UCLASS()
class SHIRONEKOCPP_API ANekoCharacter : public ACharacter
{
	GENERATED_BODY()

	///////////////////////////
	//Override functions
public:
	ANekoCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
protected:
	virtual void BeginPlay() override;

	///////////////////////////
	//Custom functions
	// カスタム関数
public:
	//attach to Jumppad
	// ジャンプ台にアタッチする
	void OnJumpPad(FVector LaunchDirection = FVector::UpVector);

	//launchItemCount++, called by BP_LaunchItem 
	// launchItemCountを増加させる、BP_LaunchItemによって呼び出される
	UFUNCTION(BlueprintCallable, Category = "Shironeko")
	void LaunchItemCountIncrease(int32 value);

private:
	//PlayerMovement
	//プレイヤー移動
	void MoveForward(float Value); // 前に移動
	void MoveRight(float Value);   // 右に移動
	void Sprint();                 // スプリントを開始
	void StopSprint();             // スプリントを停止

	//Overlay
	//オーバーレイ
	void OverlayInitialize();      // オーバーレイを初期化
	void ShowMap();                // マップを表示
	void HideMap();                // マップを非表示

	//Interact
	//インタラクト
	void Interact();               // インタラクト
	void PlaySound(USoundBase* Sound); // サウンドを再生

	//Launch skill
	//スキルを発動
	void Launch();                 // 発動
	void LaunchReady();            // 発動準備完了
	FRotator UpdateLaunchArrowRotation(); // ランチャー方向の回転を更新

	///////////////////////////
	//Custom variables
	// カスタム変数
private:
	//LaunchItemCount
	// ランチャーアイテムの数
	int32 LaunchItemCount = 0;

	//arrow for launch
	// ランチャー方向
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shironeko", meta = (AllowPrivateAccess = "true"))
	UArrowComponent* LaunchArrow;

	//JumpPad
	// ジャンプ台
	UPROPERTY(EditAnywhere, Category = Shironeko)
	float JumpPadForce = 3000.f;	/** test */

	//Camera
	// カメラ
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shironeko", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shironeko", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* ViewCamera;

	//!MapUIComponent Actor, setup components in BP
	//!includes: springArm, screenCapture2D
	// MapUIComponent アクター、BPでコンポーネントをセットアップ
	// 含まれたコンポーネント: springArm, screenCapture2D
	UPROPERTY(EditDefaultsOnly, Category = "Shironeko")
	TSubclassOf<class ANekoMapUIComponent> MapUIClassBP;
	ANekoMapUIComponent* MapUIInstanceBP;

	//!includes: springArm, screenCapture2D, paperspriteIconMap, paperspriteIconMinimap
	// 含まれたコンポーネント: springArm, screenCapture2D, paperspriteIconMap, paperspriteIconMinimap
	UPROPERTY(EditDefaultsOnly, Category = "Shironeko")
	TSubclassOf<ANekoMapUIComponent> MiniMapUIClassBP;
	ANekoMapUIComponent* MiniMapUIInstanceBP;

	//NekoOverlay
	// オーバーレイ
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shironeko", meta = (AllowPrivateAccess = "true"))
	class UNekoOverlay* Overlay;

	//Sprint parameters
	// スプリントのパラメータ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shironeko", meta = (AllowPrivateAccess = "true"))
	float WalkSpeed = 300.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shironeko", meta = (AllowPrivateAccess = "true"))
	float SprintSpeed = 800.f;

	//InteractComponent
	// インタラクトコンポーネント
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shironeko", meta = (AllowPrivateAccess = "true"))
	class UNekoComponentInteract* InteractComponent;

	//play SoundEffect
	// サウンドエフェクトを再生
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shironeko", meta = (AllowPrivateAccess = "true"))
	class USoundBase* InteractSound;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shironeko", meta = (AllowPrivateAccess = "true"))
	class USoundBase* SprintSound;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shironeko", meta = (AllowPrivateAccess = "true"))
	class USoundBase* LaunchFailedSound;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shironeko", meta = (AllowPrivateAccess = "true"))
	class USoundBase* LaunchReadySound;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shironeko", meta = (AllowPrivateAccess = "true"))
	class USoundBase* LaunchSound;
	/** JumpSound implemented in BP_NekoCharacter */
	/** JumpSound は BP_NekoCharacter で実装 */
	class UAudioComponent* AudioComponent;

	//!QuestLogComponent implemented in BP
	// QuestLogComponent は BP で実装


	///////////////////////////
	//Custom delegate
	// カスタムデリゲート
public:
	//declare delegate
	// デリゲートを宣言
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnObjectiveIDCalledDelegate, FString, ObjectiveID);

private:
	//create delegate instance
	// デリゲートインスタンスを作成
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Shironeko", meta = (AllowPrivateAccess = true))
	FOnObjectiveIDCalledDelegate OnObjectiveIDCalled;

};
