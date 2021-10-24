# Freedom

[Russian version of README](README-ru.md)

![](Resources/ReadmeImages/readme_screen1.png)

Freedom is the game developed in C++ with the help of Qt framework. The main goal of the project is to master skills of teamwork, project development and programming in __C++/Qt__.

---
<br>
<br>

![](Resources/ReadmeImages/readme_screen2.png)
![](Resources/ReadmeImages/readme_screen3.png)
![](Resources/ReadmeImages/readme_screen4.png)

## Content

* [Plot](#Plot)
* [Technology](#Technology)
* [Installation](#Installation)
* [Authors](#Authors)

## Plot
After a grueling fight for an apple with a prison guard, you wake up in
your cell and realize that you no longer have the strength to live like this anymore and you need to escape no matter what it costs. Fortunately, in this prison you will have such an opportunity. All you need to
do is break down the thick walls or kill all the guards. Talk to your
cellmates and guards, complete quests, explore locations and become the
first among equals!

## Technologies
* The system of __quests and dialogues__ allows you to create very flexible storylines.
* GUI and rendering of game objects are implemented using standard Qt tools for drawing in combination with __OpenGL__.
* All animation, appearance of game objects and characters were developed at
_MagicaVoxel_.
* Special native methods and logic were implemented to work with __isometric graphics__.
* The architecture of the application is based on the pattern __MVC__ (Model-View-Controller).
* The `resources.qrc` file was used for resource management, and `.json` files were used for data storage and __serialization/deserialization__ systems. Usage of `json-`s significantly increased the speed of the development and speed of filling the game with various content (quests, dialogues, etc.).
* А __flexible animation system__ of game objects allows you to animate objects by absolutely any state.
* __Bots and various types of interactions__ with them: _fighting, patrolling, pursuiting of the hero, route building, dialogues, looting things.

## Installation
To install the game, you need to download the archive located in the folder
`Releases`, unpack it and run the executable file `Freedom.exe`.
At the moment, our game is available for Windows, Linux and MacOS.

## Authors

**[Arseniy Tyletskiy](https://github.com/ArseniyTy)**

**[Egor Zheltkevich](https://github.com/HydeHunter2)**

**[George Krovsh](https://github.com/gosha-krovsh)**

**[Maxim Litskevich](https://github.com/Zzzabiyaka)**