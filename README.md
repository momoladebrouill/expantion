# Expantion

Simple idea I had watching a youtube short about how different grass types interact between each other in Minecraft. It was also a way to get me back into C to do some clean code, go check it and try to make it prettier ! 

## How to use
```bash
gcc main.c -o fight
./fight
```
You can specify the size of the map with
```bash
./fight <width> <height> 
```

## wtf is `gen` ?
`gen` is the number representing the time when a cell is born. This was implemented to avoid having a cell that reproduced itself multiple times in a single generation.

