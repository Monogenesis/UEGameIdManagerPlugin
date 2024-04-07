// (c) Monogenesis

using UnrealBuildTool;

public class GameIdManagerEditor : ModuleRules
{
    public GameIdManagerEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        OptimizeCode = CodeOptimization.InShippingBuildsOnly;
        
        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "UnrealEd",
                "GraphEditor",
                "BlueprintGraph",
                "ToolWidgets",
                "GameIdManager",
            }
        );
        
        PrivateIncludePaths.AddRange(new string[]
        {
            "GameIdManagerEditor/Public",
        });
    }
}