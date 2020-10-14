## Unkillable stack

## Description

Realisation of stack for different types with with 4 levels of protection

## Getting Started

### Installing
 
 * Download the project from GitHub or clone repository by
 
```
git clone https://github.com/ArtoriasAbW/ISP_IND_PROG.git
```

### Building program

```
cd ISP_IND_PROG/Task3
```

* Light protection mode
```
make light
./UnkillableStackLight
```


* Medium protection mode (asserts, code of error, stack dump)
```
make medium
./UnkillableStackMedium
```


* Hard protection mode (canaries for data and struct, asserts, code of error, stack dump)
```
make hard
./UnkillableStackHard
```

* Insane protection mode(check sum for data and struct, canaries for data and struct, asserts, code of error, stack dump)
```
make insane
./UnkillableStackInsane 
```

* Deleting exectuble file
```
make clean
```
