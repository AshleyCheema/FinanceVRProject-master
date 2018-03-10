// Fill out your copyright notice in the Description page of Project Settings.

#include "RW_TextFile.h"
#include "Runtime/Core/Public/Misc/FileHelper.h"
#include "Runtime/Core/Public/Misc/Paths.h"
#include "Runtime/Core/Public/HAL/PlatformFilemanager.h"

//bool RW_TextFile::LoadTxt(FString FileNameA, FString& SaveTextA)
//{
//	return FFileHelper::LoadFileToString(SaveTextA, *(FPaths::GameDir() + "Users/" + FileNameA));
//}

///
// Return a FString Array of the contents of the .txt file
// Even number index is the title, odd is the answers
///
TArray<FString> URW_TextFile::LoadTxt(FString FileNameA)
{
	FString content;
	FString filePath = FString(*(FPaths::GameDir() + "Users/" + FileNameA));
	TArray<FString> result = {};
	const TCHAR* Delims[] = { TEXT(":") };

	FFileHelper::LoadFileToString(content, *(FPaths::GameDir() + "Users/" + FileNameA));
	content.ParseIntoArray(result, Delims, true);

	return result;
}

///
// Save a FString to a .txt file
///
bool URW_TextFile::SaveTxt(FString SaveTextB, FString FileName, FString FileEmail, bool addExtraData = true)
{
	FString dataToSave = SaveTextB;
	FString filePath = FString(*(FPaths::GameDir() + "Users/"));
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	if (!PlatformFile.FileExists(*filePath))
	{
		PlatformFile.CreateDirectory(*filePath);
	}

	FDateTime DateTimeNow = FDateTime::Now();

	if (addExtraData == true)
	{
#pragma region Date

		FString tempDate = DateTimeNow.ToString();
		char* tempDateChar = TCHAR_TO_ANSI(*tempDate);
		FString currentDate;

		//Day
		currentDate.AppendChar(tempDateChar[8]);
		currentDate.AppendChar(tempDateChar[9]);

		// break
		currentDate.AppendChar(tempDateChar[7]);

		//month
		currentDate.AppendChar(tempDateChar[5]);
		currentDate.AppendChar(tempDateChar[6]);

		// break
		currentDate.AppendChar(tempDateChar[4]);

		// year
		currentDate.AppendChar(tempDateChar[0]);
		currentDate.AppendChar(tempDateChar[1]);
		currentDate.AppendChar(tempDateChar[2]);
		currentDate.AppendChar(tempDateChar[3]);

		dataToSave.Append(TEXT(":Date:"));
		dataToSave.Append(currentDate);

#pragma endregion

#pragma region Time

		FString tempTime = DateTimeNow.ToString();
		char* tempTimeChar = TCHAR_TO_ANSI(*tempDate);
		FString currentTime;

		//Day
		currentTime.AppendChar(tempDateChar[11]);
		currentTime.AppendChar(tempDateChar[12]);

		// break
		currentTime.AppendChar(tempDateChar[13]);

		//month
		currentTime.AppendChar(tempDateChar[14]);
		currentTime.AppendChar(tempDateChar[15]);

		// break
		currentTime.AppendChar(tempDateChar[16]);

		// year
		currentTime.AppendChar(tempDateChar[17]);
		currentTime.AppendChar(tempDateChar[18]);

		dataToSave.Append(TEXT(":Time:"));
		dataToSave.Append(currentTime);

#pragma endregion

#pragma region Score

		dataToSave.Append(TEXT(":Score:0"));

		dataToSave.Append(TEXT(":1A:0"));
		dataToSave.Append(TEXT(":2A:0"));
		dataToSave.Append(TEXT(":3A:0"));
		dataToSave.Append(TEXT(":4A:0"));
		dataToSave.Append(TEXT(":5A:0"));
		dataToSave.Append(TEXT(":6A:0"));
		dataToSave.Append(TEXT(":7A:0"));
		dataToSave.Append(TEXT(":8A:0"));
		dataToSave.Append(TEXT(":9A:0"));
		dataToSave.Append(TEXT(":10A:0"));

#pragma endregion

		dataToSave.Append(TEXT(":FileName:"));
		dataToSave.Append(FileName + FileEmail + ".txt");
	}

	return FFileHelper::SaveStringToFile(dataToSave, *(FPaths::GameDir() + "Users/" + FileName + FileEmail + ".txt")); //"Users/" + FileName + "-" + FileEmail + ".txt"));
}

///
// Return a FString
///
FString URW_TextFile::FindData(FString DataToFind, TArray<FString> StringArray)
{
	int itemIndex = StringArray.Find(DataToFind);
	return StringArray[itemIndex + 1];
}

///
// Return an int
///
int URW_TextFile::GetDataIndex(FString DataToFind, TArray<FString> StringArray)
{
	int itemIndex = StringArray.Find(DataToFind);
	return itemIndex + 1;
}

///
// Save the new data
///
TArray<FString> URW_TextFile::SetData(FString DataToSet, FString data, TArray<FString> array)
{
	TArray<FString> fileArray;
	fileArray = array;

	int index = GetDataIndex(DataToSet, fileArray);
	fileArray[index] = data;

	FString saveData;
	for (size_t i = 0; i < fileArray.Num(); i++)
	{
		saveData.Append(fileArray[i]);
		saveData.AppendChar(TCHAR(':'));
	}

	SaveTxt(saveData, fileArray[1], fileArray[3], false);
	return fileArray;
}

bool URW_TextFile::Complete(TArray<FString> array, FString &result)
{
	FString dataToFind;
	int finished = 0;

	for (size_t i = 1; i <= 10; i++)
	{
		dataToFind = FString::FromInt(i);
		dataToFind.Append("A");

		if (FindData(dataToFind, array) == TEXT("0"))
		{
			int index = GetDataIndex(dataToFind, array);
			result = array[index - 1];
			//return false;
		}
		else
		{
			finished++;
		}
	}

	//if (FindData(TEXT("10A"), array) == TEXT("0"))
	//{
	//	int index = GetDataIndex("10A", array);
	//	result = array[index - 1];
	//	return false;
	//}


	result = result.FromInt(finished);
	if (finished == 10)
	{
		return true;
	}
	else
	{
		return false;
	}
	//int index = GetDataIndex(dataToFind, array);
	//result = array[index - 1];
	//return true;
}

void URW_TextFile::FinalScore(TArray<FString> array)
{
	TArray<FString> answersArray = { TEXT("1A"), TEXT("1B"), TEXT("1C"), TEXT("1D"),
		TEXT("2A"), TEXT("2D"),
		TEXT("3A"), TEXT("3C"),
		TEXT("4A"), TEXT("4B"), TEXT("4C"),
		TEXT("5A"), TEXT("5B"), TEXT("5C"),
		TEXT("6B"), TEXT("6C"),
		TEXT("7A"), TEXT("7D"),
		TEXT("8A"),
		TEXT("9A"), TEXT("9B"),
		TEXT("10A"), TEXT("10B"), TEXT("10C"), TEXT("10D") };

	int correctAnswer = 0;

	for (size_t i = 1; i <= 10; i++)
	{
		FString dataToFind;
		dataToFind = FString::FromInt(i);
		dataToFind.Append("A");

		FString a = FindData(dataToFind, array);

		if (answersArray.Contains(a))
		{
			correctAnswer++;
		}
	}

	FString correctAnswersS;
	correctAnswersS = correctAnswersS.FromInt(correctAnswer);

	SetData(TEXT("Score"), correctAnswersS, array);
}



