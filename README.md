# DBE

A project that aims to create a small simple database engine. 

## Class Breakdown

### Json Library

json11 was the library that I chose to easily export and import the database onto a json.

Its files are:

```
json11.hpp
json11.cpp
```

[GitHub json11 repository.](https://github.com/dropbox/json11)

#### Tabla.h

The tables have a header that includes the following attributes and methods:

```c++
char * nombre;							//Name of the table
int id;								//Id of the table
int primerBloqueCampo;						//A "pointer" to the first block of fields
int actualBloqueCampo;						//A "pointer" to the last block of fields
int primerBloqueReg;						//A "pointer" to the first block of entries
int actualBloqueReg;						//A "pointer" to the last block of entries

int cantCampos;							//Number of fields in the table
int cantReg;							//Number of entries in the table

int cantBloqueCampos;						//Number of blocks storing the fields
int cantBloqueReg;						//Number of blocks storing the entires

bool campoSpace(Campo *);					//Returns true if there is enough space for another 
void addCampo(char* nombre, int tipo, BloqueMaster * bm);	//Adds a field to the table

void addRegistro(char * data, BloqueMaster * bm);		//Adds an entry to the table
char * generateReg();		//Returns a char * entry for the table through cmd and user input
int tamReg();			//Returns the size of an entry for the table

Json registrosToJson();						//Returns a json conataining all of its entries
Json camposToJson();						//Returns a json containing all of its fields
Json tablaToJson();						//Returns a json that represents the entire table

void jsonToCampos(Json jcampos, BloqueMaster * bm);		//Turns the json into fields
void jsonToRegistros(Json jregistros, BloqueMaster * bm);	//Turns the json into entries

char * toChar();			//Converts its attibutes to a char * to be written on disk
void loadTabla(char*);			//Loads the object from a char *
```

Through its attributes it is able to manage the relative physical location of the blocks that store its fields and entries. 

#### Campo.h

A class that represents a field of a table. It can be one of two types: int or char[20]. Its attributes are:

```c++
char * nombre;			//Name of the field
int tipo;			//Type of field (1 represents a char[20], 0 represents an int)
int regSize;			//Size of the field in bytes
```

#### Registro.h

A class that represents an entry of a table. Its information is stored as binary data directly as a char *. This is done to ease the writing process. However to be able to properly read the entry it uses the class Celda.h that interprets the data according to the field it represents.

```c++
char * data;			//Entry data
int len;			//Size of the entry
```

#### Celda.h

AKA CampoDato. This class is used to properly read the entries of a table. It has a pointer to its corresponding field.

```c++
Campo * campo;			//Pointer to the field it represents
char * data;			//Char array that represents the entry of the field it stores
```

#### Engine.h

This is the class that manages the entire database and its tables. It is able to create tables, add fields to a table, add entries to a table and erase the database. In its constructor it automatically loads the database from disk, and also is able to be exported onto a json and imported from a json. These are its attributes and methods:

```c++
void format();							//Formats the entire database
void load();							//Loads the database
void addTabla(char* nombre);					//Adds a table to the database
void addCampoToTabla(int idTabla, char * nombre, int tipo);	//Adds a field to a table
void addRegistroToTabla(int idTabla, char * data = 0);		//Adds an entry to a table

Tabla * searchTabla(int id);					//Searches a table through its id
Tabla * searchTablaAtBloque(int id, BloqueTabla * bt);		//Searches a table on a BloqueTabla
BloqueTabla * searchBloqueTabla(int id);			//Returns the BloqueTabla containing the table

void addCamposFromJson(int idTabla, Json jcampos);		//Takes a json containing fields and adds them to a table
void addRegistrosFromJson(int idTabla, Json jregistros);	//Takes a json containing entries aqnd adds them to a table

void writeJson();					//Writes a json on disk containing the entire database
void readJson();					//Loads a database stored on a json			

void loadTablas();					//Loads all of the tables onto primary memory
```

### Blocks

We used blocks to store our database data. The classes that are written as blocks are:

```
Bloque.h
|_ BloqueMaster.h
|_ BloqueTabla.h
|_ BloqueCampo.h
|_ BloqueRegistro.h
```

#### Bloque.h

This class passes down three essential attributes, methods, and its constructor to its children. Blocks are the only classes that are directly written on disk.

```c++
int sig;	//The number of its next same type block
int num;	//Number of the block, which also represents its relative physical location
int sizeB; 	//Size of the Block

char * toChar();		//Converts its attibutes and whatever it stores a char * to be written on disk
void load(char* data);		//Loads the object from a char *

void write();			//Using num it writes itself onto secondary memory
void read();			//Using num it reads the size of the block to load the data it stored
```

#### BloqueMaster.h 

This class contains the attributes that manages the relative physical location of the total number of blocks and BloqueTablas. Its attributes are:

```c++
int primerBloqueTabla;		//The first BloqueTabla that is written on disk, will ALWAYS be 1
int actualBloqueTabla;		//The last BloqueTabla that is on the file
int cantTablas;			//The number of tables on the database
int cantBloqueTabla;	   	//The number of TablaBloques on the database
int cantBloques;		//The number of Blocks on the database (counting itself)
```

#### BloqueTabla.h

This class stores the tables to be written in secondary memory. Its primary function is to be able to read and write tables onto secondary memory. Its methods are:

```c++
bool addTabla(Tabla*);	
//Returns true and adds the table to the block if there is enough space for it, otherwise it returns false
```

#### BloqueCampo.h

This class stores the fields of a table to be written in secondary memory. Its methods are:

```c++
bool addCampo(Campo*);	
//Returns true and adds the field to the block if there is enough space for it, otherwise it returns false
```

#### BloqueRegistro.h

This class stores the entries of a table to be written in secondary memory. Its methods are:

```c++
bool addReg(Registro * r);	
//Returns true and adds the field to the block if there is enough space for it, otherwise it returns false
```
