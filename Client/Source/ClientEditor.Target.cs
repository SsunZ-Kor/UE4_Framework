// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class ClientEditorTarget : TargetRules
{
	public ClientEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange( new string[]
		{
			"Client",
			"DataLoadLib",
			"DataLoadEditor",
			"GameCharacterEditor",
		} );
	}
}
