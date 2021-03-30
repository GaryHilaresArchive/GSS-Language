# C++ Style Guide
## Prologue
This C++ Style Guide is a common style guide developed by the GProject OSS community for its own projects, but we encourage to use it even if you do not participate on it. The text defines many convention that are used in these projects with the objective of improving readability by standarizing the way to write code.

## Definitions
### Pascal Case
Pascal Case is a casing style that capitalizes only the first letter of each word and then join all the words.

Examples:
```markdown
PascalCase
InsertSomeTextHere
```

### Snake Case
Snake Case is a casing style that writes all words in lowercase and then joins them separated by an underscore.

Examples:
```markdown
snake_case
insert_some_text_here
```

### Camel Case
Camel Case is a casing style that capitalizes only the first letter of each word, except the first, and then joins all the words

Examples:
```markdown
camelCase
insertSomeTextHere
```

### Kebab Case
Kebab Case is a casing style that writes all words in lowercase and then joins them separated by an hyphen.

Examples:
```markdown
kebab-case
insert-some-text-here
```
## File Structure
### Directories
All directories must use Camel Case.

### Code
C source files must have the `.c` file extension and C header files must have the `.h` file extension.

C++ source files must have the `.cpp` file extension and C++ header files must have the `.hpp` file extension.

Both C and C++ files (headers and sources) must use Kebab Case unless they contain a class, namespace or its methods definition, case in which the file must have the same name as the class or namespace.
### Assets
Assets like images, videos and audio files must be in Kebab Case and have their respective file extension.

## Extensions
Do not use compiler extensions. They make the code less portable.

## General Datatypes
### Namespaces
Namespaces must use Pascal Case.
### Classes
Classes must use Pascal Case.
### Enums
Do not use plain enums, use enum classes instead.

If in any situation is strictly needed to use enums, then they must use Pascal Case for the name of the enum and they must use a common prefix in uppercase, followed by an underscore and a name in Pascal Case for the enumerator name.
### Enum Classes and Enum Structs
Enum Classes and Enum Structs are exactly the same, so for consistency, always use Enum Classes.

Enum Classes must use Pascal Case for both the enum name and the enumerator name.
### Typenames
Typenames must use Pascal Case.
### Functions
Functions use Camel Case.

### Methods
#### Constructors
For the nature of the language, constructors must be in Pascal Case just as classes.

They must use Member Initializer List (MIL) where posible. For primitives (`bool`, `int`, `char`, `double` and their variants) it is aceptable to do not use MIL.
#### Getters and setters
They must be in Camel Case.

If they are one-liners then they must have their body in the same line. In other case, the body must start in the next line, including the braces.

#### Destructors
For the nature of the language, constructors must be in Pascal Case just as classes.

### Variables
All variable names must use Snake Case.

Variable's names must be concise, but at the same time they must be descriptive enoungh to understand what is it's purpose.

#### Booleans
Usually for booleans a descriptive verb must be used. This verb must describe what the boolean means and almost always it will be `is`, `are`, `have`, `has`, `do` or `does`. The name of the bool with the verb must be similiar to a yes-no question that must be answered by the bool's value.

Example:
```c++
/* In the following code */
void printColors(Color color1, Color color2)
{
    bool equal1 = color1.r == color2.r;
    bool equal2 = color1.g == color2.g;
    bool equal3 = color1.b == color2.b;
    bool equal = equal1 && equal2 && equal3;
    if(equal)
         std::cout << "Colors are equal :) !" << std::endl;
    else
         std::cout << "Colors are not equal... :(" << std::endl;
}

/* "equal1", "equal2", "equal3" and "equal" do not mean much by theirselves. What things are equal? */
/* Now consider the following example. */

void printAreColorsEquals(Color color1, Color color2)
{
    bool isRedEqual = color1.r == color2.r;
    bool isGreenEqual = color1.g == color2.g;
    bool isBlueEqual = color1.b == color2.b;
    bool areColorsEqual = isRedEqual && isGreenEqual && isBlueEqual;
    if(areColorsEqual)
         std::cout << "Colors are equal :) !" << std::endl;
    else
         std::cout << "Colors are not equal... :(" << std::endl;
}

/* Now is easier to read. Isn't it? */
/* Variable names are more meaningful. */
/* This is a silly example, but in real code this can turn very complicated. */
```

#### Other datatypes
It was only a special case for booleans. Other datatypes names must just describe what they are in a clear way.

### Control Structures
One-liners control Structures must go without braces in the next line. In other case, the control structure's body must start in the next line, including the braces.

**If you have any suggestion post it in the issues section.**
