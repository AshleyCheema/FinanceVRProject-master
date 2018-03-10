// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RW_TextFile.generated.h"

/**
*
*/
UCLASS()
class MYPROJECT_API URW_TextFile : public UBlueprintFunctionLibrary
{
	GENERATED_BODY() public:

		UFUNCTION(BlueprintCallable, Category = "Custom", meta = (Keywords = "LoadFromTxtFile"))
			static TArray<FString> LoadTxt(FString FileNameA);
		//static bool LoadTxt(FString FileNameA, FString& SaveTextA);

		UFUNCTION(BlueprintCallable, Category = "Custom", meta = (Keywords = "SaveTxt"))
			static bool SaveTxt(FString SaveTextB, FString FileName, FString FileEmail, bool addExtraData);

		UFUNCTION(BlueprintCallable, Category = "Custom", meta = (Keywords = "FindData"))
			static FString FindData(FString DataToFind, TArray<FString> StringArray);

		UFUNCTION(BlueprintCallable, Category = "Custom", meta = (Keywords = "GetDataIndex"))
			static int GetDataIndex(FString DataToFind, TArray<FString> StringArray);

		UFUNCTION(BlueprintCallable, Category = "Custom", meta = (Keywords = "SetData"))
			static TArray<FString> SetData(FString DataToSet, FString data, TArray<FString> array);

		UFUNCTION(BlueprintCallable, Category = "Custom", meta = (Keywords = "Complete"))
			static bool Complete(TArray<FString> array, FString &result);

		UFUNCTION(BlueprintCallable, Category = "Custom", meta = (Keywords = "FinalScore"))
			static void FinalScore(TArray<FString> array);
};
