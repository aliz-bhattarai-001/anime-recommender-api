## Anime Recommender Api
This was and is a project I had started to learn about C++ initially before second semester started.<br>
- Completed the first draft during first sem exam holidays.
- Test within main.cpp completed during the same period
- Wrote client.sh ( somewhat complete I'd say ) and setup.sh (incomplete) after end of 2nd sem

## Core Tools/Technologies used

1. `httplib.h` 
2. `nlohmann/json`
3. `C++`
---

## Prequisites 
1. `gcc/g++ compiler`
2. `bash` or any shell that can run the `client.sh` script

> Note: External libraries are ported alongside within vendor/ library
---
## How to Run (Linux guide)

> Note : execute all these commands from the root directory where you can see src, vendor and include directories in sight
1. compile the source code
```bash
# first create the executable
g++ -o apiServer ./src/*.cpp
```

2. Give execution permission to client script
```bash
chmod +x ./client.sh
```

3. Run the server in one terminal
```bash
./apiServer
```

4. Execute the client on another terminal
```bash
./client.sh
```

>**NOTE** : `setup.sh` is a work in progress at the moment. It's realization requires modification to the project which will be considered in the future.
---

## Author 
- Aliz Bhattarai : [Github Profile](https://www.github.com/aliz-bhattarai-001)