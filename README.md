# UE4 Utilities

Some usefull structs, classes and macros I use to develop more featured plugins.

|                                                                                                       <a href="https://www.buymeacoffee.com/NansUE4" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/default-green.png" alt="Buy Me A Coffee" height="51" width="217"></a>                                                                                                       |
| :---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------: |
| I've decided to make all the code I developed for my games free to use and open source.<br> I am a true believer in the mindset that sharing and collaborating makes the world a better place.<br> The thing is: I'm fulltime dedicated to my project and these open source plugins, for coding I need a looooot of coffee, so please, help me to get my drug :stuck_out_tongue_closed_eyes: !! |

<!-- TOC -->

-   [1. Requirements](#1-requirements)
    -   [1.1. UE4 Plugins](#11-ue4-plugins)
-   [2. Features](#2-features)
    -   [2.1. Blueprint & CPP](#21-blueprint--cpp)
        -   [2.1.1. Text Library](#211-text-library)
        -   [2.1.2. MathExtension Library](#212-mathextension-library)
        -   [2.1.3. FlashMessage](#213-flashmessage)
        -   [2.1.4. AI: Behavior Tree](#214-ai-behavior-tree)
        -   [2.1.5. FBPDelegateHandle](#215-fbpdelegatehandle)
    -   [2.2. CPP only](#22-cpp-only)
        -   [2.2.1. Array Utilities](#221-array-utilities)
        -   [2.2.2. Error Utilities](#222-error-utilities)
        -   [2.2.3. Comparator Utilities](#223-comparator-utilities)
-   [3. Contributing and Supporting](#3-contributing-and-supporting)

<!-- /TOC -->

<a id="markdown-1-requirements" name="1-requirements"></a>

## 1. Requirements

<a id="markdown-11-ue4-plugins" name="11-ue4-plugins"></a>

### 1.1. UE4 Plugins

-   [NansCoreHelpers](https://github.com/NansPellicari/UE4-CoreHelpers) (free UE4 plugins)

<a id="markdown-2-features" name="2-features"></a>

## 2. Features

<a id="markdown-21-blueprint--cpp" name="21-blueprint--cpp"></a>

### 2.1. Blueprint & CPP

<a id="markdown-211-text-library" name="211-text-library"></a>

#### 2.1.1. Text Library

[TextLibrary.h](./Source/NansUE4Utilities/Public/Misc/TextLibrary.h)

| Method, Node or Macro                                                | Type      | Goal                                                                                                                                                                                                 |
| -------------------------------------------------------------------- | --------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `ENUM_TO_STRING(EnumClassName, ValueOfEnum)`                         | CPP Macro | Passing an enum type and a value, this will return the enum label as string.                                                                                                                         |
| `ENUMNAME_TO_STRING(EnumClassName, ValueOfEnum)`                     | CPP Macro | This one will returns the "DisplayName" UMETA's attribute.                                                                                                                                           |
| ![UniqueStringFromName](./Docs/Images/text-UniqueStringFromName.png) | Blueprint | This is a blueprint wrapper for the `FMD5::HashAnsiString` function, it takes an `FName` as parameter.                                                                                               |
| ![UniqueStringFromText](./Docs/Images/text-UniqueStringFromText.png) | Blueprint | Same but takes an `FText` as parameter.                                                                                                                                                              |
| ![ArePermutations](./Docs/Images/text-ArePermutations.png)           | Blueprint | Compare two strings, checks if the first one is a [permutation](https://en.wikipedia.org/wiki/Permutation) of the second.                                                                            |
| ![ComparePermutations](./Docs/Images/text-ComparePermutations.png)   | Blueprint | Same as above + outputs a TMap: keys are each TCHAR of the first string, and values are distances with the same TCHAR in the second string.                                                          |
| ![LettersAreInString](./Docs/Images/text-LettersAreInString.png)     | Blueprint | Only checks if letters from the first string are contained in the second.                                                                                                                            |
| ![StringToWordsArray](./Docs/Images/text-StringToWordsArray.png)     | Blueprint | Will splits every words separated with a space.                                                                                                                                                      |
| ![StringToLinesArray](./Docs/Images/text-StringToLinesArray.png)     | Blueprint | Will splits text trying to make lines, each line should have a Char length defined in the 2nd argument. This algo will not cut words and always cut line before the word exceeding the chars length. |
| ![StringToLines](./Docs/Images/text-StringToLines.png)               | Blueprint | Same as above but each line will be an array entry.                                                                                                                                                  |
| ![NameToDisplayText](./Docs/Images/text-NameToDisplayText.png)       | Blueprint | Convert a name to a display text. Eg: ItIsAName => It Is A Name                                                                                                                                      |
| ![NameToDisplayString](./Docs/Images/text-NameToDisplayString.png)   | Blueprint | Same as above but string output.                                                                                                                                                                     |
| `FString WorldTypeToString(const EWorldType::Type Type)`             | CPP       | Usefull for debugging, will output the WorldType Name.                                                                                                                                               |

<a id="markdown-212-mathextension-library" name="212-mathextension-library"></a>

#### 2.1.2. MathExtension Library

[MathExtensionLibrary.h](./Source/NansUE4Utilities/Public/MathExtensionLibrary.h)

| Node                                                                               | Type      | Goal                                                                                                                                           |
| ---------------------------------------------------------------------------------- | --------- | ---------------------------------------------------------------------------------------------------------------------------------------------- |
| ![CreateBoxFromInitAndExtend](./Docs/Images/math-CreateBoxFromInitAndExtend.png)   | Blueprint | This will create an FBox (AABB object).<br> :warning: The Rotation argument will rotate the first cube, but the final result is still an AABB. |
| ![IsBoxIntersect](./Docs/Images/math-IsBoxIntersect.png)                           | Blueprint | Check if 2 boxes intersect.                                                                                                                    |
| ![IsZoneBoxIntersect](./Docs/Images/math-IsZoneBoxIntersect.png)                   | Blueprint | A ZoneBox (FZoneBox struct) is coming from the [NansCoreHelpers](https://github.com/NansPellicari/UE4-CoreHelpers) module.                     |
| ![IsLeft](./Docs/Images/math-IsLeft.png)                                           | Blueprint | Check if vector A is at the left of the point B using point as reference.                                                                      |
| ![RotateVectorRelativeTo](./Docs/Images/math-RotateVectorRelativeTo.png)           | Blueprint | Rotate a vector using a pivot point and an axis.                                                                                               |
| ![GetBox](./Docs/Images/math-GetBox.png)                                           | Blueprint | Retrieve the AABB from a FZoneBox.                                                                                                             |
| ![GetRotation](./Docs/Images/math-GetRotation.png)                                 | Blueprint | Retrieve the rotation between 2 point and a pivot point.                                                                                       |
| ![GetTrigonometryDataForAZone](./Docs/Images/math-GetTrigonometryDataForAZone.png) | Blueprint | Returns a [FTrigonometryDataForZone](./Source/NansUE4Utilities/Public/MathExtensionLibrary.h).                                                 |

<a id="markdown-213-flashmessage" name="213-flashmessage"></a>

#### 2.1.3. FlashMessage

[MessageTypes.h](./Source/NansUE4Utilities/Public/MessageTypes.h)

|                                                                               | Type               | Goal                                                                                                         |
| ----------------------------------------------------------------------------- | ------------------ | ------------------------------------------------------------------------------------------------------------ |
| [FNFlashMessage](./Source/NansUE4Utilities/Public/MessageTypes.h)             | Blueprint / Struct | Is a simple Blueprint UStruct embdeding text, duration and priority level data.                              |
| [EFlashMessagePriorityLevel](./Source/NansUE4Utilities/Public/MessageTypes.h) | Blueprint / Enum   | Blueprint UEnum to indicates priority level.                                                                 |
| [FNFlashMessageList](./Source/NansUE4Utilities/Public/MessageTypes.h)         | CPP / Struct       | A simple CPP struct which enqueue messages and prioritize their retrieval depending on their priority level. |

<a id="markdown-214-ai-behavior-tree" name="214-ai-behavior-tree"></a>

#### 2.1.4. AI: Behavior Tree

|                                                                                                        | Type                    | Goal                                                                                                                                                                                                                       |
| ------------------------------------------------------------------------------------------------------ | ----------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| [UBTTask_NotifyAIOnAbort](./Source/NansUE4Utilities/Public/AI/BehaviorTree/BTTask_NotifyAIOnAbort.h)   | CPP / Class             | An abstract Behavior Tree Task Node. When it finished in an "Abort" result, it notifies any component implementing [UAITaskAbortAware](./Source/NansUE4Utilities/Public/AI/AITaskAbortAware.h) of the Behavior Tree owner. |
| [UBTTask_NotifyAIOnAbortBP](./Source/NansUE4Utilities/Public/AI/BehaviorTree/BTTask_NotifyAIOnAbort.h) | Blueprint / Class       | The same as above but overrides UBTTask_BlueprintBase instead.                                                                                                                                                             |
| [UAITaskAbortAware](./Source/NansUE4Utilities/Public/AI/AITaskAbortAware.h)                            | CPP & Blueprint / Class | This interface allow any component to be notified by the children nodes of the both above.                                                                                                                                 |

<a id="markdown-215-fbpdelegatehandle" name="215-fbpdelegatehandle"></a>

#### 2.1.5. FBPDelegateHandle

[FBPDelegateHandle](./Source/NansUE4Utilities/Public/Misc/BPDelegateHandle.h) is a simple container which allows passing a [FDelegateHandle](https://docs.unrealengine.com/en-US/API/Runtime/Core/Delegates/FDelegateHandle/index.html) through blueprint nodes.

<a id="markdown-22-cpp-only" name="22-cpp-only"></a>

### 2.2. CPP only

<a id="markdown-221-array-utilities" name="221-array-utilities"></a>

#### 2.2.1. Array Utilities

[NansArrayUtils](./Source/NansUE4Utilities/Public/Misc/NansArrayUtils.h)

<a id="markdown-222-error-utilities" name="222-error-utilities"></a>

#### 2.2.2. Error Utilities

| Macro                                       | Goals                                                                                                              |
| ------------------------------------------- | ------------------------------------------------------------------------------------------------------------------ |
| `EDITOR_ERROR(MsgChannel, Text [, Object])` | Will output an error message in the UE editor message panel. Object arg is used to create a link to your object.   |
| `EDITOR_WARN(MsgChannel, Text [, Object])`  | Will output an warning message in the UE editor message panel. Object arg is used to create a link to your object. |
| `SCREEN_LOG(duration, color, format, ...)`  | Log a message to the game screen.                                                                                  |

<a id="markdown-223-comparator-utilities" name="223-comparator-utilities"></a>

#### 2.2.3. Comparator Utilities

[NansComparator.h](./Source/NansUE4Utilities/Public/Misc/NansComparator.h).

A bunch of functions allowing data comparisons using blueprint enums ([ENansConditionComparator](./Source/NansUE4Utilities/Public/Misc/NansComparatorHelpers.h) and [ENansConditionOperator](./Source/NansUE4Utilities/Public/Misc/NansComparatorHelpers.h)) and blueprint struct ([FNansConditionOperator](./Source/NansUE4Utilities/Public/Misc/NansComparatorHelpers.h)).  
This way you can easily create a blueprint interface to build data comparison (see [NansDialogueSystem](https://github.com/NansPellicari/UE4-DialogueSystem) for usages).

<a id="markdown-3-contributing-and-supporting" name="3-contributing-and-supporting"></a>

## 3. Contributing and Supporting

I've decided to make all the code I developed for my games free to use and open source.  
I am a true believer in the mindset that sharing and collaborating makes the world a better place.  
I'll be very glad if you decided to help me to follow my dream.

| How?                                                                                                                                                                               |                                                                                         With                                                                                         |
| :--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | :----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------: |
| **Donating**<br> Because I'm an independant developer/creator and for now I don't have<br> any income, I need money to support my daily needs (coffeeeeee).                        | <a href="https://www.buymeacoffee.com/NansUE4" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/default-green.png" alt="Buy Me A Coffee" height="51" width="217" ></a> |
| **Contributing**<br> You are very welcome if you want to contribute. I explain [here](./CONTRIBUTING.md) in details what<br> is the most comfortable way to me you can contribute. |                                                                         [CONTRIBUTING.md](./CONTRIBUTING.md)                                                                         |

[idialoguehud]: Docs/UIs/IDialogueHUD.md
[uis]: ./Docs/UIs.md
