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

| Method, Node or Macro                                                | Type      | Goal |
| -------------------------------------------------------------------- | --------- | ---- |
| `ENUM_TO_STRING(EnumClassName, ValueOfEnum)`                         | CPP Macro |      |
| `ENUMNAME_TO_STRING(EnumClassName, ValueOfEnum)`                     | CPP Macro |      |
| ![UniqueStringFromName](./Docs/Images/text-UniqueStringFromName.png) | Blueprint |      |
| ![UniqueStringFromText](./Docs/Images/text-UniqueStringFromText.png) | Blueprint |      |
| ![ComparePermutations](./Docs/Images/text-ComparePermutations.png)   | Blueprint |      |
| ![ArePermutations](./Docs/Images/text-ArePermutations.png)           | Blueprint |      |
| ![LettersAreInString](./Docs/Images/text-LettersAreInString.png)     | Blueprint |      |
| ![StringToWordsArray](./Docs/Images/text-StringToWordsArray.png)     | Blueprint |      |
| ![StringToLinesArray](./Docs/Images/text-StringToLinesArray.png)     | Blueprint |      |
| ![StringToLines](./Docs/Images/text-StringToLines.png)               | Blueprint |      |
| ![NameToDisplayText](./Docs/Images/text-NameToDisplayText.png)       | Blueprint |      |
| ![NameToDisplayString](./Docs/Images/text-NameToDisplayString.png)   | Blueprint |      |
| `WorldTypeToString(const EWorldType::Type Type)`                     | CPP       |      |

<a id="markdown-212-mathextension-library" name="212-mathextension-library"></a>

#### 2.1.2. MathExtension Library

| Node                                                                               | Type      | Goal |
| ---------------------------------------------------------------------------------- | --------- | ---- |
| ![CreateBoxFromInitAndExtend](./Docs/Images/math-CreateBoxFromInitAndExtend.png)   | Blueprint |      |
| ![IsBoxIntersect](./Docs/Images/math-IsBoxIntersect.png)                           | Blueprint |      |
| ![IsZoneBoxIntersect](./Docs/Images/math-IsZoneBoxIntersect.png)                   | Blueprint |      |
| ![IsLeft](./Docs/Images/math-IsLeft.png)                                           | Blueprint |      |
| ![RotateVectorRelativeTo](./Docs/Images/math-RotateVectorRelativeTo.png)           | Blueprint |      |
| ![GetBox](./Docs/Images/math-GetBox.png)                                           | Blueprint |      |
| ![GetTrigonometryDataForAZone](./Docs/Images/math-GetTrigonometryDataForAZone.png) | Blueprint |      |
| ![GetRotation](./Docs/Images/math-GetRotation.png)                                 | Blueprint |      |

<a id="markdown-213-flashmessage" name="213-flashmessage"></a>

#### 2.1.3. FlashMessage

|                                                                               | Type               | Goal |
| ----------------------------------------------------------------------------- | ------------------ | ---- |
| [FNFlashMessage](./Source/NansUE4Utilities/Public/MessageTypes.h)             | Blueprint / Struct |      |
| [EFlashMessagePriorityLevel](./Source/NansUE4Utilities/Public/MessageTypes.h) | Blueprint / Enum   |      |
| [FNFlashMessageList](./Source/NansUE4Utilities/Public/MessageTypes.h)         | CPP / Struct       |      |

<a id="markdown-214-ai-behavior-tree" name="214-ai-behavior-tree"></a>

#### 2.1.4. AI: Behavior Tree

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

| Macro                                       | Goals |
| ------------------------------------------- | ----- |
| `EDITOR_ERROR(MsgChannel, Text [, Object])` |       |
| `EDITOR_WARN(MsgChannel, Text [, Object])`  |       |
| `SCREEN_LOG(duration, color, format, ...)`  |       |

<a id="markdown-223-comparator-utilities" name="223-comparator-utilities"></a>

#### 2.2.3. Comparator Utilities

[NansComparator](./Source/NansUE4Utilities/Public/Misc/NansComparator.h)

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
