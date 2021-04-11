# Language Documentation
## What is GSS?
GSS is a property definition for your applications to manage properties in a very natural way.

## Philosophy
As a property definition language, GSS is mainly pointed to be a language to store information for later use and share it with other programs in a straightforward way, in a similar way to the JavaScript Object Notation (JSON) language. However, instead of using brackets and braces, GSS makes use of the end of line character and indendation practices to create an easier to read language. Additionally, in the future we are planning to add some scripting languages features like arithmetic operations and variables management.

To achieve this, GSS Language enforces the following software development philosophies and principles:

**Modularity:** GSS Language only focuses on properties and their definitions. It is not supposed to be used as the main language for a program, but is supposed to be used as a supporting language for storing and sharing information instead. GSS Language does not care nor intend to care about other programming aspects than this one. For that reason, features that add support for other actions will not be worked on.

**Keep It Simple:** GSS Language focuses on being a language that is easy to work with. It is not a language that is supposed to take a very long time to learn or a language where the user struggles to understand the meaning of a piece of code. Therefore, the Keep It Simple language must be always a priority for the language design. If it is possible a feature that can be a little helpful but will make GSS Language very harder to use, the feature won't be added.  

Any feautre, upgrade or enhancement that goes against these principles must be discussed before its implementation and will only be accepted if it's benefits outweigh it's costs.

## Basic Components
## Comment
### Definition
A Comment is a line that is ignored in GSS.

### Syntax
```
; ${comment} ${\n}
```

### Property Bond Name
#### Definition
A Property Bond Name is defined as a string that is used to refer to a Property Bond.
It may only contain english lowercase, uppercase letters, underscores and hyphens.

#### Syntax:
```
  ${name}
```

### Property Bond Value
#### Definition
A Property Bond Value is defined as a set of values.
This can be strings, numbers, floating points, etc.
It can have any length.

#### Syntax:
```
  ${value 1} ${value 2} ${value 3} ${...} ${value N}
```

### Property Bond
#### Definition
A Property Bond is defined as a pair of a Property Bond Name and a Property Bond Value.

### Syntax:
```
  ${Property Name}: ${Property Vaue}; ${\n}
```

### Property Class Name
#### Definition
A Property Class Name is defined as a string that is used to refer to a Property Class.

#### Syntax
```
  ${name}
```

### Property Class Value
#### Definition
A Property Class Value is defined as a set of Property Bond and Property Class definitions.

#### Syntax
```
  ${Property/Property Class 1}
  ${Property/Property Class 2}
  ${Property/Property Class 3}
  ${...}
  ${Property/Property Class N}
```

### Property Class
#### Definition
A Property Class is defined as a pair of a Property Class Name and a Property Class Value.

#### Syntax
```
  ${Property Class Name} =
    ${Property Class Value}
  end ${\n}
```

## Class Management
### Inheritance
#### Definition
Every object in GSS inherits the caracteristics of the outer class it is in.
