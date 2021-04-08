<div align="center">
<br>
<img width="500" src="static/logo.png" alt="hex-en logo">
</div>
<h5 align="center" color="#f62f6d">
DLL Injector made with Electron, Vue, TypeScript and C++.
</h5>
<div align=center>

[![forthebadge](https://forthebadge.com/images/badges/made-with-c-plus-plus.svg)](https://forthebadge.com)
[![forthebadge](https://forthebadge.com/images/badges/built-with-love.svg)](https://forthebadge.com)
[![forthebadge](https://forthebadge.com/images/badges/made-with-vue.svg)](https://forthebadge.com)

</div>

## Overview

HEX-EN is a DLL injector written in Node.js with a help of C++ bindings (Nan).
Feel free to contribute and use the code in your open-source projects.

##### Used projects:
* [Node.js](https://nodejs.org/en/)
* [Electron](https://electronjs.org/)
* [Vue.js](https://vuejs.org/)
* [TypeScript](https://www.typescriptlang.org/)
* [SCSS / Sass](https://sass-lang.com/)
* [Webpack](https://webpack.js.org/)
* [Babel](https://babeljs.io/)
* [C++](https://youtu.be/2Yy9RP6HQh0) / [Nan](https://github.com/nodejs/nan)
* [node-gyp](https://github.com/nodejs/node-gyp)
* [electron-builder](https://github.com/electron-userland/electron-builder)

## Screenshots
###### \*click for larger size\*
[<img width="500" src="https://i.imgur.com/rnv5kCY.png" alt="hex-en logo">](https://i.imgur.com/rnv5kCY.png)

### Prerequisites to build
* [npm](https://www.npmjs.com/) or [yarn](https://yarnpkg.com/lang/en/)
* [node-gyp and tools required by node-gyp](https://github.com/nodejs/node-gyp)

### Prerequisites to run
* 32bit/64bit Windows operating system

### Getting Started

The use of `node@^7` or higher required. electron-vue also officially recommends the [`yarn`](https://yarnpkg.org) package manager as it handles dependencies much better and can help reduce final build size with `yarn clean`.

```bash
# Clone repo
git clone https://github.com/alza54/hexen-dll-injector.git
cd hexen-dll-injector/
yarn # or npm install
yarn run dev # or npm run dev
```

### Building C++ module

```bash
cd hexen-dll-injector/lib/bindings/injector
yarn # or npm install
yarn run build # or npm run build
```

### Building executable

```bash
yarn run build # or npm run build
```

## Contributing

Just contribute!

## License

This project is licensed under the MIT License.
