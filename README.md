# PSU_2015_zappy
Developpement repository for zappy project

> Don't forget to switch on david_h repo at the end of this project !

### Serveur
- Reseau
- (Parser)
- Validation
- Execution
### Structures
```
struct maptile
 *item (liste chainee)
 * up
 * down
 * left
 * right
 ```
```
struct player
```
```
struct item (ressources & nourriture)
 enum type
 * void item
```
```
struct drone
 * socket
 * mapTile
 * move()
 * take(* item)
 * fork()
 * inventory
 * team
 * UUID
 * broadcast(char *)
 enum orientation
 ```
```
struct inventory
 * take(* item)
 * drop(* item)
 * list()
```
```
struct request
 * message
 int fd
 * respond(char *)
 ENUM type (verbe take drop fork...)
 char *subject (sujet de l'action, drop sibure etc)
 ```

#### Hippolyte
-   C modulaire
-   Validation requete

#### Christian
-    Mono
-    Map

#### Antoine
-    Parser de requete
-    Enum request

#### Etienne
-   Reseau
-   UI
-   Listes Chainees





