FlappyBird
---

This is a game made using [Reprocessing](https://github.com/schmavery/reprocessing).

This project builds using the build system [bsb-native](https://github.com/bsansouci/bsb-native) which allows the project to be built to **JS** as well as built to **bytecode** and **native assembly**.

<p align="center"> 
<img src="https://user-images.githubusercontent.com/2154522/32364085-14c66842-c030-11e7-9822-288478b3291e.gif">
</p>


## Install
**warning**: this does **not** work with `npm5` yet. To downgrade to `npm4` you can run `npm i -g npm@latest-4`. Alternatively you can use the latest `yarn`.

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

## Details
We made a [livestream](https://youtu.be/5aD3aPvNpyQ?t=6m47s) of us making this.

Those commands build and run the bytecode version. 

To play with the JS version you can simply do `npm run build:web` and start a static server (like using python: `python -m SimpleHTTPServer`). On safari you can also simply tick `Disable Cross-Origin Restrictions` from the `Develop` menu and then open the `index.html` directly.

To build the native version you can run `npm run build:native` and to run `npm run start:native`.

The bytecode version supports hotreloading, if you go in `index.re` and change anything while the app's running, the file will get compiled and injected into the running app, keeping the state. Have fun!
