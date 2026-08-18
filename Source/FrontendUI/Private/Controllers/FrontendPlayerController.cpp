#include "Controllers/FrontendPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraActor.h"
#include "Characters/StoryCharacter.h"
#include "FrontendSettings/FrontendGameUserSettings.h"


void AFrontendPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	// 拥有自带跟随相机的可操控角色时，不抢占视角到场景相机
	if (!Cast<AStoryCharacter>(aPawn))
	{
		TArray<AActor*> FoundCameras;
		UGameplayStatics::GetAllActorsOfClassWithTag(this, ACameraActor::StaticClass(), FName("Default"), FoundCameras);

		if (!FoundCameras.IsEmpty())
		{
			SetViewTarget(FoundCameras[0]);
		}
	}

	UFrontendGameUserSettings* GameUserSettings = UFrontendGameUserSettings::Get();

	if (GameUserSettings && (GameUserSettings->GetLastCPUBenchmarkResult() == -1.f || GameUserSettings->GetLastGPUBenchmarkResult() == -1.f))
	{
		GameUserSettings->RunHardwareBenchmark();
		GameUserSettings->ApplyHardwareBenchmarkResults();
	}
}
