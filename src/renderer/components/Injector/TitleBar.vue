<template>
  <div id="title-bar">
    <svg xmlns="http://www.w3.org/2000/svg" width="54" height="14" viewBox="0 0 54 14">
      <g fill="none" fill-rule="evenodd" transform="translate(1 1)">
        <circle @click="close" cx="6" cy="6" r="6" fill="#FF5F56" stroke="#E0443E" stroke-width=".5"></circle>
        <circle @click="maximize" cx="26" cy="6" r="6" fill="#FFBD2E" stroke="#DEA123" stroke-width=".5"></circle>
        <circle @click="minimize" cx="46" cy="6" r="6" fill="#27C93F" stroke="#1AAB29" stroke-width=".5"></circle>
      </g>
    </svg>
  </div>
</template>

<script lang="ts">

  const { remote } = require('electron');
  const { BrowserWindow } = remote;

  export default {
    name: 'title-bar',
    data () {
      return {
        maximized: false
      }
    },
    methods: {
      close () {
        BrowserWindow.getFocusedWindow().close();
      },
      maximize () {
        if (this.maximized = !this.maximized) {
          BrowserWindow.getFocusedWindow().minimize();
        } else {
          BrowserWindow.getFocusedWindow().setSize(600, 450);
        }
      },
      minimize () {
        BrowserWindow.getFocusedWindow().minimize();
      }
    }
  }

</script>

<style lang="scss" scoped>

  #title-bar {
    -webkit-app-region: drag;
    position: fixed;
    top: 7px;
    left: 7px;
    width: 100%;
    height: 20px;
  }

  #title-bar > svg {
    -webkit-app-region: no-drag;
  }

  circle:hover {
    opacity: .8;
  }

  circle:active {
    opacity: .6;
  }

</style>
