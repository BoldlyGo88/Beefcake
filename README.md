# Beefcake

Beefcake is an attempt to expand Noitas modding API to make it more user-friendly and to remove many
of the restrictions imposed by the original.

Beefcake uses Noitas existing modloader (which means it supports ALL existing mods) and includes plenty
of custom functions to make coding less bloated and easier to read.

Latest release supported version: Jun 19 2023 Build

Latest compiled supported version: Jun 19 2023 Build

## Setting up

### Prerequisites

As of right now Beefcake has only been tested with the Steam version of Noita, it is likely it will
not work with other versions.
- [Noita on Steam](https://store.steampowered.com/app/881100/Noita/)

For the average users (people wanting to mod, or use mods) setting up Beefcake is pretty easy.

1. Navigate to Noitas directory

![](https://github.com/WadeBA/Beefcake/blob/main/exampleimg/example1.png)

2. Create a new folder named "beefcake" inside of Noitas directory

![](https://github.com/WadeBA/Beefcake/blob/main/exampleimg/example2.png)

3. Download and extract both setup.bat and remove.bat and Beefcake+.dll (the main api) into the beefcake folder and then run the setup.bat
   
![](https://github.com/WadeBA/Beefcake/blob/main/exampleimg/example3.png)

4. Launch Noita & you should be greeted with the Beefcake Console

![](https://github.com/WadeBA/Beefcake/blob/main/exampleimg/example4.png)

5. Start a new run/game and enjoy modding!

![](https://github.com/WadeBA/Beefcake/blob/main/exampleimg/example5.png)

Lua can be executed through the console once the game starts.

## Example Mods

Some example mods can be found [here](mods/Mods.md)

## Documentation

Full documentation can be found [here](docs/Documentation.md)

## License

This project is licensed under the [MIT License](LICENSE.md)

As a developer you get control over:
- Commercial use
- Modification
- Distribution
- Private use 

Find out more information about the [MIT License](LICENSE.md)

## Acknowledgments

  - The developers of [Noita](https://store.steampowered.com/app/881100/Noita/), [Nolla Games](https://nollagames.com/)
  - The developer of [libmem](https://github.com/rdbo/libmem), [rdbo](https://github.com/rdbo)
