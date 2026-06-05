# Mindustry Logic Script  
**在[`这里`](./README.md)可见中文版本**  
This repository provides a compiler  
that converts the mls scripting language into Mindustry Logic, i.e., Mindustry Logic.  
For more details, see [`this repository's Wiki`](https://zmzm-zm.github.io/MindustryLogicScript).  

## About mls  
- **mls is not any existing language out there**  
Any name collisions or similarities are purely coincidental.  
For specific syntax, see [`this repository's Wiki`](https://zmzm-zm.github.io/MindustryLogicScript).  

- **mls is not a programming language**  
It is designed to simplify Mindustry Logic and provide higher-level features.  
After being converted into Mindustry Logic, it runs in the game.  
Thus, it cannot be compiled by a compiler into assembly code.  
However, it has basic logic, control statements, etc.,  
and provides various syntactic sugars and functional templates, encapsulating common logic and functionality into functions.  

- **mls is a typeless language**  
Because specific type checking is left to the game at runtime,  
and Mindustry Logic itself is weakly typed,  
even writing `"Hello World" / 3` will not cause a compilation error.  
**However, this feature is under consideration** —  
impossible operations like `"Hello World" / 3` will be checked.  
> Currently still in development, only a very few features are available.  

## How to Use  
- Download the compiler from the [release page](https://github.com/zmzm-zm/MindustryLogicScript/releases) of this repository.  
	> If it's not there, it means even the initial version hasn't been released yet.  

- Set up environment variables so the command can be found.  
- Enter the compilation command, for example:  
	```console
	mls output input1.mls input2.msl
	```
  	The first argument is the name of the output file.
	The second and subsequent arguments are the input files.
	Currently only single-file input is supported; additional files will not be processed.
	
- The resulting output.ml is the final output.
	Copy and paste it into the game for use.
	> Currently, the output is still native Mindustry Logic.
	Blueprint functionality will be added in the future.