FlappyBird
---

This is a demo of [Reprocessing](https://github.com/schmavery/reprocessing).

This project builds using the build system [bsb-native](https://github.com/bsansouci/bsb-native) which allows the project to be built to JS as well as built to bytecode and native assembly.

<p align="center"> 
<img src="https://user-images.githubusercontent.com/2154522/32364085-14c66842-c030-11e7-9822-288478b3291e.gif">
</p>


## Install
**warning**: this won't work with `npm5`. To downgrade to `npm4` you can run `npm i -g npm@latest-4`. Alternatively you can use the latest `yarn`.

```
npm install
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
Those commands build and run the bytecode version. To play with the JS version you can simply do `npm run build:web` and start a static server (like using python: `python -m SimpleHTTPServer`).

The bytecode version supports hotreloading, if you go in `index.re` and change anything, the file will get compiled and injected into the running app, keeping the state. Have fun!
