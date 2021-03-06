FlappyBird
---

This is a game made using [Reprocessing](https://github.com/schmavery/reprocessing).

This was a practice demo I wrote while preparing to record the [FlappyBird livestream](https://www.youtube.com/watch?v=5aD3aPvNpyQ) ([source code](https://github.com/bsansouci/reprocessing-example/tree/livestream-flappybird)). That one is a little more polished, so check it out!

## Install
```
git clone https://github.com/Schmavery/FlappyBird
cd FlappyBird
npm install # or just `yarn`
```


## Build
```
npm run build
```


## Run
```
npm start
```

<p align="center"> 
<img src="https://user-images.githubusercontent.com/2154522/32364085-14c66842-c030-11e7-9822-288478b3291e.gif">
</p>

## Details

This project builds using the build system [bsb-native](https://github.com/bsansouci/bsb-native) which allows the project to be built to **JS** as well as built to **bytecode** and **native assembly**.

The above commands build and run the bytecode version. 

To play with the JS version you can simply do `npm run build:web` and start a static server (like using python: `python -m SimpleHTTPServer`). On safari you can also simply tick `Disable Cross-Origin Restrictions` from the `Develop` menu and then open the `index.html` directly.

To build the native version you can run `npm run build:native` and to run `npm run start:native`.

The bytecode version supports hotreloading, if you go in `index.re` and change anything while the app's running, the file will get compiled and injected into the running app, keeping the state. Have fun!
