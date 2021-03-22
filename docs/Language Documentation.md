# Language Documentation
## Basic Components
## Comment
### Definition
A Comment is a line that is ignored in GSS.

### Syntax
```
; ${comment} \n
```

### Property Name
#### Definition
A Property Name is defined as a string that is used to refer to a Property.

#### Syntax:
```
  ${name}
```

### Property Value
#### Definition
A Property Value is defined as a set of values.
It can have any length.

#### Syntax:
```
  ${value 1} ${value 2} ${value 3} ${...} ${value N}
```

### Property
#### Definition
A property is defined as a pair of a Property Name and a Property Value.

### Syntax:
```
  ${Property Name}: ${Property Vaue}; \n
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
A Property Class Value is defined as a set of Property definitions.

#### Syntax
```
  ${Property 1}
  ${Property 2}
  ${Property 3}
  ${...}
  ${Property N}
```

### Property Class
#### Definition
A Property Class is defined as a pair of a Property Class Name and a Property Class Value.

#### Syntax
```
  ${Property Class Name} =
    ${Property Class Value}
  end
```

## Class Management
### Inheritance
