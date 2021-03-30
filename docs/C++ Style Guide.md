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


## General Datatypes
### Namespaces
Namespaces must use Pascal Case.
### Classes
Classes must use Pascal Case.
### Enums
Do not use plain enums, use enum classes instead.

If in any situation is strictly needed to use enums, then they must use Pascal Case.
### Enum Classes
Enum Classes must use Pascal Case.
### Typenames
Typenames must use Pascal Case.
### Functions and methods
Functions and methos must use Camel Case.

The one-liners getters and setters methods must have their body in the same line. In other case, the function or method's body must start in the next line, including the braces.
### Variables
Variables must use Snake Case.
### Control Structures
One-liners control Structures must go without braces in the next line. In other case, the control structure's body must start in the next line, including the braces.

## File Structure
All the directories and files names must use Camel Case.

Assets like images, videos and audio files must be in Kebab Case and have their respective file extension.

C source files must have the `.c` file extension and C header files must have the `.h` file extension.

C++ source files must have the `.cpp` file extension and C++ header files must have the `.hpp` file extension.

Both C and C++ files (headers and sources) must use Kebab Case unless they contain a class, namespace or its methods definition, case in which the file must have the same name as the class or namespace.

## Extensions
Do not use compiler extensions. They make the code not portable.

**If you have any suggestion post it in the issues section.**
